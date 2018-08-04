#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 10

int id[CAPACITY], sz[CAPACITY], size = CAPACITY;

void initialize_sets() {
	for(int i = 0; i < size; ++i) {
		id[i] = i;
		sz[i] = 1;
	}	
}

int root(int i) {
	while(i != id[i]) {
		id[i] = id[id[i]];
		i = id[i];
	}
	return i;
}

int unite(int p, int q) {
	int i = root(p);
	int j = root(q);
	if (i != j) {
		if(sz[i] < sz[j]) {
			id[i] = j;
			sz[j] += sz[i];	
		} else {
			id[j] = i;
			sz[i] += sz[j];
		}
	}
}

int find(int p, int q) {
	return root(p) == root(q);
}

void print_id() {
	for(int i = 0 ; i < size ; ++i) {
		printf("%d ", id[i]);
	}
	printf("\n");
}

int main() {
	initialize_sets();
	print_id();
	unite(1, 2);
	print_id();
	unite(2, 0);
	print_id();
	printf("%d\n", find(1, 0));
	return 0;	
}
