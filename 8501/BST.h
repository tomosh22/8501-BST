#pragma once
class BST
{
public:
	BST(int value);
	~BST();
	void insert_integer(int value);
	void print_tree();
private:
	node** tree;
	void print_tree_recursion(struct node* tree);
};

