//
//  set.c
//  ExerciseC
//
//  Created by lunner on 10/2/15.
//  Copyright © 2015 lunner. All rights reserved.
//
#include <stdlib.h>
#include <string.h>
#include "set.h"

// s1 union(U) s2
// s1 intersection(&) s2
// s1 difference(-) s2
// nil empty set

// s U nil = s
// s & nil = nil

// s & s = s
// s U s = s

// s1 & s2 = s2 & s1
// s1 U s2 = s2 U s1

// s1 & (s2 & s3) = (s1 & s2) & s3
// s1 U (s2 U s3) = (s1 U s2) U s3

// s1 & (s2 U s3) = (s1 & s2) U (s1 & s3)
// s1 U (s2 & s3) = (s1 U s2) & (s1 U s3)

// s1 & (s1 U s2) = s1
// s1 U (s1 & s2) = s1

// s1 - (s2 U s3) = (s1 - s2) & (s1 - s3)
// s1 - (s2 & s3) = (s1 - s2) U (s1 - s3)


void set_init(Set *set, int (*match)(const void *key1, const void *key2), void (*destroy)(void *data)) {
	list_init(set, destroy);
	set->match = match;
}

int set_insert(Set *set, const void *data) {
	if (set_is_member(set, data)) {
		return 1;
	}
	return list_ins_next(set, list_tail(set), data);
}

int set_remove(Set *set, void **data) {
	ListElmt *member, *prev;
	prev = NULL;
	
	for (member = list_head(set); member != NULL; member = list_next(member)) {
		if (set->match(*data, list_data(member))) {
			break;
		}
		
		prev = member;
	}
	
	if (member == NULL) {
		return -1;
	}
	
	return list_rem_next(set, prev, data);
	
}

int set_union(Set *setu, const Set *set1, const Set *set2) {
	ListElmt *member;
	void *data;
	set_init(setu, set1->match, NULL);
	for (member = list_head(set1); member != NULL; member = list_next(member)) {
		data = list_data(member);
		if (list_ins_next(setu, list_tail(setu), data) != 0) {
			set_destory(setu);
			return -1;
		}
	}
	
	for (member = list_head(set2); member != NULL; member = list_next(member)) {
		if (set_is_member(set1, list_data(member))) {
			continue;
		} else {
			data = list_data(member);
			if (list_ins_next(setu, list_tail(setu), data) != 0) {
				set_destory(setu);
				return -1;
			}
		}
	}
	return 0;
}

int set_inersection(Set *seti, const Set *set1, const Set *set2) {
	ListElmt *member;
	void *data;
	set_init(seti, set1->match, NULL);
	for (member = list_head(set1); member != NULL; member = list_next(member)) {
		if (set_is_member(set2, list_data(member))) {
			data = list_data(member);
			if (list_ins_next(seti, list_tail(seti), data) != 0) {
				set_destroy(seti);
				return -1;
			}
		}
	}
	return 0;
}

