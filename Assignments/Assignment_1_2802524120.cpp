#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct doc{
	char name[101];
	int size;
	struct doc* prev;
	struct doc* next;
};

struct doc* head = NULL;
struct doc* tail = NULL;

void enter_to_continue(){
	
	getchar();
	printf(" Press enter to continue...");
	if(getchar() == '\n') printf("\e[H\e[2J");
}

/* --------------------------- */

struct doc* create_node(char* name, int size){
	
	struct doc* newDoc = (struct doc*)malloc(sizeof(struct doc));
	
	newDoc->prev = NULL;
	newDoc->next = NULL;
	
	strcpy(newDoc->name, name);
	newDoc->size = size;
	
	return newDoc;
}

void push_head(struct doc* newDoc){
	
	newDoc->next = head;
	head->prev = newDoc;
	head = newDoc;
}

void push_tail(struct doc* newDoc){
	
	newDoc->prev = tail;
	tail->next = newDoc;
	tail = newDoc;
}

void push_pq(struct doc* newDoc){
	
	if(!head) head = tail = newDoc;
	else if(newDoc->size > head->size) push_head(newDoc);
	else if(newDoc->size <= tail->size) push_tail(newDoc);
	else{
		struct doc* curr = head->next;
		while(curr->size <= newDoc->size) curr = curr->next;
		
		curr->next->prev = newDoc;
		newDoc->next = curr->next;
		
		curr->next = newDoc;
		newDoc->prev = curr;
	}
}

void register_new_document(){ // MENU 1
	
	printf("\e[H\e[2J");
	printf(" Register New Document\n");
	printf(" -----------------------------------------------------\n\n");
	
	char docName[101] = "";	
	while(!strcmp(docName, ".doc") || !strstr(docName, ".doc")){
		printf(" Input document name [*.doc]: ");
		scanf(" %[^\n]", docName);
	} 
	
	int docSize = -1;
	while(docSize < 1 || 9999 < docSize){
		printf(" Input document size [1-9999 kB]: ");
		if(!scanf("%d", &docSize)) 
			while(getchar() != '\n') docSize = -1;
	} 
	
	push_pq(create_node(docName, docSize));
	printf("\n Success registered new document!\n");
	enter_to_continue();
}

/* --------------------------- */

void view(){
	
	if(!head) printf(" There is no data!!\n\n");
	else{
		struct doc* curr = head;
		int num = 1;
		while(curr){
			printf("  %d. %-35s %d kB\n", num, curr->name, curr->size);
			curr = curr->next;
			num++;
		} printf("\n");
	}
}

void pop_head(){
	
	if(head == tail) head = tail = NULL;
	else{
		head = head->next;
		free(head->prev);
		head->prev = NULL;
	}	
}

void pop_tail(){
	
	if(head == tail) head = tail = NULL;
	else{
		tail = tail->prev;
		free(tail->next);
		tail->next = NULL;
	}	
}

void pop_specific(char* docName){
	
	struct doc* curr;
	if(head == tail) curr = head;
	else curr = head->next;
	while(strcmp(curr->name, docName) && curr != tail) curr = curr->next;
	
	if(curr == tail) printf("\n There is no match document with name: %s\n", docName);
	else{
		curr->prev->next = curr->next;
		curr->next->prev = curr->prev;
		printf("\n Document: %s (%d kB) successfully removed!\n", docName, curr->size);
		free(curr);
	}
}

void delete_document(char* docName){
	
	if(!strcmp(head->name, docName)){
		printf("\n Document: %s (%d kB) successfully removed!\n", docName, head->size);
		pop_head();
	} else if(!strcmp(tail->name, docName)){
		printf("\n Document: %s (%d kB) successfully removed!\n", docName, tail->size);
		pop_tail();
	} else pop_specific(docName);
}

void remove_document(){ // MENU 2
	
	printf("\e[H\e[2J");
	printf(" Remove Old Document\n");
	printf(" -----------------------------------------------------\n\n");
	view();
	
	if(!head){
		enter_to_continue();
		return;
	} else{
		char docName[101];
		printf(" Input document name [*.doc]: ");
		scanf(" %[^\n]", docName);
		
		delete_document(docName);
	}
		
	enter_to_continue();
}

/* --------------------------- */

void view_document(){ // MENU 3
	
	printf("\e[H\e[2J");
	printf(" View Existing File\n");
	printf(" -----------------------------------------------------\n\n");
	
	view();
	
	enter_to_continue();
}

/* --------------------------- */

void pop_all(){
	
	while(head) pop_head();
}

void exit_program(){ // MENU 4
	
	printf("\e[H\e[2J");
	printf(" All data successfully removed!");
	
	pop_all();
	
	getchar();
	exit(0);
}

/* --------------------------- */

short option(){
	
	short opt = 0;
	while(opt < 1 || 4 < opt){
		printf(" Choose: ");
		if(!scanf("%hd", &opt)) 
			while(getchar() != '\n') opt = 0;
	}
	
	return opt;
}

void menu(){
	
	printf(" Zzrot File Manager\n");
	printf(" =====================================================\n\n");
	printf(" 1. Register New Document\n");
	printf(" 2. Remove Document\n");
	printf(" 3. View Existing File\n");
	printf(" 4. Exit\n\n");
}

int main(){
	
	while(true){		
		menu();
		
		switch(option()){
			case 1:
				register_new_document();
			break;
			case 2:
				remove_document();
			break;
			case 3:
				view_document();
			break;
			case 4:
				exit_program();
			break;
		}
	}
}
