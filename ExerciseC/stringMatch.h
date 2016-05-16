//
//  stringMatch.h
//  ExerciseC
//
//  Created by lunner on 9/24/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#ifndef stringMatch_h
#define stringMatch_h

#include <stdio.h>
int *naive_string_matcher(const char* str, const char *pattern);
int *KMP_matcher(const char *str, const char *pattern);
#endif /* stringMatch_h */
