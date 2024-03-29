﻿#include "terminal.h"
#include "biblio.h"
#include "fsprint.h"

int main() {

    filesystem* fs = malloc(sizeof(filesystem));
    filesystem_init(fs);

    directory_add_file(fs->root, "rootfile");
    file_set_content(directory_find(fs->root, "rootfile"), crea_content("This is a file at root."));

    node* dira = directory_add_directory(fs->root, "dirA");
    directory_add_file(dira, "fileAA");
    directory_add_file(dira, "fileAB");
    file_set_content(directory_find(dira, "fileAA"), crea_content("This is file fileAA."));
    file_set_content(directory_find(dira, "fileAB"), crea_content("This is file fileAB."));
    node* dirb = directory_add_directory(fs->root, "dirB");
    directory_add_file(dirb, "fileBA");
    directory_add_file(dirb, "fileBB");
    file_set_content(directory_find(dirb, "fileBA"), crea_content("This is file fileBA."));
    file_set_content(directory_find(dirb, "fileBB"), crea_content("This is file fileBB."));
   
    filesystem_print(fs, 3, 1);

    node* current = fs->root;

    while (1) {
        char* ligne = NULL; size_t capa = 0;

        printf("$ ");

        my_getline(&ligne, &capa, stdin);
        char* arguments[100];
        int n_args = 0;

        for (char* str = strtok(ligne, " \n"); str != NULL; str = strtok(NULL, " \n")) {
            arguments[n_args] = str;
            n_args++;
        }

        if (n_args == 0) {
            printf("Veuillez rentrer une commande\n");
            continue;
        }



        if (strcmp(arguments[0], "man") == 0) {
            printf("\t cd [dos] : permet de changer de dossier courant \n");
            printf("\t pwd : permet d'afficher le chemin vers le dossier courant \n");
            printf("\t cat [fic] : permet d’afficher le contenu d’un fichier  \n");
            printf("\t touch [nom] : permet de créer un fichier  \n");
            printf("\t mkdir [nom] : permet de créer un dossier  \n");
            printf("\t ls : permet de lister le contenu du dossier courant \n");
            printf("\t tree {1}: permet d’afficher l’arborescence à partir du dossier courant, si 1 alors on affiche les contenues \n");
            printf("\t edit [nom] [contenu] : permet d'editer le contenu d'un fichier \n");
            printf("\t exit : quitte le programme\n");

        }
        else if (strcmp(arguments[0], "exit") == 0) {
            filesystem_free(fs);
            exit(0);
        }
        else if (strcmp(arguments[0], "cd") == 0) {
            if (n_args < 2) {
                current = filesystem_get_root(fs);
            }
            else {
                node* new;
                char* pt;
                pt = (char*)memchr(arguments[1], '.', 2);
                if (pt != NULL) {
                    char* pt2;
                    pt2 = (char*)memchr(pt + 1, '.', 2);
                    if (pt2 != NULL) {
                        new = current->parent;
                        if ((new!=NULL)&&(new->t != FI)) {
                            current = new;
                        }
                    }
                    else {
                        char* token;
                        token = strtok(pt + 1, "/");
                        while (token != NULL) {
                            new = directory_find(current, token);
                            token = strtok(NULL, "/");
                            if ((new!=NULL)&&(new->t != FI)) {
                                current = new;
                            }
                        }
                    }
                }
                else {
                    char* token;
                    token = strtok(arguments[1], "/");
                    while (token != NULL) {
                        new = directory_find(filesystem_get_root(fs), token);
                        token = strtok(NULL, "/");
                        if ((new!=NULL)&&(new->t != FI)) {
                            current = new;
                        }
                    }
                }
                if(new==NULL){printf("cd : impossible de se déplacer dans ce dossier \n");}
            }
        }
        else if (strcmp(arguments[0], "pwd") == 0) {
            print_path(current);
            printf("\n");
        }
        else if (strcmp(arguments[0], "touch") == 0) {
            if (n_args < 2) {
                printf("touch: argument manquant \n Essayez la commande 'man' pour plus d'information \n");
            }
            else {
                directory_add_file(current, (char*)arguments[1]);
            }
        }
        else if (strcmp(arguments[0], "cat") == 0) {
            if (directory_find(current, arguments[1]) == NULL) {
                printf("cat impossible, fichier non existant\n");
            }
            else{
                if (n_args < 2) {
                    printf("cat: argument manquant \n Essayez la commande 'man' pour plus d'information \n");
                }
                else {
                    struct file* ptr = (struct file*)directory_find(current, arguments[1])->data;
                    printf("%s", (char*)ptr->cont->desc);
                    printf("\n");
                }
            }
          }
          else if (strcmp(arguments[0], "mkdir") == 0) {
            if (n_args < 2) {
                printf("mkdir: argument manquant \n Essayez la commande 'man' pour plus d'information");
            }
            else {
                directory_add_directory(current, (char*)arguments[1]);
            }
          }
          else if (strcmp(arguments[0], "ls") == 0) {
            directory* ptr = (directory*)current->data;
            if (ptr->child != NULL) {
                node_print(ptr->child, 1, 1, 0);
            }
          }
          else if (strcmp(arguments[0], "tree") == 0) {
                if (strcmp(arguments[1], "1") == 0){
                    printf("filesystem");
                  	if(fs->filesystname!=NULL){
                  		printf("%s", fs->filesystname);
                  	}
                  	printf("\n");
                  	node_print(current,-1,1,0);
                  }
                else{
                    printf("filesystem");
                  	if(fs->filesystname!=NULL){
                  		printf("%s", fs->filesystname);
                  	}
                  	printf("\n");
                  	node_print(current,0,0,0);
                }
            }
            else if (strcmp(arguments[0], "edit") == 0) {
                if (directory_find(current, arguments[1]) == NULL) {
                    printf("edit impossible, file not existant\n");
                }
                else{
                    if (n_args < 3) {
                        printf("edit: argument manquant \n Essayez 'man' pour plus d'information \n");
                    }
                    else
                        file_set_content(directory_find(current, arguments[1]), crea_content((char*)arguments[2]));
                }
            }
            else {
                printf("Commande \"%s\" inconnue.\n", arguments[0]);
            }
            free(ligne);
        }

    system("pause");
    return 0;

}


void clearEcran()
{
    system("@cls||clear");
}


size_t my_getline(char** lineptr, size_t* n, FILE* stream) {
    char* bufptr = NULL;
    char* p = bufptr;
    size_t size;
    int c;

    if (lineptr == NULL) {
        return -1;
    }
    if (stream == NULL) {
        return -1;
    }
    if (n == NULL) {
        return -1;
    }
    bufptr = *lineptr;
    size = *n;

    c = fgetc(stream);

    if (c == EOF) {
        return -1;
    }
    if (bufptr == NULL) {
        bufptr = malloc(128);
        if (bufptr == NULL) {
            return -1;
        }
        size = 128;
    }
    p = bufptr;
    while (c != EOF) {
        if ((p - bufptr) > (size - 1)) {
            size = size + 128;
            bufptr = realloc(bufptr, size);
            if (bufptr == NULL) {
                return -1;
            }
        }
        *p++ = c;
        if (c == '\n') {
            break;
        }
        c = fgetc(stream);
    }

    *p++ = '\0';
    *lineptr = bufptr;
    *n = size;

    return p - bufptr - 1;
}
