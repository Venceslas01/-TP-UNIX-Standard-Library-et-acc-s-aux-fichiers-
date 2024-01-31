#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Fonction exécutée par chaque thread, il affiche l'id du thread 
void * Thread(void * numero) {
    int numeroThread = *( (int *) numero);
    printf("Hello, je suis %d\n", numeroThread);
    free(numero);
    return NULL;
}

int main(int argc, char *argv[]) {
    // Vérification des arguments du programme
    if (argc < 2) {
        fprintf(stderr, "Usage: %s 'nombre de threads'\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    // Conversion de l'argument en nombre de threads
    int nombreThreads = atoi(argv[1]);

    // Tableau de thread
    pthread_t tableauThreads[nombreThreads];

    // Création des threads
    for (int i = 0; i < nombreThreads; i++) {
        int *numeroThread = malloc(sizeof(int)); // Allouer de la mémoire pour le numéro du thread
        if (numeroThread == NULL) {
            perror("Erreur : malloc");
            exit(EXIT_FAILURE);
        }
        *numeroThread = i + 1; // Le numéro du thread
        if (pthread_create(&tableauThreads[i], NULL, Thread, numeroThread)) {
            perror("Erreur : pthread_create");
            free(numeroThread);
            exit(EXIT_FAILURE);
        }
    }
    // Attente de la fin des threads
    for (int i = 0; i < nombreThreads; i++) {
        if (pthread_join(tableauThreads[i], NULL)) {
            perror("Erreur : pthread_join");// Gestion d'erreur 
            exit(EXIT_FAILURE);
        }
    }
    printf("Les threads sont terminés.\n");
    return 0;
}