#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

	How to QUEUE (DLL):
	1. Node -> isi nodenya apa aja
	2. Declare head and tail -> buat pala ama buntut
	3. Create Node -> buat nodenya
	4. Insertion (QUEUE) -> masukin nodenya (queue)
	5. Deletion -> cara ngehapus nodenya
	6. Display Linked List -> ngeprint semua node yang ada di linked list
	done bang

*/

// 1. Node
typedef struct studentProfile{
	
	char name[50];
	int age;
	
	studentProfile* prev;
	studentProfile* next;
	
} node;

// 2. Declare head and tail
node* head = NULL;
node* tail = NULL;

// 3. Create Node
node* create_node(const char* name, int age){
	
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode->prev = newNode->next = NULL;
	
	strcpy(newNode->name, name);
	newNode->age = age;
	
	return newNode;
}

// 4. Insertion Method (QUEUE)
void push_tail(node* newNode){
	
	if(!tail) tail = head = newNode;
	else{
		newNode->prev = tail;
		tail->next = newNode;
		tail = newNode;
	}
}

// 5. Deletion Method
void pop_head(){
	
	if(head == tail){
		free(head);
		head = tail = NULL;
  	} else{
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}
}

// 6. Display Linked List
void display(){
	
	node* curr = head;
	if(!head) printf("kosong bang kosong\n\n");
	else{
		int i = 1;
		while(curr){
			printf("%d. Name: %s\n   Age: %d\n\n", i++, curr->name, curr->age);
			curr = curr->next;
		}
	} 
}

int main(){
	
//	push_tail(create_node("Hans", 17));
//	push_tail(create_node("Valen", 16));
//	push_tail(create_node("William", 18));
//	push_tail(create_node("Declan", 18));
//	push_tail(create_node("Ricko", 30));
//	push_tail(create_node("Albert", 20));
//	push_tail(create_node("Lery", 50));
//	push_tail(create_node("Mekel", 7));
//	push_tail(create_node("Pepeng", 12));
//	push_tail(create_node("Han", 40));
//	
//	pop_head();
//	pop_head();
//	pop_head();
//	pop_head();
//	pop_head();
	
	display();
	
	return 0;
}
