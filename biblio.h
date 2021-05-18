#ifndef BIBLIO_H
#define BIBLIO_H

#pragma warning (disable:4996)



typedef struct node {
	char* name;
	int type;
	void *data;
	struct node* parents;
}node;

// .. = remonte
// ./ descend


typedef struct filesystem { // racine
	node* root;
	char* filesystname;
}filesystem;


typedef struct file_content {
	char* desc;
}file_content;

typedef struct file {
	file_content cont;
}file;

typedef struct directory {
	node* child;
	node* bro;
}directory;



void filesystem_init(filesystem *fs);
void filesystem_free(filesystem *fs);
void free_node(node* n);
node* filesystem_get_root(filesystem *fsys);
node* directory_find(node* dir, const char* name);
node* directory_add_file(node* dir, const char* name);
node* directory_add_directory(node* dir, const char* name);
int directory_remove_node(node* dir, const char* name);
file_content* file_get_content(node* file);
int file_set_content(node* file,file_content* content);
void file_print(node* file,int with_content);
void directory_print(node* dir,int depth,int with_content);
void filesystem_print(filesystem* fs,int depth,int with_content);
void foo(node* nd);
#endif
