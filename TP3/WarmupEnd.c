#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

// Structure pour transmettre les paramètres à chaque thread
typedef struct {
    int numeroThread;       // Identifiant unique pour chaque thread
    int nombreRepetitions;  // Nombre d'itérations pour l'ajout à la somme
    int sommePartielle;     // Somme partielle calculée par chaque thread
} structParametre;

// Fonction principale de chaque thread
void * Thread(void * arg) {
    structParametre * Parametre = (structParametre *)arg;
    Parametre->sommePartielle = 0; // Initialisation de la somme partielle

    // Boucle d'ajout à la somme partielle
    for (int i = 0; i < Parametre->nombreRepetitions; i++) {
        Parametre->sommePartielle += Parametre->numeroThread;
    }
    printf("Thread %d a ajouté %d à sa somme partielle %d fois\n", Parametre->numeroThread, Parametre->numeroThread, Parametre->nombreRepetitions);
    return NULL; // Retourne la somme partielle
}

int main(int argc, char *argv[]) {
    int sommeTotale = 0; // Somme totale 
    // Vérification des arguments du programme
    if (argc < 3) {
        fprintf(stderr, "Usage: %s 'nombre de threads' 'nombre de repetitions'\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    int nombreThreads = atoi(argv[1]);
    int nombreRepetitions = atoi(argv[2]);

    // Tableau de threads
    pthread_t tableauThreads[nombreThreads];
    structParametre parametres[nombreThreads]; // Tableau pour stocker les paramètres de chaque thread

    // Création des threads
    for (int i = 0; i < nombreThreads; i++) {
        parametres[i].numeroThread = i + 1;
        parametres[i].nombreRepetitions = nombreRepetitions;
        parametres[i].sommePartielle = 0;

        if (pthread_create(&tableauThreads[i], NULL, Thread, &parametres[i])) {
            perror("Erreur : pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Attente de la fin de tous les threads et collecte des sommes partielles
    for (int i = 0; i < nombreThreads; i++) {
        if (pthread_join(tableauThreads[i], NULL)) {
            perror("Erreur : pthread_join");
            exit(EXIT_FAILURE);
        }
        sommeTotale += parametres[i].sommePartielle; // Ajout de la somme partielle de chaque thread à la somme totale
    }

    printf("La somme est %d\n", sommeTotale);
    return 0;
}
