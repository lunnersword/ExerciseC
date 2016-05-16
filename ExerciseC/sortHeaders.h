//
//  sortHeaders.h
//  ExerciseC
//
//  Created by lunner on 8/26/15.
//  Copyright (c) 2015 lunner. All rights reserved.
//

#ifndef ExerciseC_sortHeaders_h
#define ExerciseC_sortHeaders_h
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

#define MERGE_HEAP_ALLOCATION
#define INSERTION_SORT_TRESHOLD 20
#define SELECTION_SORT_TRESHOLD 15

#define PARENT(i) (((i) - 1) / 2)
#define LEFT(i)   (2 * (i) + 1)
#define RIGHT(i)  (2 * (i) + 2)
#define EXCHANGE(A, B) do{\
tmp = A;\
A = B;\
B = tmp;\
}while(0)


#define DPARENT(i,d) ((i - 1) / d)
#define DCHILD(i,c,d) (d * i + c + 1)


typedef struct {
	int *nodes;
	int length;
	int heap_size;
} heap;

typedef struct {
	int *elements;
	int d;
	int heap_size;
	int length;
} heap_t;

typedef struct {
	int q;
	int t;
} pivot_t;

typedef struct {
	int left;
	int right;
} interval;

#endif
