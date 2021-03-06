/*

Issues:

	Siempre saca tres frases de 17, 1 y 6 palabras.

	Fallo de segmantación al intentar leer J =  j, w }. Debería abortar con mensaje de línea del error.

	Todos los conjuntos de valores de un grupo tienen un elemento vacío al final, y hay que poner el -1 en word().

	Cambiar el nobmre de un grupo a char.

	Cómo actúa ante ((A)B)C. ¿Puede hacer B si ha elegido no hacer A?
		Siempre la saltaría.

Next:

	Condicionar reglas.
		consonante geminada sólo si no está al principio o final de una palabra,
		sílaba V sólo si las últimas dos no han sido V...

	Distintos tipos de sílabas: normal, primera de la palabra última de la palabra y palabra monosilábica, si proceden.

	Rewrite.
		ti: chi

*/

#include "../lib/wordgen.h"


wordgen::wordgen(){

	srand( time( NULL ) );
	word_length = normal_distribution<double>{ 2, 1 };
	sentence_length = normal_distribution<double>{ 7, 5 };

//	for ( int i = 0; i < 50; i++ )
//		cout << sentence_length( generator ) << endl;
}

bool wordgen::parse_group( string def ){

	string name;
	vector<string> values;
	string::iterator it = def.begin();

	// Jump garbage
	while ( ( *it < 'A' or *it > 'Z' ) and it != def.end() )
		it++;
	if ( it == def.end() )
		return false;

	// Take the name of the group
	name = *it;

	// Jump to start of the definition
	while ( *it != '{' and it != def.end() )
		it++;
	it++;
	if ( it == def.end() )
		return false;
	while ( *it == ' ' and it != def.end() )
		it++;
	if ( it == def.end() )
		return false;

	// Take the values
	while ( *it != '{' and it != def.end() ){

		// Take every meaningfull character into a new value
		values.push_back( "" );
		while ( *it != ',' and *it != ' ' and *it != '}' and it != def.end() ){
			values.back().push_back( *it );
			it++;
		}

		// Jump spaces
		it++;
		while ( *it == ' ' and it != def.end() )
			it++;
	}

	// Insert parsed group
	groups.insert( make_pair( name, values ) );

	return true;
}


bool wordgen::insert_syllable( string syllable, int priority ){

	if ( check_pattern( syllable ) and priority > 0 ){
		syllables.push_back( make_pair( syllable, priority ) );
		return true;
	}
	return false;
}


bool wordgen::insert_group( string group_name, vector<string> group_values ){

	return groups.insert( make_pair( group_name, group_values ) ).second;
}


bool wordgen::parse_file( string file_name ){

	string line;
	string path_name = "languages/" + file_name;
	ifstream file;
	bool failed = false;
	int i = 0;

	// Check if file exists
	file.open( path_name, ifstream::in );
	if ( file.fail() ){
		cout << "Unable to open file: " << path_name << endl;
		failed = true;
	}

	// Parse and insert groups
	getline( file, line ); i++;
	while ( line != "." and not file.eof() and not failed ){
		if ( not parse_group( line ) ){
			failed = true;
			cout << "Unable to parse line " << i << ": " << line << endl;
		}
		getline( file, line ); i++;
	}

	// Parse and insert syllable structures
	getline( file, line ); i++;
	while ( line != "." and line != "#" and not file.eof() and not failed ){
		if ( not insert_syllable( line ) ){
			failed = true;
			cout << "Unable to parse line " << i << ": " << line << endl;
		}
		getline( file, line ); i++;
	}

	// Parse word length distribution mean and deviation
	if ( line == "." ){
		double mean, stddev;
		string number;
		file >> number; mean = stod(number);
		file >> number; stddev = stod(number);
		word_length = normal_distribution<double>{ mean, stddev };		
	}

	file.close();

	return not failed;
}


string wordgen::word(){

	string word;
	string syllable = syllables[ rand() % syllables.size() ].first;
	unsigned int w_length, i, j;
	bool skipping = false;
	int depth;

	// Determine through normal distribution 
	// the number of syllables the word will have
	do
		w_length = word_length( generator );
	while ( w_length < 1 );

	// Produce each syllable, taking optionallity,
	// marked with parenthesis, into account
	for ( i = 0; i < w_length; i++ ){

		j = 0;		// position in the syllable definition
		depth = 0;	// amount of open parenthesis behind
		while ( j < syllable.size() ){

			if ( syllable[j] == '(' ){
				depth++;
				j++;
				if ( not skipping ) skipping = rand() % 2;
			}
			else if ( syllable[j] == ')' ){
				depth--;
				j++;
				if ( not depth ) skipping = false;
			}
			else if ( skipping )
				j++;
			else{
				word += groups[ string(1,syllable[j]) ]
					[ rand() % ( groups[ string(1,syllable[j]) ].size() - 1 ) ];
				j++;
			}
		}
	}

/*
	stack<int> parentheses;
	bool skipping = false;
	int depth;

	// Determine through normal distribution 
	// the number of syllables the word will have
	do
		w_length = word_length( generator );
	while ( w_length < 1 );

	// Produce each syllable, taking optionallity,
	// marked with parenthesis, into account
	for ( i = 0; i < w_length; i++ ){

		j = 0;				// position in the syllable definition
		depth = 0;			// amount of open parenthesis behind
		parentheses = stack<int>();		// last skipped depth
		parentheses.push( 0 );
		while ( j < syllable.size() ){ ///// FOR


cout << "aaa" << endl;

			// When reaching a left parenthesis,
			if ( syllable[j] == '(' ){
cout << "bbb" << endl;

				depth++;
				j++;
				// if it wasn't skipping before,
				if ( not skipping )
					// but now it is,
					if ( skipping = rand() % 2 )
						// remember at what depth this happened
						parentheses.push( depth );
			}
			// When reaching a right parenthesis,
			else if ( syllable[j] == ')' ){
cout << "ccc" << endl;

				depth--;
				j++;
				// if we're now at the last skipped depth,
				if ( depth == parentheses.top() ){
					// stop skipping and forget that depth
					skipping = false;
					parentheses.pop();
cout << "fff" << endl;
				}
cout << "eee" << endl;
			}
			else if ( skipping ){
cout << "ggg" << endl;
				j++;
}			else{
cout << "ddd" << endl;
				word += groups[ string(1,syllable[j]) ]
					[ rand() % ( groups[ string(1,syllable[j]) ].size() - 1 ) ];
				j++;
			}
		}
	}
*/

	return word;
}


string wordgen::sentence(){

	string sentence;
	int s_length;

	// Determine through normal distribution
	// the number of words the sentence will have
	do
		s_length = sentence_length( generator );
	while ( s_length < 1 );

	// Randomly generate the words and join them
	// with blankspaces in the sentence
	for ( int i = 0; i < s_length; i++ )
		sentence += word() + " ";
	sentence.back() = '.';

	return sentence;
}


bool wordgen::check_pattern( string pattern ){

	int depth = 0;

	for ( char c : pattern )
		if ( c == '(' ) depth ++;
		else if ( c == ')' ) depth--;

	return not depth;
}

