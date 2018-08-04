#include <stdio.h>
#include <stdlib.h>
#define CAPACITY 10

int parent(int i) {
	return (i - 1) / 2;	
}

int left(int i) {
	return 2 * i + 1;
}

int right(int i) {
	return 2 * i + 2;
}

void swap(int *a, int *b) {
	int temp = *a;
	*a = *b;
	*b = temp;
}

void print_heap_array(int heap_array[], int size) {
	for(int i = 0; i < size; ++i) {
		printf("%d ", heap_array[i]);
	}
	printf("\n");
}

void bubble_up(int heap_array[], int i) {
	while(i > 0 && heap_array[parent(i)] > heap_array[i]) {
		swap(&heap_array[i], &heap_array[parent(i)]);
		i = parent(i);
	} 
}

void bubble_down(int heap_array[], int size, int i) {
	int min;
	if(left(i) < size && heap_array[left(i)] < heap_array[i]) {
		min = left(i);
	} else {
		min = i;
	}
	if(right(i) < size && heap_array[right(i)] < heap_array[min]) {
		min = right(i);
	}
	if(min != i) {
		swap(&heap_array[i], &heap_array[min]);
		bubble_down(heap_array, size, min);
	}
}

void build_min_heap(int heap_array[], int size) {
	for(int i = size / 2; i >= 0; --i) {
		bubble_down(heap_array, size, i);
	}
}

int extract_min(int heap_array[], int *size) {
	int min = heap_array[0];
	swap(&heap_array[0], &heap_array[*size - 1]);
	*size -= 1;
	bubble_down(heap_array, *size, 0);
	return min;
}

void decrease_key(int heap_array[], int index, int new_key) {
	heap_array[index] = new_key;
	bubble_up(heap_array, index);
}

void heap_sort_descending(int heap_array[], int size) {
	build_min_heap(heap_array, size);
	for(int i = size - 1; i > 0; --i) {
		swap(&heap_array[0], &heap_array[i]);
		--size;
		bubble_down(heap_array, size, 0);
	}
}

int main() {
	int heap_array[CAPACITY] = {10, 7, 3, 6, 1, 5, 4, 2, 9, 8}, size = CAPACITY;
	print_heap_array(heap_array, size);
	build_min_heap(heap_array, size);
	print_heap_array(heap_array, size);
	printf("Min: %d\n", extract_min(heap_array, &size));
	print_heap_array(heap_array, size);
	printf("Decreasing key at index: %d to %d\n", 7, 1);
	decrease_key(heap_array, 7, 1);
	print_heap_array(heap_array, size);
	heap_sort_descending(heap_array, size);
	print_heap_array(heap_array, size);
	return 0;
}
