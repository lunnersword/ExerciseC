//
//  fmt.c
//  ExerciseC
//
//  Created by lunner on 8/8/15.
//  Copyright (c) 2015 lunner. All rights reserved.
//

#include <stdio.h>
#include "line.h"
#include "word.h"
#define MAX_WORD_LEN 20
int mainfunc() {
	char word[MAX_WORD_LEN+2];
	int word_len;
	
	clear_line();
	for (;;){
		read_word(word, MAX_WORD_LEN+1);
		word_len = strlen(word);
		
		if (word_len == 0) {
			flush_line();
			return 0;
		}
		if (word_len > MAX_WORD_LEN)
			word[MAX_WORD_LEN] = '*';
		if (word_len + 1 > space_remaining()) {
			write_line();
			clear_line();
		}
		add_word(word);
	}
}
