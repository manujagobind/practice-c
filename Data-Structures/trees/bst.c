#include <stdio.h>
#include <stdlib.h>

struct Node {
	int data;
	struct Node *left, *right;
};

struct Node* get_new_node(int data) {
	struct Node *node = malloc(sizeof(struct Node));
	node->data = data;
	node->left = node->right = NULL;
	return node;
}

void destroy_node(struct Node *node) {
	free(node);
}

void inorder(struct Node *root) {
	if(root) {
		inorder(root->left);
		printf("%d ", root->data);
		inorder(root->right);
	}
}

int minimum(struct Node *root) {
	while(root->left) {
		root = root->left;
	}
	return root->data;
}

int maximum(struct Node *root) {
	while(root->right) {
		root = root->right;
	}
	return root->data;
}

struct Node* insert(struct Node *root, int data) {
	if(root == NULL){
		return get_new_node(data);
	} else if (data < root->data) {
		root->left = insert(root->left, data);
	} else {
		root->right = insert(root->right, data);
	}
}

struct Node* delete_val(struct Node *root, int data) {
	if(root->data == data) {
		if(!root->left && !root->right) {
			root = NULL;
		} else if(!root->right) {
			root = root->left;
		} else if(!root->left) {
			root = root->right;
		} else {
			int min = minimum(root->right);
			root->data = min;
			root->right = delete_val(root->right, min);
		}
	} else if(data < root->data) {
		root->left = delete_val(root->left, data);
	} else {
		root->right = delete_val(root->right, data);	
	}
	return root;
}

int get_node_count(struct Node *root) {
	if(!root) {
		return 0;
	}
	return get_node_count(root->left) + get_node_count(root->right) + 1;
}

int height(struct Node *root) {
	if(!root) {
		return -1;
	} 
	int left_height = height(root->left);
	int right_height = height(root->right);
	if(left_height > right_height) {
		return left_height + 1;
	} else {
		return right_height + 1;
	}
}

int diameter(struct Node *root) {
	if(root) {
		int left_height, right_height, left_diam, right_diam;
		left_height = height(root->left);
		right_height = height(root->right);
		left_diam = diameter(root->left);
		right_diam = diameter(root->right);
		int max_diam = left_diam > right_diam ? left_diam : right_diam;
		if(left_height + right_height + 1 > max_diam) {
			return left_height + right_height + 1;
		} else {
			return max_diam;
		}
	}
	return 0;
}

struct Node* destroy_tree(struct Node *root) {
	if(root) {
		destroy_tree(root->left);
		destroy_tree(root->right);
		destroy_node(root);
	}
	return NULL;
}

int is_bst(struct Node *root) {
	if(!root) {
		return 0;
	}
	if(root->left && root->data > maximum(root->left) && root->right && root->data < minimum(root->right)){
		return 1;				
	}
	return 0;
}

int main() {
	struct Node *root = NULL;
	root = insert(root, 10);
	root = insert(root, 5);
	root = insert(root, 15);
	root = insert(root, 7);
	root = insert(root, 13);
	root = insert(root, 20);
	inorder(root);
	printf("\n");
	printf("Minimum value: %d\n", minimum(root));	
	printf("Maximum value: %d\n", maximum(root));	
	printf("Node count: %d\n", get_node_count(root));	
	printf("Height: %d\n", height(root));	
	printf("Diameter: %d\n", diameter(root));	
	printf("Is BST?: %d\n", is_bst(root));	
	root = delete_val(root, 10);
	inorder(root);
	printf("\n");
	root = destroy_tree(root);
	inorder(root);
	printf("\n");
	root = insert(root, 10);
	root = insert(root, 5);
	root = insert(root, 15);
	root = insert(root, 7);
	root = insert(root, 13);
	root = insert(root, 20);
	inorder(root);
	printf("\n");
    return 0;
}
