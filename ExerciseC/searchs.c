//
//  searchs.c
//  ExerciseC
//
//  Created by lunner on 8/17/15.
//  Copyright (c) 2015 lunner. All rights reserved.
//
#include <limits.h>
#include <stdlib.h>
#include <string.h>
//#include "searchs.h"
//[low,high)
// Indices in the C code are different
static int binary_search(int A[], int length, int v) {
	int low  = 0;
	int high = length;
	
	int mid;
	while (low < high) {
		mid = (low + high) / 2;
		
		if (A[mid] == v)
			return mid;
		else if (A[mid] < v)
			low = mid + 1;
		else
			high = mid;
	}
	
	return -1;
}//O(lgn) worst case
//end binary search

int pair_exists(int *A, int num, int x) {
	//is there exists two elements of S whose sum is exactly x.
	/*
	 PAIR-EXISTS(S, x):
	 A = MERGE-SORT(S)
	 
	 for i = 1 to S.length
		if BINARY-SEARCH(A, x - S[i]) != NIL
	 		return true
	 return false

	 */
	return 0;
}

// MARK: find max subarray
/*
find_max_crossing_subarray(A, low, mid, high) {
	leftSum = -∞
	sum = 0
	for i = mid downto low {
		sum = sum + A[i]
		if sum > leftSum {
			leftSum = sum
			maxLeft = i 
		}
	}
	rightSum = -∞
	sum = 0
	for j = mid + 1 to high {
		sum = sum + A[j]
		if sum > rightSum {
			rightSum = sum
			maxRight = j 
		}
	}
	return (max_left, max_right, left_sum+right_sum)
}

find_maximum_subarray(A, low, high) {
	if high == low {
		return (low, high, A[low]) //base case
	}
	else {
		mid = (low+high)/2 
		(left_low, left_high, left_sum) = find_maximum_subarray(A, low, mid)
		(right_low, right_high, right_sum) = find_maximum_subarray(A, mid+1, high)
		(cross_low, cross_high, cross_sum) = find_max_crossing_subarray(A, low, mid, high)
		if left_sum >= right_sum && left_sum >= cross_sum {
			return (left_low, left_high, left_sum)
		}
		else if right_sum>=left_sum && right_sum >= cross_sum {
			return (right_low, right_high, right_sum)
		} else {
			return (cross_low, cross_high, cross_sum)
		}
	}
}
*/

//Exercise 4.1.3
//#include <limits.h>

#define CROSSOVER_POINT 37

// A struct to representthe tuple
//[left, right)
typedef struct {
	unsigned left;
	unsigned right;
	int sum;
} max_subarray;

// The brute force approach

max_subarray find_maximum_subarray_brute(int A[], unsigned low, unsigned high) {
	max_subarray result = {0, 0, INT_MIN};
	
	for (int i = low; i < high; i++) {
		int current_sum = 0;
		for (int j = i; j < high; j++) {
			current_sum += A[j];
			if (result.sum < current_sum) {
				result.left = i;
				result.right = j + 1;
				result.sum = current_sum;
			}
		}
	}
	
	return result;
}

// The divide-and-conquer solution

max_subarray find_max_crossing_subarray(int A[], unsigned low, unsigned mid, unsigned high) {
	max_subarray result = {-1, -1, 0};
	int sum = 0,
	left_sum = INT_MIN,
	right_sum = INT_MIN;
	
	for (int i = mid - 1; i >= (int) low; i--) {
		sum += A[i];
		if (sum > left_sum) {
			left_sum = sum;
			result.left = i;
		}
	}
	
	sum = 0;
	
	for (int j = mid; j < high; j++) {
		sum += A[j];
		if (sum > right_sum) {
			right_sum = sum;
			result.right = j + 1;
		}
	}
	
	result.sum = left_sum + right_sum;
	return result;
}

max_subarray find_maximum_subarray(int A[], unsigned low, unsigned high) {
	if (high == low + 1) {
		max_subarray result = {low, high, A[low]};
		return result;
	} else {
		unsigned mid = (low + high) / 2;
		max_subarray left = find_maximum_subarray(A, low, mid);
		max_subarray right = find_maximum_subarray(A, mid, high);
		max_subarray cross = find_max_crossing_subarray(A, low, mid, high);
		
		if (left.sum >= right.sum && left.sum >= cross.sum) {
			return left;
		} else if (right.sum >= left.sum && right.sum >= cross.sum) {
			return right;
		} else {
			return cross;
		}
	}
}

// The mixed algorithm

max_subarray find_maximum_subarray_mixed(int A[], unsigned low, unsigned high) {
	if (high - low < CROSSOVER_POINT) {
		return find_maximum_subarray_brute(A, low, high);
	} else {
		unsigned mid = (low + high) / 2;
		max_subarray left = find_maximum_subarray_mixed(A, low, mid);
		max_subarray right = find_maximum_subarray_mixed(A, mid, high);
		max_subarray cross = find_max_crossing_subarray(A, low, mid, high);
		
		if (left.sum >= right.sum && left.sum >= cross.sum) {
			return left;
		} else if (right.sum >= left.sum && right.sum >= cross.sum) {
			return right;
		} else {
			return cross;
		}
	}
}
//end exercise 4.1.3
//Exercise 4.1.5
//linear-time algorithm for the maximum-subarray problem.
max_subarray find_maximum_subarray_linear(int A[], unsigned int low, unsigned int high) {
    max_subarray suffixes[high-low];
    suffixes[0].left = low;
    for (int i = low + 1; i < high; i++) {
        if (suffixes[i-1].sum < 0) {
            suffixes[i].left = i;
            suffixes[i].right = i+1;
            suffixes[i].sum = A[i];
        } else {
            max_subarray *previous  = suffixes+(i-1);
            suffixes[i].left = previous->left;
            suffixes[i].right = i+1;
            suffixes[i].sum = previous->sum + A[i];
        }
    }
    
    max_subarray *max = &suffixes[0];
    for (int i = low+1; i < high; i++) {
        if (max->sum < suffixes[i].sum) {
            max = &suffixes[i];
        }
    }
    return *max;
}


