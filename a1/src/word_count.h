#ifndef A1_H
#define A1_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <ctype.h>

#define MAX_FILESIZE    5000
#define MAX_WORD_CNT    750
#define MAX_WORD_LEN    35 


void low_case(char* str);
void tokenize_string(char* line);
void read_file(FILE* data,char buf[]);
void print_a();
void print_b();
void print_c();
int by_freq(const void* a, const void* b);
int by_length(const void* a, const void* b);
int by_alphanum(const void* a, const void* b);


#endif
