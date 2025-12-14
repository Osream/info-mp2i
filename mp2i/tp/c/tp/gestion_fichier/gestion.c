#include "gestion.h"
#include <stdio.h>

int main(int argc, char** argv){
    assert(argc>=3);
    copie(argv[1], argv[2]);
}

void copie10(char *f1, char *f2){
    FILE* file_to_read = fopen(f1, "r");
    FILE* file_to_write = fopen(f2, "w");
    char* ligne = malloc(25*sizeof(char));
    for (int i = 0; i < 10; i++){
        fscanf(file_to_read, "%s", ligne);
        fprintf(file_to_write, "%s\n", ligne);
    }
    free(ligne);
    fclose(file_to_read);
    fclose(file_to_write);
}

void copie(char *f1, char *f2){
    FILE* file_to_read = fopen(f1, "r");
    FILE* file_to_write = fopen(f2, "w");
    if(file_to_read != NULL && file_to_write != NULL){
        char* ligne = malloc(25*sizeof(char));
        while (fscanf(file_to_read, "%s", ligne) != EOF){
            fprintf(file_to_write, "%s\n", ligne);
        }
        free(ligne);
        fclose(file_to_read);
        fclose(file_to_write);
    }
    else{
        fprintf(stderr, "Un des fichiers n'est pas accessible.\n");
    }
}