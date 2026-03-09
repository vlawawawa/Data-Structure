#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

	How to BINARY SEARCH TREE:
	1. Node -> isi nodenya apa aja, dan tentuin keynya yang mana (key itu harus unique)
	2. Declare root -> buat akar bosss
	3. Create Node -> buat nodenya
	4. Insertion -> masukin nodenya ke pohon (cabang kiri buat yang kecil & cabang kanan buat yang besar)
	5. Deletion -> cara ngehapus nodenya
	6. Display Methods -> ngeprint semua node yang ada di tree (ada 3 cara yaitu preorder, inorder(ini buat ngeprint berurutan), postorder)
	done bang

*/

// 1. Node
typedef struct studentProfile{
	
	char NIM[20];
	char name[50];
	int age;
	
	studentProfile* left;
	studentProfile* right;
	
} node;

// 2. Declare root
node* root = NULL;

// 3. Create Node
node* create_node(const char* NIM, const char* name, int age){
	
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode->left = newNode->right = NULL;
	
	strcpy(newNode->NIM, NIM);
	strcpy(newNode->name, name);
	newNode->age = age;
	
	return newNode;
}

// 4. Insertion
node* insert_node(node* curr, node* newNode){
	
	if(!curr) return newNode;
	else if(strcmp(newNode->NIM, curr->NIM) < 0) curr->left = insert_node(curr->left, newNode);
	else if(strcmp(newNode->NIM, curr->NIM) > 0) curr->right = insert_node(curr->right, newNode);
	
	return curr;	
}

// 5. Deletion
node* get_predecessor(node* curr){
	
	while(curr->right) curr = curr->right;
	
	return curr;
}

node* get_successor(node* curr){
	
	while(curr->left) curr = curr->left;
	
	return curr;
}

node* delete_node(node* curr, const char* NIM);

node* pop_node(node* curr){
	
	if(!curr->left && !curr->right){
		free(curr);
		curr = NULL;
	} 
	else if(!curr->left || !curr->right){		
		node* temp = (curr->left) ? curr->left : curr->right;
		free(curr);
		curr = temp;
	} 
	else if(curr->left && curr->right){
		node* predecessor = get_predecessor(curr->left);
		
		strcpy(curr->NIM, predecessor->NIM);
		strcpy(curr->name, predecessor->name);
		curr->age = predecessor->age;
		
		curr->left = delete_node(curr->left, predecessor->NIM);
	}
	
	return curr;
}

node* delete_node(node* curr, const char* NIM){
	
	if(!curr) return NULL;
	else if(strcmp(NIM, curr->NIM) < 0) curr->left = delete_node(curr->left, NIM);
	else if(strcmp(NIM, curr->NIM) > 0) curr->right = delete_node(curr->right, NIM);
	else if(strcmp(NIM, curr->NIM) == 0) curr = pop_node(curr);
	
	return curr;
}

// 6. Display Methods
void display_preorder(node* curr, int* i){
	
	if(!curr) return;
	
	printf("%d. NIM: %s\n   Name: %s\n   Age: %d\n\n", (*i)++, curr->NIM, curr->name, curr->age);
	display_preorder(curr->left, i);
	display_preorder(curr->right, i);
}

void display_inorder(node* curr, int* i){
	
	if(!curr) return;
	
	display_inorder(curr->left, i);
	printf("%d. NIM: %s\n   Name: %s\n   Age: %d\n\n", (*i)++, curr->NIM, curr->name, curr->age);
	display_inorder(curr->right, i);
}

void display_postorder(node* curr, int* i){
	
	if(!curr) return;
	
	display_postorder(curr->left, i);
	display_postorder(curr->right, i);
	printf("%d. NIM: %s\n   Name: %s\n   Age: %d\n\n", (*i)++, curr->NIM, curr->name, curr->age);
}

int main(){
	
//	root = insert_node(root, create_node("2807361278", "Hans", 17));
//	root = insert_node(root, create_node("2802524120", "Valen", 16));
//	root = insert_node(root, create_node("2807382638", "William", 18));
//	root = insert_node(root, create_node("2893761278", "Declan", 18));
//	root = insert_node(root, create_node("2807369374", "Ricko", 30));
//	root = insert_node(root, create_node("2807824578", "Albert", 20));
//	root = insert_node(root, create_node("2807946278", "Lery", 50));
//	root = insert_node(root, create_node("2873674278", "Mekel", 7));
//	root = insert_node(root, create_node("2873689288", "Pepeng", 12));
//	root = insert_node(root, create_node("2848714278", "Han", 40));
//	
//	root = delete_node(root, "2893761278");
//	root = delete_node(root, "2807824578");
//	root = delete_node(root, "2873674278");
//	
//	int i;
//	
//	printf("PRE-ORDER\n");
//	printf("--------------------------\n\n");
//  i = 1;
//	display_preorder(root, &i);
//	printf("--------------------------\n\n");
//	
//	printf("IN-ORDER\n");
//	printf("--------------------------\n\n");
//	i = 1;
//	display_inorder(root, &i);
//	printf("--------------------------\n\n");
//	
//	printf("POST-ORDER\n");
//	printf("--------------------------\n\n");
//	i = 1;
//	display_postorder(root, &i);
//	printf("--------------------------\n\n");
	
	return 0;
}
