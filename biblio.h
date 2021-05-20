#ifndef BIBLIO_H
#define BIBLIO_H

#pragma warning (disable:4996)

typedef enum type { DIR, FI }type;

typedef struct node {
	char* name;
	type t;
	void *data;
	struct node* parent;
	struct node* bro;
	struct node* broG;
}node;

// .. = remonte
// ./ descend


typedef struct filesystem { // racine
	node* root;
	char* filesystname;
}filesystem;


typedef struct file_content {
	char* desc;
	int taille;
}file_content;

typedef struct file {
	file_content* cont;
	char* ext; // .txt .
}file;

typedef struct directory {
	node* child;
}directory;


// OK
void filesystem_init(filesystem *fs);
void filesystem_free(filesystem *fs);
void free_node(node* n);


// OK
node* filesystem_get_root(filesystem *fsys);

// OK
node* directory_find(node* dir, char* name);
node* find_rec(node*dir, char* name);


// OK
node* directory_add_file(node* dir, char* name);
node* directory_add_directory(node* dir, char* name);
node* directory_add_node(node* dir, node* add);


//OK
int directory_remove_node(node* dir, char* name);

//PAS OK
file_content* file_get_content(node* file);
int file_set_content(node* file,file_content* content);

#include "fsprint.h"
//OK
// void file_print(node* file, int with_content);
// void directory_print(node* dir,int depth,int with_content,int step);
// void node_print(node* nd, int depth, int with_content,int step);
// char* indent(int step);
// void filesystem_print(filesystem* fs,int depth,int with_content);

#endif
