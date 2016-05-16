//
//  dict.h
//  ExerciseC
//
//  Created by lunner on 9/24/15.
//  Copyright © 2015 lunner. All rights reserved.
//
// MARK: important the dict's value must be allocated in the heap, and you should not free it excipilitly. The dict manage the heap object's life cycle.
#ifndef dict_h
#define dict_h

#include <stdio.h>
#include <stdlib.h>
typedef struct _node {
	char *key; 
	void *value; 
	struct _node *next; 
} bucket_t; 

typedef struct {
	int size_pos; //size_pos in prime_array, the size of dict = prime_array[size_pos]
	int ele_num; //ele number in dict
	bucket_t **bucket; 
} dict_t; 

/* API */

int dict_init(dict_t *); 

int dict_size(dict_t *); 

void dict_set(dict_t *, char *, void *); 

int dict_get(dict_t *, char *, void **); 

int dict_del(dict_t *, char *); 

void dict_keys(dict_t *, char **); 

void dict_reset(dict_t *); 

void dict_destory(dict_t *); 

int dict_iter(dict_t *, char **, void **); 

int dict_contains(dict_t *dict, char *key );


void dictExample() ;

#endif /* dict_h */
