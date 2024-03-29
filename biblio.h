#ifndef BIBLIO_H
#define BIBLIO_H

#pragma warning (disable:4996)
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


typedef enum type { DIR, FI }type;

typedef struct node {
	char* name;
	type t;
	void *data;
	struct node* parent;
	struct node* bro;
	struct node* broG;
}node;

typedef struct filesystem {
	node* root;
	char* filesystname;
}filesystem;


typedef struct file_content {
	char* desc;
	int fsize;
}file_content;

typedef struct file {
	file_content* cont;
}file;

typedef struct directory {
	node* child;
}directory;


void filesystem_init(filesystem *fs);
void filesystem_free(filesystem *fs);
void free_node(node* n);
node* filesystem_get_root(filesystem *fsys);
node* directory_find(node* dir, const char* name);
node* find_rec(node*dir, const char* name);
node* directory_add_file(node* dir, const char* name);
node* directory_add_directory(node* dir, const char* name);
node* directory_add_node(node* dir, node* add);
int directory_remove_node(node* dir, const char* name);
file_content* file_get_content(node* file);
int file_set_content(node* file,file_content* content);
file_content* crea_content(char* valeur);

#endif
