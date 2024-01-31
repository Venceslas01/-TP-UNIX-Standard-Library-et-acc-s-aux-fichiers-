#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Somme globale partagée par tous les threads
int somme = 0;

// Structure pour transmettre les paramètres à chaque thread
typedef struct {
    int numeroThread; // Identifiant unique pour chaque thread
    int nombreRepetitions;  // Nombre d'itérations pour l'ajout à la somme
} structParametre;

// Fonction principale de chaque thread
void * Thread(void * arg) {
    structParametre * Parametre = (structParametre *)arg;
    // Boucle d'ajout à la somme globale
    for (int i = 0; i < Parametre->nombreRepetitions; i++) {
        somme = (somme + Parametre->numeroThread);
    }
    printf("Thread %d a ajouté %d à somme %d fois\n", Parametre->numeroThread, Parametre->numeroThread, Parametre->nombreRepetitions);
    free(arg); // Nettoyage de la mémoire allouée pour les paramètres du thread
    return NULL;
}

int main(int argc, char *argv[]) {
    // Vérification des arguments du programme
    if (argc < 3) {
        fprintf(stderr, "Usage: %s 'nombre de threads' 'nombre de repetitions'\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int nombreThreads = atoi(argv[1]);
    int nombreRepetitions = atoi(argv[2]);

    // Tableau de threads
    pthread_t tableauThreads[nombreThreads];

    // Création des threads
    for (int i = 0; i < nombreThreads; i++) {
        structParametre *Parametre = malloc(sizeof(structParametre));
        if (Parametre == NULL) {
            perror("Erreur : malloc");
            exit(EXIT_FAILURE);
        }
        Parametre->numeroThread = i + 1; // Configuration de l'identifiant du thread
        Parametre->nombreRepetitions = nombreRepetitions;

        if (pthread_create(&tableauThreads[i], NULL, Thread, Parametre)) {
            perror("Erreur : pthread_create");
            free( Parametre); // Libération de la mémoire en cas d'échec
            exit(EXIT_FAILURE); // Configuration du nombre de répétitions
        }
    }

    // Attente de la fin de tous les threads
    for (int i = 0; i < nombreThreads; i++) {
        if (pthread_join(tableauThreads[i], NULL)) {
            perror("Erreur : pthread_join");
            exit(EXIT_FAILURE);
        }
    }

    printf("La somme est %d\n", somme);
    return 0;
}
