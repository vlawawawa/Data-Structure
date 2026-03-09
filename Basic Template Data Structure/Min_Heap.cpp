#include <stdio.h>

int minHeap[100] = {0};
int lastIndex = 0;

int get_parent_index(int index) { return (index - 1) / 2; }
int get_left_child(int index)   { return 2 * index + 1;   }
int get_right_child(int index)  { return 2 * index + 2;   }

void swap(int* a, int* b){
	
	int temp = *a;
	*a = *b;
	*b = temp;
	
}

void up_heap(int index){
	
	if(index <= 0) return;
	
	int parentIndex = get_parent_index(index);
	if(minHeap[parentIndex] <= minHeap[index]) return;
	
	swap(&minHeap[parentIndex], &minHeap[index]);
	up_heap(parentIndex);
	
}

void push(int value){ 

	minHeap[lastIndex++] = value; 
	up_heap(lastIndex - 1);

}

void down_heap(int index){
	
	if(index >= lastIndex) return;
	
	int smallestIndex = index, leftChildIndex = get_left_child(index), rightChildIndex = get_right_child(index);	
	if(leftChildIndex < lastIndex && minHeap[leftChildIndex] < minHeap[smallestIndex]) smallestIndex = leftChildIndex;
	if(rightChildIndex < lastIndex && minHeap[rightChildIndex] < minHeap[smallestIndex]) smallestIndex = rightChildIndex;
	
	if(smallestIndex == index) return;
	
	swap(&minHeap[smallestIndex], &minHeap[index]);
	down_heap(smallestIndex);
	
}

void pop(){
	
	if(lastIndex == 0) return;
	
	swap(&minHeap[0], &minHeap[lastIndex - 1]);
	lastIndex--;
	
	down_heap(0);
	
}

int find_min() { return minHeap[0]; }

int main(){
	
	push(18);
	push(22);
	push(45);
	push(12);
	push(43);
	push(67);
	push(89);
	push(56);
	push(29);
	push(33);
	push(67);
	push(73);
	
	for(int i = 0; i < lastIndex; i++) printf("minHeap[%02d]: %d\n", i, minHeap[i]);
	
	pop();
	
	printf("\nMin = %d\n", find_min());
	for(int i = 0; i < lastIndex; i++) printf("minHeap[%02d]: %d\n", i, minHeap[i]);
	
	int num_data = lastIndex;
	for(int i = 0; i < num_data; i++){
		printf("Delete: %d\n", minHeap[0]);
		pop();
	}
	
	return 0;
	
}
