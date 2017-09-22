#include "HashTable.h"
#include <fstream>
#include <iostream>

using namespace std;

void insertGame(string file, string word, HashTable<string, HashRecord<string>> &h, HashRecord<string>* hr){       // inseart word from file
	ifstream fin;
	fin.open(file);
	while (!fin.eof()){
		int count = 1;
		getline(fin, word);
		for (unsigned int i = 0; i < word.size(); i++){
			word[i] = tolower(word[i]);
		}
		if (h.find(word) != NULL){
			hr = h.find(word);
			++hr->count;
		}
		else{
			hr = new HashRecord<string>(word, count);
		}
		h.calcScore(hr->key, hr);             // calculate score of word
		h.insert(hr->key, hr);                // insert word
	}
	fin.close();
}

int main(){
	string word = "";
	HashTable<string, HashRecord<string>> h;        // hash table for game0
	HashTable<string, HashRecord<string>> h1;       // hash table for game1
	HashTable<string, HashRecord<string>> h2;       // hash table for game2
	HashTable<string, HashRecord<string>> h3;       // hash table for game3
	HashTable<string, HashRecord<string>> h4;       // hash table for game4
	HashRecord<string>* hr = nullptr;
	
	cout << "----------------Game 0----------------\n\n";
	insertGame("game0.txt", word, h, hr);
	cout << h.toString(50);                      // print out the first 50 or less words in the table
	cout << "---------------End Game---------------\n\n";
	
	cout << "----------------Game 1----------------\n\n";
	insertGame("game1.txt", word, h1, hr);
	cout << h1.toString(50);                     // print out the first 50 or less words in the table
	cout << "---------------End Game---------------\n\n";
	
	cout << "----------------Game 2----------------\n\n";
	insertGame("game2.txt", word, h2, hr);
	cout << h2.toString(50);                     // print out the first 50 or less words in the table
	cout << "---------------End Game---------------\n\n";
	
	cout << "----------------Game 3----------------\n\n";
	insertGame("game3.txt", word, h3, hr);
	cout << h3.toString(50);                     // print out the first 50 or less words in the table
	cout << "---------------End Game---------------\n\n";
	
	cout << "----------------Game 4----------------\n\n";
	insertGame("game4.txt", word, h4, hr);
	cout << h4.toString(50);                     // print out the first 50 or less words in the table
	cout << "---------------End Game---------------\n\n";
	return 0;
}