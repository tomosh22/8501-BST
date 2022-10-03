#include <iostream>
#include <map>
struct node { int value; struct node* left; struct node* right; };

void insert_integer(struct node* tree, int value) {
	if (value > tree->value) {
		if(tree->right == nullptr){
			struct node* newNode = new node;
			newNode->value = value;
			newNode->left = nullptr;
			newNode->right = nullptr;
			tree->right = newNode;
			return;
		}
		else {
			insert_integer(tree->right,value);
		}
		
	}
	else {
		if (tree->left == nullptr) {
			struct node* newNode = new node;
			newNode->value = value;
			newNode->left = nullptr;
			newNode->right = nullptr;
			tree->left = newNode;
			return;
		}
		else {
			insert_integer(tree->left, value);
		}
	}
	
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
	std::cout << "terminating " << tree->value << "\n";
	delete tree;
}

void in_order_traversal(struct node* tree, std::map<int,int>* values) {
	if (tree->left != nullptr) {
		in_order_traversal(tree->left,values);
	}
	if (values->find(tree->value) != values->end()) {
		(*values)[tree->value]++;
	}
	else {
		(*values)[tree->value] = 1;
	}
	if (tree->right != nullptr) {
		in_order_traversal(tree->right,values);
	}
}

int most_common_integer(struct node* tree) {
	std::map<int,int> values;
	in_order_traversal(tree, &values);
	int max = values.begin()->first;
	for (std::pair<int,int> value : values) {
		if (value.second > values[max]) { max = value.first; }
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

void insert_integers(node* tree,int values[], int numValues) {
	for (int x = 0; x < numValues;x++) {
		insert_integer(tree, values[x]);
	}
	return;
}

int main() {
	struct node* root =  new node;
	root->value = 5;
	root->left = nullptr;
	root->right = nullptr;
	int values[] = { 1,2,3,4 };
	insert_integers(root, values, sizeof(values) / sizeof(int));
	print_tree(root);
	std::cout << "sum " << sum_of_all_integers(root) << "\n";
	std::cout << "largest value " << largest_integer(root) << "\n";
	std::cout << "most common value " << most_common_integer(root) << "\n";
	terminate_tree(root);
	return 0;
}