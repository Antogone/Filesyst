#include "terminal.h"
#include "biblio.h"
#include "fsprint.h"

int main() {

  filesystem *fs = malloc(sizeof(filesystem));
  filesystem_init(fs);
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



        if (strcmp(arguments[0], "man") == 0){
            printf("\t cd [dos] : permet de changer de dossier courant \n");
            printf("\t pwd : permet d'afficher le chemin vers le dossier courant \n");
            printf("\t cat [fic] : permet d’afficher le contenu d’un fichier  \n");
            printf("\t touch [nom.ext] : permet de créer un fichier  \n");
            printf("\t mkdir [nom] : permet de créer un dossier  \n");
            printf("\t ls : permet de lister le contenu du dossier courant \n");
            printf("\t tree : permet d’afficher l’arborescence à partir du dossier courant \n");
            printf("\t exit : quitte le programme\n");

        }
        else if (strcmp(arguments[0], "exit") == 0){
          filesystem_free(fs);
          exit(0);
        }
        else if (strcmp(arguments[0], "cd") == 0){
          printf("cd\n");
        }
        else if (strcmp(arguments[0], "pwd") == 0){
          print_path(current);
        }
        else if (strcmp(arguments[0], "cat") == 0)
            printf("cat\n");
        else if (strcmp(arguments[0], "touch") == 0)
            printf("touch\n");
        else if (strcmp(arguments[0], "mkdir") == 0){
          if(n_args<2){
            printf("mkdir: missing operand \n Try 'man' for more information \n");
          }
          else {
            char* name = arguments[1];
            directory_add_directory(current,name);
            //prolème: le nom est perdu
          }
        }
        else if (strcmp(arguments[0], "ls") == 0){
          filesystem_print(fs,1,0);
        }
        else if (strcmp(arguments[0], "tree") == 0){
          filesystem_print(fs,-1,0);
        }
        else
            printf("Commande \"%s\" inconnue.\n", arguments[0]);
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
