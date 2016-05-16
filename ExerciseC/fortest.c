//
//  fortest.c
//  ExerciseC
//
//  Created by lunner on 9/27/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#include "fortest.h"
#include "Array.h"
#include "dict.h"
#include <limits.h>


typedef struct {
	int min;
	int count;
}treasure_t;

//n*m gezi , from left top to right bottom, down or right
int count = 0;

void countOfPaths( int i, int j, int n, int m) {
	if (i >= n || j >= m) {
		return ;
	}
	if (i == n-1 && j == m-1) {
		count++;
		return;
	}
	if (i < n-1) {
		countOfPaths( i+1, j, n, m);
	}
	if (j < m - 1) {
		countOfPaths(i, j+1, n, m);
	}
	
}

void bruteTreasureHunt(int *treasures, Array *array, treasure_t treasure, int i, int j, int n, int m) {
	//treasure_t temp;
	if (i >= n || j >= m) {
		return;
	}
	if (treasures[i*m+j] >= treasure.min) {
		treasure.count++;
	} else {
		//treasure.min = treasures[i*m+j];
	}
	if (i == n-1 && j == m-1) {
		//appendToArray(array, treasure);
		appendToArray(array, &treasure);
		return;
	}
	if (i<n-1) {
		//temp = treasure;
		bruteTreasureHunt(treasures, array, treasure, i+1, j, n, m);
	}
	if (j < m -1) {
		bruteTreasureHunt(treasures, array, treasure, i, j+1, n, m);
	}
}
void treasureHunt() {
	treasure_t treasure;
	int n, m, k;
	int *treasures;
	int i, j;
	int count;
	Array array;
	scanf("%d %d %d", &n, &m, &k);
	treasures = (int*)malloc(sizeof(int)*(n*m));
	for (i = 0; i<n; i++) {
		for (j = 0; j < m; j++) {
			scanf("%d", treasures+i*m+j);
		}
	}
	treasure.min = treasures[0];
	treasure.count = 0;
	//initArray(&array);
	initArray(&array, sizeof(treasure));
	bruteTreasureHunt(treasures, &array, treasure, 0, 0, n, m);
	count = 0;
	for (i = 0; i < array.count; i++) {
		getElementOfArray(&array, i, &treasure);
		if (treasure.count >= k) {
			count++;
		}
	}
	printf("%d", count%1000000007);
	
}

void maxSubSumIsZero() {
	int tmp, i, j = 0, k;
	Array array;
	int sum = 0;
	int haveFount = 0;
	initArray(&array, sizeof(int));

	
	while (scanf("%d", &tmp) == 1) {
		appendToArray(&array, &tmp);
	}//endless loop, 
	for (i = 0; i < array.count; i++) {
		if (haveFount) {
			break;
		}
		getElementOfArray(&array, i, &tmp);
		sum = tmp;
		for (j = array.count - 1; j > i; j--) {
			for (k = j; k > i; k--) {
				getElementOfArray(&array, k, &tmp);
				sum += tmp;
			}
			if (sum == 0) {
				haveFount = 1;
				break;
			}
		}
	}
	for (k = i-1; k<=j; k++) {
		getElementOfArray(&array, k, &tmp);
		printf("%d", tmp);
	}
}

void maxSubMatrix2x2Sum() {
	int col, row;
	int tmp, sum = 0;
	int maxSum= INT_MIN;
	Array array;
	initArray(&array, sizeof(int));
	col = 0;
	
	while (scanf("%d", &tmp) == 1) {
		appendToArray(&array, &tmp);
		col++;
	}
	row = 1;
	while (getchar() == ',') {
		for (int c = 0; c < col; c++) {
			scanf("%d", &tmp);
			appendToArray(&array, &tmp);
		}
		row++;
	}
	printf("col=%d, row=%d\n", col, row);
	
	for (int i=0; i<row-1; i++) {
		for (int j=0; j<col-1; j++) {
			int temp1,temp2, temp3,temp4;
			getElementOfArray(&array, i*col+j, &temp1);
			getElementOfArray(&array, i*col+j+1, &temp2);
			getElementOfArray(&array, (i+1)*col+j, &temp3);
			getElementOfArray(&array, (i+1)*col+j+1, &temp4);
			sum = temp1 + temp2 + temp3 + temp4;
			if (sum > maxSum) {
				maxSum = sum;
			}
		}
	}
	
	printf("%d", maxSum);
}

char *intToStr(int num) {
	char *ch = "0123456789";
	char rel[1001];
	char *temp;
	int i = 1000;
	rel[i--] = '\0';
	while (num) {
		int rem = num % 10;
		num = num /10;
		rel[i--] = ch[rem];
	}
	i++;
	memmove(rel, rel+i, 1000-i+1);
	temp = (char*)malloc(sizeof(char) * strlen(rel));
	strcpy(temp, rel);
	return temp;
}

typedef struct {
	int left;
	int right;
}friend_t;

void renLaoXiang() {
	int left, right;
	int m, n;
	int i;
	//int count = 0;
	dict_t *set = (dict_t*)malloc(sizeof(dict_t));
	dict_init(set);
	dict_set(set, "1", (char*)malloc(sizeof(char)));
	Array friends;
	initArray(&friends, sizeof(friend_t));
	scanf("%d %d", &n, &m);
	while (!(n == 0 && m == 0)) {
		for (i=0; i<m; i++) {
			scanf("%d %d", &left, &right);
			char *leftstr = intToStr(left);
			char *rightstr = intToStr(right);
			//printf("%s\n", leftstr);
			//printf("%s\n", rightstr);
			
			char *lval = (char*)malloc(sizeof(char));
			char *rval = (char*)malloc(sizeof(char));
			//count++;
			if (dict_contains(set, rightstr) || dict_contains(set, leftstr)) {
				if (dict_contains(set, rightstr) && !dict_contains(set, leftstr)) {
					dict_set(set, leftstr, lval);
				}
				else if (dict_contains(set, leftstr) && !dict_contains(set, rightstr)) {
					dict_set(set, rightstr, rval);
				}

			}
			else {
				friend_t friend = {left, right};
				appendToArray(&friends, &friend);
			}

		}
		while (friends.count) {
			friend_t friend;
			firstElementOfArray(&friends, &friend);
			char *leftstr = intToStr(friend.left);
			char *rightstr = intToStr(friend.right);
			//printf("%s\n", leftstr);
			//printf("%s\n", rightstr);
			while (friends.count) {
				char *lval = (char*)malloc(sizeof(char));
				char *rval = (char*)malloc(sizeof(char));
				//count++;
				if (dict_contains(set, rightstr) || dict_contains(set, leftstr)) {
					
					if (dict_contains(set, rightstr) && !dict_contains(set, leftstr)) {
						dict_set(set, leftstr, lval);
					}
					else if (dict_contains(set, leftstr) && !dict_contains(set, rightstr)) {
						dict_set(set, rightstr, rval);
					}
				}
				
				else {
					removeFirstElementOfArray(&friends, &friend);
				}

			}

		}
		printf("%d\n", set->ele_num-1);
		dict_reset(set);
		dict_set(set, "1", (char*)malloc(sizeof(char)));
		scanf("%d %d", &n, &m);
		
	}
	
}

int largestCommonDivisor(int a, int b) {
	while(a != b) {
		if(a>b) {
			a = a - b;
		} else {
			b = b - a;
		}
	}
	return a;
}

void xiaoyi() {
	int a, n, i;
	int  *mons = NULL;
	
	while (scanf("%d %d", &n, &a) != EOF) {
		if (mons!=NULL) {
			free(mons);
		}
		mons = (int*)malloc(sizeof(int)*n);
		for (i=0; i<n; i++) {
			scanf("%d",mons+i);
		}
		
		for	(i=0; i<n; i++) {
			if (a >= mons[i]) {
				a += mons[i];
			} else {
				a += largestCommonDivisor(a, mons[i]);
			}
		}
		printf("%d\n", a);
	}
	
}

int counts33(int *mogus, int cols, int row, int col) {
	int i,j;
	int count = 0;
	for (i=row; i < row+3; i++) {
		for (j=col; j < col+3; j++) {
			count += mogus[row*cols + col];
		}
	}
	return count;
}

int countsOfAll(int *mogus, int len) {
	int i;
	int count = 0;
	for (i = 0; i < len; i++) {
		count += mogus[i];
	}
	return count;
}

int countLess3(int *mogus, int rows, int cols, int row, int col) {
	int i, j;
	int count = 0;
	if (rows <= 3) {
		for (i=row; i < rows; i++) {
			for (j=col; j < col+3; j++) {
				count += mogus[row*cols + col];
			}
		}
		//return count;

	}
	if (cols <= 3) {
		for (i=row; i < row+3; i++) {
			for (j=col; j < cols; j++) {
				count += mogus[row*cols + col];
			}
		}

	}
	
	return count;
}

void shamogu() {
	int n, m, k;
	int i;
	int row, col;
	int *mogus = NULL;
	int firstCount, firstRIndex, firstCIndex, seCount, seRIndex, seCIndex;
	while (scanf("%d %d %d", &n, &m, &k) != EOF) {
		if (mogus == NULL) {
			mogus = (int*)calloc(n*m, sizeof(int));
			for (i=0; i < k; i++) {
				scanf("%d %d", &col, &row);
			}
			if ((n<=3 && m <= 6) || (m<=3 && n <= 6)) {
				firstCount = countsOfAll(mogus, m*n);
				printf("%d\n", firstCount);
			} else if (n<=3) {
				for (i=0; i<m; i++) {
					countLess3(mogus, n, m, 0, i);
				}
			} else if (m<= 3) {
				
			} else {
				
			}
		}
	}
}