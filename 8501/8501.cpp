#include <iostream>
#include <map>
struct node { int value; struct node* left; struct node* right; };

struct node* create_node(int value) {
	struct node* newNode = new node;
	newNode->value = value;
	newNode->left = nullptr;
	newNode->right = nullptr;
	return newNode;
}


//void insert_integer(struct node** tree, int value) {
//	if (value > (*tree)->value) {
//		if((*tree)->right == nullptr){
//			struct node* newNode = create_node(value);
//			(*tree)->right = newNode;
//			return;
//		}
//		insert_integer(&((*tree)->right),value);
//	}
//	else {
//		if ((*tree)->left == nullptr) {
//			struct node* newNode = create_node(value);
//			(*tree)->left = newNode;
//			return;
//		}
//		insert_integer(&((*tree)->left), value);
//		
//	}
//}
void insert_integer(struct node** tree, int value) {
	struct node* tempNode = *tree;
	bool dir = 1;//1-right	0-left
	while (true) {
		dir = value > (tempNode)->value ? 1 : 0;
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
	std::cout << "terminating " << tree->value << "\n";
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

void insert_integers(node* tree,int values[], int numValues) {
	for (int x = 0; x < numValues;x++) {
		insert_integer(&tree, values[x]);
	}
	return;
}

int main() {
	struct node* root =  new node;
	root->value = 5;
	root->left = nullptr;
	root->right = nullptr;
	int values[] = { 2,7,6,9,8,3,1,4 };
	std::map<int, int> map;
	int numValues = sizeof(values) / sizeof(int);
	for (int x = 0; x < numValues; x++)
	{
		map[values[x]] = 0;
	}
	insert_integers(root, values, numValues);
	print_tree(root);
	std::cout << "sum " << sum_of_all_integers(root) << "\n";
	std::cout << "largest value " << largest_integer(root) << "\n";
	std::cout << "most common value " << most_common_integer(root,map) << "\n";
	terminate_tree(root);
	return 0;
}