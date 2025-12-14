#include "../../c/libraries.h"

struct formule_s {
    char* nom;
    struct formule_s* sfg;
    struct formule_s* sfd;
}; typedef struct formule_s* formule;

bool verifie (formule f){
    if (f->sfg != NULL && f->sfd != NULL){
        if(
            (strcmp(f->nom, "ou") == 0 || strcmp(f->nom, "et") == 0))
            {
            return verifie(f->sfg) && verifie(f->sfd);
        }
    }
    else if (f->sfg == NULL && f->sfd != NULL){
        if(strcmp(f->nom, "non") == 0){
            return verifie(f->sfd);
        }
    }
    else if (f->sfg == f->sfd && f->sfg == NULL){
        if (strcmp(f->nom, "bottom") == 0 
        ||  strcmp(f->nom, "top") == 0
        || (f->nom[1] == '\0' && (int)f->nom[0] >= 97 && (int)f->nom[0] <= 122)){
            return true;
        }
    }
    return false;
}


void affiche_aux(formule f){
    switch (strlen(f->nom)){
        case 1:
            printf("%s", f->nom); 
            break;
        case 2:
            printf("(");
            affiche_aux(f->sfg);
            if (f->nom[0] == 'o'){
                printf(" ∨ ");
            }
            else{
                printf(" ∧ ");
            }
            affiche_aux(f->sfd);
            printf(")");
            break;
        case 3:
            if (f->nom[0] == 'n'){
                printf("¬");
                affiche_aux(f->sfd);
            }
            else{
                printf("⊤");
            }
            break;
        default:
            printf("⊥");
    }
}

void affiche(formule f){
    affiche_aux(f);
    printf("\n");
}

int hauteur(formule f){
    if(f->sfd != NULL && f->sfg != NULL){
        int g = hauteur(f->sfg);
        int d = hauteur(f->sfd);
        if (g>= d){
            return 1 + g;
        }
        else{
            return 1 + d;
        }
    }
    else if (f->sfd != NULL){
        return 1 + hauteur(f->sfd); 
    }
    else{
        return 0;
    }
}

char* variable(formule f){
    if(f->sfd != NULL && f->sfg != NULL){
        char* g = variable(f->sfg);
        char* d = variable(f->sfd);
        if (g == NULL){
            return d;
        }
        return g;
    }
    else if (f->sfd != NULL){
        return variable(f->sfd); 
    }
    else{
        if (strlen(f->nom) == 1){
            return f->nom;
        }
        else{
            return NULL;
        }
    }
}

formule substitue(formule f, char* v, bool variable){
    formule nouv = malloc(sizeof(struct formule_s));
    nouv->nom = f->nom;
    if(f->sfd != NULL && f->sfg != NULL){
        nouv->sfg = substitue(f->sfg, v, variable);
        nouv->sfd = substitue(f->sfd, v, variable);
    }
    else if (f->sfd != NULL){
        nouv->sfg = NULL;
        nouv->sfd = substitue(f->sfd, v, variable);
    }
    else{
        nouv->sfg = NULL;
        nouv->sfd = NULL;
        if(strcmp(f->nom, v) == 0 && variable){
            nouv->nom = "top";
        }
        else if (strcmp(f->nom, v) == 0 && !variable) {
            nouv->nom = "bottom";
        }
    }
    return nouv;
}

void free_formule(formule f){
    if(f != NULL){
        free_formule(f->sfg);
        free_formule(f->sfd);
        free(f);
    }
}

void modifie_connecteur(formule f, formule sfg, formule sfd){
    int taille = strlen(sfg->nom); 
    if (taille == 3){
        if(sfg->nom[0] != 'n'){
            if (f->nom[0] == 'o'){
                *f = *sfg;
                free(sfg);
                free_formule(sfd);
            }
            else{
                *f = *sfd;
                free(sfd);
                free_formule(sfg);
            }
        }
    }
    else if (taille == 6){
        if (f->nom[0] == 'o'){
            *f = *sfd;
            free(sfd);
            free_formule(sfg);
        }
        else{
            *f = *sfg;
            free(sfg);
            free_formule(sfd);
        }
    }
}

void modifie_negation(formule f, formule sfd){
    if (strcmp(sfd->nom, "bottom") == 0){
        f->nom = "top";
        free(sfd);
        f->sfd = NULL;
    }
    else if (strcmp(sfd->nom, "top") == 0){
        f->nom = "bottom";
        free(sfd);
        f->sfd = NULL;
    }   
}

formule regles_quine(formule f){
    formule nouv = malloc(sizeof(struct formule_s));
    nouv->nom = f->nom;
    if(f->sfd != NULL && f->sfg != NULL){
        formule sfg = regles_quine(f->sfg);
        formule sfd = regles_quine(f->sfd);
        nouv->sfg = sfg;
        nouv->sfd = sfd;
        modifie_connecteur(nouv, sfg, sfd);
        if (nouv->sfd != NULL){
            modifie_connecteur(nouv, nouv->sfd, nouv->sfg);
        }
    }
    else if (f->sfd != NULL){
        formule sfd = regles_quine(f->sfd);
        nouv->sfg = NULL;
        nouv->sfd = sfd;
        modifie_negation(nouv, sfd);
    }
    else{
        nouv->sfg = NULL;
        nouv->sfd = NULL;
    }
    return nouv;
}

bool sat_quine(formule f){
    char* v = variable(f);
    if (v == NULL){
        return strcmp(f->nom, "bottom");
    }
    else{
        formule sub_gauche = substitue(f, v, false);
        formule sub_droite = substitue(f, v, true);

        formule sag = regles_quine(sub_gauche);
        formule sad = regles_quine(sub_droite);

        free_formule(sub_gauche);
        free_formule(sub_droite);

        bool res = sat_quine(sag) || sat_quine(sad);

        free_formule(sag);
        free_formule(sad);

        return res;
    }
}


int main(){
}