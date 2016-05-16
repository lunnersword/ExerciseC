//
//  lists.c
//  ExerciseC
//
//  Created by lunner on 10/3/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#include "list.h"
#include <stdlib.h>
#include <string.h>

void list_init(List *list, void (*destroy)(void *data)) {
	list->size = 0;
	list->destroy = destroy;
	list->head = NULL;
	list->tail = NULL;
}

void list_destroy(List *list) {
	void *data;
	while (list_size(list) > 0) {
		if (list_rem_next(list, NULL, (void**)&data) == 0 && list->destroy != NULL) {
			list->destroy(data);
		}
	}
	//No operations are allowed now, but clear the structure as a precaution
	memset(list, 0, sizeof(List));
	
}

int list_ins_next(List *list, ListElmt *element, const void *data) {
	ListElmt *new_element;
	// allocate storage for the element.
	if ((new_element = (ListElmt*)malloc(sizeof(ListElmt))) == NULL) {
		return -1;
	}
	//insert the element into the list.
	new_element->data = (void*)data;
	
	if (element == NULL) {
		//handle insertion at the head of the lsit.
		if (list_size(list) == 0) {
			list->tail = new_element;
		}
		
		new_element->next = list->head; //if size is 0 head is NULL
		list->head = new_element;
	} else {
		// handle insertion somewhere other than at the head
		if (element->next == NULL) {
			list->tail = new_element;
		}
		new_element->next = element->next;
		element->next = new_element;
	}
	list->size++;
	return 0;
}

int list_rem_next(List *list, ListElmt *element, void **data) {
	ListElmt *old_element;
	// Do not allow removal from an empty list.
	
	if (list_size(list) == 0) {
		return -1;
	}
	if (element == NULL) {
		//handle removal from the head of the list.
		*data = list->head->data;
		old_element = list->head;
		list->head = list->head->next;
		
		if (list_size(list) == 1) {
			list->tail = NULL;
		}
	} else {
		//handle removal from somewhere other than the head.
		if (element->next == NULL) {
			return -1;
		}
		*data = element->next->data;
		old_element = element->next;
		element->next = element->next->next;
		
		if (element->next == NULL) {
			list->tail = element;
		}
	}
	
	//free the storage allocated by the abstract datatype.
	free(old_element);
	
	list->size--;
	return 0;
}


