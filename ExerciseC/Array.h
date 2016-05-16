//
//  Array.h
//  ExerciseC
//
//  Created by lunner on 9/23/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#ifndef Array_h
#define Array_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct {
	char *base;
	int size_pos;
	int count;
	int elementSize;
}Array;

int initArray(Array *array, int elementSize);
void deinitArray(Array *array);

int appendToArray(Array* array, void *elem);

int lastElementOfArray(Array *array, void *elem);
int firstElementOfArray(Array *array, void *elem);
int getElementOfArray(Array *array,int index, void *elem);

bool isArrayEmpty(Array *array);

int removeFromArray(Array *array, int index, void *elem);
int removeFirstElementOfArray(Array *array, void *elem);
int removeLastElementOfArray(Array *array, void *elem) ;
#endif /* Array_h */
