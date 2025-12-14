struct maillon {
    int val;
    struct maillon* suivant;
};

typedef struct maillon maillon;
typedef maillon* liste;

struct maillon_couple {
    int cle;
    int valeur;
    struct maillon_couple* suivant;
};

typedef struct maillon_couple maillon_couple;
typedef maillon_couple* liste_couples;

typedef struct dico {
    int capacite;
    int nb_elements;
    liste_couples* donnees;
} dico;

//Libère l'espace mémoire occupé par une liste.
void liberer_liste(liste l);

//Crée une nouvelle liste étant donnée une tête et une queue.
liste cons(int x, liste l);

//Libère l'espace mémoire occupé par une liste de couples.
void liberer_liste_couples(liste_couples l);

 //Crée une nouvelle liste de couples étant donnée une tête et une queue.
liste_couples cons_couple(int k, int v, liste_couples l);

//Libère l'espace mémoire occupé par un dictionnaire.
void liberer_dico(dico* d);

//Crée un dictionnaire vide.
dico* creer_dico(void);

//Renvoie le nombre d'éléments compris dans un dictionnaire.
int taille_dico(dico* d);

//Renvoie le haché d'un entier.
int hash(int taille_dico, int k);

//Teste l'appartenance d'un entier en tant que premier membre d'une liste de couples.
bool appartient_liste_cle(liste_couples l, int k);

//Teste l'appartenance d'une clé à un dictionnaire.
bool appartient_cle(dico* d, int k);

//Renvoie la valeur associée à une clé dans un dictionnaire.
int valeur_associee(dico* d, int k);

//Renvoie une clé quelconque d'un dictionnaire.
int obtenir_cle(dico* d);

 //Ajoute une association (clé, valeur) à un dictionnaire sans redimensionner
void ajoute_entree_base(dico* d, int c, int v);

//Redimensionne la table de hachage d'un dictionnaire.
void redimensionne(dico* d, int t);

//Ajoute une association (clé, valeur) à un dictionnaire.
void ajoute_entree(dico* d, int k, int v);

//Supprime une association d'un dictionnaire.
void supprime_entree(dico* d, int k);

//Renvoie la liste des clés d'un dictionnaire.
liste liste_cles(dico* d);
