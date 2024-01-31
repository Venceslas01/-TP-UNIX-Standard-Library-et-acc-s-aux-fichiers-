#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int indexDepart;
    int indexFin;
    int *vecteurA;
    int *vecteurB;
    int *resultat;
} structVect;

// Fonction pour multiplier les éléments des vecteurs 
void *multiplication(void *arg) {
    structVect *vec = (structVect *)arg;
    for (int i = vec->indexDepart; i < vec->indexFin; ++i) {
        vec->resultat[i] = vec->vecteurA[i] * vec->vecteurB[i];
    }
    return NULL;
}

// Fonction pour additionner les éléments d'un vecteur
void *addition(void *arg) {
    structVect *vec = (structVect *)arg;
    int somme = 0;
    for (int i = 0; i < vec->indexFin; ++i) {
        somme += vec->resultat[i];  // Addition des résultats de la multiplication
    }
    printf("Le produit scalaire est : %d\n", somme);
    return NULL;
}

int main() {
    int tailleVecteur, nombreThreads , taille ;
    do{
        // Taille des vecteurs
        printf("Donner la taille des vecteurs \n");
        scanf("%d",&tailleVecteur);
        printf("\n");  
        // Nombre de threads pour la multiplication 
        printf("Donner le nombre de threads pour la multiplication \n");
        scanf("%d",&nombreThreads);
        printf("\n"); 

    } while ((tailleVecteur == 0) || (nombreThreads == 0));
    
    // Allocation et initialisation des vecteurs
    int *vecteurA = malloc(tailleVecteur * sizeof(int));
    int *vecteurB = malloc(tailleVecteur * sizeof(int));
    int *resultats = malloc(tailleVecteur * sizeof(int));

    // Initialisation des vecteurs
    for (int i = 0; i < tailleVecteur; ++i) {
        vecteurA[i] = i;
        vecteurB[i] = i;
    }

    // Création et lancement des threads de multiplication
    pthread_t threads[nombreThreads];
    structVect vecs[nombreThreads];

    taille = tailleVecteur / nombreThreads;
    for (int i = 0; i < nombreThreads; ++i) {
        vecs[i].indexDepart = i * taille;
        vecs[i].indexFin = (i == nombreThreads - 1) ? tailleVecteur : (i + 1) * taille;
        vecs[i].vecteurA = vecteurA;
        vecs[i].vecteurB = vecteurB;
        vecs[i].resultat = resultats;
        pthread_create(&threads[i], NULL, multiplication, &vecs[i]);
    }
    
    // Attente de la fin des threads de multiplication
    for (int i = 0; i < nombreThreads; ++i) {
        pthread_join(threads[i], NULL);
    }

    // Création et lancement du thread d'addition
    pthread_t sommeThread;
    structVect addvec = {0, tailleVecteur, vecteurA, vecteurB, resultats};
    pthread_create(&sommeThread, NULL, addition, &addvec);
    pthread_join(sommeThread, NULL);

    free(vecteurA);
    free(vecteurB);
    free(resultats);
    return 0;
}

/*L'augmentation du nombre de threads entraîne une augmentation du temps d'exécution. Il n'améliore donc pas la performance.*/