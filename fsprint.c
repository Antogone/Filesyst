#include "biblio.h"
#include "fsprint.h"


void file_print(node* file, const int with_content) { // OK (pas testé contenu)
	struct file* ptr = (struct file*)file->data;
	if (with_content == 0)
		printf("file: %s, size : %d", file->name, ptr->cont->taille);
	if (with_content != 0)
		printf("file: %s, content: %s ,size :%d", file->name,ptr->cont->desc, ptr->cont->taille);
	printf("\n");
}

void directory_print(node* dir, int depth,const int with_content,int step) {//penser à mettre step=0 au premier appel
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

void node_print(node* nd, int depth,const int with_content,int step){
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

void filesystem_print(filesystem* fs, int depth, const int with_content) {
	printf("filesystem");
	if(fs->filesystname!=NULL){
		printf("%s", fs->filesystname);
	}
	printf("\n");
	node_print(fs->root,depth,with_content,0);
}

void print_path(node* dir){
  if(dir == NULL){
    return;
  }
  if(strcmp(dir->name,"root")==0){
    printf("~");
  }
  else{
    print_path(dir->parent);
    printf("/");
    printf("%s",dir->name);
  }
}
