//
//  heapSort.h
//  ExerciseC
//
//  Created by lunner on 8/17/15.
//  Copyright (c) 2015 lunner. All rights reserved.
//

#ifndef ExerciseC_heapSort_h
#define ExerciseC_heapSort_h

#include "sortHeaders.h"



/// MARK: func heads
void bubble_sort(int A[], int p, int r);
void bubble1_sort(int a[], int n);
void insertion_sort(int A[], int p, int r);
void binary_insert_sort(int *A, int num);
void selection_sort(int A[], int p, int r);

void merge_sort(int A[], int p, int r);
void mixed_merge_sort_insertion(int A[], int p, int r);
void mixed_merge_sort_selection(int A[], int p, int r);

void max_heapify(heap *A, int i);
void build_max_heap(heap *A);
void heap_sort(heap *A);

void max_heapify_dary(heap_t *heap, int i);
int extract_max(heap_t *heap);
void increase_key(heap_t *heap, int i, int key);
void insert(heap_t *heap, int key);

void quicksort(int A[], int p, int r);
void modified_quicksort(int A[], int p, int r);
void limited_quicksort(int A[], int p, int r, int treshold);
int partition(int A[], int p, int r);
int hoare_partition(int A[], int p, int r);
void quicksort_hoare_partition(int A[], int p, int r);
void tail_recursive_quicksort(int A[], int p, int r);
int randomized_partition(int A[], int p, int r);
pivot_t partition_equal(int[], int, int);
pivot_t randomized_partition_equal(int[], int, int);
pivot_t median_partition_equal(int A[], int p, int r, int elem);
pivot_t partition_equal(int A[], int p, int r);

void fuzzy_sort(interval array[], int p, int r);
interval partition_interval(interval A[], int p, int r);
#endif
