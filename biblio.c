#include "biblio.h"
#include "fsprint.h"




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

node* directory_find(node* dir, const char* name){ // OK
	if(dir == NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;
	return find_rec(ptr->child,name);
}

node* find_rec(node* nd, const char* name){ // OK
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

node* directory_add_file(node* dir, const char* name){ // OK

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
	faddfil->ext = strstr(name,".");
	fadd->data = faddfil;
	return directory_add_node(dir,fadd);
}

node* directory_add_directory(node* dir, const char* name){ // OK
	if(directory_find(dir,name)!=NULL){
		return NULL;
	}
	directory *ptr = (directory*) dir->data;
	node* diradd = malloc(sizeof(node));
	char* cpname = malloc(100*sizeof(char));
	strcpy(cpname,name);
	diradd->name = cpname;
	diradd->t = DIR;
	diradd->name = name;
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

int directory_remove_node(node* dir, const char* name){ //OK
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
		ptr->child=next;
	}
	rm->bro = NULL;
	rm->broG = NULL;
	free_node(rm);
	return 0;
}


file_content* file_get_content(node* file) {

}

int file_set_content(node* file, file_content* content) {

}

/***********************************************/
//             déplacé dans fsprint.c
//
// void file_print(node* file, int with_content) { // OK (pas testé contenu)
// 	printf("file: %s", file->name);
// 	if (with_content != 0) {
// 		struct file* ptr = (struct file*)file->data;
// 		printf(",content: %s,size :%d", ptr->cont->desc,ptr->cont->taille);
// 	}
// 	printf("\n");
// }
//
//
//
// void directory_print(node* dir, int depth, int with_content,int step) {//penser à mettre step=0 au premier appel
// 	// depth = profondeur max
// 	// with_content = si on affiche le contenu des fichiers
// 	printf("directory: %s\n",dir->name);
// 	if (depth<=0){
// 		directory* ptr = (directory*)dir->data;
// 		node_print(ptr->child,depth,with_content,step+1);
// 	}
// 	else{
// 		depth-=1;
// 		if(depth){
// 			directory* ptr = (directory*)dir->data;
// 			node_print(ptr->child,depth,with_content,step+1);
// 		}
// 	}
// }
// void node_print(node* nd, int depth, int with_content,int step){
// 		while (nd!=NULL){
// 			char* strplus = indent(step);
// 			printf("%s",strplus);
// 			if(nd->t==DIR){
// 				directory_print(nd,depth,with_content,step);
// 			}
// 			else{
// 				file_print(nd,with_content);
// 			}
// 			nd = nd->bro;
// 		}
// }
// char* indent(int step){
// 	char* strplus = malloc((step+10)*sizeof(char));
// 	char* strdec = "\t";
// 	for (int i = 0; i < step; i++) {
// 		strcat(strplus, strdec);
// 	}
// 	strcat(strplus, "+ ");
// 	return strplus;
// }
// void filesystem_print(filesystem* fs, int depth, int with_content) {
// 	printf("filesystem");
// 	if(fs->filesystname!=NULL){
// 		printf("%s", fs->filesystname);
// 	}
// 	printf("\n");
// 	node_print(fs->root,depth,with_content,0);
// }


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


 //int main(){ //(pour tester directement les fonction définies ici)
 //	filesystem *fsi = malloc(sizeof(filesystem));
 //	filesystem_init(fsi);
 //	directory_add_file(fsi->root,"fic.txt");
 //	filesystem_print(fsi,-1,0);
 //	node* dir = directory_add_directory(fsi->root,"Documents");
 //	directory_add_file(dir,"fic.txt");
 //	filesystem_print(fsi,-1,0);
 //	directory_remove_node(fsi->root,"fic.txt");
 //	filesystem_print(fsi,-1,0);
 //	directory_add_file(fsi->root,"fic.txt");
 //	filesystem_print(fsi,2,0);
 //	return 0;
 //}
