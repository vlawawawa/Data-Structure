#include <stdio.h>
#include <stdlib.h>

typedef struct Contoh{
	
	int key;
	
	int height;
	Contoh* left;
	Contoh* right;
	
} node;

node* Create(int key){
	
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode->key = key;
	
	newNode->height = 1;
	newNode->left = newNode->right = NULL;
	
	return newNode;
	
}

node* ROOT = NULL;

int Height(node* curr)            { return (curr) ? curr->height : 0;                        }
int Max(int a, int b)             { return (a > b) ? a : b;                                  }
int Calculate_height(node* curr)  { return Max(Height(curr->left), Height(curr->right)) + 1; }
int Calculate_balance(node* curr) { return Height(curr->left) - Height(curr->right);         }

node* Left_rotate(node* violation){
	
	node* pivot = violation->right;
	node* cut = pivot->left;
	
	pivot->left = violation;
	violation->right = cut;
	
	violation->height = Calculate_height(violation);
	pivot->height = Calculate_height(pivot);
	
	return pivot;
	
}

node* Right_rotate(node* violation){
	
	node* pivot = violation->left;
	node* cut = pivot->right;
	
	pivot->right = violation;
	violation->left = cut;
	
	violation->height = Calculate_height(violation);
	pivot->height = Calculate_height(pivot);
	
	return pivot;
	
}

node* Insert(node* curr, int key){
	
	if(!curr) return Create(key); // Ketemu yang tempat kosong buat node baru
	
	else if(key < curr->key) curr->left = Insert(curr->left, key);
	else if(key > curr->key) curr->right = Insert(curr->right, key);
	else{ // Ga ketemu
		printf("Node is a duplicate, no can do sir!\n"); 
		return curr;
	}
	
	curr->height = Calculate_height(curr);
	
	int balance = Calculate_balance(curr);
	
	// left left
	if(balance > 1 && key < curr->left->key)
		return Right_rotate(curr);
		
	// left right
	if(balance > 1 && key > curr->left->key){
		curr->left = Left_rotate(curr->left);
		return Right_rotate(curr);
	}	
	
	// right right
	if(balance < -1 && key > curr->right->key)
		return Left_rotate(curr);
		
	// right left
	if(balance < -1 && key < curr->right->key){
		curr->right = Right_rotate(curr->right);
		return Left_rotate(curr);
	}
	
	return curr;
}

node* Find_predecessor(node* curr){
	
	while(curr->right) curr = curr->right;
	return curr;
	
}

node* Delete(node* curr, int key){
	
	if(!curr){ // Ga ketemu
		printf("Node not found, no can do sir!\n");
		return NULL;
	} 
	
	if(key < curr->key) curr->left = Delete(curr->left, key);
	else if(key > curr->key) curr->right = Delete(curr->right, key);
	else{ // Ketemu node lama yang mau dihapus		
		if(!curr->left || !curr->right){
			node* temp = (curr->left) ? curr->left : curr->right;
			free(curr);
			return temp;
		} 
		else{
			node* predecessor = Find_predecessor(curr->left);
			
			curr->key = predecessor->key;
			
			curr->left = Delete(curr->left, predecessor->key);
		}
	} 
	
	curr->height = Calculate_height(curr);
	
	int balance = Calculate_balance(curr);
	
	// left left
	if(balance > 1 && Calculate_balance(curr->left) >= 0) 
		return Right_rotate(curr);
			
	// left right
	if(balance > 1 && Calculate_balance(curr->left) < 0){
		curr->left = Left_rotate(curr->left);
		return Right_rotate(curr);
	}	
	
	// right right
	if(balance < -1 && Calculate_balance(curr->right) <= 0)
		return Left_rotate(curr);
	
	// right left
	if(balance < -1 && Calculate_balance(curr->right) > 0){
		curr->right = Right_rotate(curr->right);
		return Left_rotate(curr);
	}
	
	return curr;
	
}

void View_inOrder(node* curr){
	
	if(!curr) return;
	
	View_inOrder(curr->left);
	printf("%d -> ", curr->key);
	View_inOrder(curr->right);
	
}

int main(){
	
	printf("Hello World!");
	
	return 0;
	
}
