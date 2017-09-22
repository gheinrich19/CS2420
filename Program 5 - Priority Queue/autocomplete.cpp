#include "priorityqueue.h"
#include <fstream>

int numOfTerms;

int binarySearch(Term a[], int low, int high, string key, int r)            // binary search function
{
	int position;

	position = (low + high) / 2;
	string target = a[position].word.substr(0, r);
	signed int compare = target.compare(key);

	while ((compare != 0) && (low <= high))
	{
		if (compare > 0)               
		{                                                       // decrease position by one.
			high = position - 1;
		}
		else
		{                                                        // Else, increase position by one.
			low = position + 1;
		}
		position = (low + high) / 2;
		target = a[position].word.substr(0, r);
		compare = target.compare(key);
	}
	if (low <= high)
	{
		return position;
	}
	else{
		return -1;                      // return -1 if not found
	}
}

int firstIndexOf(Term a[], string target, int r){                      // find first instance of given prefix
	int index = binarySearch(a, 0, numOfTerms - 1, target, r);
	int first = index;
	while (index != -1){
		index = binarySearch(a, 0, index - 1, target, r);
		if (index != -1){
			first = index;
		}
	}
	return first;
}

int lastIndexOf(Term a[], string target, int r){                         //find last instance of given prefix
	int index = binarySearch(a, 0, numOfTerms - 1, target, r);
	int last = index;
	while (index != -1){
		index = binarySearch(a, index + 1, numOfTerms - 1, target, r);
		if (index != -1){
			last = index;
		}
	}
	return last;
}

int main(){

	cout << "-------------------TEST 1 - Leftist Heap (Intergers)-------------------\n\n";       //test case for priority queue
	LeftistHeap<int> l1;
	LeftistHeap<int> l2;

	cout << "Insert: 4, 15, 2, 3, 7, 8, 13, 6 into Queue L1\n";
	l1.insert(4);
	l1.insert(15);
	l1.insert(2);
	l1.insert(3);
	l1.insert(7);
	l1.insert(8);
	l1.insert(13);
	l1.insert(6);
	cout << "Print Queue L1\n\n" << l1.toString() << endl;
	cout << "Delete Max from Queue L1\n";
	l1.deleteMax();
	cout << "Print Queue L1\n\n" << l1.toString() << endl;
	cout << "------------------------------------------------------------------------\n";

	cout << "Insert: 23, 35, 5, 9, 67, 14, 33, 45 into Queue L2\n";
	l2.insert(23);
	l2.insert(35);
	l2.insert(5);
	l2.insert(9);
	l2.insert(67);
	l2.insert(14);
	l2.insert(33);
	l2.insert(45);
	cout << "Print Queue L2\n\n" << l2.toString() << endl;
	cout << "Delete Max from Queue L2\n";
	l2.deleteMax();
	cout << "Print Queue L2\n\n" << l2.toString() << endl;
	cout << "------------------------------------------------------------------------\n";

	cout << "Merge Queues L1 and L2\n";
	LeftistHeap<int> l3(l1.merge(l1.getRoot(), l2.getRoot()));                     //merge heap2 l1 and l2 into a new heap l3
	cout << "Print Resulting Queue\n\n" << l3.toString() << endl;
	cout << "------------------------------------------------------------------------\n";

	cout << "-------------------------Program - Autocomplete-------------------------\n";
	ifstream fin;
	fin.open("SortedWords.txt");

	fin >> numOfTerms;         //number of words in file

	Term *terms = new Term[numOfTerms];
	
	for (int i = 0; i < numOfTerms; i++){
		fin >> terms[i].word;
		fin >> terms[i].wt;
	}

	string prefix;           //first prefix
	string prefix1;              // second prefix
	int count;                 // # of outputs
	char res = 'Y';
	char mode;        // decides how many prefix user wants to enter
	LeftistHeap<Term> heap1;
	LeftistHeap<Term> heap2;
	while (res != 'N'){                       // continues as long as user wants to continue
		cout << "------------------------------------------------------------------------\n";
		cout << "\nIf you have only one prefix to input press A, else press B: ";
		cin >> mode;
		mode = toupper(mode);
		while (mode != 'A' || mode != 'B'){
			if (mode == 'A'){      // one prefix
				cout << "\nPlease enter a prefix and the Number of Outputs You Want\n";
				cout << "Prefix: ";
				cin >> prefix;
				cout << "# Outputs: ";
				cin >> count;
				cout << endl;
				int first = firstIndexOf(terms, prefix, prefix.size());             // find first instance of prefix
				int last = lastIndexOf(terms, prefix, prefix.size());                // find last instance of prefix
				for (int i = first; i < last + 1 && i > -1; i++){                  // insert all words with prefix into heap
					heap1.insert(terms[i]);
				}
				heap1.printElements(count);                       // print heap
				heap1.empty();                         // empty heap
				break;
			}
			else if (mode == 'B'){     // two prefixes
				cout << "\nPlease enter two prefixes and the Number of Outputs You Want\n";
				cout << "Prefix 1: ";
				cin >> prefix;
				cout << "Prefix 2: ";
				cin >> prefix1;
				cout << "# Outputs: ";
				cin >> count;
				cout << endl;
				int first = firstIndexOf(terms, prefix, prefix.size());            // find first instance of first prefix
				int last = lastIndexOf(terms, prefix, prefix.size());               // find last instance of first prefix
				int first1 = firstIndexOf(terms, prefix1, prefix1.size());          // find first instance of second prefix
				int last1 = lastIndexOf(terms, prefix1, prefix1.size());           // find last instance of second prefix
				for (int i = first; i < last + 1 && i > -1; i++){                 // insert all words with first prefix into heap1
					heap1.insert(terms[i]);
				}
				for (int i = first1; i < last1 + 1 && i > -1; i++){               // insert all words with second prefix into heap2
					heap2.insert(terms[i]);
				}
				LeftistHeap<Term> temp(heap1);          // temporary heaps
				LeftistHeap<Term> temp1(heap2);
				LeftistHeap<Term> temp2;
				LeftistHeap<Term> heap3(temp2.merge(temp.getRoot(), temp1.getRoot()));     // heap3 is the merge of heap1 and heap2
				heap3.printElements(count);                          // print out words in heap 3
				heap1.empty();               // empty heaps
				heap2.empty();
				heap3.empty();
				break;
			}
			else{
				cout << "Please press A or B: ";                // if user response is incorrect
				cin >> mode;
				mode = toupper(mode);
			}
		}
		cout << "\nEnter Y to Continue or N to Quit: ";                      // ask user if they want to quit
		cin >> res;
		res = toupper(res);
		while (true){
			if (res == 'Y' || res == 'N')
				break;
			else{                                     // if user response is invalid
				cout << "Please Enter Y or N: ";
				cin >> res;
				res = toupper(res);
			}
		}
	}
	fin.close();
	cout << "------------------------------------------------------------------------\n";
	return 0;
}