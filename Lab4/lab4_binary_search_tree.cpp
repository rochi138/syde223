#include <iostream>
#include "lab4_binary_search_tree.hpp"
#include <sstream>
#include <queue>

using namespace std;

// PURPOSE: Default/empty constructor
BinarySearchTree::BinarySearchTree() {
	root = NULL;
	size = 0;
}

// PURPOSE: Explicit destructor of the class BinarySearchTree
BinarySearchTree::~BinarySearchTree() {
	if (root == NULL)
		return;
}

// PURPOSE: Returns the number of nodes in the tree
unsigned int BinarySearchTree::get_size() const {
	return size;
}

// PURPOSE: Returns the maximum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::max() const {
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
	TaskItem* parent = root;
	while (parent->right){
		parent = parent->right;
	}
	return *parent;
}

// PURPOSE: Returns the minimum value of a node in the tree
// if the tree is empty, it returns (-1, "N/A")
BinarySearchTree::TaskItem BinarySearchTree::min() const {
	if (!root)
		return BinarySearchTree::TaskItem(-1, "N/A");
	TaskItem* parent = root;
	while (parent->left){
		parent = parent->left;
	}
	return *parent;
}

// PURPOSE: Returns the tree height
unsigned int BinarySearchTree::height() const {
	return 0;
}

// PURPOSE: Prints the contents of the tree; format not specified
void BinarySearchTree::print() const {
	cout<<endl<<endl<<endl<<endl<<endl<<"see"<<endl;
	if (!root) {
    	cout<<"Empty"<<endl;
    	return;
    }    
	stringstream ss;
	queue<BinarySearchTree::TaskItem*> node_queue;
	node_queue.push(root);
	while (!node_queue.empty()) {
		BinarySearchTree::TaskItem* cur_node = node_queue.front();
		node_queue.pop();
		ss << cur_node->priority << " ";
		if (cur_node->left) {
			node_queue.push(cur_node->left);
		}
		if (cur_node->right) {
			node_queue.push(cur_node->right);
		}
	}
    
	string level_order_str = ss.str();

	cout<<level_order_str.substr(0, level_order_str.size() - 1)<<endl;	
}

// PURPOSE: Returns true if a node with the value val exists in the tree	
// otherwise, returns false
bool BinarySearchTree::exists( BinarySearchTree::TaskItem val ) const {
	if (!root)
		return false;
	TaskItem* parent = root;
	while(parent){
		if (val.priority == parent->priority)
			return true;
		if (val.priority < parent->priority){
			parent = parent->left;
		} else {
			parent = parent->right;
		}
	}
	return true;
}

// PURPOSE: Optional helper function that returns a pointer to the root node
BinarySearchTree::TaskItem* BinarySearchTree::get_root_node() {
    return NULL;
}

// PURPOSE: Optional helper function that returns the root node pointer address
BinarySearchTree::TaskItem** BinarySearchTree::get_root_node_address() {
    return NULL;
}

// PURPOSE: Optional helper function that gets the maximum depth for a given node
int BinarySearchTree::get_node_depth( BinarySearchTree::TaskItem* n ) const {
	return 0;
}

// PURPOSE: Inserts the value val into the tree if it is unique
// returns true if successful; returns false if val already exists
bool BinarySearchTree::insert( BinarySearchTree::TaskItem val ) {
	cout<<"insert "<<val.priority<<endl;
	if (!root){
		root = new TaskItem(val);
		++size;
		return true;
	}
	TaskItem* parent = root;
	TaskItem* grandparent = NULL;
	while(parent){
		if (val.priority == parent->priority)
			return false;
		grandparent = parent;
		if (val.priority < parent->priority){
			parent = parent->left;
		} else {
			parent = parent->right;
		}
	}
	parent = new TaskItem(val);
	if (parent->priority > grandparent->priority)
		grandparent->right = parent;
	else
		grandparent->left = parent;
	++size;
    return true;
}

// PURPOSE: Removes the node with the value val from the tree
// returns true if successful; returns false otherwise
bool BinarySearchTree::remove( BinarySearchTree::TaskItem val ) {
	cout<<"remove "<<val.priority<<endl;
	if (!root){
		return false;
	}
	TaskItem* parent = root;
	TaskItem* grandparent = NULL;
	while(parent){
		if (parent == NULL)
			return false;
		if (val.priority == parent->priority){
			TaskItem* replacement = parent->right;
			if (replacement){
				while (replacement->left){
					replacement = replacement->left;
				}	
				replacement->left = parent->left;
			}
			else
				replacement = parent->left;
			if (grandparent){
				if (parent == grandparent->left)
					grandparent->left = replacement;
				else 
					grandparent->right = replacement;
			}
			if (replacement && parent->right){
				while (replacement->right){
					replacement = replacement->right;
				}
				replacement->right = parent->right;
			}
			delete parent;
			--size;
			return true;
		}
		grandparent = parent;
		if (val.priority < parent->priority){
			parent = parent->left;
		} else {
			parent = parent->right;
		}
	}
	return false;
}
