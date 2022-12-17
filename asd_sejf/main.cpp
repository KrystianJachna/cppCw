// Krystian Jachna - SEJF ZADANIE
#include <iostream>
#include <cstdio>
#define max_Size 10000

bool readRods ( FILE* file, int m, int arr[] ) {
    int y1;
    int x1;
    int x2;
    int y2;

    for ( int i = 0; i < m; ++i ) {
        int ch = fscanf( file, "%d %d %d %d\n", &x1, &y1, &x2, &y2 );

        if ( ch != 4)
            return false;

        if ( arr[y1] < y2)
            arr[y1] = y2;
    }

    return true;
}

bool findSafePattern( int arr[], int size ) {
    int start = 0;
    int stop = 0;
    int paths = 0;

    FILE *file;
    file = fopen( "out.txt", "w" );

    if ( file == NULL )
        return false;

    for ( int i = 0; i < size; ++i ) {
        if ( arr[i] == -1 ) {
            if ( i > start )
                stop++;
        }
        else if ( arr[i] == i ) {

             if (i > start) {
                fprintf(file, "(%d,%d)\n", start, stop);
                start = i;
                stop = i;
                paths++;
             } else if (i == start)
                 stop ++;
        } else {

            if ( i == start ) {
                start = arr[i];
                stop = arr[i];
            } else if ( i >= stop ) {
                fprintf(file, "(%d,%d)\n", start, i);
                start = arr[i];
                stop = arr[i];
                paths++;
            }
        }
    }
    if ( start != size ) {
        fprintf(file, "(%d,%d)\n", start, size);
        paths++;
    }
    fprintf(file, "%d\n", paths);

    fflush(file);
    fclose(file);

    return true;
}


int main( int argc, char *argv[] ) {
    FILE* file;


    if ( argc == 1 )
        file = stdin;

    else if ( argc == 2 ) {
        file = fopen ( argv[1], "r" );

        if ( file == NULL ) {
            std::cout << "wrong filename " << argv[1] << "\n";
            return 2;
        }
    }

    int n = 0;
    int m = 0;

    if ( fscanf( file, "%d %d\n", &n, &m ) != 2 ) {
        std::cout << "file's input problem\n";
        fclose( file );
        return 2;
    }

    int arr[max_Size];

    for ( int i = 0; i < n; ++i )
        arr[i] = -1;

    if ( !readRods(file, m, arr) ) {
        std::cout << "file's intput problem\n";
        fclose( file );
        return 2;
    }

    if ( !findSafePattern(arr, n)) {
        std::cout << "cannot open file\n";
    }
    fclose( file );

    return 0;
}



/*

TEST1.in
13 9
1 0 2 1
3 1 4 1
5 1 5 2
3 3 3 4
4 3 5 3
3 5 4 5
3 6 4 6
3 8 4 9
3 9 4 10
1 10 2 10
3 10 3 11

TEST1.out
(2, 3)
(4, 5)
(5, 6)
(6, 8)
(11, 13)
5

 */
