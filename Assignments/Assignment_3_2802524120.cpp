#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Product{
	
	long long price;
	char name[31];
	
	int height;
	Product* left;
	Product* right;
	
} node;

node* ROOT = NULL;

node* Create_node(long long price, char* name){
	
	node* newNode = (node*)malloc(sizeof(node));
	
	newNode->price = price;
	strcpy(newNode->name, name);
	
	newNode->height = 1;
	newNode->left = newNode->right = NULL;
	
	return newNode;
}

int Compare(int a, int b){
	
	return (a > b) ? a : b;
}

int Height(node* curr){
	
	if(!curr) return 0;
	return curr->height;
}

int Calculate_height(node* curr){
	
	return Compare(Height(curr->left), Height(curr->right)) + 1;
}

int Calculate_balance_factor(node* curr){
	
	return Height(curr->left) - Height(curr->right);
}

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

node* Insert(node* curr, long long price, char* name){
	
	if(!curr) return Create_node(price, name);
	else if(price < curr->price) curr->left = Insert(curr->left, price, name);
	else if(price > curr->price) curr->right = Insert(curr->right, price, name);
	
	curr->height = Calculate_height(curr);
	
	int balanceFactor = Calculate_balance_factor(curr);
	
	// left left
	if(balanceFactor > 1 && price < curr->left->price)
		return Right_rotate(curr);
		
	// right right	
	if(balanceFactor < -1 && price > curr->right->price)
		return Left_rotate(curr);		
		
	// left right
	if(balanceFactor > 1 && price > curr->left->price){
		curr->left = Left_rotate(curr->left);
		return Right_rotate(curr);
	}
		
	// right left
	if(balanceFactor < -1 && price < curr->right->price){
		curr->right = Right_rotate(curr->right);
		return Left_rotate(curr);
	}
	
	return curr;
}

void Insert_product(){
	
	long long price;
	char name[31];
	scanf("%lld %s", &price, name);
				
	ROOT = Insert(ROOT, price, name);
	printf("\n");
}

node* Get_predecessor(node* curr){
	
	while(curr->right) curr = curr->right;
	return curr;
}

node* Delete(node* curr, long long price){
	
	if(!curr) return NULL;
	else if(price < curr->price) curr->left = Delete(curr->left, price);
	else if(price > curr->price) curr->right = Delete(curr->right, price);
	else{
		if(!curr->left || !curr->right){
			node* temp = (curr->left) ? curr->left : curr->right;
			free(curr);
			return temp;
		}
		else{
			node* predecessor = Get_predecessor(curr->left);
			
			curr->price = predecessor->price;
			strcpy(curr->name, predecessor->name);
			
			curr->left = Delete(curr->left, predecessor->price);
		}
	}
	
	curr->height = Calculate_height(curr);
	
	int balanceFactor = Calculate_balance_factor(curr);
	
	// left left
	if(balanceFactor > 1 && Calculate_balance_factor(curr->left) >= 0)
		return Right_rotate(curr);
	
	// right right
	if(balanceFactor < -1 && Calculate_balance_factor(curr->right) <= 0)
		return Left_rotate(curr);
	
	// left right
	if(balanceFactor > 1 && Calculate_balance_factor(curr->left) < 0){
		curr->left = Left_rotate(curr->left);
		return Right_rotate(curr);
	}
	
	// right left
	if(balanceFactor < -1 && Calculate_balance_factor(curr->right) > 0){
		curr->right = Right_rotate(curr->right);
		return Left_rotate(curr);
	}
	
	return curr;
}

void Delete_product(){
	
	long long price;
	scanf("%lld", &price);
	
	ROOT = Delete(ROOT, price);
	printf("\n");
}

node* Search(node* curr, long long price){
	
    node* closest = NULL;
    long long min = llabs(curr->price - price);

    while(curr){
        long long diff = llabs(curr->price - price);

        if(diff <= min){
            min = diff;
            closest = curr;
        }

        if(price < curr->price) curr = curr->left;
        else if(price > curr->price) curr = curr->right;
        else break;
    }

    return closest;
}

void Find_similar_product(){
	
	long long price;
	scanf("%lld", &price);
	
	node* similar = Search(ROOT, price);
	if(similar) printf("%lld %s\n\n", similar->price, similar->name);
	else printf("There are no products\n\n");
}

void View_in_order(node* curr, int limit, int end, int* counter){
	
	if(!curr) return;
	
	View_in_order(curr->left, limit, end, counter);
	if(*counter <= end && *counter < limit) printf("%d: %lld %s\n", (*counter)++, curr->price, curr->name);
	View_in_order(curr->right, limit, end, counter);
}

//void View_pre_order(node* curr, int limit, int end, int* counter){
//	
//	if(!curr) return;
//	
//	if(*counter <= end && *counter < limit) printf("%d: %lld %s\n", (*counter)++, curr->price, curr->name);
//	View_pre_order(curr->left, limit, end, counter);
//	View_pre_order(curr->right, limit, end, counter);
//}

void Show_data_in_range(){
	
	int start, end;
	scanf("%d %d", &start, &end);
	
	int counter = start;
	View_in_order(ROOT, start + 10, end, &counter);
	printf("\n");
}

int main(){
	
	int numOfCase;
	scanf("%d", &numOfCase);
	printf("\n");
	
	for(int i = 0; i < numOfCase; i++){
		short operation;
		scanf("%hd", &operation);
		
		switch(operation){
			case 1: Insert_product();       break;	
			case 2: Delete_product();       break;
			case 3: Find_similar_product(); break;
			case 4: Show_data_in_range();   break;
		}
	}
	
	return 0;
}
