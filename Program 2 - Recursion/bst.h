#ifndef BST_H
#define BST_H

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <algorithm>
#include <sstream>
#include <assert.h>
using namespace std;

class TreeNode
{
public:
	int element;
	TreeNode *left;
	TreeNode *right;
	TreeNode *parent;
	int left_count = 0;
	int right_count = 0;
	TreeNode(int e = 0, TreeNode *l = NULL, TreeNode *r = NULL, TreeNode *p = NULL) :
		element(e), left(l), right(r), parent(p) {}
};

class BinarySearchTree
{
protected:
	int count = 0;
	vector<TreeNode*> path1, path;
	TreeNode *root;
	bool insert(int & x, TreeNode * & t, TreeNode *p);                     // insert method
	string toString(TreeNode * t, string indent) const;                     // toString method
	string traverse(TreeNode * t) const;                                   // inorder travesal
	void makeEmpty_p(TreeNode* &t);                                    // empty tree
	int fringe(TreeNode * t);                                        // count number of leaf nodes
	int inorderPre(int key, TreeNode* t);                             // find inorder predecessor of given key
	int nodesInLevel(TreeNode* t, int current, int given);               // find nodes in given level
	TreeNode* findKthInOrder(TreeNode* t, int k, int &count, TreeNode* &result);            // the the kth element in order
	int widthHeight(TreeNode * t, int & height);                               // find diameter of tree
	bool isIsomorphic(BinarySearchTree tree, TreeNode*& t, TreeNode*& t1);            // Isomorphic?
	bool isQuasiIsomorphic(BinarySearchTree tree, TreeNode*& t, TreeNode*& t1);       // Quasi-Isomorphic?
	TreeNode* lca(int num, int num1, TreeNode* t);                                 // lowest common ancestor

public:
	BinarySearchTree() : root(NULL) { }

	string toString(string msg = "") const                      // call toString method
	{
		if (root == NULL){
			return msg + "\n" + "Tree is Empty";
		}
		return msg + "\n" + toString(root, "  ");
	}
	bool insert(int & x) { return insert(x, root, NULL); }             // call insert method
	string traverse(string msg) const                       // call travesr method
	{
		return msg + "\n" + traverse(root);
	}
	void makeTree(vector<int> all);                         // make tree
	int size(){ cout << count << endl; }       // find size of tree
	void makeEmpty(){          // call makeEmpty method
		makeEmpty_p(root);
	}
	int fringe(){                      // call fringe method
		if (root == NULL){
			return 0;
		}
		return fringe(root); 
	}
	int inorderPre(int key){               // call inorderPre method
		if (root == NULL) return 0;
		return inorderPre(key, root);
	}
	int nodesInLevel(int level){         // call nodesInLevel method
		if (root == NULL) return 0;
		return nodesInLevel(root, 0, level);
	}

	TreeNode* findKthInOrder(int k){              // call findKthInOrder method
		if (root == NULL) return NULL;
		int count = k;
		TreeNode* result;
		return findKthInOrder(root, k, count, result);
	}

	bool isIsomorphic(BinarySearchTree tree){                     // call isIsomorphic method
		if (root == NULL) false;
		TreeNode* t1 = tree.root;
		return isIsomorphic(tree, root, t1);
	}

	bool isQuasiIsomorphic(BinarySearchTree tree){                  // call isQuasiIsomorphic method
		if (root == NULL) false;
		TreeNode* t1 = tree.root;
		return isQuasiIsomorphic(tree, root, t1);
	}

	bool find(TreeNode* t, vector<TreeNode*> &path, int k)          // find method, used for lca method
	{																// Complexity: O(n)
		if (t == NULL) return false;
		path.push_back(t);
		if (t->element == k)
			return true;

		if (find(t->left, path, k) || find(t->right, path, k))
			return true;
		path.pop_back();
		return false;
	}

	TreeNode* lca(int num, int num1){
		if (root == NULL) return NULL;
		return lca(num, num1, root);
	}

	int width(){
		if (root == NULL) return 0;
		int height = 0;
		return widthHeight(root, height);
	}
};


#endif // !BST_H