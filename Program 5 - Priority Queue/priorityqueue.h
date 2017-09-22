#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include "term.h"

template <typename Comparable>
class LeftistNode{
public:
	Comparable element;
	LeftistNode *left;
	LeftistNode *right;
	int npl;                       // null path length
	LeftistNode(const Comparable & e, LeftistNode *lt = nullptr,
		LeftistNode *rt = nullptr, int np = 0)
		: element{ e }, left{ lt }, right{ rt }, npl{ np } { }
};

template <typename Comparable>
class LeftistHeap{
public:
	LeftistHeap(){
		root = nullptr;
	}
	LeftistHeap(LeftistNode<Comparable>* n){
		root = n;
	}
	LeftistHeap(LeftistHeap<Comparable>& l){                  // copy constructor
		root = copy(l.getRoot());
	}
	LeftistNode<Comparable>* copy(LeftistNode<Comparable>* n){                   // clone nodes
		if (n == nullptr)
			return n;
		LeftistNode<Comparable>* n1 = new LeftistNode<Comparable>(n->element);
		n1->npl = n->npl;
		n1->left = copy(n->left);
		n1->right = copy(n->right);
		return n1;
	}
	bool isEmpty() const;
	void insert(Comparable const & x);
	LeftistNode<Comparable>* deleteMax();
	LeftistNode<Comparable>* merge(LeftistNode<Comparable> * t1, LeftistNode<Comparable> * t2);
	string toString() const
	{
		return toString(root, "");
	}
	LeftistNode<Comparable> * getRoot(){
		return root;
	}
	LeftistNode<Comparable> * getMax(){            // deletes root
		return deleteMax();
	}
	void printElements(int num){               //only works if Comparable is Term
		for (int i = 0; i < num; i++){
			if (getRoot() != nullptr)
				cout << getMax()->element.toString();
			else
				cout << "";
		}
	}
	int getSize(){
		if (root == nullptr)
			return 0;
		return getSize(root);
	}
	void empty(){             // empty heap
		while (root != nullptr){
			deleteMax();
		}
	}

private:
	LeftistNode<Comparable> *root;
	int size;
	void swapChildren(LeftistNode<Comparable> *t);
	int getSize(LeftistNode<Comparable>* t){
		if (t == nullptr)
			return 0;
		return getSize(t->left) + getSize(t->right) + 1;
	}
	string toString(LeftistNode<Comparable> *t, string indent) const
	{
		stringstream ss;
		if (t != nullptr)
		{
			ss << toString(t->right, indent + "   ");
			ss << indent << t->element << endl;
			ss << toString(t->left, indent + "   ");
		}
		return ss.str();
	}
	bool notLeftist(LeftistNode<Comparable>* t){            // check if heap is leftist
		if (t->left == nullptr && t->right != nullptr) return true;
		else if (t->left != nullptr && t->right != nullptr)
			if (t->right->npl > t->left->npl) return true;
		return false;
	}
	void setLeftist(LeftistNode<Comparable>* t){              // sets the null path lengths of heap
		if (t == nullptr) return;
		if (t->right == nullptr)
			t->npl = 0;
		else
			t->npl = t->right->npl + 1;
	}
};

template <typename Comparable>
LeftistNode<Comparable>* LeftistHeap<Comparable>::merge(LeftistNode<Comparable> * t1, LeftistNode<Comparable> * t2){   //merge
	LeftistNode<Comparable> * max;
	if (t1 == nullptr)  return t2;
	if (t2 == nullptr) return t1;
	if (t2->element < t1->element)               // if t1 is max
	{
		t1->right = merge(t1->right, t2);
		max = t1;
	}
	else
	{
		t2->right = merge(t2->right, t1);              // if t2 is max
		max = t2;
	}
	if (notLeftist(max)) swapChildren(max);   //checks if max leftist
	setLeftist(max);                                // sets max's npl
	return max;
}

template <typename Comparable>
void LeftistHeap<Comparable>::insert(Comparable const & x){
	root = merge(new LeftistNode<Comparable>(x), root);                  // just merge the root and the desired insert
}

template <typename Comparable>
bool LeftistHeap<Comparable>::isEmpty() const{
	if (root == nullptr)
		return true;
	return false;
}

template <typename Comparable>
void LeftistHeap<Comparable>::swapChildren(LeftistNode<Comparable> *t){
	swap(t->left, t->right);                  // use swap fucntion
}

template <typename Comparable>
LeftistNode<Comparable>* LeftistHeap<Comparable>::deleteMax(){
	if (isEmpty())
		return nullptr;

	LeftistNode<Comparable> *oldRoot = root;
	root = merge(root->left, root->right);                          // take out root and merge it's children
	return oldRoot;
}

#endif