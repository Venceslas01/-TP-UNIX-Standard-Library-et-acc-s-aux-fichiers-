#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// Structure pour partager les données entre les threads
typedef struct {
    int valeur;           // Valeur partagée
    int flag;            // Indicateur de disponibilité de la ressource
    pthread_mutex_t lock; // Mutex pour  contrôler l'accès à la ressource
    pthread_cond_t condition;  // Variable de condition
} PartageDonnee;

// Fonction du producteur
void* production(void* arg) {
    PartageDonnee* donnee = (PartageDonnee*)arg;
    while (1) {
        pthread_mutex_lock(&donnee->lock);
        while (donnee->flag == 1) { // Attendre que la ressource soit consommée
            pthread_cond_wait(&donnee->condition, &donnee->lock);
        }
        donnee->valeur++;   // Incrémenter la valeur partagée
        donnee->flag = 1;  // Marquer la ressource comme disponible
        printf("Producteur a produit : %d\n", donnee->valeur);
        pthread_cond_signal(&donnee->condition); // Signaler aux consommateurs
        pthread_mutex_unlock(&donnee->lock);
        sleep(1); 
    }
    return NULL;
}

// Fonction des consommateurs
void* consommation(void* arg) {
    PartageDonnee* donnee = (PartageDonnee*)arg;
    while (1) {
        pthread_mutex_lock(&donnee->lock);
        while (donnee->flag == 0) { // Attendre qu'une ressource soit disponible
            pthread_cond_wait(&donnee->condition, &donnee->lock);
        }
        printf("Consommateur %ld a consommé : %d\n", pthread_self(), donnee->valeur);
        donnee->flag = 0; // Marquer la ressource comme consommée
        pthread_cond_signal(&donnee->condition); // Signaler au producteur
        pthread_mutex_unlock(&donnee->lock);
    }
    return NULL;
}

int main() {

    int nombCosommateur = 0; // Nombre de consommateurs
    do{
        printf("Donner le nombre de consommateur (le nombre doit etre superieur à 2): \n");
        scanf("%d",&nombCosommateur);
        printf("\n");   
    } while (nombCosommateur < 2);
    
    PartageDonnee donnee = {0, 0, PTHREAD_MUTEX_INITIALIZER, PTHREAD_COND_INITIALIZER};
    pthread_t prod, consm[nombCosommateur];

    
    // Lancement du thread producteur
    pthread_create(&prod, NULL, production, &donnee);

    // Lancement des threads consommateurs
    for (int i = 0; i < nombCosommateur; ++i) {
        pthread_create(&consm[i], NULL, consommation, &donnee);
    }

    // Attente de la fin du producteur 
    pthread_join(prod, NULL);

    // Attente de la fin des threads consommateurs
    for (int i = 0; i < nombCosommateur; ++i) {
        pthread_join(consm[i], NULL);
    }

    return EXIT_SUCCESS;
}
