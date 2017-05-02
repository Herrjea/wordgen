#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <ctime>
#include <random>
#include <vector>
#include <map>

using namespace std;


class wordgen{

	map<string,vector<string> > groups;
	vector<pair<string,int> > syllables;
	int mean_word_syllables;
	int mean_sentence_words;
	normal_distribution<double> word_length;
	normal_distribution<double> sentence_length;
	default_random_engine generator;

	public:

		wordgen();

		bool parse_group( string def );

		bool insert_syllable( string syllable, int priority = 1 );

		bool insert_group( string group_name, vector<string> group_values );

		bool parse_file( string file_name );

		string word();

		string sentence();

	private:

		bool check_pattern( string pattern );
};
