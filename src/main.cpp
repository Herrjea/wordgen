#include <iostream>
#include <fstream>
#include "../lib/wordgen.h"

using namespace std;


int main( int argc, char ** argv ){

	wordgen names;

	ifstream file;

	if ( argc < 2 ){
		cout << "Please specify the name of a file in syllables/ containing the phonotactics description of the language." << endl;
		return 0;
	}


	if ( not names.parse_file( string( argv[1] ) ) )
		return 0;

	cout << names.sentence() << " " << names.sentence() << " " << names.sentence() << endl;
}

