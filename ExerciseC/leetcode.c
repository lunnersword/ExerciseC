//
//  leetcode.c
//  ExerciseC
//
//  Created by lunner on 9/24/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#include "leetcode.h"
#include "sorts.h"
#include "searchs.h"
#include <stdlib.h>
#include "dict.h"
// MARK: twoSum
int searchKeyAfter(int *nums, int start, int numsSize, int key) {
	int i;
	for(i = start; i<numsSize; i++) {
		if(nums[i] == key) {
			return i;
		}
	}
	return -1;
}
int* twoSum_brute(int* nums, int numsSize, int target) {
	int i,j;
	for(i = 0; i < numsSize; i++) {
		j = searchKeyAfter(nums, i+1, numsSize, target-nums[i]);
		if (j!=-1) {
			int *results= (int*)malloc(sizeof(int)*2);
			results[0] = i+1;
			results[1] = j+1;
			return results;
		}
	}
	return NULL;
}

typedef struct node {
	int val;
	int index;
}twoSumNode;

int compar(const void *a, const void *b) {
	twoSumNode *first = (twoSumNode*)a;
	twoSumNode *second = (twoSumNode*)b;
	
	if (first->val > second->val) {
		return 1;
	} else if (first->val == second->val) {
		return 0;
	} else {
		return -1;
	}
}

int* twoSum(int* nums, int numsSize, int target) {
	int i;
	//merge_sort(nums, 0, numsSize);
	twoSumNode *nodes = (twoSumNode*)malloc(sizeof(twoSumNode) * numsSize);
	
	for (i=0; i<numsSize; i++) {
		nodes[i].val = nums[i];
		nodes[i].index = i+1;
	}
	qsort(nodes, numsSize, sizeof(twoSumNode), compar);
	for (i = 0; i < numsSize; i++) {
		//j = binary_search(nums+i+1, numsSize-(i+1), target-nums[i]);
		twoSumNode key = {target-nodes[i].val, 0};
		twoSumNode *temp = bsearch(&key, nodes+i+1, numsSize-(i+1), sizeof(twoSumNode), compar);
		if (temp != NULL) {
			int *results= (int*)malloc(sizeof(int)*2);
			if (nodes[i].index < temp->index) {
				results[0] = nodes[i].index;
				results[1] = temp->index;

			} else {
				results[0] = temp->index;
				results[1] = nodes[i].index;
			}
			free(nodes);
			return results;
		}
	}
	free(nodes);	
	return NULL;
}

// MARK: addTwoNumbers
struct ListNode {
	int val;
	struct ListNode *next;
};
//here we put null on the head node.
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2) {
	int jin=0;
	int isFirst = 1;
	struct ListNode *result = NULL;
	struct ListNode *temp;
	//temp = result;
	//result->next = NULL;
	while (l1 && l2) {
		int sum;
		if (isFirst) {
			temp = (struct ListNode*)malloc(sizeof(struct ListNode));
			result = temp;
			temp->next = NULL;
			isFirst = 0;
		} else {
			temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			temp = temp->next;
			temp->next = NULL;
		}
		sum = l1->val + l2->val + jin;
		temp->val = sum % 10;
		jin = sum/10;
		l1 = l1->next;
		l2 = l2->next;
	}
	while (l1) {
		int sum;
		if (isFirst) {
			temp = (struct ListNode*)malloc(sizeof(struct ListNode));
			result = temp;
			temp->next = NULL;
			isFirst = 0;
		} else {
			temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			temp = temp->next;
			temp->next = NULL;
		}		
		sum = l1->val + jin;
		temp->val = sum % 10;
		jin = sum / 10;
		l1 = l1->next;

	}
	while (l2) {
		int sum;
		if (isFirst) {
			temp = (struct ListNode*)malloc(sizeof(struct ListNode));
			result = temp;
			temp->next = NULL;
			isFirst = 0;
		} else {
			temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
			temp = temp->next;
			temp->next = NULL;
		}
		
		sum = l2->val + jin;
		temp->val = sum % 10;
		jin = sum / 10;
		l2 = l2->next;
		
	}
	if (jin) {
		temp->next = (struct ListNode*)malloc(sizeof(struct ListNode));
		temp = temp->next;
		temp->next = NULL;
		temp->val = jin;
	}

	
	return result;
	
}

// MARK: Longest Substring Without Repeating Characters
long strIndexOfChar(const char *s, char ch) {
	char *addr = strchr(s , ch);
	if (addr == NULL) {
		return -1;
	}
	return addr - s;
}
long strRightIndexOfChar(const char *s, char ch) {
	char *addr = strrchr(s, ch);
	if (addr == NULL) {
		return -1;
	}
	return addr - s;
}
int lengthOfLongestSubstring(char* s) {
	int i, start, len, count;
	dict_t *dict = (dict_t*)malloc(sizeof(dict_t));
	len = strlen(s);
	count = 0;
	dict_init(dict);
	
	if (len <= 0) {
		return 0;
	}
	if (len == 1) {
		return 1;
	}
	
	for (i=0, start=0; i<len; i++) {
		char *key = malloc(sizeof(char)*2);
		key[0] = s[i];
		key[1] = '\0';
		if (dict_contains(dict, key)) {
			int j;
			//int temp = i - start;
			int *tempi = (int*)malloc(sizeof(int));
			if (dict->ele_num > count) {
				count = dict->ele_num;
			}
			//start += strIndexOfChar(s+start, s[i]);
			
			dict_get(dict, key, (void**)&tempi);
			//i = *tempi;
			for (j = start; j < *tempi; j++) {
				char *key = malloc(sizeof(char)*2);
				key[0] = s[j];
				key[1] = '\0';
				dict_del(dict , key);
			}
			start = *tempi + 1;
			int *val = (int*)malloc(sizeof(int));
			*val = i;
			dict_set(dict, key, val);
			//dict_reset(dict);
			
		} else {
			int *val = (int*)malloc(sizeof(int));
			*val = i;
			dict_set(dict , key, val);

		}
	}
	
	// the last
	{
		int lastcount = dict->ele_num;
		if (lastcount > count)
			count = lastcount;
	}
	
	dict_destory(dict);
	free(dict);
	
	return count;
}

// MARK: findMedianSortedArrays

double medianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {

	if ((nums1Size+nums2Size) % 2 == 0) {
		int rightIndex = (nums1Size+nums2Size)/2;
		int leftIndex =  rightIndex - 1;
		int left, right;
		if (leftIndex >= nums1Size) {
			left = nums2[leftIndex-nums1Size];
			right = nums2[rightIndex-nums1Size];
		} else if (rightIndex < nums1Size) {
			left = nums1[leftIndex];
			right = nums1[rightIndex];
		} else {
			left = nums1[leftIndex];
			right = nums2[rightIndex-nums1Size];
		} 
		
		return (double)(left + right)/2.0;
	} else {
		int medianIndex = (nums1Size+nums2Size)/2;
		int median;
		if (medianIndex >= nums1Size) {
			median = nums2[medianIndex-nums1Size];
		} else {
			median = nums2[medianIndex];
		}
		return median;
	}
}

int binarySearch(int A[], int length, int v) {
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
	
	return high;
} 

double findKSortedArrays(int *nums1, int nums1Size, int *nums2, int nums2Size, int k, int single) {
	int leftIndex, rightIndex, leftInsertIndex, rightInsertIndex;
	if (nums1Size == 0) {
		if (!single) {
			return (nums2[nums2Size/2-1] + nums2[nums2Size/2] )/2.0;
		} else {
			return nums2[nums2Size/2];
		}
		
	}
	if (nums2Size == 0) {
		if (!single) {
			return (nums1[nums1Size/2-1] + nums1[nums1Size/2])/2.0;
		} else {
			return nums1[nums1Size/2];
		}
	}
	if (nums1Size ==1 && nums2Size==1) {
		if (single) {
			return nums1[0];
		}
		return (nums1[0]+nums2[0])/2.0;
	}
	if (nums1[nums1Size-1] <= nums2[0]) {
		return medianSortedArrays(nums1, nums1Size, nums2, nums2Size);
	}
	if (nums2[nums2Size-1] <= nums1[0]) {
		return medianSortedArrays(nums2, nums2Size, nums1, nums1Size);
	}
	
	leftIndex = nums1Size/2;
	rightIndex = nums2Size/2;
	
	if (nums1[leftIndex] < nums2[rightIndex]) {
		int leftCount, rightCount;
		rightInsertIndex = binarySearch(nums1+leftIndex, nums1Size-leftIndex, nums2[rightIndex]);
		leftInsertIndex = binarySearch(nums2, rightIndex, nums1[leftIndex]);
		leftCount = nums1Size - leftIndex;
		rightCount = rightIndex;
		return findMedianSortedArrays(nums1+leftIndex, rightInsertIndex, nums2, rightIndex-leftInsertIndex);
	} else if (nums1[leftIndex] > nums2[rightIndex]){
		return findMedianSortedArrays(nums2+rightIndex, nums2Size-rightIndex, nums1 , leftIndex);
	} else {
		return nums1[leftIndex];
	}

}

double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size) {
	int leftIndex, rightIndex, leftInsertIndex, rightInsertIndex;
	if (nums1Size == 0) {
		if (nums2Size % 2 == 0) {
			return (nums2[nums2Size/2-1] + nums2[nums2Size/2] )/2.0;
		} else {
			return nums2[nums2Size/2];
		}

	}
	if (nums2Size == 0) {
		if (nums1Size % 2 == 0) {
			return (nums1[nums1Size/2-1] + nums1[nums1Size/2])/2.0;
		} else {
			return nums1[nums1Size/2];
		}
	}
	if (nums1Size ==1 && nums2Size==1) {
		return (nums1[0]+nums2[0])/2.0;
	}
	if (nums1[nums1Size-1] <= nums2[0]) {
		return medianSortedArrays(nums1, nums1Size, nums2, nums2Size);
	}
	if (nums2[nums2Size-1] <= nums1[0]) {
		return medianSortedArrays(nums2, nums2Size, nums1, nums1Size);
	}
	
	leftIndex = nums1Size/2;
	rightIndex = nums2Size/2;
	
	if (nums1[leftIndex] < nums2[rightIndex]) {
		int leftCount, rightCount;
		rightInsertIndex = binarySearch(nums1+leftIndex, nums1Size-leftIndex, nums2[rightIndex]);
		leftInsertIndex = binarySearch(nums2, rightIndex, nums1[leftIndex]);
		leftCount = nums1Size - leftIndex;
		rightCount = rightIndex;
		return findMedianSortedArrays(nums1+leftIndex, rightInsertIndex, nums2, rightIndex-leftInsertIndex);
	} else if (nums1[leftIndex] > nums2[rightIndex]){
		return findMedianSortedArrays(nums2+rightIndex, nums2Size-rightIndex, nums1 , leftIndex);
	} else {
		return nums1[leftIndex];
	}
}

int binary_search(int A[], int length, int v) {
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

//function: 旋转数组的最值
//return: the max elem index
//[p, r)

int findMaxIndex(int *array, int p, int r) {
	if (array == NULL || p < 0 || r <= 0 || (r-p) < 1) {
		return -1;
	}
	if ((r - p) == 1 ) {
		return p; //only one element
	}
	int low = p, high = r, mid;

	while (low < high) {
		printf("(%d, %d)\n", low, high);
		mid = (high + low)/2;
		if (array[mid] >= array[high-1]) {
			low = mid;
		}
		else if (array[mid] <= array[low]) {
			high = mid;
		}
		else {
			return r-1;
		}
	}
	return low;
}

//function: 旋转数组的最小值
//return: the max elem index
//[p, r)

int findKeyIndex(int *array, int p, int r, int key) {
	int maxIndex = findMaxIndex(array, p, r);
	if (key == array[maxIndex]) {
		return maxIndex;
	}
	if (maxIndex == r-1) {
		return binary_search(array+p, r-p, key);
	} else if (key >= array[p]){
		return binary_search(array+p, maxIndex-p, key);
		
	} else {
		return binary_search(array+maxIndex+1, r-(maxIndex+1), key);
	}
}











