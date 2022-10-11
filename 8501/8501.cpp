#include <iostream>
#include <map>
#include <chrono>
#include "BST.h"

struct node { int value; struct node* left; struct node* right; };

struct node* create_node(int value) {
	struct node* newNode = new node;
	newNode->value = value;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}


void insert_integer_recursive(struct node** tree, int value) {
	if (value > (*tree)->value) {
		if((*tree)->right == nullptr){
			struct node* newNode = create_node(value);
			(*tree)->right = newNode;
			return;
		}
		insert_integer_recursive(&((*tree)->right),value);
	}
	else {
		if ((*tree)->left == nullptr) {
			struct node* newNode = create_node(value);
			(*tree)->left = newNode;
			return;
		}
		insert_integer_recursive(&((*tree)->left), value);
		
	}
}
void insert_integer_loop(struct node** tree, int value) {
	struct node* tempNode = *tree;
	bool dir;
	while (true) {
		dir = value > (tempNode)->value ? 1 : 0;//1-right	0-left
		if ((dir ? tempNode->right : tempNode->left) == nullptr) { break; }
		tempNode = dir ? tempNode->right : tempNode->left;
	}
	struct node* newNode = create_node(value);
	dir ? tempNode->right = newNode : tempNode->left = newNode;
}

void print_tree(struct node* tree) {
	if (tree->left != nullptr) {
		print_tree(tree->left);
	}
	std::cout << tree->value << "\n";
	if(tree->right != nullptr){
		print_tree(tree->right);
	}
}

void terminate_tree(struct node* tree) {
	
	if (tree->left != nullptr) {
		terminate_tree(tree->left);
	}
	if (tree->right != nullptr) {
		terminate_tree(tree->right);
	}
	//std::cout << "terminating " << tree->value << "\n";
	delete tree;
}

void count_elements(struct node* tree, std::map<int,int>* values) {
	if (tree->left != nullptr) {
		count_elements(tree->left,values);
	}
	(*values)[tree->value]++;
	if (tree->right != nullptr) {
		count_elements(tree->right,values);
	}
}

int most_common_integer(struct node* tree, std::map<int,int> map) {
	count_elements(tree, &map);
	int max = map.begin()->first;
	for (std::pair<int,int> value : map) {
		if (value.second > map[max]) { max = value.first; }
	}
	return max;
}

int largest_integer(struct node* tree) {
	if (tree->right == nullptr) { return tree->value; }
	return largest_integer(tree->right);
}

int sum_of_all_integers(struct node* tree) {
	if (tree == nullptr) { return 0; }
	return tree->value + sum_of_all_integers(tree->left) + sum_of_all_integers(tree->right);
}

void insert_integers_recursive(node** tree,int values[], int numValues) {
	for (int x = 1; x < numValues;x++) {
		insert_integer_recursive(tree, values[x]);
	}
	return;
}

void insert_integers_loop(node** tree, int values[], int numValues) {
	for (int x = 1; x < numValues; x++) {
		insert_integer_loop(tree, values[x]);
	}
	return;
}

void test_recursive() {
	struct node** tree = new node*;

	int values[] = { 2,7,6,9,5,8,3,1,4 };
	*tree = create_node(values[0]);
	std::map<int, int> map;
	int numValues = sizeof(values) / sizeof(int);
	for (int x = 0; x < numValues; x++)
	{
		map[values[x]] = 0;
	}
	insert_integers_recursive(tree, values, numValues);
	//print_tree(*tree);
	//std::cout << "sum " << sum_of_all_integers(*tree) << "\n";
	//std::cout << "largest value " << largest_integer(*tree) << "\n";
	//std::cout << "most common value " << most_common_integer(*tree, map) << "\n";
	terminate_tree(*tree);
}

void test_loop() {
	struct node** tree = new node*;

	int values[] = { 2,7,6,9,5,8,3,1,4 };
	*tree = create_node(values[0]);
	std::map<int, int> map;
	int numValues = sizeof(values) / sizeof(int);
	for (int x = 0; x < numValues; x++)
	{
		map[values[x]] = 0;
	}
	insert_integers_loop(tree, values, numValues);
	//print_tree(*tree);
	//std::cout << "sum " << sum_of_all_integers(*tree) << "\n";
	//std::cout << "largest value " << largest_integer(*tree) << "\n";
	//std::cout << "most common value " << most_common_integer(*tree, map) << "\n";
	terminate_tree(*tree);
}

int main() {

	int values[9] = { 2,7,6,9,5,8,3,1,4 };
	BST bst(values[0]);
	for (int x = 1; x < 10; x++)
	{
		bst.insert_integer(x);
	}
	bst.print_tree();

	return 0;
	test_loop();
	test_recursive();
	using namespace std::chrono;
	auto start = high_resolution_clock::now();
	test_loop();
	auto end = high_resolution_clock::now();
	std::cout << "time taken " << duration_cast<microseconds>(end-start).count() << '\n';
	start = high_resolution_clock::now();
	test_recursive();
	end = high_resolution_clock::now();
	std::cout << "time taken " << duration_cast<microseconds>(end - start).count() << '\n';
}