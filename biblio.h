#ifndef BIBLIO_H
#define BIBLIO_H

#pragma warning (disable:4996)

typedef enum type { DIR, FI }type;

typedef struct node {
	char* name;
	type t;
	void *data;
	struct node* parents;
	struct node* bro;
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
}directory;


// I - a finir
void filesystem_init(filesystem *fs);
void filesystem_free(filesystem *fs);
void free_node(node* n);


// A
node* filesystem_get_root(filesystem *fsys);

// A - doit finir
node* directory_find(node* dir, const char* name);
node* find_rec(node*dir,const char* name);
// I
node* directory_add_file(node* dir, const char* name);
node* directory_add_directory(node* dir, const char* name);
node* directory_add_node(node* dir, node* add);


//I
int directory_remove_node(node* dir, const char* name);
file_content* file_get_content(node* file);
int file_set_content(node* file,file_content* content);

//A
void file_print(node* file,int with_content);
void directory_print(node* dir,int depth,int with_content);
void filesystem_print(filesystem* fs,int depth,int with_content);


#endif
