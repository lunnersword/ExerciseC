//
//  leetcode.h
//  ExerciseC
//
//  Created by lunner on 9/24/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#ifndef leetcode_h
#define leetcode_h

#include <stdio.h>
int* twoSum(int* nums, int numsSize, int target);
struct ListNode* addTwoNumbers(struct ListNode* l1, struct ListNode* l2);
int lengthOfLongestSubstring(char* s);
double findMedianSortedArrays(int* nums1, int nums1Size, int* nums2, int nums2Size);

int findMaxIndex(int *array, int p, int r); 
int findKeyIndex(int *array, int p, int r, int key) ;

#endif /* leetcode_h */
