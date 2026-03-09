#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*

	How to PRIORITY QUEUE (DLL):
	1. Node -> isi nodenya apa aja
	2. Declare head and tail -> buat pala ama buntut
	3. Create Node -> buat nodenya
	4. Insertion (PRIORITY QUEUE) -> masukin nodenya (disini pake priority queue)
	5. Deletion Methods -> cara" ngehapus nodenya
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

// 4. Insertion Method (PRIORITY QUEUE)
void push_head(node* newNode){
	
	newNode->next = head;
	head->prev = newNode;
	head = newNode;
}

void push_tail(node* newNode){
	
	newNode->prev = tail;
	tail->next = newNode;
	tail = newNode;
}

	/* String */ // Contoh kali yang mau diurutin berdasarkan string
void push_mid_name(node* newNode){
	
	node* curr = head;
	while(curr->next && strcmp(curr->next->name, newNode->name) <= 0) curr = curr->next;
	
	newNode->next = curr->next;
	curr->next->prev = newNode;
	
	curr->next = newNode;
	newNode->prev = curr;
}

void push_priority_queue_name(node* newNode){
	
	if(!head) head = tail = newNode;
	else if(strcmp(newNode->name, head->name) < 0) push_head(newNode);
	else if(strcmp(newNode->name, tail->name) >= 0) push_tail(newNode);
	else push_mid_name(newNode);
}

	/* Integer */ // Contoh kalo yang mau diurutin berdasarkan angka
void push_mid_age(node* newNode){
	
	node* curr = head;
	while(curr->next && curr->next->age <= newNode->age) curr = curr->next;
	
	newNode->next = curr->next;
	curr->next->prev = newNode;
	
	curr->next = newNode;
	newNode->prev = curr;
}

void push_priority_queue_age(node* newNode){
	
	if(!head) head = tail = newNode;
	else if(newNode->age < head->age) push_head(newNode);
	else if(newNode->age >= tail->age) push_tail(newNode);
	else push_mid_age(newNode);
}

// 5. Deletion Methods
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

void pop_tail(){
	
	if(tail == head){
		free(tail);
		tail = head = NULL;
  	} else{
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL;
	}
}

	/* String */ // Contoh kalo yang mau di hapus berdasarkan string
void pop_search_name(const char* name){
	
	node* curr = head;
	while(curr && strcmp(curr->name, name) != 0) curr = curr->next;
	
	if(!curr) printf("Gaada muridnya bang\n\n");
	else if(head == tail){
		free(head);
		head = tail = NULL;
	} else{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		free(curr);
	}
}

void pop_specific_name(const char* name){
	
	if(!head) printf("udah kosong bang udah bang\n\n");
	else if(strcmp(head->name, name) == 0) pop_head();
	else if(strcmp(tail->name, name) == 0) pop_tail();
	else pop_search_name(name);
}

	/* Integer */ // Contoh kalo yang mau di hapus berdasarkan angka 
void pop_search_age(int age){
	
	node* curr = head;
	while(curr && curr->age != age) curr = curr->next;
	
	if(!curr) printf("Gaada muridnya bang\n\n");
	else if(head == tail){
		free(head);
		head = tail = NULL;
	} else{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		free(curr);
	}
}

void pop_specific_age(int age){
	
	if(!head) printf("udah kosong bang udah bang\n\n");
	else if(head->age == age) pop_head();
	else if(tail->age == age) pop_tail();
	else pop_search_age(age);
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

// Uncommand either string or integer (NOT BOTH)
// Kalo di uncommand dua"nya yang jalan yang /* Integer */ dibawah /* String */
int main(){
	
	/* String */
//	push_priority_queue_name(create_node("Hans", 17));
//	push_priority_queue_name(create_node("Valen", 16));
//	push_priority_queue_name(create_node("William", 18));
//	push_priority_queue_name(create_node("Declan", 18));
//	push_priority_queue_name(create_node("Ricko", 30));
//	push_priority_queue_name(create_node("Albert", 20));
//	push_priority_queue_name(create_node("Lery", 50));
//	push_priority_queue_name(create_node("Mekel", 7));
//	push_priority_queue_name(create_node("Pepeng", 12));
//	push_priority_queue_name(create_node("Han", 40));
//	
//	pop_specific_name("Declan");
//	pop_specific_name("Albert");
//	pop_specific_name("Mekel");
	
	/* Integer */
//	push_priority_queue_age(create_node("Hans", 17));
//	push_priority_queue_age(create_node("Valen", 16));
//	push_priority_queue_age(create_node("William", 18));
//	push_priority_queue_age(create_node("Declan", 18));
//	push_priority_queue_age(create_node("Ricko", 30));
//	push_priority_queue_age(create_node("Albert", 20));
//	push_priority_queue_age(create_node("Lery", 50));
//	push_priority_queue_age(create_node("Mekel", 7));
//	push_priority_queue_age(create_node("Pepeng", 12));
//	push_priority_queue_age(create_node("Han", 40));
//
//	pop_specific_age(18);
//	pop_specific_age(20);
//	pop_specific_age(7);
	
	display();
	
	return 0;
}
