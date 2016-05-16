//
//  insertSort.c
//  ExerciseC
//
//  Created by lunner on 8/17/15.
//  Copyright (c) 2015 lunner. All rights reserved.
//
#include "sortHeaders.h"

//x-1 < [x]_ <= [x]- < x+1
//for any integer n, [n/2]_ + [n/2]- = n 

//a mod n = a - n[a/n]_ 
//0 ≤ a mod n < n 
//(a mod n) = (b mod n) if and only if n is a divisor of b - a.
//
// MARK: bubble sort
//[p, r)
void bubble_sort(int A[], int p, int r) {
	int i, j, tmp;
	for(i=p; i < r-1; i++) {
		for (j=r-1; j>i; j--) {
			if (A[j] < A[j-1])
			{
				tmp = A[j];
				A[j] = A[j-1];
				A[j-1] = tmp;
			}
		}
	}
}

void bubble_sink_sort(int A[], int p, int r) {
	int i, j, tmp;
	for (i=r-1; i>p; i--) {
		for (j=p; j < i; j++) {
			if (A[j] > A[j+1]) {
				EXCHANGE(A[j], A[j+1]);
			}
		}
	}
}

void bubble1_sort(int a[], int n) {
	int i, j, change, tmp;
	for(i = n-1, change = 1; i>=1&&change; --i) {
		change = 0;
		for(j = 0;j<i;++j) {
			if(a[j]>a[j+1]) {
				//a[j] <-->a[j+1];
				tmp = a[j];
				a[j] = a[j+1];
				a[j+1] = tmp;
				change = 1;
			}
		}
	}
}
// MARK: insertion sort
//[p,r)
void insertion_sort(int A[], int p, int r) {
	int i, j, key;
	for (j = p + 1; j < r; j++) {
		key = A[j];
		i = j - 1;
		while (i >= p && A[i] > key) {
			A[i + 1] = A[i];
			i = i - 1;
		}
		A[i + 1] = key;
	}
}//最坏O(n^2) stable

//void insertion_sort(int A[], int num) {
//    insertion_sort(A, 0, num);
//}

void binary_insertion_sort(int A[], int p, int r) {
	int i, j, key;
	int low, mid, high;
	for (j = p+1; j < r; j++) {
		key = A[j];
		low = p;
		high = j;
		while (low < high) {
			mid = (low + high) / 2;
			if (key < A[mid]) {
				high = mid;
			} else {
				low  = mid + 1;
			}
		}
		for (i = j - 1; i >= high; i--) {
			A[i+1] = A[i];
		}
		A[high] = key;
	}
}


// MARK: insert sort
void insert_sort(int *A, int num) {
	int i, j, key;
	for (i = 1; i < num; i++) {
		key = A[i];
		j = i-1;
		while ( j >= 0 && A[j] > key) {
			A[j+1] = A[j];
			j--;
		}
		A[j+1] = key;
	}
}
void binary_insert_sort(int *A, int num) {
	int i, j, key;
	int low, high, mid;
	for (i = 1; i < num; i++) {
		low = 0;
		high = i;
		key = A[i];
		while (low < high) {
			mid = (low + high) / 2;
			if (key < A[mid]) {
				high = mid;
			} else {
				low = mid + 1;
			}
		}
		for (j = i - 1; j >= high; j--) {
			A[j+1] = A[j];
		}
		A[high] = key;
	}
}

void insert_sort_recursive(int *A, int num) {
	int i, key;
	insert_sort_recursive(A, num - 1);
	i = num - 2;
	key = A[num-1];
	while (i >= 0 && key < A[i]) {
		A[i+1] = A[i];
		i--;
	}
	A[i+1] = key;
}

// MARK: selection sort
//[P, r)
void selection_sort(int A[], int p, int r) {
	int min, temp;
	int i, j;
	for (i = p; i < r-1; i++) {
		min = i;
		for (j = i + 1; j < r; j++)
			if (A[j] < A[min])
				min = j;
		temp = A[i];
		A[i] = A[min];
		A[min] = temp;
	}
}//O(n^2) unstable


// MARK: merge sort
//[start, end)
void merge(int A[], int p, int q, int r) {
	
	int i, j, k;
	
	int n1 = q - p;
	int n2 = r - q;
#define MERGE_HEAP_ALLOCATION
#ifdef MERGE_HEAP_ALLOCATION
	int *L = calloc(n1, sizeof(int));
	int *R = calloc(n2, sizeof(int));
#else
	int L[n1];//n1 should be sure while compiling, here maybe compile error
	int R[n2];
#endif
	
	memcpy(L, A + p, n1 * sizeof(int));
	memcpy(R, A + q, n2 * sizeof(int));
	
	for(i = 0, j = 0, k = p; k <= r; k++) {
		if (i == n1) {
			A[k] = R[j++];
		} else if (j == n2) {
			A[k] = L[i++];
		} else if (L[i] <= R[j]) {
			A[k] = L[i++];
		} else {
			A[k] = R[j++];
		}
	}
	
#ifdef MERGE_HEAP_ALLOCATION
	free(L);
	free(R);
#endif
}

void merge_sort(int A[], int p, int r) {
	if (p < r-1) {
		int q = (p + r) / 2;
		merge_sort(A, p, q);
		merge_sort(A, q, r);
		merge(A, p, q, r);
	}
}//nlog2(n) stable   ^[log2(n)]趟

// MARK: mixed merge sort
//#define INSERTION_SORT_TRESHOLD 20
//#define SELECTION_SORT_TRESHOLD 15
void mixed_merge_sort_insertion(int A[], int p, int r) {
	if (p >= r-1) return;
	
	if (r - p < INSERTION_SORT_TRESHOLD) {
		insertion_sort(A, p, r);
	} else {
		int q = (p + r) / 2;
		mixed_merge_sort_insertion(A, p, q);
		mixed_merge_sort_insertion(A, q, r);
		merge(A, p, q, r);
	}
}

void mixed_merge_sort_selection(int A[], int p, int r) {
	if (p >= r-1) return;
	
	if (r - p < SELECTION_SORT_TRESHOLD) {
		selection_sort(A, p, r);
	} else {
		int q = (p + r) / 2;
		mixed_merge_sort_selection(A, p, q);
		mixed_merge_sort_selection(A, q, r);
		merge(A, p, q, r);
	}
}



// MARK: heap sort
//C code
//#define PARENT(i) (((i) - 1) / 2)
//#define LEFT(i)   (2 * (i) + 1)
//#define RIGHT(i)  (2 * (i) + 2)
//#define EXCHANGE(A, B) do{\
//	tmp = A;\
//	A = B;\
//	B = tmp;\
//}while(0)
//typedef struct {
//	int *nodes;
//	int length;
//	int heap_size;
//} heap;

// When it is called, MAX- HEAPIFY assumes that the binary trees rooted at LEFT(i) and RIGHT(i) are max- heaps, but that A[i] might be smaller than its children
void max_heapify(heap *A, int i) {
	int left, right, largest, temp;
	
	while(1) {
		left  = LEFT(i);
		right = RIGHT(i);
		
		if (left < A->heap_size && A->nodes[left] > A->nodes[i])
			largest = left;
		else
			largest = i;
		
		if (right < A->heap_size && A->nodes[right] > A->nodes[largest])
			largest = right;
		
		if (largest == i)
			return;
		
		temp = A->nodes[i];
		A->nodes[i] = A->nodes[largest];
		A->nodes[largest] = temp;
		
		i = largest;
	}
}//O(lgn)

void max_heapify_recursive(heap *A, int i) {
	int left, right, largest, temp;
	left = LEFT(i);
	right = RIGHT(i);
	if (left < A->heap_size && A->nodes[left] > A->nodes[i])
		largest = left;
	else 
		largest = i;
	if (right < A->heap_size && A->nodes[right] > A->nodes[largest]) {
		largest = right;
	}
	if (largest != i) {
		temp = A->nodes[i];
		A->nodes[i] = A->nodes[largest];
		A->nodes[largest] = temp;
		max_heapify_recursive(A, largest);
	}
}

void build_max_heap(heap *A) {
	A->heap_size = A->length;
	int i;
	for (i = A->length/2; i>=0; i--) {
		max_heapify(A, i);
	}
}//linear time O(nlgn)

void heap_sort(heap *A) {
	int i;
	build_max_heap(A);
	for (i = A->length-1; i>0; i--) {
		int tmp;
		EXCHANGE(A->nodes[0], A->nodes[i]);
		A->heap_size--;
		max_heapify(A, 0);
	}
}//O(nlgn) stable

int heap_maximum(const heap *A) {
	return A->nodes[0];
}
int heap_extract_max(heap *A) {
	int max;
	if (A->heap_size < 1) {
		printf("heap underflow");
		return INT_MIN;
	}
	max = A->nodes[0];
	A->nodes[0] = A->nodes[A->heap_size-1];
	A->heap_size--;
	max_heapify(A, 0);
	return max;
}//O(lgn)

void heap_delete(heap* A, int i) {
	if (i >= A->heap_size) {
		return;
	}
	A->nodes[i] = A->nodes[A->heap_size-1];
	A->heap_size--;
	max_heapify(A, i);
}//O(lgn)


void heap_increase_key(heap* A, int i, int key) {
	int tmp;
	if (key < A->nodes[i]) {
		return;
	}  
	A->nodes[i] = key;
	while (i > 0 && A->nodes[PARENT(i)] < A->nodes[i]) {
		
		EXCHANGE(A->nodes[PARENT(i)], A->nodes[i]);
		i = PARENT(i);
	}
}//O(lgn)

void max_heap_insert(heap *A, int key) {
	A->heap_size++;
	A->nodes[A->heap_size] = INT_MIN;//
	heap_increase_key(A, A->heap_size-1, key);
}//O(lgn)


void build_max_heap_byinsert(heap *A) {
	int i;
	A->heap_size = 1;
	for (i = 1; i < A->length; i++) {
		max_heap_insert(A, A->nodes[i]);
	}
}

// MARK: d-ary heaps
//A d-ary heaps is like a binary heap, but non-leaf nodes have d children instead of 2 children.
//#include <stdio.h>
//#include <stdlib.h>
//#include <limits.h>
//
//#define DPARENT(i,d) ((i - 1) / d)
//#define DCHILD(i,c,d) (d * i + c + 1)

//typedef struct {
//	int *elements;
//	int d;
//	int heap_size;
//	int length;
//} heap_t;

void max_heapify_dary(heap_t *heap, int i) {
	int largest = i;
	
	for (int k = 0; k < heap->d; k++) {
		int child = DCHILD(i, k, heap->d);
		if (child < heap->heap_size && heap->elements[child] > heap->elements[largest])
			largest = child;
	}
	
	if (largest != i) {
		int tmp = heap->elements[i];
		heap->elements[i] = heap->elements[largest];
		heap->elements[largest] = tmp;
		
		max_heapify_dary(heap, largest);
	}
}

int extract_max(heap_t *heap) {
	int max = heap->elements[0];
	heap->elements[0] = heap->elements[heap->heap_size - 1];
	heap->heap_size--;
	max_heapify_dary(heap, 0);
	return max;
};

void increase_key(heap_t *heap, int i, int key) {
	
	if (key < heap->elements[i]) {
		fprintf(stderr, "new key is smaller than current key\n");
		return ;//exit(0);
	}
	
	while (i > 0 && heap->elements[DPARENT(i,heap->d)] < key) {
		heap->elements[i] = heap->elements[DPARENT(i,heap->d)];
		i = DPARENT(i,heap->d);
	}
	
	heap->elements[i] = key;
}

void insert(heap_t *heap, int key) {
	heap->heap_size++;
	heap->elements[heap->heap_size - 1] = INT_MIN;
	increase_key(heap, heap->heap_size - 1, key);
}

// MARK: priority queue A min-priority queue can be used in an event-driven simulator



// MARK: quick sort
#define K 550
int partition(int[], int, int);
void limited_quicksort(int[], int, int, int);
void insertion_sort(int[], int, int);
//[p,r)
void quicksort(int A[], int p, int r) {
	if (p < r - 1) {
		int q = partition(A, p, r);
		quicksort(A, p, q);
		quicksort(A, q, r);
	}
}

void modified_quicksort(int A[], int p, int r) {
	limited_quicksort(A, p, r, K);
	insertion_sort(A, p, r);
}

void limited_quicksort(int A[], int p, int r, int treshold) {
	if (r - p > treshold) {
		int q = partition(A, p, r);
		limited_quicksort(A, p, q, treshold);
		limited_quicksort(A, q, r, treshold);
	}
}
int randomized_partition(int A[], int p, int r) {
	int i, tmp;
	srand((unsigned int)time(0));
	i = rand() % (r - p) + p;
	EXCHANGE(A[i], A[r-1]);
	
	return partition(A, p, r);
}
int partition(int A[], int p, int r) {
	int x, i, j, tmp;
	
	x = A[r - 1];
	i = p;
	
	for (j = p; j < r - 1; j++) {
		if (A[j] <= x) {
			tmp = A[i];
			A[i] = A[j];
			A[j] = tmp;
			i++;
		}
	}
	
	tmp = A[i];
	A[i] = A[r - 1];
	A[r - 1] = tmp;
	
	return i;
}
// MARK: hoare partition
//#include <stdbool.h>

int hoare_partition(int A[], int p, int r) {
	int x = A[p],
	i = p - 1,
	j = r,
	tmp;
	
	while(true) {
		do { j--; } while (!(A[j] <= x));
		do { i++; } while (!(A[i] > x)); // is >= it is unstable
		
		if (i < j) {
			tmp = A[i]; A[i] = A[j]; A[j] = tmp;
		} else {
			return j;
		}
	}
}

void quicksort_hoare_partition(int A[], int p, int r) {
	if (p < r - 1) {
		int q = hoare_partition(A, p, r);
		quicksort_hoare_partition(A, p, q + 1);
		quicksort_hoare_partition(A, q + 1, r);
	}
}

// MARK tail recursive quicksort
/*void tail_recursive_quicksort(int A[], int p, int r) {
	while (p < r-1) {
		int q = partition(A, p, r);
		tail_recursive_quicksort(A, p, q-1);
		p = q+1; 
	}
}*/
//We are always doing a tail-recursive call on the second partition. We can modify the algorithm to do the tail recursion on the larger partition. That way, we'll consume less stack.
//C code
//#include <stdio.h>
#define ANALYZE_TAIL_RECURSIVE_QUICKSORT

#ifdef ANALYZE_TAIL_RECURSIVE_QUICKSORT
static int stack_depth = 0;
static int max_stack_depth = 0;
#endif

void reset_stack_depth_counter();
void increment_stack_depth();
void decrement_stack_depth();

void tail_recursive_quicksort(int A[], int p, int r) {
#ifdef ANALYZE_TAIL_RECURSIVE_QUICKSORT
	increment_stack_depth();
#endif
	
	while (p < r - 1) {
		int q = partition(A, p, r);
		
		if (q < (p + r) / 2) {
            tail_recursive_quicksort(A, q, r);//tail_recursive_quicksort(A, p, q);//
			r = q;
		} else {
            tail_recursive_quicksort(A, p, q);//tail_recursive_quicksort(A, q + 1, r);
			p = q;
		}
	}
#ifdef ANALYZE_TAIL_RECURSIVE_QUICKSORT
	decrement_stack_depth();
#endif
}


void increment_stack_depth() {
	stack_depth++;
	if (max_stack_depth < stack_depth) {
		max_stack_depth = stack_depth;
	}
}

void decrement_stack_depth() {
	stack_depth--;
}

void reset_stack_depth_counter() {
	max_stack_depth = 0;
	stack_depth = 0;
}



// MARK skip equil pivot quick sort
//#define EXCHANGE(a, b) tmp = a; a = b; b = tmp;

//typedef struct {
//	int q;
//	int t;
//} pivot_t;
//[q, t)

pivot_t partition_equal(int[], int, int);
pivot_t randomized_partition_equal(int[], int, int);
//[p, r) [q,t)
void quicksort_equal(int A[], int p, int r) {
	if (p < r - 1) {
		pivot_t pivot = randomized_partition_equal(A, p, r);
		quicksort_equal(A, p, pivot.q);
		quicksort_equal(A, pivot.t, r);
	}
}

pivot_t randomized_partition_equal(int A[], int p, int r) {
	srand((unsigned int)time(0));
	int i = rand() % (r - p) + p,
	tmp;
	
	EXCHANGE(A[i], A[r-1]);
	
	return partition_equal(A, p, r);
}

pivot_t median_partition_equal(int A[], int p, int r, int elem) {
	int i;
	for (i=p; i<r; i++) {
		if (A[i] == elem) {
			int tmp;
			EXCHANGE(A[i], A[r-1]);
			break;
		}
	}
	return partition_equal(A, p, r);
}

pivot_t partition_equal(int A[], int p, int r) {
	int x = A[r - 1],
	q = p,
	t,
	tmp;
	pivot_t result;
	
	for (int i = p; i < r - 1; i++) {
		if (A[i] < x) {
			EXCHANGE(A[q], A[i]);
			q++;
		}
	}
	
	for (t = q; t < r && A[t] == x; t++);
	
	for (int i = r - 1; i >= t; i--) {
		if (A[i] == x) {
			EXCHANGE(A[t], A[i]);
			t++;
		}
	}
	
	result.q = q;
	result.t = t;
	return result;
}


// MARK: fuzzy sorting of intervals

//#include <stdbool.h>
//#include <stdlib.h>



bool intersects(interval a, interval b) { return a.left <= b.right && b.left <= a.right; }
bool before(interval a, interval b)     { return a.right < b.left; }
bool after(interval a, interval b)      { return a.left > b.right; }

//#define EXCHANGE(a, b) tmp = a; a = b; b = tmp;

interval partition_interval(interval A[], int p, int r) {
	int pick, s, t, i;
	interval intersection, tmp;
	
	// Pick a random interval as a pivot
	pick = p + rand() % (r - p);
	EXCHANGE(A[pick], A[r-1]);
	intersection = A[r-1];
	
	// Find an intersection of the pivot and other intervals
	for (i = p; i < r - 1; i++) {
		if (intersects(intersection, A[i])) {
			if (A[i].left > intersection.left)
				intersection.left = A[i].left;
			if (A[i].right < intersection.right)
				intersection.right = A[i].right;
		}
	}
	
	// Classic partition around the intersection
	for (i = s = p; i < r - 1; i++) {
		if (before(A[i], intersection)) {
			EXCHANGE(A[i], A[s]);
			s++;
		}
	}
	EXCHANGE(A[r-1], A[s]);
	
	// Group intervals including the intersection
	for (t = s + 1, i = r - 1; t <= i;) {
		if (intersects(A[i], intersection)) {
			EXCHANGE(A[t], A[i]);
			t++;
		} else {
			i--;
		}
	}
	
	return (interval) {s, t};
}

void fuzzy_sort(interval array[], int p, int r) {
	if (p < r - 1) {
		interval pivot = partition_interval(array, p, r);
		fuzzy_sort(array, p, pivot.left);
		fuzzy_sort(array, pivot.right, r);
	}
}



// MARK: counting sort
void counting_sort(int A[], int B[], int k, int num) {
	int *C = (int *)calloc(k, sizeof(int));
	int i,j;
	for (j = 0; j < num; j++) {
		C[A[j]] += 1;
	}
	
	////C[i] now contains the number of elements equal to i.
	for (i = 1; i < num; i++) {
		C[i] += C[i-1];
	}
	//C[i] now contains the number of elements less than or equal to i.
	for (j = num-1; j >= 0; j++) {
		B[C[A[j]]] = A[j];
		C[A[j]]--;
	}
}//O(n+k) stable




