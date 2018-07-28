#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 5

// HEAD = Index of first element
// TAIL = Index of last element

int HEAD, TAIL, SIZE;
int queue[CAPACITY];

int empty() {
	return HEAD == -1;
}

int full() {
	if(HEAD == 0) {
		return TAIL == CAPACITY - 1;
	}
	return TAIL == HEAD - 1;
}

void enqueue(int data) {
	if(!full()) {
		if (empty()) {
			HEAD = TAIL = 0;
			queue[HEAD] = data;
		} else {
			TAIL = (TAIL + 1) % CAPACITY;
		    queue[TAIL] = data;
		}
	} else {
		printf("ERROR: OVERFLOW\n");
	}
}

void dequeue() {
	if(!empty()) {
		if(HEAD == TAIL) {
			HEAD = TAIL = -1;
		} else {
			HEAD = (HEAD + 1) % CAPACITY;
		}
	} else {
		printf("ERROR: UNDERFLOW\n");
	}
}

void show() {
	if(!empty()) {
		if(HEAD <= TAIL) {
			for(int i = HEAD; i <= TAIL; ++i) {
				printf("%d ", queue[i]);
			}			
		} else {
			for(int i = HEAD; i < CAPACITY; ++i) {
				printf("%d ", queue[i]);
			}
			for(int i = 0; i <= TAIL; ++i) {
				printf("%d ", queue[i]);
			}
		}
	}
	printf("\n");
}

int main() {
    HEAD = TAIL = -1;
    enqueue(1);
    enqueue(2);
    enqueue(3);
    enqueue(4);
    enqueue(5);
    enqueue(6);
    show();
    dequeue();
    dequeue();
    dequeue();
    dequeue();	
    dequeue();
    dequeue();
    show();
    return 0;
}
