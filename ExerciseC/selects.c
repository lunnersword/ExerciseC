//
//  selects.c
//  ExerciseC
//
//  Created by lunner on 8/26/15.
//  Copyright (c) 2015 lunner. All rights reserved.
//

#include <stdlib.h>
#include "sorts.h"
#include "Array.h"

// MARK: Minimum and Maximum
//[p, r)
int minimum(int A[], int p, int r) {
	int min = A[p];
	int i;
	for (i = p + 1; i < r; i++) {
		if (min > A[i])
			min = A[i];
	}
	return min;
}// n-1

int maximum(int A[], int p, int r) {
	int max = A[p];
	int i;
	for (i=p+1; i < r; i++) {
		if (max < A[i])
			max = A[i];
	}
	return max;
}

// MARK: selection kth smallest element of the array A[p,r), k[0,1,...] [q,t)
int randomized_select(int A[], int p, int r, int k) {
	pivot_t pivot, span;
	if (p == r-1) {
		return A[p];
	}
	pivot = randomized_partition_equal(A, p, r);
	span.q = pivot.q - p;
	span.t = pivot.t - p;

	if (k >= span.q && k < span.t) {
		return A[pivot.q];
	} else if (k >= span.t) {
		return randomized_select(A, pivot.t, r, k-span.t);
	} else {
		return randomized_select(A, p, pivot.q, k);
	}
} //expected not worst ø(n) assuming that the elements are distinct, but here the elements can be equal because of pivot_t

// MARK: Selection in worst-case linear time
#define SELECTGROUPCOUNT 5
int median_index(int n) {
	//always return lower
	if (n % 2 == 0) {
		return n/2-1;
	} else {
		return n/2;
	}
	
}

//k[0,1,2,3...]
int select_kth_smallest(const int *A, int len, int k) {
	int *medians, *tempA, *tempAA;
	int groupCount;
	int lastGroupElementCount;
	int i, j, median;
	int pivotElem;
	pivot_t pivot;
	//pivot_t span;
	if (len <= 1) {
		return A[0];
	}
	if (len % SELECTGROUPCOUNT == 0) {
		groupCount = len / SELECTGROUPCOUNT;
		lastGroupElementCount = SELECTGROUPCOUNT;
	} else {
		groupCount = len / SELECTGROUPCOUNT + 1;
		lastGroupElementCount = len % SELECTGROUPCOUNT;
	}
	
	medians = (int*)malloc(sizeof(int) * groupCount);
	tempA = (int*)malloc(sizeof(int) * len);
	memcpy(tempA, A, sizeof(int) * len);
	j = 0;
	for (i=0; i<groupCount-1; i++) {
		int start = i * SELECTGROUPCOUNT;
		insertion_sort(tempA, start, start+SELECTGROUPCOUNT);
		median = tempA[median_index(SELECTGROUPCOUNT) + start];
		medians[j++] = median;
	}
	// for last group

	insertion_sort(tempA,  i * SELECTGROUPCOUNT, lastGroupElementCount);
	median = tempA[median_index(lastGroupElementCount) +  i * SELECTGROUPCOUNT];
	medians[j] = median;
	
	pivotElem = select_kth_smallest(medians, groupCount, median_index(groupCount));
	pivot  = median_partition_equal(tempA, 0, len, pivotElem);
	if (medians) {
		free(medians);
		medians = NULL;
	}

	if (k >= pivot.q && k < pivot.t) {
		i = tempA[pivot.q];
		if(tempA) {
			free(tempA);
			tempA = NULL;
		}
		return i;
	}
	else if (k >= pivot.t) {
		tempAA = malloc(sizeof(int) * (len - pivot.t));
		memcpy(tempAA, tempA+pivot.t, sizeof(int) * (len-pivot.t));
		if (tempA) {
			free(tempA);
			tempA = NULL;
		}

		i = select_kth_smallest(tempAA, len-pivot.t, k-pivot.t);
		if (tempAA) {
			free(tempAA);
			tempAA = NULL;
		}

		return i;
	} else {
		tempAA = malloc(sizeof(int) * (pivot.q));
		memcpy(tempAA, tempA, sizeof(int) * (pivot.q));
		if (tempA) {
			free(tempA);
			tempA = NULL;
		}
		i = select_kth_smallest(tempAA, pivot.q, k);
		if (tempAA) {
			free(tempAA);
			tempAA = NULL;
		}
		return i;
	}
	
}

