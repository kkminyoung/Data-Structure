#include<stdio.h>
#include<malloc.h>
#include <random>

typedef struct TreeNode {
	int key;
	struct TreeNode * left, *right;
}TreeNode;

void insert_node(TreeNode **root, int key){
	TreeNode *parent_node, *current_node;
	TreeNode *new_node;
	current_node = *root;
	parent_node = NULL;

	while (current_node != NULL) {
		if (key == current_node->key) {
			printf("same key. error\n");
			return;
		}
		parent_node = current_node;
		if (key < current_node->key) 
			current_node = current_node->left;
		else 
			current_node = current_node->right;
	}

	new_node = (TreeNode *)malloc(sizeof(TreeNode));
	if (new_node == NULL) 
		return;
	new_node->key = key;
	new_node->left = new_node->right = NULL;
	if (parent_node != NULL)
		if (key < parent_node->key)
			parent_node->left = new_node;
		else parent_node->right = new_node;
	else 
		*root = new_node;
}

void print(TreeNode *root) {
	if (root != NULL) {
		print(root->left);
		printf("%d	", root->key);
		print(root->right);
	}
}

int random(int n) {
	return rand() % n;
}



int main()
{
	TreeNode * root = NULL;

	int input_size = 1000;
	int data_maxval = 10000;

	// output: sorted result
	int *input = (int *)malloc(sizeof(int)*input_size);
	// Generate an input data randomly
	for (int i = 0; i < input_size; i++)
		input[i] = random(data_maxval);
	
	printf("input\n");
	for (int i = 0; i < input_size; i++)
		printf("%d	", input[i]);
	printf("\n");

	printf("output\n");
	for (int i = 0; i < input_size; i++)
		insert_node(&root, input[i]);
	print(root);
	printf("\n");

	return 0;
}
