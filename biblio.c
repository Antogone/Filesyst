#include "biblio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void filesystem_init(filesystem *fs){
	strcpy(fs->root->name,"root");
	fs->root->parents = NULL;
	fs->bro = NULL;
	fs->root->t = DIR;
	directory *dir = malloc(sizeof(directory));
	dir->child = NULL;
	fs->root->data = dir;
	free(dir);
}

void filesystem_free(filesystem *fs){
	if(fs == NULL)
    return;
	directory *ptr = (directory*) fs->root;
	free_node(ptr->child);
	free(fs);
}

void free_node(node* nd){
	if(nd == NULL)
    return;
	free_node(nd->bro);
	if (nd->t == 0){
		directory *ptr = (directory*) nd->data;
		free_node(ptr->child);
	}
  if (nd->t ==1){
		file *ptr = (file*) nd->data;
		free(ptr->cont);
  }
	free(nd);
}

node* filesystem_get_root(filesystem *fsys){
	return fsys->root;
}

node* directory_find(node* dir, const char* name){
	if(dir == NULL)
    return;
	directory *ptr = (directory*) dir->data;
	return find_rec(ptr->child);
}
node* find_rec(node* nd, const char* name){
	if(nd == NULL)
    return;
	if(strcmp(nd->name,name) == 0){
		return nd;
	}
	else {
		node* res = malloc(sizeof(node));
		if(nd->t==DIR){
			directory *ptr = (directory*) dir->data;
			res=find_rec(ptr->child,name);
		if (res!=NULL) return res;
		}
		res=find_rec(nd->bro,name);
		return res;
	}
}

node* directory_add_file(node* dir, const char* name){

	if(directory_find(dir,name)!=NULL){
		return;
	}

	directory *ptr = (directory*) dir->data;

	node* fadd = malloc(sizeof(node);
	fadd->name = name;
	fadd->type = FI;
	file faddfil;
	fadd->data = faddfil;

	return directory_add_node(dir,diradd);
}

node* directory_add_directory(node* dir, const char* name){
	if(directory_find(dir,name)!=NULL){
		return;
	}
	directory *ptr = (directory*) dir->data;

	node* diradd = malloc(sizeof(node);
	diradd->name = name;
	diradd->type = DIR;
	directory diraddfil;
	diradd->data = diraddfil;

	return directory_add_node(dir,diradd);
}

node* directory_add_node(node* dir, node*add){
	directory *ptr = (directory*) dir->data;
	if(ptr->child==NULL){
		ptr->child = *add;
	}
	else {
		node* freebro = ptr->child->bro;
		while (freebro!=NULL) {
			freebro = freebro->bro;
		}
		freebro = *add;
	}
	return freebro;
}

int directory_remove_node(node* dir, const char* name){
	node* rm = directory_find(dir,name);
	if(rm==NULL)return 1;
	node* next = rm->bro;
	rm->bro = NULL;
	free(rm);
	directory_add_node(dir,next);
	return 0;
}

/*
 * modèle d'utilisation des types de noeud dans une fonction
 *
 * void foo(node *nd) {
 * 	if (nd->type == 0){
 * 		directory *ptr = (directory*) nd->data;
 * 	}
 * 	if (nd->type ==1){
 * 		file *ptr = (file*) nd->data;
 * 	}
 * }
 *
 * */


//
//int main(){
//	filesystem *fs;
//	fs = malloc(sizeof(filesystem));
//	fs->root->name = malloc(10*sizeof(char));
//	filesystem_init(fs);
//	//filesystem_free(fs);
//	return 0;
//}
