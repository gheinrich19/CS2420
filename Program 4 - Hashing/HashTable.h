#ifndef QUADRATIC_PROBING_H
#define QUADRATIC_PROBING_H

#include <vector>
#include <algorithm>
#include <functional>
#include <string>
#include <sstream>
#include <iomanip>
using namespace std;

int nextPrime(int n);
bool isPrime(int n);

enum Status { ACTIVE, EMPTY, DELETED };

// We store two things.  The key itself and the record associated with the key.
// In our case, the HashKey will be the word. The HashRecord will be a node containing the word (again) and the count.
// Note that you have to supply a toString for the HashRecord or you can't print the hash table.

template <typename HashKey>
class HashRecord
{
public:
	HashKey key;
	int count = 0;
	HashRecord(HashKey k, int c){
		key = k;
		count = c;
	}

	string toString(){
		stringstream ss;
		ss << left << "Word: " << setw(15) << key << "Frequency: " << count << endl;
		return ss.str();
	}
};

template <typename HashKey, typename HashRecord>
class HashEntry
{
public:
	HashKey key;
	HashRecord * rec;
	Status info;

	HashEntry(HashRecord * hr = NULL, const HashKey & e = HashKey(), Status i = EMPTY)
		: key(e), rec(hr), info(i) { }

};


template <typename HashKey, typename HashRecord>
class HashTable
{
public:
	bool remove(const HashKey & x);
	bool isEmpty() { return activeElements == 0; }
	HashRecord * insert(const HashKey x, HashRecord * h);
	HashTable(int size = 977) : hashTable(nextPrime(size))
	{
		makeEmpty();
	};
	HashRecord *find(const HashKey & x);
	void makeEmpty();
	string toString(int howMany = 50);
	int score = 0;
	void calcScore(HashKey x, HashRecord* h);

private:
	vector<HashEntry<HashKey, HashRecord>> hashTable;
	int activeElements;
	bool isActive(int currentPos) const;
	size_t myhash(const HashKey & x) const;
	int findPos(const HashKey & x);
	size_t offsetStep(const HashKey & x) const;
	void rehash();
	int numProbes = 0;
	int numFinds = 0;
};

// Convert the Hash table to a string.  Since the hashtablel is large, HowMany indicates how many entries will be displayed.  
template <typename HashKey, typename HashRecord>
string HashTable<HashKey, HashRecord>::toString(int howMany)
{
	int ct = 0;
	stringstream ss;
	ss << "Total Number of Finds: " << numFinds << endl;
	ss << "Total Number of Probes: " << numProbes << endl;
	ss << "# of Items in Table: " << activeElements << endl;
	ss << "Current Hash Table size: " << hashTable.size() << endl;
	ss << "Items:\n";
	for (int i = 0; i < (int)hashTable.size() && ct < howMany; i++)
		if (hashTable[i].info == ACTIVE){
			ss << "  " << hashTable[i].rec->toString();
			ct++;
		}
	ss << "\nGame Score: " << score << endl;
	return ss.str();

}

// return the subscript where x is located in the hash table.    
// Quadratic probing is used.  Can you figure out why this implements quadratic probing?
template <typename HashKey, typename HashRecord>
int HashTable<HashKey, HashRecord>::findPos(const HashKey & x)
{
	int offset = offsetStep(x);
	int currentPos = myhash(x);

	while (hashTable[currentPos].info != EMPTY &&
		hashTable[currentPos].key != x)
	{
		++numProbes;
		currentPos += offset;  // Compute ith probe
		while (currentPos >= (int)hashTable.size())    // Cheaper than  mod
			currentPos -= hashTable.size();
	}
	return currentPos;
};

template<typename HashKey, typename HashRecord>
size_t HashTable<HashKey, HashRecord>::offsetStep(const HashKey & x) const
{
	int hashval = 0;
	for (unsigned int i = 0; i < x.size(); i++){
		hashval = (hashval << 5) ^ x[i] ^ hashval;
	}
	return hashval % hashTable.size();
};

// Remove all elements of the table by setting status to empty.
// Have you seen the range based loop for accessing elements of a vector?
// for (auto &entry:hashTable) says, let a reference variable "entry" iterate through all entries of the hashTable vector
// The "auto" part says to figure out the type of the element automatically (based on what is passed in).
template <typename HashKey, typename HashRecord>
void HashTable<HashKey, HashRecord>::makeEmpty()
{
	activeElements = 0;
	score = 0;
	for (auto & entry : hashTable)
		entry.info = EMPTY;
};

// Create a new hashtable which is at least twice as large as the current size.
// Actually, rehashing can make the table smaller (if entries have been removed), but this isn't considered here.
template <typename HashKey, typename HashRecord>
void HashTable<HashKey, HashRecord>::rehash()
{
	vector<HashEntry <HashKey, HashRecord>> oldhashTable = hashTable;

	// Create new double-sized, empty table
	hashTable.resize(nextPrime(2 * oldhashTable.size()));
	for (auto & entry : hashTable)
		entry.info = EMPTY;

	// Copy table over
	activeElements = 0;
	for (auto & entry : oldhashTable)
		if (entry.info == ACTIVE)
			insert(entry.key, entry.rec);

};

// Return true if given entry is active.
template <typename HashKey, typename HashRecord>
bool HashTable<HashKey, HashRecord>::isActive(int currentPos) const
{
	return hashTable[currentPos].info == ACTIVE;
};

// use built=in hash functions to find a location.
template<typename HashKey, typename HashRecord>
size_t HashTable<HashKey, HashRecord>::myhash(const HashKey & x) const
{
	int hashval = 0;
	for (unsigned int i = 0; i < x.size(); i++){
		hashval = (hashval << 7) ^ x[i] ^ hashval;
	}
	return hashval % hashTable.size();
};

// Use lazy deletion to remove an element
// Return boolean to indicate success of operation
template <typename HashKey, typename HashRecord>
bool HashTable<HashKey, HashRecord>::remove(const HashKey & x)
{
	int currentPos = findPos(x);
	if (!isActive(currentPos))
		return false;

	hashTable[currentPos].info = DELETED;
	activeElements -= 1;
	return true;
};

// Insert item with key x and record pointer h into the hash table.
template<typename HashKey, typename HashRecord>
HashRecord * HashTable<HashKey, HashRecord>::insert(const HashKey x, HashRecord * h)
{
	// Insert x as active
	numFinds += 1;
	int currentPos = findPos(x);
	if (isActive(currentPos))
		return NULL;

	hashTable[currentPos].key = x;
	hashTable[currentPos].rec = h;
	hashTable[currentPos].info = ACTIVE;

	// Rehash; see Section 5.5
	if (++activeElements > (int)(hashTable.size() / 2))
		rehash();

	return h;
};

// Return record for item with key x.
template<typename HashKey, typename HashRecord>
HashRecord * HashTable<HashKey, HashRecord>::find(const HashKey & x)
{
	int pos = findPos(x);
	if (isActive(pos)){
		return hashTable[pos].rec;
	}
	return NULL;
};

// A = 1   B = 3   C = 3   D = 2   
// E = 1   F = 4   G = 2   H = 4   
// I = 1   J = 8   K = 5   L = 1   
// M = 3   N = 1   O = 1   P = 3   
// Q = 10  R = 1   S = 1   T = 1   
// U = 1   V = 4   W = 4   X = 8   
// Y = 4   Z = 10      
template<typename HashKey, typename HashRecord>
void HashTable<HashKey, HashRecord>::calcScore(HashKey x, HashRecord* h){
	int letter = 0;
	int length, bonus;
	char c;
	for (int i = 0; i < x.size(); i++){
		c = x[i];
		if (c == 'a' || c == 'e' || c == 'i' || c == 'l' || c == 'n' || c == 'o' || c == 'r' || c == 's' || c == 't' || c == 'u'){
			letter += 1;
		}
		else if (c == 'd' || c == 'g'){
			letter += 2;
		}
		else if (c == 'b' || c == 'c' || c == 'm' || c == 'p'){
			letter += 3;
		}
		else if (c == 'f' || c == 'h' || c == 'v' || c == 'w' || c == 'y'){
			letter += 4;
		}
		else if (c == 'k'){
			letter += 5;
		}
		else if (c == 'j' || c == 'x'){
			letter += 8;
		}
		else if (c == 'q' || c == 'z'){
			letter += 10;
		}
		else{
			letter += 0;
		}
	}

	int size = x.size();
	if (size <= 2)
		length = 0;
	else if (size == 3)
		length = 1;
	else if (size == 4)
		length = 2;
	else if (size == 5)
		length = 3;
	else if (size == 6)
		length = 4;
	else if (size == 7)
		length = 5;
	else
		length = 6;

	int freq = h->count - 1;
	if (freq == 0)
		bonus = 5;
	else if (freq >= 1 && freq <= 5)
		bonus = 4;
	else if (freq >= 6 && freq <= 10)
		bonus = 3;
	else if (freq >= 11 && freq <= 15)
		bonus = 2;
	else
		bonus = 1;

	score += letter * length * bonus;
}
#endif