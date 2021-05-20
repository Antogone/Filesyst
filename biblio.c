#include "biblio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void filesystem_init(filesystem *fs){ //OK
	fs->root = malloc(sizeof(node));
	fs->root->name = malloc(10*sizeof(char));
	strcpy(fs->root->name,"root");
	fs->root->parent = NULL;
	fs->root->bro = NULL;
	fs->root->broG = NULL;
	fs->root->t = DIR;
	directory *dir = malloc(sizeof(directory));
	dir->child = NULL;
	fs->root->data = dir;
}

void filesystem_free(filesystem *fs){ // OK
	if(fs == NULL)
    return;
	free_node(fs->root);
	free(fs);
}

void free_node(node* nd){  // OK
	if(nd == NULL)
    return;
	if (nd->t == DIR){
		directory *ptr = (directory*) nd->data;
		free_node(ptr->child);
	}
	free_node(nd->bro);
	 if (nd->t == FI){
		free(nd->data);
	 }
	free(nd);
}

node* filesystem_get_root(filesystem *fsys){ // OK
	return fsys->root;
}

node* directory_find(node* dir, char* name){ // OK
	if(dir == NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;
	return find_rec(ptr->child,name);
}

node* find_rec(node* nd, char* name){ // OK
	if(nd == NULL){
    return NULL;
	}
	if(strcmp(nd->name,name) == 0){
		return nd;
	}
	else {
		node* res = malloc(sizeof(node));
		if(nd->t==DIR){
			directory *ptr = (directory*) nd->data;
			res=find_rec(ptr->child,name);
			if (res!=NULL)
				return res;
		}
		else{
			res=NULL;
		}
		//res=find_rec(nd->bro,name);
		//if (res != NULL)
		//	return res;
		return (res != NULL) ? res : find_rec(nd->bro, name);
	}
}

node* directory_add_file(node* dir, char* name){ // OK

	if(directory_find(dir,name)!= NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;
	node* fadd = malloc(sizeof(node));
	fadd->t = FI;
	fadd->name = name;
	fadd->bro = NULL;
	fadd->broG = NULL;
	fadd->parent = dir;
	file* faddfil = malloc(sizeof(file));
	faddfil->ext = strstr(name,".");
	fadd->data = faddfil;
	return directory_add_node(dir,fadd);
}

node* directory_add_directory(node* dir, char* name){ // OK
	if(directory_find(dir,name)!=NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;

	node* diradd = malloc(sizeof(node));
	diradd->name = name;
	diradd->t = DIR;
	diradd->bro = NULL;
	diradd->broG = NULL;
	diradd->parent = dir;
	directory* diraddfil = malloc(sizeof(directory));
	diradd->data = diraddfil;

	return directory_add_node(dir,diradd);
}

node* directory_add_node(node* dir, node* add){ // OK
	directory* ptr = (directory*) dir->data;
	if(ptr->child==NULL){
		ptr->child = add;
	}
	else {
		node* freebro = ptr->child;
		while (freebro->bro!=NULL) {
			freebro = freebro->bro;
		}
		add->broG = freebro;
		freebro->bro = add;
	}
	return add;
}

int directory_remove_node(node* dir, char* name){ //OK
	node* rm = directory_find(dir,name);
	if(rm==NULL)
		return 1;

	// Redirection
	node* prev = rm->broG;
	node* next = rm->bro;
	node* par = rm->parent;
	directory* ptr = (directory *) par->data;
	if(ptr->child!=rm){
		if(next!=NULL){
			next->broG = prev;
		}
		prev->bro = next;
	}
	else{
		if(next!=NULL){
			next->broG = NULL;
		}
		ptr->child=NULL;
	}
	rm->bro = NULL;
	rm->broG = NULL;
	free_node(rm);
	return 0;
}


/***********************************************/


void file_print(node* file, int with_content) { // Pas certain
	printf("file: %s", file->name);
	if (with_content != 0) {
		struct file* ptr = (struct file*)file->data;
		printf(",content: %s,size :%d", ptr->cont->desc,ptr->cont->taille);
	}
	printf("\n");
}



void directory_print(node* dir, int depth, int with_content,int step) {//penser à mettre step=0 au premier appel
	// depth = profondeur max
	// with_content = si on affiche le contenu des fichiers
	printf("directory: %s\n",dir->name);
	if (depth<=0){
		directory* ptr = (directory*)dir->data;
		node_print(ptr->child,depth,with_content,step+1);
	}
	else{
		depth-=1;
		if(depth){
			directory* ptr = (directory*)dir->data;
			node_print(ptr->child,depth,with_content,step+1);
		}
	}
}
void node_print(node* nd, int depth, int with_content,int step){
		while (nd!=NULL){
			char* strplus = indent(step);
			printf("%s",strplus);
			if(nd->t==DIR){
				directory_print(nd,depth,with_content,step);
			}
			else{
				file_print(nd,with_content);
			}
			nd = nd->bro;
		}
}
char* indent(int step){
	char* strplus = malloc((step+10)*sizeof(char));
	char* strdec = "\t";
	for (int i = 0; i < step; i++) {
		strcat(strplus, strdec);
	}
	strcat(strplus, "+ ");
	return strplus;
}
void filesystem_print(filesystem* fs, int depth, int with_content) {
	printf("filesystem");
	if(fs->filesystname!=NULL){
		printf("%s", fs->filesystname);
	}
	printf("\n");
	node_print(fs->root,depth,with_content,0);
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


int main(){
	filesystem *fs = malloc(sizeof(filesystem));
	filesystem_init(fs);
	directory_add_file(fs->root,"fic.txt");
	filesystem_print(fs,-1,0);
	directory_remove_node(fs->root,"fic.txt");
	filesystem_print(fs,-1,0);
	return 0;

}
