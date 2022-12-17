#include <iostream>
#include <vector>
#include <stdio.h>

/*
 * Program po odczytaniu danych z pliku. Tworzy nowa tablice w ktorej zapisuje sumy kazdych
 * dwoch elementow z wejcia. Wybiera wiec kombinatorycznie z n elementow dwa n(n-1) ale, ze
 * kolejnosc nie ma tutaj znaczenia n(n-1)/2 roznych par i zapisuje je w tablicy razem z in-
 * deksami elementow ktore sumujemy. Nastepuje kolejnosc sortowanie tablicy sum par metoda
 * QuickSort. Nastepnie ustawiane sa dwa wskazniki na poczatek i n koniec naszej posortowan-
 * ej tablicy i w zaleznosci czy suma dwoch elementow jest:
 * - < 0     (wtedy wiemy ze potrzeba nam wiekszych elementow wiec lewy wskaznik jest prze-
 * suwany w prawo,
 * - > 0     (wtedy wiemy ze potrzeba nam mniejszych elementow wiec prawy wskaznik przesuw-
 * amy w lewo,
 * - == 0    (wtedy sprawdzamy dodatkowo ile jest takich par o roznych indeksach, ktorych
 * suma jest rowna 0. Nalezy jeszcze pamietac, ze z 4 elementow mozemy wybrac 2 pary na
 * 4 po 2,2 / 2 (bo kolejnosc nie ma znaczenia) sposobow. Czyli wynik dzielimy na 3.
 *
 * Zapisanie par sum do nowej tablicy zajmie n(n-1)/2 czyli O(n^2). Nastepnie sortowanie
 * przy uzyciu QuickSorta O(nlogn). Nastpenie sprawdzamy liniowo czy suma nie rowna sie 0
 * t.j. O(n). Co sumie daje to zlozonosc O(n^3).
 *
 *
 * Krystian Jachna
 */

struct pairSum {
    int first;
    int second;
    long sum;

    pairSum ( int f = 0, int s = 0, long sum = 0 ) {
        this->first = f;
        this->second = s;
        this->sum = sum;
    }
};

int paritionHoare( struct pairSum arr [], int L, int R ) {
    int pivot = arr[R].sum;
    int start = L - 1;
    int stop = R;

    while ( true ) {
        while ( arr[++start].sum < pivot );
        while ( stop > L && arr[--stop].sum > pivot );

        if ( start >= stop )
            break;
        else {
            pairSum tmp = arr[start];
            arr[start] = arr[stop];
            arr[stop] = tmp;
        }
    }
    pairSum tmp = arr[start];
    arr[start] = arr[R];
    arr[R] = tmp;

    return start;
}

void quickSort( struct pairSum arr [], int L, int R ) {
    if ( L >= R )
        return;

    int q = paritionHoare( arr, L, R) ;
    quickSort( arr, L, q-1 );
    quickSort( arr, q+1, R );
}

bool noCommon(pairSum a, pairSum b) {
    if (a.first == b.first || a.first == b.second || a.second == b.first || a.second == b.second)
        return false;
    return true;
}

unsigned long equalPairs( struct pairSum arr [], int *L, int *R) {
    int i = *L;
    int j = *R;

    long startSum = arr[i].sum;
    long endSum = arr[j].sum;

    unsigned long count = 0;

    while( arr[i].sum == startSum && i < *R ) {
        j = *R;

        while ( j > i && arr[j].sum == endSum ) {
            if ( noCommon(arr[i], arr[j]) )
                ++count;
            --j;
        }
        ++i;
    }
    *L = i;
    *R = j;

    return count;
}

struct pairSum* crateTwoSumArray( std::vector<int> arr, int size )
{
    struct pairSum* two_Sums = new pairSum [size];

    int id = 0;

    for ( int i = 0; i < arr.size() - 1; ++i )
        for ( int j = i + 1; j < arr.size(); ++j )
            two_Sums[id++] = pairSum(i, j, arr[i] + arr[j]);


    return two_Sums;
}

unsigned long findFour( std::vector<int> arr ) {
    int size = (arr.size() * (arr.size() - 1) ) / 2;
    struct pairSum *two_Sums = crateTwoSumArray(arr, size);

    quickSort(two_Sums, 0, size - 1);

    int L = 0;
    int R = size - 1;
    unsigned long count = 0;

    while( L < R ) {

        if ( two_Sums[L].sum + two_Sums[R].sum == 0 )
            count += equalPairs(two_Sums, &L, &R);
        else if (two_Sums[L].sum + two_Sums[R].sum < 0 )
            ++L;
        else
            --R;
    }

    delete [] two_Sums;
    return count / 3;
}

int main( int argc, char *argv[] ) {
    FILE* file;

    if ( argc == 1 ) {
        file = stdin;

    } else if ( argc == 2 ) {
        file = fopen( argv[1], "r" );

        if ( file == NULL ) {
            printf( "%s: cannot find file '%s'\n", argv[0], argv[1] );
            return 2;
        }

    } else {
        printf( "usage: '%s input.txt' (file name is optional; default stdin)\n", argv[0] );
        return 1;
    }

    int line = 0;
    std::vector <int> arr;

    while ( fscanf( file, "%d\n", &line ) == 1 )
        arr.push_back(line);

    fclose( file );


    printf ( "%s: found %lu combinations", argv[0], findFour(arr) );

    return 0;
}

