#include <stdio.h>

#include <stdlib.h>

#include <stdbool.h>

 

typedef struct HeapStruct {

	int Capacity;

	int Size;

	int *Element;

}Heap;

 

Heap* CreateHeap(int heapSize);

void Insert(Heap* heap, int value);

void Find(Heap* heap, int value);

bool isFull(Heap* heap);

void main(int argc, char* argv[]) {

	FILE *fi = fopen(argv[1], "r");

	char cv;

	Heap* maxHeap = NULL;

	int heapSize, key;

	while (fscanf(fi, "%c", &cv) != EOF) {

		switch (cv) {

		case 'n':

			fscanf(fi, "%d", &heapSize);

			maxHeap = CreateHeap(heapSize);

			break;

		case 'i':

			fscanf(fi, "%d", &key);

			Insert(maxHeap, key);

			break;

			/*case 'p':

			for (int i = 1; i <= maxHeap->Size; i++) {

			printf("%d ", maxHeap->Element[i]);

			}

			printf("\n");

			break;*/

		case 'f':

			fscanf(fi, "%d", &key);

			Find(maxHeap, key);

			break;

		}

	}

	free(maxHeap->Element);

	free(maxHeap);

	fclose(fi);

}

 

Heap* CreateHeap(int heapSize) {

	Heap* newHeap = NULL;

	newHeap = (Heap*)malloc(sizeof(Heap));

	newHeap->Element = (int*)malloc(sizeof(int)*(heapSize + 1));

	newHeap->Capacity = heapSize;

	newHeap->Size = 0;

	return newHeap;

}

void Insert(Heap* heap, int value) {

 

	int i;

 

	for (i = 1; i <= heap->Size; i++) {

		if (heap->Element[i] == value) {

			printf("%d is already in the heap\n", value);

			return;

		}

	}

	int index;

	if (isFull(heap)) {

		printf("Insertion Error : Priority queue is full\n");

		return;

	}

	heap->Size++;

	for (index = heap->Size; index > 1 && heap->Element[index / 2] < value; index /= 2) {

		heap->Element[index] = heap->Element[index / 2];

	}

	heap->Element[index] = value;

	printf("insert %d\n", value);

}

 

bool isFull(Heap* heap) {

	if (heap->Capacity == heap->Size) {

		return true;

	}

	else {

		return false;

	}

}

 

void Find(Heap* heap, int value) {

	int index;

	for (index = 1; index <= heap->Size; index++) {

		if (heap->Element[index] == value) {

			printf("%d is in the heap\n", value);

			return;

		}

	}

	printf("%d is not in the heap\n", value);

}

