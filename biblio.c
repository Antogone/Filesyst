#include "biblio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void filesystem_init(filesystem *fs){
	strcpy(fs->root->name,"root");
	fs->root->parents = NULL;
	fs->root->t = DIR;
	directory *dir = malloc(sizeof(directory));
	dir->child = NULL;
	dir->bro = NULL;
	fs->root->data = dir;
	free(dir);
}

void filesystem_free(filesystem *fs){
	if(fs == NULL)
    return;
	directory *ptr = (directory*) fs->root;
	free_node(ptr->child);
	free_node(ptr->bro);//normalement pas nécessaire car root ne devrait pas avoir de frère
	free(fs);
}

void free_node(node* nd){
	if(nd == NULL)
    return;
	if (nd->t == 0){
		directory *ptr = (directory*) nd->data;
		free_node(ptr->child);
		free_node(ptr->bro);
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
	if(strcmp(ptr->child->name,name)==0){
		return ptr->child;
	}
	if(strcmp(ptr->bro->name,name)==0){
		return ptr->bro;
	}
	if(ptr->child->t==DIR){
		return directory_find(ptr->child->data,name);
	}
	if(ptr->bro->t==DIR){
		return directory_find(ptr->bro->data,name);
	}
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
