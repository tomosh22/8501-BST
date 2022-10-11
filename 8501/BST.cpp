#include "BST.h"
BST::BST(int value) {
	*tree = create_node(value);
}

void BST::insert_integer(int value) {
	struct node* tempNode = *(this->tree);
	bool dir;
	while (true) {
		dir = value > (tempNode)->value ? 1 : 0;//1-right	0-left
		if ((dir ? tempNode->right : tempNode->left) == nullptr) { break; }
		tempNode = dir ? tempNode->right : tempNode->left;
	}
	struct node* newNode = create_node(value);
	dir ? tempNode->right = newNode : tempNode->left = newNode;
}

void BST::print_tree() {
	this->print_tree_recursion(*this->tree);
}

void BST::print_tree_recursion(struct node* tree) {
	if (tree->left != nullptr) {
		print_tree_recursion(tree->left);
	}
	std::cout << tree->value << "\n";
	if (tree->right != nullptr) {
		print_tree_recursion(tree->right);
	}
}