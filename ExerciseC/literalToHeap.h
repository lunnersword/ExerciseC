//
//  literalToHeap.h
//  ExerciseC
//
//  Created by lunner on 9/26/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#ifndef literalToHeap_h
#define literalToHeap_h
#include "types.h"
int64 *int64ToHeap(const int64 integer); 
uint64 *uint64ToHeap(const uint64 integer);
int32 *int32ToHeap(const int32 integer);
uint32 *uint32ToHeap(const uint32 integer);
int16 *int16ToHeap(const int16 integer);
uint16 *uint16ToHeap(const uint16 integer);
int8 *int8ToHeap(const int8 integer);
uint8 *uint8ToHeap(const uint8 integer);
double *doubleToHeap(const double f);
float *floatToHeap(const float f);
char *strToHeap(const char* literal);

#endif /* literalToHeap_h */
