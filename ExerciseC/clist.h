//
//  clist.h
//  ExerciseC
//
//  Created by lunner on 10/3/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#ifndef clist_h
#define clist_h

#include <stdio.h>

typedef struct CListElmt_ {
	void *data;
	struct CListElmt_ *next;
}CListElmt;

typedef struct CList_ {
	int size;
	int (*match)(const void *key1, const void *key2);
	void (*destroy)(void *data);
	CListElmt *head;
}CList;

void clist_init(CList *list, void(*destroy)(void *data));
void clist_destroy(CList *list);
int clist_ins_next(CList *list, CListElmt *element, const void *data);
int clist_rem_next(CList *list, CListElmt *element, void **);

#define clist_size(list) ((list)->size)

#define clist_head(list) ((list)->head)

#define clist_data(element) ((element)->data)

#define clist_next(element) ((element)->next)

#endif /* clist_h */
