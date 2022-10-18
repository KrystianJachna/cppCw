// Krystian Jachna - SEJF ZADANIE
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

using namespace std;

void parseString( string str, int * Nums ) {
    stringstream stream( str );

    int i = 0;
    while( stream ) {
        int num;
        stream >> num;
        Nums[i] = num;
        ++i;
    }
}

int readFile( int ** Rods ) {
    fstream file;
    file.open( "aaa.txt", ios::in );

    if( !file.good() ) {
        cout << "error" << std::endl;
        exit( 0 );
    }

    string line;
    int Nums [5];
    getline( file, line );
    parseString( line, Nums );

    int n = Nums [0];
    *Rods = new int [n];

    for ( int i = 0; i < n; ++i)
        *( *Rods + i ) = -1;

    while(getline(file, line)) {
        parseString(line, Nums);

        if ( *( *Rods + Nums[1] ) < Nums[3] )
            ( *( *Rods + Nums[1] )) = Nums[3];
    }

    file.close();
    return n;
}

void safePattern( int * Rods, int size ) {
    int start = 0;
    int stop = 0;
    int paths = 0;

    fstream file;
    file.open( "out.txt", ios::out );



    for ( int i = 0; i < size; ++i ) {
        if ( Rods[i] == -1 ) {
            if ( i > start )
                stop++;
        }
        else if ( Rods[i] == i ) {

             if (i > start) {
                file << "(" << start << ", " << i << ")" << endl;
                start = i;
                stop = i;
                paths++;
             } else if (i == start)
                 stop ++;
        } else {

            if ( i == start ) {
                start = Rods[i];
                stop = Rods[i];
            } else if ( i >= stop ) {
                file << "(" << start << ", " << i << ")" << endl;
                start = Rods[i];
                stop = Rods[i];
                paths++;
            }
        }
    }
    if ( start != size )
        file << "(" << start << ", " << size << ")" <<  endl;

    file << paths;
    file.close();
}


int main() {
    int * Rods = nullptr;
    int size = readFile( &Rods );
    safePattern( Rods, size );
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
4

 */
