//
//  literalToHeap.c
//  ExerciseC
//
//  Created by lunner on 9/26/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#include "literalToHeap.h"
#include "types.h"
#include <stdlib.h>
#include <string.h>

int64 *int64ToHeap(const int64 integer) {
	int64 *Int;
	Int = (int64*)malloc(sizeof(int64));
	Int[0] = integer;
	return Int;
}
uint64 *uint64ToHeap(const uint64 integer) {
	uint64 *Int = (uint64*)malloc(sizeof(uint64));
	Int[0] = integer;
	return Int;
}
int32 *int32ToHeap(const int32 integer) {
	int32 *Int;
	Int = (int32*)malloc(sizeof(int32));
	Int[0] = integer;
	return Int;
}

uint32 *uint32ToHeap(const uint32 integer) {
	uint32 *UInt;
	UInt = (uint32 *)malloc(sizeof(uint32));
	UInt[0] = integer;
	return UInt;
}

int16 *int16ToHeap(const int16 integer) {
	int16 *temp;
	temp = (int16*)malloc(sizeof(int16));
	temp[0] = integer;
	return temp;
}

uint16 *uint16ToHeap(const uint16 integer) {
	uint16 *temp = (uint16*)malloc(sizeof(uint16));
	temp[0] = integer;
	return temp;
}

int8 *int8ToHeap(const int8 integer) {
	int8 *temp = (int8*)malloc(sizeof(int8));
	temp[0] = integer;
	return temp;
}

uint8 *uint8ToHeap(const uint8 integer) {
	uint8 *temp = (uint8*)malloc(sizeof(uint8));
	temp[0] = integer;
	return temp;
}

double *doubleToHeap(const double f) {
	double *temp = (double*)malloc(sizeof(double));
	*temp = f;
	return temp;
}
float *floatToHeap(const float f) {
	float *temp = (float*)malloc(sizeof(float));
	*temp = f;
	return temp;
}

char *strToHeap(const char* literal) {

	char *str = (char*)malloc(sizeof(char)*(strlen(literal)+1));
	//char *p = str;
	strcpy(str, literal);
//	while (literal) {
//		*p++ = *literal++;
//	}
	return str;
}

