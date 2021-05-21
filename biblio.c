#include "biblio.h"
#include "fsprint.h"




void filesystem_init(filesystem *fs){
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

void filesystem_free(filesystem *fs){
	if(fs == NULL)
    return;
	free_node(fs->root);
	free(fs);
}

void free_node(node* nd){
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

node* filesystem_get_root(filesystem *fsys){
	return fsys->root;
}

node* directory_find(node* dir, const char* name){
	if(dir == NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;
	return find_rec(ptr->child,name);
}

node* find_rec(node* nd, const char* name){
	if(nd == NULL){
    return NULL;
	}
	if(strcmp(nd->name,name) == 0){
		return nd;
	}
	// else {
	// 	node* res = malloc(sizeof(node));
	// 	if(nd->t==DIR){
	// 		directory *ptr = (directory*) nd->data;
	// 		res=find_rec(ptr->child,name);
	// 		if (res!=NULL)
	// 			return res;
	// 	}
	// 	else{
	// 		res=NULL;
	// 	}
	// 	return (res != NULL) ? res : find_rec(nd->bro, name);
	// } recherche en profondeur pas utile pour l'instant
	return find_rec(nd->bro, name);
}

node* directory_add_file(node* dir, const char* name){

	if(directory_find(dir,name)!= NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;
	node* fadd = malloc(sizeof(node));
	fadd->t = FI;
	char* cpname = malloc(100*sizeof(char));
	strcpy(cpname,name);
	fadd->name = cpname;
	fadd->bro = NULL;
	fadd->broG = NULL;
	fadd->parent = dir;
	file* faddfil = malloc(sizeof(file));
	faddfil->cont = malloc(sizeof(file_content));
	faddfil->cont->fsize = 0;
	fadd->data = faddfil;

	return directory_add_node(dir,fadd);
}

node* directory_add_directory(node* dir, const char* name){
	if(directory_find(dir,name)!=NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;
	node* diradd = malloc(sizeof(node));
	char* cpname = malloc(100*sizeof(char));
	strcpy(cpname,name);
	diradd->name = cpname;
	diradd->t = DIR;
	diradd->bro = NULL;
	diradd->broG = NULL;
	diradd->parent = dir;
	directory* diraddfil = malloc(sizeof(directory));
	diradd->data = diraddfil;

	return directory_add_node(dir,diradd);
}

node* directory_add_node(node* dir, node* add){
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

int directory_remove_node(node* dir, const char* name){
	node* rm = directory_find(dir,name);
	if(rm==NULL)
		return 1;
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
		ptr->child=next;
	}
	rm->bro = NULL;
	rm->broG = NULL;
	free_node(rm);
	return 0;
}

file_content* file_get_content(node* file) {
	struct file* ptr = (struct file*)file->data;
	return ptr->cont;
}

int file_set_content(node* file, file_content* content) {
	struct file* ptr = (struct file*)file->data;
	free(ptr->cont);
	ptr->cont = malloc(sizeof(file_content));
	ptr->cont->fsize = content->fsize;
	ptr->cont->desc = (char*) content->desc;
	return 0;
}

file_content* crea_content(char* valeur) {
	file_content* fic = malloc(sizeof(file_content));
	fic->fsize = strlen(valeur) + 1;
	fic->desc = malloc(sizeof(char*)*fic->fsize);
	memcpy(fic->desc, valeur, fic->fsize);
	return fic;
}
