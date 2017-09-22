#include "bst.h"

string BinarySearchTree::traverse(TreeNode *t) const                     //Complexity: O(n)
{
	stringstream ss;
	if (t == NULL) return "";
	ss << traverse(t->left);
	ss << t->element << " ";
	ss << traverse(t->right);
	return ss.str();
}

string BinarySearchTree::toString(TreeNode *t, string indent) const             //Complexity: O(n)
{
	stringstream ss;
	if (t == NULL) {
		return ss.str();
	}
	ss << toString(t->right, indent + "  ");
	if (t->parent == NULL){
		ss << indent << t->element << "(no parent)";
		ss << "[" << t->left_count << "," << t->right_count << "]\n";
	}
	else{
		ss << indent << t->element << "(" << t->parent->element << ")";
		ss << "[" << t->left_count << "," << t->right_count << "]\n";
	}
	ss << toString(t->left, indent + "  ");
	return ss.str();
}

// Return true if insertion is successful
bool BinarySearchTree::insert(int & x, TreeNode * & t, TreeNode *  p)                 //Complexity: O(n)
{
	if (t == NULL)
	{
		count++;
		t = new TreeNode(x, NULL, NULL, p);
		if (t == NULL) return false;
		return true;
	}
	bool succeed = false;
	if (x < t->element){
		t->left_count++;
		count++;
		succeed = insert(x, t->left, t);
	}
	else if (x > t->element) {
		t->right_count++;
		count++;
		succeed = insert(x, t->right, t);
	}

	return succeed;  // does not allow duplicate insertions
}

void BinarySearchTree::makeTree(vector<int> all)                 //Complexity: O(n)
{
	//makeEmpty(root);
	for (unsigned i = 0; i < all.size(); i++)
		insert(all[i]);
}

void BinarySearchTree::makeEmpty_p(TreeNode* &t){                 //Complexity: O(n)
	if (t == NULL) return;
	makeEmpty_p(t->left);
	makeEmpty_p(t->right);
	count = 0;
	t->left_count = 0;
	t->right_count = 0;
	delete t;
	t = NULL;
}

int BinarySearchTree::fringe(TreeNode* t){          //Complexity: O(n)
	int left_count = 0;
	int right_count = 0;
	if (t == NULL) return 0;
	if (t->left == NULL && t->right == NULL){
		return 1;
	}
	right_count = fringe(t->right);
	left_count = fringe(t->left);
	return right_count + left_count;
}

int BinarySearchTree::inorderPre(int key, TreeNode* t){          //predecessor method  //Complexity: O(n)
	if (t == NULL) return 0;
	if (t->element == key){
		if (t->left != NULL){
			TreeNode* temp = t->left;
			while (temp->right != NULL){
				temp = temp->right;
			}
			return temp->element;
		}
		else if (t->parent != NULL){
			if (t->parent->element < t->element){
				return t->parent->element;
			}
			else if (t->parent->element > t->element){
				TreeNode* temp = t->parent;
				while (temp->parent != NULL && temp->element > t->element){
					temp = temp->parent;
				}
				return temp->element;

			}
		}
		return 0;
	}
	else if (t->element < key){
		return inorderPre(key, t->right);
	}
	else if (t->element > key){
		return inorderPre(key, t->left);
	}
}

int BinarySearchTree::nodesInLevel(TreeNode* t, int current, int given){                      //Complexity: O(n)
	if (t == NULL) return 0;
	if (given == current){
		return 1;
	}
	return nodesInLevel(t->right, current+1, given) + nodesInLevel(t->left, current+1, given);
}

TreeNode* BinarySearchTree::findKthInOrder(TreeNode* t, int k, int &count, TreeNode*& result){            //Complexity: O(n)
	if (t == NULL) return NULL;
	findKthInOrder(t->left, k, count, result);
	if (count-- == 1){
		result = t;
	}
	findKthInOrder(t->right, k, count, result);
	return result;
}

bool BinarySearchTree::isIsomorphic(BinarySearchTree tree, TreeNode*& t, TreeNode*& t1){             // Complexity: O(n)
	if (t == NULL || t1 == NULL) return false;
	if (t->left_count == t1->left_count && t->right_count == t1->right_count){
		return true;
	}
	else return false;
	return isIsomorphic(tree, t->left, t1->left) && isIsomorphic(tree, t->right, t1->right);
}

bool BinarySearchTree::isQuasiIsomorphic(BinarySearchTree tree, TreeNode*& t, TreeNode*& t1){     //Complexity: O(n)
	if (t == NULL || t1 == NULL) return false;
	if (t->left_count == t1->left_count && t->right_count == t1->right_count){
		return true;
	}
	else if (t->left_count == t1->right_count || t->right_count == t1->left_count){
		return true;
	}
	else{
		return false;
	}
	return isQuasiIsomorphic(tree, t->left, t1->left) && isQuasiIsomorphic(tree, t->right, t1->right);
}

TreeNode* BinarySearchTree::lca(int num, int num1, TreeNode* t){              // Complexity: O(n)
	int i;
	if (root == NULL) return NULL;
	if (find(root, path, num) || find(root, path1, num1)){              //find is a recursive function
		if (!find(root, path, num))
			return path1[path1.size() - 1];
		if (!find(root, path1, num1))
			return path[path.size() - 1];
		for (i = 0; i < path.size() && i < path1.size(); i++){
			if (path[i]->element != path1[i]->element)
				break;
		}
	}
	return path[i - 1];
}

int BinarySearchTree::widthHeight(TreeNode * t, int & height){               // Complexity: O(n)
	if (t == NULL) return 0;
	int left_diameter = widthHeight(t->left, height);
	int right_diameter = widthHeight(t->right, height);
	if ((left_diameter + right_diameter + 1) > height)
		height = left_diameter + right_diameter + 1;
	return (max(left_diameter, right_diameter) + 1);
}
