#ifndef FSPRINT_H
#define FSPRINT_H

#pragma warning (disable:4996)

#define MAXCAR 100
#define _GNU_SOURCE

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_print(node* file, int with_content);
void directory_print(node* dir,int depth,int with_content,int step);
void node_print(node* nd, int depth, int with_content,int step);
char* indent(int step);
void filesystem_print(filesystem* fs,int depth,int with_content);
void print_path(node* dir);

#endif
