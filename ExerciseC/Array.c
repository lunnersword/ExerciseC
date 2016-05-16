//
//  Array.c
//  ExerciseC
//
//  Created by lunner on 9/23/15.
//  Copyright © 2015 lunner. All rights reserved.
//

#include "Array.h"

/*
 * prime array
 */

static int prime_array[] = {
	7, 
	17,             
	37,            
	79,            
	163,           
	331,           
	673,           
	1361,          
	2729,          
	5471,          
	10949,         
	21911,         
	43853,         
	87719,         
	175447,        
	350899,        
	701819,        
	1403641,       
	2807303,       
	5614657,       
	11229331,      
	22458671,      
	44917381,      
	89834777,      
	179669557,     
	359339171,     
	718678369,     
	1437356741,    
	2147483647     
};      

/* the max of size_pos is 28 */

#define SIZE_POS_MAX 28

int initArray(Array *array, int elementSize) {
	array->size_pos = 0;
	array->count = 0;
	array->elementSize = elementSize;
	array->base = (char*)malloc(elementSize * prime_array[0]);
	if (!array->base) {
		return 0;
	} 
	return 1;
}

void deinitArray(Array *array) {
	if (array->base) {
		free(array->base);
	}
	array->size_pos = 0;
	array->count = 0;
	array->elementSize = 0;
}

static int incrementArraySize(Array *array) {
	if (array->size_pos - SIZE_POS_MAX >= 0) {
		return 0;
	}
	array->size_pos += 1;
	array->base = (char*)realloc(array->base, array->elementSize * prime_array[array->size_pos]);
	if (array->base) {
		return 1;
	}else {
		return 0;
	}
}

int appendToArray(Array* array, void *elem) {
	char *temp;
	if (!array->base) {
		return 0;
	}
	if (prime_array[array->size_pos] - array->count <= 1) {
		incrementArraySize(array);
	}
	//array->base[array->count++] = elem;
	temp = (char*)elem;
	memcpy(array->base+array->elementSize*array->count, temp, array->elementSize);
	array->count++;
	return 1;
	
}

int insertIntoArray(Array *array, int index, void *elem) {
	char *temp = (char*)elem;
	if (!array->base) {
		return 0;
	}
	if (index < 0 || index > array->count) {
		return 0;
	}
	if (prime_array[array->size_pos] - array->count <= 1) {
		incrementArraySize(array);
	}
	if (index != array->count) {
		memmove(array->base + array->elementSize*(index), array->base + array->elementSize*(index+1), array->elementSize*(array->count-index));
		
	}
	memcpy(array->base+array->elementSize*index, temp, array->elementSize);
	array->count++;

	return 1;
}

int lastElementOfArray(Array *array, void *elem) {
	char *temp;
	temp = (char*)elem;
	if (!array->base) {
		return 0;
	}
	memcpy(temp, array->base+array->elementSize*(array->count-1), array->elementSize);
	return 1;
	
}
int firstElementOfArray(Array *array, void *elem) {
	char *temp = (char*)elem;
	if (!array->base) {
		return 0;
	}
	memcpy(temp, array->base, array->elementSize);
	return 1;
}

int getElementOfArray(Array *array,int index, void *elem) {
	char *temp = (char*)elem;
	if (!array->base) {
		return 0;
	}
	memcpy(temp, array->base + array->elementSize*index, array->elementSize);
	return 1;

}
bool isArrayEmpty(Array *array) {
	return array->count == 0;
}

int removeFromArray(Array *array, int index, void *elem) {
	char *temp = (char*)elem;
	if (!array->base) {
		return 0;
	}
	if (index >= array->count || index < 0) {
		return 0;
	}
	memcpy(temp, array->base + array->elementSize*index, array->elementSize);
	if (index != array->count-1) {
		memmove(array->base+array->elementSize*index, array->base+array->elementSize*(index+1), array->count-(index+1)*array->elementSize);
	}
	array->count--;

	return 1;
}

int removeFirstElementOfArray(Array *array, void *elem) {
	return removeFromArray(array, 0, elem);
}

int removeLastElementOfArray(Array *array, void *elem) {
	return removeFromArray(array, array->count-1, elem);
}


 
