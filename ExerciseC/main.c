//
//  main.c
//  ExerciseC
//
//  Created by lunner on 8/7/15.
//  Copyright (c) 2015 lunner. All rights reserved.
//

#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stddef.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include "stringMatch.h"
#include "searchs.h"
#include "selects.h"
#include "dictTest.h"
#include "fortest.h"
#include "leetcode.h"
#define square(a) ((a)*(a))
#define PRINT_INT(x) printf(#x " = %d\n", x)

void f2();
void f1() {
	f2();
}
void f2() {
	int i = 1;
	{
		int i = 2;
		printf("%d in block",i);
	}
	printf("%d in f2", i);
}

struct ListNode
{
	int  m_nKey;
	struct ListNode *m_pNext;
};
void reverseTraveLinkList(struct ListNode *T) {
	struct ListNode *lastNode = NULL;
	struct ListNode *head = T;
	do{
		head = T;
		while(head->m_pNext != lastNode) {
			head = head->m_pNext;
		}
		lastNode = head;
		if(lastNode != T)
			printf("%d", lastNode->m_nKey);
	}while(head != T);

}

void randomlyPutCoinIntoRooms(unsigned int *rooms, int roomNum) {
	int i = 0;
	srand((int)time(0));
	for (i = 0; i < roomNum; i++) {
		rooms[i] = (unsigned int)rand();
	}
}

unsigned int getCoinFromRooms(unsigned int *rooms, int roomNum) {
	//int coin = 0;
	int i = 0;
	unsigned int maxFour = rooms[0];
	for(i=0; i < 4; i++) {
		if (rooms[i] > maxFour) {
			maxFour = rooms[i];
		}
	}
	for(i=4; i<roomNum; i++) {
		if(rooms[i] > maxFour) {
			return rooms[i];
		}
	}
	return rooms[roomNum - 1];
	
}
unsigned int getMaxCoinOfRooms(unsigned int *rooms, int roomNum) {
	int i = 0;
	unsigned int max = rooms[0];
	for (i=2; i<roomNum; i++) {
		if (max < rooms[i]) {
			max = rooms[i];
		}
	}
	return max;
}

double computeRate() {
	unsigned int rooms[10];
	int count = 0;
	int testNum = 100000;
	int i = 0;
	for (i=0; i<testNum; i++) {
		randomlyPutCoinIntoRooms(rooms, 10);
		if(getCoinFromRooms(rooms, 10) == getMaxCoinOfRooms(rooms, 10)) {
			count++;
		}
	}
	return (double)count / (double)testNum;
}

int *maxMin(int a[], int n) {
	int b[2];
	b[0] = b[1] = a[0];
	for(int i = 1; i < n; i++) {
		if (a[i] < b[0]) {
			int tmp = b[0];
			b[0] = a[i];
			a[i] = tmp;
		}  
		if (a[i] > b[1]) {
			int tmp = b[1];
			b[1] = a[i];
			a[i] = tmp;
		}
	}
	printf("\n%d fuck %d\n", b[0], b[1]);
	printf("b address %p\n", b);
	return b;
}

int readline(char str[], int n) {
	int ch, i = 0;
	while (isspace(ch = getchar())) {
		;
	}
	while (ch != '\n' && ch != EOF) {
		if (i < n) {
			str[i++] = ch;
		}
		ch = getchar();
	}
	str[i] = '\0';
	return i;
}

int compare_strings(const void *p, const void *q) {
	//return strcmp(p, q);
	return strcmp(*(char**)p, *(char**)q);
}

typedef struct slice{
	int start;
	int end;
}Slice;
void insertSort(int *a, int num) {
	int i,j;
	int key;
	for(i=1;i<num;i++) {
		j = i-1;
		key = a[i];
		while(j>=0 && key < a[j]) {
			a[j+1] = a[j];
			j -= 1;
		}
		a[j+1] = key;
	}
}
int getContinueSlices(int *a, int num, Slice *s) {
	//Slice *s = (Slice*)malloc(num*sizeof(Slice));
	int i=0,start=0, end,count = 0;
	while (i<num) {
		start = end = i;
		while ((i+1)<num && (a[i+1]-a[i] == 1) ) {
			i++;
		}
		end = i;
		s[count].start = start;
		s[count].end = end;
		count++;
	}
	return s;
}
int combine(int *a, int num) {
	int step, count = 0;
	int *p,*start, *end, *temp;
	for (p = a; p < a+num; p++) {
		start = p;
		while(*(p+1) - *p == 1) {
			p++;
		}
		end = p;
		step = (int)(end - start - 1);
		if (step >= 1) {
			for(temp = end; temp < a + num; temp++) {
				*(temp-step) = *temp;
			}
			count += step;
		}
	}
	return num-count;
}


#include <stdio.h>
#include <stdlib.h>
#include <string.h>


int max_score(int *scores, int start, int end) {
	int i, max;

	max = scores[start];
	for (i = start+1; i <= end; i++) {
		if (scores[i] > max) {
			max = scores[i];
		}
	}
	return max;
}

void huawei1() {
	int n, m;
	int *scores;
	int i;
	char commd;
	int id, newScore;
	fscanf(stdin, "%d %d", &n, &m);
	printf("%d \n", m);
	scores = (int*)malloc((n+1) * sizeof(int));
	i = 0;
	for (i=0; i < n; i++) {
		fscanf(stdin, "%d", scores+i);
	}
	for (i = 0; i < m; i++) {
		fscanf(stdin, "%c %d %d", &commd, &id, &newScore);
		if (commd == 'Q') {
			printf("%d %d\n", id, newScore);
			fprintf(stdout, "%d\n",max_score(scores, id, newScore));
		} else if (commd == 'U') {
			scores[id] = newScore;
		}
	}
	
}

int string_to_int(const char* str) {
	const char *ch;
	int number = 0;
	bool isNegative = false;
	if (str == NULL) {
		printf("There are nothing to parse\n");
		exit(1);
	}
	ch = str;
	if (*ch == '-') {
		isNegative = true;
	}
	while (*ch != '\0') {
		if (!isNegative && number >= INT_MAX) {
			printf("Exceed the INT_MAX\n");
			return INT_MAX;
		}
		if (isNegative && number <= INT_MIN) {
			printf("Below the INT_MIN\n");
			return INT_MIN;
		}
		number = number * 10 + *ch - '0';
		ch++;
	}
	if (isNegative){
		number = 0 - number;
	}
	return number;
	
}
/*

ListNode* findKthToTail(ListNode *head, unsigned int k) {
	ListNode *pAhead;
	ListNode *pBehind;
	int count;
	count = 0;
	if (head == NULL) {
		return NULL;
	}
	pAhead = head;
	while (pAhead->next) {
		pAhead = pAhead->next;
		count++;
	}
	if (count < k) {
		printf("%d is greater than the list's length %d\n", k, count);
		return NULL;
	}
	pBehind = pAhead = head;
	for (count = 0; count < k; <#increment#>) {
		pAhead = pAhead->next;
	}
	while (pAhead->next != NULL) {
		pAhead = pAhead->next;
		pBehind = pBehind->next;
	}
	return pBehind;
}*/



int main(int argc, const char * argv[]) {

    
	/*
	// insert code here...
//	int a[5] = {1,2,3,4,4};
	int c[3][4] = { {1,2,3,4},
		{5,6,7,8},
		{9,10,11,12}};
	int (*line)[4];
	char *cp;

//	int *b;
//	f2();
//	b = maxMin(a, 5);//int b[2] is in the stack, so when func return it is destroyed, so return b, is return 
//	printf("%d\n", square((*a)++));
//	printf("%d fuck %d", b[0], b[1]);
//	printf("\nb is NULL %c", b ? 'y' : 'n');
//	b[6] = 5;
	for (line = c; line <= &c[2]; line++) {
		for(int i = 0; i <4; i++) {
			printf("%d ", (*line)[i]);
		}
		printf("\n");
	}
	printf(" char %c\n","adea"[2]);
	cp = "Iloveyou";
	
	//*cp = 'e';
	printf("%ld", strlen(cp));
	char *format = "%d";
	printf(format, c[0][0]);
	PRINT_INT(c[0][0]/c[1][1]);
	struct {
		char a;
		int b;
	}s; 
	printf("%ld\n", sizeof(s));
	{
		char *str1 = "I love you";
		char *str2 = "fuck away";
		char *str3 = "I hate";
		char *p[3];
		p[0] = str1, p[1] = str2; p[2]=str3;
		qsort(p, 3, sizeof(char*), compare_strings);
		for (int i = 0; i<3; i++) {
			printf("%s\n", p[i]);
		}
	}
	{
		unsigned int i = 8, j = 9;
		//printf("%d", i >> j+1 >> 1);
	}
	printf("\n  %lf", computeRate());
	
	{
		int a[5] = {1,2,3,4,5};
		int *ptr = (int *)(&a+1);
		printf("%d, %d\n", *(a+1), *(ptr-1));
	}
	{
		char ch = "0123"[4];
		if (ch==NULL) {
			printf("NULL: %d\n", ch);
		}
		
	}
	//input: 1,2,3,5,11,7,9
	//output: 1,3,5,7,9,11
	{
		//printf("\n begin");
		int a[10];
		int i = 0,count = 0, j;
		int sliceCount = 0;
		Slice s[10];
		while (scanf("%d,", a+i) != -1) {
			i++;
			
		}
		count = i;
		printf("count %d\n", count);
//		for (i=0; i<count; i++) {
//			printf("%d, ", a[i]);
//		}
		insertSort(a, count);
		j = combine(a, count);
		for (i = 0; i<j; i++) {
			printf("%d ", a[i]);
		}
//		sliceCount = getContinueSlices(a, count, s);
//		i = 0;j=0;
//		for (i=0; i<sliceCount; i++) {
//			for(;j<=s[i].start;j++) 
//				printf("%d ", a[j]);
//			j = s[i].end;
//		}
//		for (j=s[i].end; j < count; j++)
//		{
//			printf("%d ", a[j]);
//		}
	}*/
	/*{
		printf("begin match\n");
		char *str = "I fuck you deuckaddadadswafdasadasaadddaaddaaddaaddaadda";
		//"16, 40, 44, 48, 52"
		char *pattern = "adda";
		int *indices, *p;
		printf(" before matche\n");
		indices = KMP_matcher(str, pattern);
		printf(" out matcher\n");
		if (indices) {
			p = indices;
			while (*p != -1) {
				printf("%d ", *p++);
			}
			free(indices);
		} else {
			printf("No matchs\n");
		}
		

	}*/
	/*
	{
		struct T {
			char a;
			int *d;
			int b;
			int c:16;
			double e;
		};
		struct T *p;
		printf("%ld %ld %ld %ld %ld %ld %ld\n", sizeof(struct T), sizeof(p), sizeof(*p), sizeof(p->a), sizeof(p->b), sizeof(p->e), sizeof(short)); 
	}
	 */
	
	//huawei1();
	
//	testDict();
//	dictExample();
//	{
//		int A[] = {0, 1, 2, 3, 4, 5, 5, 5, 5, 10, 6, 6, 6, 7, 7, 8, 9, 10, 11};
//
//		int k = select_kth_smallest(A, 19, 15);
//		printf("median: %d\n", k);
//	}
	//treasureHunt();
	//maxSubSumIsZero();
	//maxSubMatrix2x2Sum();
//	{
//		int nums[] = {2,7,11,15};
//		int *result = twoSum(nums, 4, 9);
//		if (result) {
//			printf("index1=%d, index2=%d\n", result[0], result[1]);
//			free(result);
//		} else {
//			printf("is NULL\n");
//		}
//
//	}
//	{
//		struct ListNode {
//			int val;
//			struct ListNode *next;
//		};
//		struct ListNode l11,l12,l13, l21, l22,l23, *result;
//		
//		l11.val = 2;
//		l11.next = &l12;
//		l12.val = 4;
//		l12.next = &l13;
//		l13.val = 3;
//		l13.next = NULL;
//		
//	
//		l21.val = 5;
//		l21.next = &l22;
//		l22.val = 6;
//		l22.next = &l23;
//		l23.val = 4;
//		l23.next = NULL;
//		result = addTwoNumbers(&l11, &l21);
//		while (result) {
//			printf("%d ", result->val);
//			result = result->next;
//		}
//		
//	}
//	
//	{
//		char *s = "hhtekvlurjuufladcd";
//		printf("%d\n", lengthOfLongestSubstring(s));
//	}
//	{
//		int nums1[] = {1, 2, 3};
//		int nums2[] = {1, 2};
//		double re = findMedianSortedArrays(nums1, 3, nums2, 2);
//		printf("%f\n", re);
//	}
	//xiaoyi();
//	{
//		char *str;
//		str = "I love you";
//		printf("%s", str);
//	}
	{
		int a[] = { 4, 5, 6, 7, 9, 1, 2, 3,};
		int min = findMaxIndex(a, 0, 9);
		printf("%d\n", min);
		int key = 7;
		printf("%d\n", findKeyIndex(a, 0, 9, key));
	}
    {
        typedef void (*fp)(void);
        fp f= f2;
        f();
    }
	return 0;
	
}
