#include "biblio.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void filesystem_init(filesystem *fs){ //OK
	strcpy(fs->root->name,"root");
	fs->root->parents = NULL;
	fs->root->bro = NULL;
	fs->root->broG = NULL;
	fs->root->t = DIR;
	directory *dir = malloc(sizeof(directory));
	dir->child = NULL;
	fs->root->data = dir;
	// free(dir);  --> bah non sinon ça le supprime ? fin le free me parait illogique ici genre ça eneleve l'initialisation
}

void filesystem_free(filesystem *fs){ // OK
	if(fs == NULL)
    return;
	directory *ptr = (directory*) fs->root;
	free_node(ptr->child);
	free(fs);
}

void free_node(node* nd){ // A discuter ensemble mais OK
	if(nd == NULL)
    return;
	//free_node(nd->broG);
	free_node(nd->bro);
	if (nd->t == 0){
		directory *ptr = (directory*) nd->data;
		free_node(ptr->child);
	}
  if (nd->t ==1){
		free(nd->data);
  }
	free(nd);
}

/***********************************************/

node* filesystem_get_root(filesystem *fsys){ // OK
	return fsys->root;
}

node* directory_find(node* dir, char* name){ // OK mais a voir ensemble
	if(dir == NULL)
    return NULL;
	directory *ptr = (directory*) dir->data;
	return find_rec(ptr->child,name);
}

node* find_rec(node* nd, char* name){ // OK mais a voir ensemble
	if(nd == NULL)
    return NULL;
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
		//res=find_rec(nd->bro,name);
		//if (res != NULL)
		//	return res;

		return (res != NULL) ? res : find_rec(nd->bro, name);
	}
}

/***********************************************/


node* directory_add_file(node* dir, const char* name){ // A DISCUTER ENSEMBLE

	if(directory_find(dir,name)!=NULL){ 
		return NULL;
	}

	directory *ptr = (directory*) dir->data;

	node* fadd = malloc(sizeof(node));
	fadd->name = name;
	fadd->t = FI;
	file faddfil;
	fadd->data = &faddfil;  // faddfill est vide donc on ajoute rien la c'est problème ?

	return directory_add_node(dir,fadd);
}

node* directory_add_directory(node* dir, char* name){ // A discuter Ensemble
	if(directory_find(dir,name)!=NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;

	node* diradd = malloc(sizeof(node));
	diradd->name = name;
	diradd->t = DIR;
	diradd->parents = dir;
	directory diraddfil;
	diradd->data = &diraddfil; // CHelou aussi a discuter ensemble

	return directory_add_node(dir,diradd);
}

node* directory_add_node(node* dir, node* add){ // Me semble OK
	directory *ptr = (directory*) dir->data;
	if(ptr->child==NULL){
		ptr->child = add;
	}
	else {
		node* freebro = ptr->child->bro;
		while (freebro!=NULL) {
			freebro = freebro->bro;
		}
		freebro = add;
	}
	return add;
}

int directory_remove_node(node* dir, const char* name){ // PAS OK - ne supprime pas vraiment faut juste redirectionner les bro et on doit supprimer les childs ?
	node* rm = directory_find(dir,name);
	if(rm==NULL)
		return 1;
	node* next = rm->bro;
	rm->bro = NULL;
	free(rm);
	directory_add_node(dir,next);
	return 0;

}

/***********************************************/


void file_print(node* file, int with_content) {
	if (with_content != 0) {
		struct file* ptr = (struct file*)file->data;
		printf("%s", ptr->cont.desc);
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
