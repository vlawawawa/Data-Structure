#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <windows.h>

#define ALPHABET_SIZE 68

/* Utils */

bool firstMenu = true;

void Title(){
	
	printf(" =======================================================  \n\n"); if(firstMenu) Sleep(200);
	printf("  BBBBB                                    LL             \n");   if(firstMenu) Sleep(200);
	printf(" BB   BB                                   LL             \n");   if(firstMenu) Sleep(200);
	printf(" BB   BB                               GG  LL             \n");   if(firstMenu) Sleep(200);
	printf(" BB  BB      OOOOO      OOOOO      GGGGG   LL    EEEEE    \n");   if(firstMenu) Sleep(200);
	printf(" BB   BB    OO   OO    OO   OO    GG   GG  LL   EE   EE   \n");   if(firstMenu) Sleep(200);
	printf(" BB    BB  OO     OO  OO     OO  GG    GG  LL  EE  EEEEE  \n");   if(firstMenu) Sleep(200);
	printf(" BB   BB    OO   OO    OO   OO    GG   GG  LL   EE        \n");   if(firstMenu) Sleep(200);
	printf("  BBBBB      OOOOO      OOOOO      GGGGG   LL    EEEEE    \n");   if(firstMenu) Sleep(200);
	printf("                                       GG                 \n");   if(firstMenu) Sleep(200);
	printf("                                       GG                 \n");   if(firstMenu) Sleep(200);
	printf("                                  GG   GG                 \n");   if(firstMenu) Sleep(200);
	printf("                                   GGGGG                  \n\n"); if(firstMenu) Sleep(200);
	printf(" =======================================================  \n\n"); if(firstMenu) Sleep(200);
	
	firstMenu = false;
	
}
 
void Press_Any_Key_To_Continue(){
	
	printf(" >> Press any key to continue...");
	_getch();
	system("cls");
	
}

void Hide_Cursor(){
	
	printf("\e[?25l");
	fflush(stdout);
	
}

void Show_Cursor(){
	
	printf("\e[?25h");
	fflush(stdout);
	
}

/* 1. Release a new slang word */

void Release_Guide(){
	
	Title();
	
	printf(" << ");
	const char* message1 = "Release Guide :\n";
	for(int i = 0; message1[i] != '\0'; i++){ 
		printf("%c", message1[i]); 
		Sleep(50);
	}
	printf(" << ");
	const char* message2 = "1. Release new slang into the dictionary!\n"; 
	for(int i = 0; message2[i] != '\0'; i++){ 
		printf("%c", message2[i]); 
		Sleep(50); 
	}
	printf(" << ");
	const char* message3 = "2. If slang exist already, you will change the description!\n\n"; 
	for(int i = 0; message3[i] != '\0'; i++){ 
		printf("%c", message3[i]); 
		Sleep(50); 
	}
	
	Press_Any_Key_To_Continue();
	
}

void Validate_Word(char* word){
	
	if(strlen(word) > 1) printf(" << Slang word more than 1 character [v]\n"); 
	else printf(" << Slang word more than 1 character [ ]\n"); 
	if(!strchr(word, ' ')) printf(" << Slang word contains no space [v]\n\n"); 
	else printf(" << Slang word contains no space [ ]\n\n"); 
	
}

void Validate_Description(char* space){
	
	if(space && (isalnum(space[1]) || ispunct(space[1]))) printf(" << Description more than 1 word [v]\n\n"); 
	else printf(" << Description more than 1 word [ ]\n\n"); 
	
}

typedef struct Trie{
	
	Trie* alphaNumeric[ALPHABET_SIZE]; 
	bool isWord; 
	
	char* description; 
	
} node;

node* Create(){
	
	node* newNode = (node*)malloc(sizeof(node)); 
	
	for(int i = 0; i < ALPHABET_SIZE; i++) newNode->alphaNumeric[i] = NULL; 
	newNode->isWord = false; 
	
	return newNode; 
	
}

node* ROOT = Create();

void Insert(node* curr, char* word, char* description){
	
	int character = 0;
	while(*word){ 
		if(isalpha(*word) && isupper(*word)) character = *word - 'A';
		if(isalpha(*word) && islower(*word)) character = *word - 'a'; 
		if(isdigit(*word)) character = *word - '0' + 26; 
		if(ispunct(*word) && '!' <= *word && *word <= '/') character = *word - '!' + 36; 
		if(ispunct(*word) && ':' <= *word && *word <= '@') character = *word - ':' + 51; 
		if(ispunct(*word) && '[' <= *word && *word <= '`') character = *word - '[' + 58; 
		if(ispunct(*word) && '{' <= *word && *word <= '~') character = *word - '{' + 64;
		
		if(!curr->alphaNumeric[character]) curr->alphaNumeric[character] = Create(); 
		curr = curr->alphaNumeric[character]; 
		
		word++;	
	}
	
	system("cls");
	Title();
	if(curr->isWord){ 
		printf(" << The slang exist already in the dictionary,\n");
		printf(" << Description updated!\n\n");
		free(curr->description); 
	} else{ 
		printf(" << New slang has been released into the dictionary!\n\n");
		curr->isWord = true; 
	}
	
	curr->description = (char*)malloc(strlen(description) * sizeof(char) + 1);
	strcpy(curr->description, description); 
	
	Press_Any_Key_To_Continue();
	
}

bool notGuided = true;

void Release_New_Slang(){
	
	system("cls"); 
	
	if(notGuided){ 
		Release_Guide();
		notGuided = false;
	}
	
	Show_Cursor(); 
	
	int i = 0; 
	char word[256] = {0}; 
	while(true){ 
		system("cls");		
		Title();
		
		Validate_Word(word); 
		
		printf(" >> Input slang word ['Esc' to return to menu]: %s", word);
		
		char ch = _getch(); 
		
		if(ch == '\e'){ 
			Hide_Cursor(); 
			return;	
		} 
		if(ch == '\r'){ 
			if(strlen(word) > 1 && !strchr(word, ' ')) break; 
			else continue; 
		}
		if(ch == '\b' && i > 0) word[--i] = '\0';
		if((isalnum(ch) || ispunct(ch) || isspace(ch)) && i < 255){ 
			word[i++] = ch;
			word[i] = '\0';
		}		
	}
	
	i = 0; 
	char description[256] = {0};
	while(true){ 
		system("cls");	
		Title();
		
		printf(" << Slang word: \"%s\"\n\n", word);
		
		char* space = strchr(description, ' '); 
		Validate_Description(space); 
		
		printf(" >> Input description ['Esc' to return to menu]: %s", description);
		
		char ch = _getch();	
	
		if(ch == '\e'){ 
			Hide_Cursor(); 
			return; 
		}
		if(ch == '\r'){ 
			if(space && (isalnum(space[1]) || ispunct(space[1]))) break; 
			else continue; 
		}
		if(ch == '\b' && i > 0) description[--i] = '\0'; 
		if((isalnum(ch) || ispunct(ch) || isspace(ch)) && i < 255){ 
			description[i++] = ch; 
			description[i] = '\0';
		}			
	} 
	
	Hide_Cursor(); 
	printf("\n\n");
	
	Insert(ROOT, word, description); 
	
	return; 
	
}

/* 2. Search a slang word */

node* Search(node* curr, char* word){
	
	int character = 0;
	while(*word){
		if(isalpha(*word) && isupper(*word)) character = *word - 'A';
		if(isalpha(*word) && islower(*word)) character = *word - 'a';
		if(isdigit(*word)) character = *word - '0' + 26;
		if(ispunct(*word) && '!' <= *word && *word <= '/') character = *word - '!' + 36;
		if(ispunct(*word) && ':' <= *word && *word <= '@') character = *word - ':' + 51;
		if(ispunct(*word) && '[' <= *word && *word <= '`') character = *word - '[' + 58;
		if(ispunct(*word) && '{' <= *word && *word <= '~') character = *word - '{' + 64;
		
		if(!curr->alphaNumeric[character]) return NULL;
		
		curr = curr->alphaNumeric[character];
		
		word++;	
	}
	
	return curr;
	
}

void Search_Slang(){
	
	system("cls");
	
	Show_Cursor();
	
	int i = 0;
	char word[256] = {0};
	while(true){
		system("cls");		
		Title();
		
		Validate_Word(word);
		
		printf(" >> Input slang word ['Esc' to return to menu]: %s", word);
		
		char ch = _getch();
		
		if(ch == '\e'){
			Hide_Cursor();
			return;	
		} 
		if(ch == '\r'){
			if(strlen(word) > 1 && !strchr(word, ' ')) break;
			else continue;
		} 
		if(ch == '\b' && i > 0) word[--i] = '\0';			
		if((isalnum(ch) || ispunct(ch) || isspace(ch)) && i < 255){
			word[i++] = ch;
			word[i] = '\0';
		}		
	}
	
	Hide_Cursor();
	printf("\n\n");
	
	node* found = Search(ROOT, word);
	
	system("cls");
	Title();
	if(found && found->isWord){
		printf(" << Slang word  : %s\n", word);
		printf(" << Description : %s\n\n", found->description);
	} else{
		printf(" << The slang \"%s\" is not in the dictionary\n\n", word);
	}
	
	Press_Any_Key_To_Continue();
	
}

/* 3. View all slang words starting with a certain prefix word */

void Validate_Prefix(char* prefix){
	
	if(strlen(prefix) > 1) printf(" << Prefix more than 1 character [v]\n");
	else printf(" << Prefix more than 1 character [ ]\n");
	if(!strchr(prefix, ' ')) printf(" << Prefix contains no space [v]\n\n");
	else printf(" << Prefix contains no space [ ]\n\n");
	
}

bool alreadyDigit = false;
bool alreadySpecial = false;

void Display(node* curr, char* word, int index, int* num){
	
	if(curr->isWord){
        word[index] = '\0';
        printf(" << %d. %s\n", (*num)++, word);
    }

    for(int i = 0; i < ALPHABET_SIZE; i++){
    	if(curr == ROOT && curr->alphaNumeric[i] && i < 26){
			printf(" << ~ %c ~\n", 'A' + i);
			*num = 1;
		} else if(curr == ROOT && curr->alphaNumeric[i] && 26 <= i && i < 36 && !alreadyDigit){
			printf(" << ~ DIGITS ~\n");
			*num = 1;
			alreadyDigit = true;
		} else if(curr == ROOT && curr->alphaNumeric[i] && 36 <= i && i < 68 && !alreadySpecial){
			printf(" << ~ SPECIAL CHARACTERS ~\n");
			*num = 1;
			alreadySpecial = true;
		}
    	
        if(curr->alphaNumeric[i] && i < 26 && index == 0){ 
			word[index] = 'A' + i;
			Display(curr->alphaNumeric[i], word, index + 1, num);
		} 
		else if(curr->alphaNumeric[i] && i < 26){
			word[index] = 'a' + i;
			Display(curr->alphaNumeric[i], word, index + 1, num);
		}
		if(curr->alphaNumeric[i] && 26 <= i && i < 36){
			word[index] = i + '0' - 26;
			Display(curr->alphaNumeric[i], word, index + 1, num);
		}
		if(curr->alphaNumeric[i] && 36 <= i && i < 51){
			word[index] = i + '!' - 36;
			Display(curr->alphaNumeric[i], word, index + 1, num);
		}
		if(curr->alphaNumeric[i] && 51 <= i && i < 58){
			word[index] = i + ':' - 51;
			Display(curr->alphaNumeric[i], word, index + 1, num);
		}
		if(curr->alphaNumeric[i] && 58 <= i && i < 64){
			word[index] = i + '[' - 58;
			Display(curr->alphaNumeric[i], word, index + 1, num);
		}
		if(curr->alphaNumeric[i] && 64 <= i && i < 68){
			word[index] = i + '{' - 64;
			Display(curr->alphaNumeric[i], word, index + 1, num);
		}
		
		if(curr == ROOT && curr->alphaNumeric[i] && i < 26) printf("\n");
		else if(curr == ROOT && i == 35 && alreadyDigit){
			printf("\n");
			alreadyDigit = false;
		} 
		else if(curr == ROOT && i == 67 && alreadySpecial){
			printf("\n");
			alreadySpecial = false;
		}
    }
	
}

void View_With_Prefix(){
	
	system("cls");
	
	Title();
	
	Show_Cursor();
	
	int i = 0;
	char prefix[256] = {0};
	while(true){
		system("cls");		
		Title();
		
		Validate_Prefix(prefix);
		
		printf(" >> Input the prefix ['Esc' to return to menu]: %s", prefix);
		
		char ch = _getch();
		
		if(ch == '\e'){
			Hide_Cursor();
			return;	
		} 
		if(ch == '\r'){
			if(strlen(prefix) > 1 && !strchr(prefix, ' ')) break;
			else continue;
		}
		if(ch == '\b' && i > 0) prefix[--i] = '\0';			
		if((isalnum(ch) || ispunct(ch) || isspace(ch)) && i < 255){
			prefix[i++] = ch;
			prefix[i] = '\0';
		}		
	}
	
	Hide_Cursor();
	printf("\n\n");
	
	int num = 1;
	char word[256] = {0};
	strcpy(word, prefix);	
	node* found = Search(ROOT, word);
	
	system("cls");
	Title();
	if(found){
		printf(" << Slang found in the dictionary with prefix \"%s\" :\n", prefix);
		Display(found, word, strlen(prefix), &num);
	}
	else printf(" << The slang with the prefix \"%s\" is not in the dictionary\n", prefix);
	
	printf("\n");
	
	Press_Any_Key_To_Continue();
	
}

/* 4. View all slang words */

void View_All(){
	
	system("cls");
	
	Title();
	
	bool thereIsWord = false;
	
	for(int i = 0; i < ALPHABET_SIZE; i++){
		if(ROOT->alphaNumeric[i]){
			thereIsWord = true;
			break;
		}
	}
	
	if(thereIsWord){
		printf(" << Dictionary :\n\n");		
		int num = 1;
		char word[256] = {0};
		Display(ROOT, word, 0, &num);
	} else{
		printf(" << There is no word in the dictionary\n\n");
	}	
	
	Press_Any_Key_To_Continue();
	
}

/* 5. Exit */

void Exit(){
	
	system("cls");
	Title();
	
	printf(" << ");
	const char* message1 = "Until next time sigma,\n";
	for(int i = 0; message1[i] != '\0'; i++){
		printf("%c", message1[i]);
		Sleep(50);
	}	
	printf(" << ");
	const char* message2 = "Stay skibidi ohio and be a hydrated rizzler!";
	for(int i = 0; message2[i] != '\0'; i++){
		printf("%c", message2[i]);
		Sleep(50);
	}
	
	Sleep(1500);
	system("cls");
	
	exit(0);
	
}

/* MAIN PROGRAM */

void Menu_Guide(){
	
	Title();
	
	printf(" << "); 
	const char* message1 = "Welcome to Boogle,\n"; 
	for(int i = 0; message1[i] != '\0'; i++){ 
		printf("%c", message1[i]); 
		Sleep(50); 
	}
	printf(" << ");
	const char* message2 = "A place to release and find slang words!\n"; 
	for(int i = 0; message2[i] != '\0'; i++){
		printf("%c", message2[i]); 
		Sleep(50); 
	}
	
	printf("\n");
	
	printf(" << ");
	const char* message3 = "Press 'w' or 's' to navigate the menu,\n"; 
	for(int i = 0; message3[i] != '\0'; i++){ 
		printf("%c", message3[i]);
		Sleep(50); 
	}	
	printf(" << "); 
	const char* message4 = "Then 'Enter' to select!\n\n"; 
	for(int i = 0; message4[i] != '\0'; i++){ 
		printf("%c", message4[i]); 
		Sleep(50); 
	}
	
	Press_Any_Key_To_Continue();
	
}

char Menu(){
	
	char choice = '1'; 
	
	while(true){
		system("cls");
		
		Title();
		
		if(choice == '1') printf(" >> Release\n");
		else printf(" Release\n"); 
		
		if(choice == '2') printf(" >> Search\n");
		else printf(" Search\n");
		
		if(choice == '3') printf(" >> View with prefix\n");
		else printf(" View with prefix\n");
		
		if(choice == '4') printf(" >> View all\n");
		else printf(" View all\n");
		
		if(choice == '5') printf(" >> Exit\n");
		else printf(" Exit\n");
		
		
		switch(_getch()){
			case 'W':			
			case 'w':
				choice -= 1; 
				if(choice < '1') choice = '5'; 
			break;
			
			case 'S':
			case 's':
				choice += 1;
				if(choice > '5') choice = '1'; 
			break;
			
			case '\r': return choice; 
		}
	}
	
	return choice;
	
}

int main(){
	
	Hide_Cursor(); 
	
	Menu_Guide(); 
	
	while(true){ 		
		switch(Menu()){	
			case '1': Release_New_Slang();  break;
			case '2': Search_Slang();       break;
			case '3': View_With_Prefix();   break;
			case '4': View_All();           break;
			case '5': Exit();               break;			
		}				
	}
	
	return 0;
	
}
