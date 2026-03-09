#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <windows.h>
#include <conio.h>

struct vehicle{
	
	char code[11];
	char ownerName[21];
	char type[11];
	short inTime;
	char status[4];
	
	struct vehicle* left;
	struct vehicle* right;
};

struct vehicle* root = NULL;

/* --------------------------- */

void any_key_to_continue(){
	
	printf(" Press any key to continue...");
	_getch();
	system("cls");
}

void hide_cursor(){
	
	printf("\e[?25l");
	fflush(stdout);
}

void show_cursor(){
	
	printf("\e[?25h");
	fflush(stdout);
}

/* --------------------------- */

struct vehicle* create_leaf(char* code, char* name, char* type, short time, char* status){
	
	struct vehicle* newLeaf = (struct vehicle*)malloc(sizeof(struct vehicle));
	
	newLeaf->left = newLeaf->right = NULL;
	
	strcpy(newLeaf->code, code);
	strcpy(newLeaf->ownerName, name);
	strcpy(newLeaf->type, type);
	newLeaf->inTime = time;
	strcpy(newLeaf->status, status);
	
	return newLeaf;
}

struct vehicle* insert_leaf(struct vehicle* curr, char* code, char* name, char* type, short time, char* status){
	
	if(!curr) return create_leaf(code, name, type, time, status);
	
	if(strcmp(code, curr->code) > 0) curr->left = insert_leaf(curr->left, code, name, type, time, status);
	else if(strcmp(code, curr->code) <= 0) curr->right = insert_leaf(curr->right, code, name, type, time, status);
	
	return curr;
}

void generate_random_code(char* code){
	
	srand(time(0));
	strcpy(code, "B ");
	
	for(short i = 0; i < 4; i++)	
		code[2 + i] = rand() % 10 + '0';	
	code[6] = ' ';
	
	for(short i = 0; i < 3; i++)
		code[7 + i] = rand() % 26 + 'A';
	code[10] = '\0';
}

void show_data_in(char* code, char* name, char* type, short time, char* status){
	
	system("cls");
	printf(" VEHICLE PARKED IN\n");
	printf(" -------------------------------------------------------------------\n\n");
	
	printf(" Vehicle's code: %s\n", code);
	printf(" Owner's name  : %s\n", name);
	printf(" Vehicle's type: %s\n", type);
	printf(" In time       : %hd\n", time);
	printf(" Status        : %s\n\n", status);
}

void park_in(){ // MENU 1
	
	show_cursor();
	system("cls");
	printf(" PARK VEHICLE\n");
	printf(" ===================================================================\n\n");
	
	char code[11] = {0};
	generate_random_code(code);
	
	char name[21] = {0};
	while(strlen(name) < 5 || strlen(name) > 20 || !strstr(name, " ")){
		printf(" Input owner's name [5-20 characters, at least two words]: ");
		scanf(" %[^\n]", name);
	}
	
	short time = 0;
	while(time < 6 || time > 9){
		printf(" Input in time [6 A.M. - 9 A.M.]: ");
		if(!scanf("%hd", &time))
			while(getchar() != '\n') time = 0;
	}
	
	char type[11] = {0};
	while(strcmp(type, "Sedan") && strcmp(type, "Truck") && strcmp(type, "Motorcycle")){
		printf(" Input vehicle's type [Sedan || Truck || Motorcycle]: ");
		scanf(" %s", type);
	}
	
	char status[4] = {0};
	strcpy(status, "IN");
	
	root = insert_leaf(root, code, name, type, time, status);
	
	hide_cursor();
	show_data_in(code, name, type, time, status);
	
	printf(" Data added successfully!\n");
	any_key_to_continue();
}

/* --------------------------- */

void view_pre_order(struct vehicle* curr){
	
	if(curr){
		printf(" %-13s %-23s %-19s %-5hd %s\n", curr->code, curr->ownerName, curr->type, curr->inTime, curr->status);
		view_pre_order(curr->left);
		view_pre_order(curr->right);
	}
}

void view_in_order(struct vehicle* curr){
	
	if(curr){
		view_in_order(curr->left);
		printf(" %-13s %-23s %-19s %-5hd %s\n", curr->code, curr->ownerName, curr->type, curr->inTime, curr->status);
		view_in_order(curr->right);
	}
}

void view_post_order(struct vehicle* curr){
	
	if(curr){
		view_post_order(curr->left);
		view_post_order(curr->right);
		printf(" %-13s %-23s %-19s %-5hd %s\n", curr->code, curr->ownerName, curr->type, curr->inTime, curr->status);
	}
}

void view_parking_data(){ // MENU 2
	
	system("cls");
	if(!root) printf(" There's no vehicle parked in!\n\n");
	else{
		printf(" PRE-ORDER\n");
		printf(" ===================================================================\n");
		printf(" %-13s %-23s %-13s %-8s %s\n", "CODE", "OWNER", "TYPE", "IN-TIME", "STATUS");
		printf(" -------------------------------------------------------------------\n");	
		view_pre_order(root);
		printf("\n\n\n");
		
		printf(" IN-ORDER\n");
		printf(" ===================================================================\n");
		printf(" %-13s %-23s %-13s %-8s %s\n", "CODE", "OWNER", "TYPE", "IN-TIME", "STATUS");
		printf(" -------------------------------------------------------------------\n");		
		view_in_order(root);
		printf("\n\n\n");
		
		printf(" POST-ORDER\n");
		printf(" ===================================================================\n");
		printf(" %-13s %-23s %-13s %-8s %s\n", "CODE", "OWNER", "TYPE", "IN-TIME", "STATUS");
		printf(" -------------------------------------------------------------------\n");
		view_post_order(root);
		printf("\n\n\n");
	}
	
	any_key_to_continue();
}

/* --------------------------- */

short check_type(char* type){
	
	if(!strcmp(type, "Sedan")) return 1; 
    else if(!strcmp(type, "Truck")) return 2;
    else return 3;
}

void show_data_out(struct vehicle* curr, short timeOut){
	
	system("cls");
	printf(" VEHICLE PARKED OUT\n");
	printf(" -------------------------------------------------------------------\n\n");
	
	printf(" Vehicle's code: %s\n", curr->code);
	printf(" Owner's name  : %s\n", curr->ownerName);
	printf(" Vehicle's type: %s\n", curr->type);
	printf(" In time       : %hd\n", curr->inTime);
	printf(" Out time      : %hd\n", timeOut);
	printf(" Status        : %s\n", curr->status);
	
	int pay = 0;
	switch(check_type(curr->type)){
		case 1:
			pay = (timeOut - curr->inTime) * 3000;
		break;
		case 2:
			pay = (timeOut - curr->inTime) * 4000;
		break;
		case 3:
			pay = (timeOut - curr->inTime) * 2000;
		break;
	}
	printf(" Payment       : %d\n\n", pay);
}

struct vehicle* find_code(struct vehicle* curr, char* code){
	
	if(!curr) return NULL;
	
	if(strcmp(code, curr->code) > 0) return find_code(curr->left, code);
	else if(strcmp(code, curr->code) < 0) return find_code(curr->right, code);
	else return curr;
}

void check_data(struct vehicle* data){
	
	if(!data) printf("\n Vehicle not found!\n");
	else if(!strcmp(data->status, "OUT")) printf("\n Vehicle parked out already!\n");
	else{
		show_cursor();
		strcpy(data->status, "OUT");
		
		short time = 0;
		while(time < 10 || time > 18){
			printf(" Input out time [10 A.M. - 18 P.M.]: ");
			if(!scanf("%hd", &time))
				while(getchar() != '\n') time = 0;
		}
		
		hide_cursor();
		show_data_out(data, time);
	}
}

void park_out(){ // MENU 3
	
	system("cls");
	if(!root) printf(" There's no vehicle parked in!\n\n");
	else{
		show_cursor();
		printf(" LIST OF VEHICLE(s)\n");
		printf(" ===================================================================\n");
		printf(" %-13s %-23s %-13s %-8s %s\n", "CODE", "OWNER", "TYPE", "IN-TIME", "STATUS");
		printf(" -------------------------------------------------------------------\n");
		view_in_order(root);
		printf("\n\n");
		
		char code[11] = {0};
		printf(" Input vehicle's code: ");
		scanf(" %[^\n]", code);
		
		struct vehicle* data = find_code(root, code);
		
		hide_cursor();
		check_data(data);
	}
	
	any_key_to_continue();
}

/* --------------------------- */

struct vehicle* pop_tree(struct vehicle* curr){
	
	if(!curr) return curr;
	
	pop_tree(curr->left);
	pop_tree(curr->right);
	free(curr);
	
	return NULL;
}

void close_parking(){ // MENU 4
	
	system("cls");
	
	root = pop_tree(root);
	
	printf(" All data cleared!\n");
	printf(" Closing parking lot..\n\n");
	
	any_key_to_continue();
	
	exit(0);
}

/* --------------------------- */

void menu(){
	
	printf(" VEHICLE - PARK ARENA\n");
	printf(" ===================================================================\n\n");
	printf(" [1] Register New Vehicle\n");
	printf(" [2] View Existing Vehicle(s)\n");
	printf(" [3] Remove Vehicle\n");
	printf(" [4] Exit\n");
}

int main(){
	
    while(true){
		hide_cursor();
    	menu();
    	
    	switch(_getch()){
    		case '1':
    			park_in();
    		break;
    		case '2':
    			view_parking_data();
    		break;
    		case '3':
    			park_out();
    		break;
    		case '4': 
    			close_parking();
    		break;
    		default:
    			system("cls");
		}
	}
}
