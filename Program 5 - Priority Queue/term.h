#ifndef TERM_H
#define TERM_H
#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>

using  namespace std;

class Term
{
public:
	int wt;
	string word;
	Term(string t = "no word", long int w = 0)
	{
		word = t;
		wt = w;
	}
	string toString() {
		stringstream ss;
		ss << word << endl;
		return ss.str();
	}
	bool operator<(Term & t2) { return wt<t2.wt; }

};

#endif