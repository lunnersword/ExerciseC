//
//  set.h
//  ExerciseC
//
//  Created by lunner on 10/2/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#ifndef set_h
#define set_h

#include <stdlib.h>
#include "list.h"

typedef List Set;

void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data));//O(1)

void set_destory(Set *set); //O(n)

int set_insert(Set *set, const void *data);//O(n) 
int set_remove(Set *set, void **data); //O(n)
int set_union(Set *setu, const Set *set1, const Set *set2);
int set_intersection(Set *seti, const Set *set1, const Set *set2);
int set_difference(Set *setd, const Set *set1, const Set *set2);
int set_is_member(const Set *set, const void *data);
int set_is_subset(const Set *set1, const Set *set2);
int set_is_equal(const Set *set1, const Set *set2);

#define set_size(set) ((set)->size)

#endif /* set_h */
