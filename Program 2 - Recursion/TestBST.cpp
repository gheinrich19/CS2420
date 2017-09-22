#include "bst.h"
#include <ctime>

int main()
{
	int val = 460;
	const int SIZE = 8;
	BinarySearchTree tree0, tree1, tree2, tree3, tree4, tree5, tree6, tree7, tree_c;
	vector<int> v0{ 25, 10, 60, 55, 45 };
	vector<int>v7{ 30, 15, 65, 75, 83 };
	vector<int> v1{ 25, 10, 60, 55, 58, 56, 14, 10, 75, 80, 20, 10, 5, 7, 61, 62, 63 };
	vector<int> v2, v3, v4, v5, v6;
	for (int i = 0; i < SIZE; i++){
		int t = rand() % 100;
		v2.push_back(t);
		v3.push_back(t + rand() % 5);
		v4.push_back(t + 18);
		v5.push_back(100 - t);
	}
	for (int i = 0; i < SIZE*SIZE; i++){
		int t = rand() % 2000;
		v6.push_back(t);
	}
	v6.push_back(val);
	tree0.makeTree(v0);
	tree1.makeTree(v1);
	tree7.makeTree(v7);

	cout << tree0.toString("Tree 0") << endl;
	cout << tree0.traverse("Simple traveral of tree0") << endl;
	tree6.makeTree(v0);
	cout << tree6.toString("clone of tree0");
	tree6.makeEmpty();
	cout << tree0.toString("tree0 Not destroyed even though clone is");
	cout << tree6.toString("clone of tree0 (Now empty)") << endl;

	cout << tree1.toString("Tree 1");
	cout << "Fringe count tree1:" << tree1.fringe() << endl;


	tree3.makeTree(v3);
	tree4.makeTree(v4);
	tree5.makeTree(v5);
	tree6.makeTree(v6);
	cout << tree6.traverse("tree6") << endl;
	cout << "In Tree6, starting at " << val << endl;
	for (int i = 0; i < 5; i++)
	{
	val = tree6.inorderPre(val);
	cout << "The next predecessor is " << val << endl;
	}
	cout << tree4.toString("Tree 4");
	int myLevel = 3;
	cout << "Number nodes at level " << myLevel << " is " << tree4.nodesInLevel(myLevel) << endl;
	myLevel = 4;
	cout << "Number nodes at level " << myLevel << " is " << tree4.nodesInLevel(myLevel) << endl;
	cout << tree1.toString("tree1");
	int k = 1;
	cout << "In tree1, the " << k << "th smallest value is  " << tree1.findKthInOrder(k)->element << endl;
	k = 7;
	cout << "In tree1, the " << k << "th smallest value is  " << tree1.findKthInOrder(k)->element << endl;
	k = 12;
	cout << "In tree1, the " << k << "th smallest value is  " << tree1.findKthInOrder(k)->element << endl;
	cout << "The width of  tree1 is " << tree1.width() << endl;
	tree2.makeTree(v2);
	cout << "The width of  tree2 is " << tree2.width() << endl;

	cout << tree2.toString("tree2");
	cout << tree3.toString("tree3");
	cout << tree4.toString("tree4");
	cout << tree5.toString("tree5");
	if (tree2.isIsomorphic(tree3)) cout << "Trees 2 and 3 are Isomorphic" << endl;
	if (tree2.isIsomorphic(tree4)) cout << "Trees 2 and 4 are Isomorphic" << endl;
	if (tree3.isIsomorphic(tree4)) cout << "Trees 3 and 4 are Isomorphic" << endl;
	if (tree0.isIsomorphic(tree1)) cout << "Trees 2 and 1 Are Isomorphic" << endl;
	if (tree2.isQuasiIsomorphic(tree3)) cout << "Trees 2 and 3 Are Quasi-Isomorphic" << endl;
	if (tree2.isQuasiIsomorphic(tree5)) cout << "Trees 2 and 5 Are Quasi-Isomorphic" << endl;
	if (tree2.isQuasiIsomorphic(tree4)) cout << "Trees 2 and 4 Are Quasi-Isomorphic" << endl;
	if (tree0.isQuasiIsomorphic(tree7)) cout << "Trees 0 and 7 Are Quasi-Isomorphic" << endl;

	cout << tree1.toString("tree1");
	if (tree1.lca(56, 61) == NULL)
		cout << "No Least Common Ancestor\n";
	else
		cout << "Least Common Ancestor " << tree1.lca(56, 61)->element << endl;
	return 0;
}