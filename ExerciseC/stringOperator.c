//
//  stringOperator.c
//  ExerciseC
//
//  Created by lunner on 9/17/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <string.h>

// MARK:最长公共子序列问题
//1
int c[100][100];
int LCS_LENGTH(const char *str1, const char *str2) {
	int m,n;
	int i,j;
	if (str1 == NULL || str2 == NULL) {
		return 0;
	}
	m = strlen(str1);
	n = strlen(str2);
	for (i = 1 ; i < n ; i++) {
		c[0][i] = 0;
	}
	c[0][0]=0;
	for (i=1; i <= m; i++) {
		for (j=1; j <= n; j++) {
			if (str1[i] == str2[j]) {
				c[i][j] = c[i-1][j-1] + 1;
			} else {
				c[i][j] = (int)fmax(c[i][j-1], c[i-1][j]);
			}
		}
	}
	return c[m][n];
}


//int c[100][100];
int LCS_Memo(const char* str1, const char *str2, int **c, int i, int j) {
	int p,q;
	if (c[i][j] < INT_MAX) {
		return c[i][j];
	}
	if ((i==0) || (j==0)) {
		c[i][j] = 0;
	} else if (str1[i] == str2[j]) {
		c[i][j] = LCS_Memo(str1, str2, c, j-1, j-1) + 1;
	} else {
		p = LCS_Memo(str1, str2, c, i-1, j);
		q = LCS_Memo(str1, str2, c, i, j-1);
		c[i][j] = (int)fmax(p, q);
	}
	return c[i][j];
}

int LCS_Length(const char* str1, const char *str2) {
	int m = strlen(str1);
	int n = strlen(str2);
	int i,j;
    int **c = (int**)malloc(sizeof(int*)*m);
    for (i = 0; i < m; i++) {
        c[i] = (int*)malloc(sizeof(int)*n);
    }
	for (i=0;i<100;i++) {
		for (j=0;j<100;j++) {
			c[i][j] = INT_MAX;
		}
	}
	return LCS_Memo(str1, str2, c, m , n);
}

/// TODO: k maybe -1 fix it
char* bigNumberAdd(char *a, char *b, int m, int n) {
	int jin = 0;
	int s = 0;
	int i,j;
	int k = (int)fmax(m,n);
    char *sum = (char*)malloc(sizeof(char)*(k+1));
    // a is awlays point to the array with longer length
    sum[0] = '0';
    if (n > m) {
        char *temp;
        temp = a;
        a = b;
        b = temp;
    }
	sum[0] = 0;
	for(i = m-1, j = n-1; i >= 0 && j >= 0; i--, j--) {
		s = (a[i] - '0') + (b[j] - '0') + jin;
		sum[k--] = '0' + s % 10;
		jin = s / 10;
	}
	while(jin&&i>=0) {
		s = (a[i--] - '0') + jin;
		sum[k--] = s % 10 + '0';
		jin = s / 10;
	}
    if (jin && k >= 0) {
        sum[k] = jin + '0';
    }
    return sum;
}