//
//  selects.h
//  ExerciseC
//
//  Created by lunner on 9/24/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#ifndef selects_h
#define selects_h
#include "sortHeaders.h"
int minimum(int A[], int p, int r);
int maximum(int A[], int p, int r);
int randomized_select(int A[], int p, int r, int k);
int select_kth_smallest(const int *A, int len, int k);
#endif /* selects_h */
