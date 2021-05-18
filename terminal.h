#ifndef TERMINAL_H
#define TERMINAL_H
#pragma warning (disable:4996)

#define MAXCAR 100
#define _GNU_SOURCE

#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <Windows.h>

void clearEcran();
size_t my_getline(char** lineptr, size_t* n, FILE* stream);

#endif
