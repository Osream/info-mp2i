#include "../../mp2i/c/libraries.h"

struct maillon_s{
    int valeur;
    struct maillon_s* suivant;
};

struct pile_s{
    struct maillon_s* sommet;
    int compteur;
};

typedef struct pile_s* pile;

pile create(void){
    pile res = malloc(sizeof(struct pile_s));
    assert(res != NULL);
    res->compteur = 0;
    res->sommet = NULL;
    return res;
}

void push(int elt, pile p){
    struct maillon_s* nouv = malloc(sizeof(struct maillon_s));
    assert(nouv != NULL);
    nouv->suivant=p->sommet;
    nouv->valeur = elt;
    p->sommet = nouv;
    p->compteur ++;
}

void drop(pile p){
    assert(p!= NULL);
    struct maillon_s* mem = p->sommet;
    p->sommet = mem->suivant;
    p->compteur ++;
    free(mem);
}

void emet(pile p){
    assert(p!=NULL);
    printf("%d\n", p->sommet->valeur);
    p->compteur ++;
}

void aux(pile p){
    if (p!=NULL){
        drop(p);
        aux(p);
    }
}

int clear(pile p){
    int tmp = p->compteur;
    aux(p);
    // p->compteur = tmp;
    free(p);
    return tmp;
}

int* lire_entrees(char* nom_de_fichier, int* taille){
    
    FILE* en_lecture = fopen(nom_de_fichier, "r");
    fscanf(en_lecture,"%d", taille);
    int* t_com = malloc((*taille)*sizeof(int));
    
    for (int i = 0; i < *taille; i++){
        fscanf(en_lecture, "%d", &t_com[i]);
    }
    fclose(en_lecture);
    return t_com;
}

int generation_naive(int n, int* t_com){
    pile gener = create();
    
    for (int i = 0; i < n; i++){
        push(t_com[i], gener);
        emet(gener);
        drop(gener);
    }
    int cout = clear(gener);
    return cout;
}

int generation_sans_repetitions(int n, int* t_com){
    pile gener = create();
    
    for (int i = 0; i < n; i++){
        push(t_com[i], gener);
        
        while(i<n && t_com[i+1] == t_com[i]){
            emet(gener);
            i++;
        }
        
        drop(gener);
    }
    int cout = clear(gener);
    return cout;
}


int generation_sim(int n, int *t_com, int *t_sim){
    pile gener = create();
    
    int tab[n];

    for (int i = 0; i < n; i++){
        tab[i] = 0;
        if(t_sim[i] != -1){
            tab[t_sim[i]] = 1;
        }
    }

    for (int i = 0; i < n; i++){
        if(t_sim[i] == -1){
            push(t_com[i], gener);
        }
        if(tab[i] == 0){
            emet(gener);
            drop(gener);
        }
        else{
            emet(gener);
        }
    }            

    int cout = clear(gener);
    return cout;
}


int calcul_sim(int n, int *t_com, int bin, int *t_sim){
    int temp = bin;
    int entier_en_binaire[n];
    int cout = n;
    
    for (int i = 0; i<n ;i ++){
        entier_en_binaire[i] = temp % 2;
        temp /= 2;
    }

    for(int i = 0; i<n; i++){
        if(entier_en_binaire[i] == 0){
            t_sim[i] = -1;
            cout += 2;
        }
        else{
            int* j_max = NULL;
            for (int j = 0; j<i; j++){
                if (t_com[j] == t_com[i]){
                   *j_max = j; 
                }
            }
            if(j_max != NULL){
                t_sim[i] = *j_max;
            }
            else{
                t_sim[i] = -1;
                cout += 2;
            }
        }
    }
    return cout;

}


int main(){
    return 0;
}

