#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <signal.h>
#include <string.h>

// variable globale pour la réception du signal
volatile sig_atomic_t receptionsignal = 0;

// gestionnaire de signal
void gestion_signal(int) {
    // mise à jour de la variable globale lors de la réception du signal
    receptionsignal = 1;
}

// configuration de la gestion des signaux
void setupSignalHandling() {
    struct sigaction sig;
    // initialisation de la structure à zéro
    memset(&sig, 0, sizeof(sig));
    // définition de la fonction de gestion des signaux
    sig.sa_handler = gestion_signal;
    // application du gestionnaire de signal pour SIGINT
    sigaction(SIGINT, &sig, NULL);
}

// fonction pour le processus de filtrage
void processus_de_filtrage(int read_end) {
    int descripteurTube[2]; // descripteurs pour le nouveau tube
    int nombre_premier, nombre; // variables pour les nombres

    // création d'un nouveau tube
    if (pipe(descripteurTube) == -1) {
        printf("Erreur de création de tube.\n");
        exit(EXIT_FAILURE);
    }

    // lecture du premier nombre (nombre premier pour le filtrage)
    if (read(read_end, &nombre_premier, sizeof(int)) <= 0) {
        //close(read_end); // fermeture du tube en cas d'erreur de lecture
        exit(EXIT_FAILURE);
    }

    // traitement du signal de fin
    if (nombre_premier == -1) {
        printf("Fin du processus: %d\n", nombre_premier); // affichage de la fin du processus
        exit(0); // sortie du processus
    }

    // affichage du nombre premier utilisé pour le filtrage
    printf("Premier: %d\n", nombre_premier);

    // création d'un processus fils
    pid_t pid = fork();
    if (pid == -1) {
        printf("Erreur de création du processus.\n");
        exit(EXIT_FAILURE);
    }

    // dans le processus parent
    if (pid != 0) {
        close(descripteurTube[0]); // fermeture de l'extrémité de lecture du tube
        // boucle de lecture et d'écriture des nombres
        while (read(read_end, &nombre, sizeof(int)) > 0) {
            // vérification de la réception du signal
            if (receptionsignal) {
                int fin = -1;
                write(descripteurTube[1], &fin, sizeof(int)); // écriture de la valeur de fin
                break;
            }
            // écriture des nombres non-divisibles par le nombre premier
            if (nombre % nombre_premier != 0) {
                write(descripteurTube[1], &nombre, sizeof(int));
            }
        }
        close(descripteurTube[1]); // fermeture du tube après utilisation
        close(read_end); // fermeture du tube de lecture
        wait(NULL); // attente de la fin du processus fils
    } else {
        // dans le processus fils
        close(descripteurTube[1]); // fermeture de l'extrémité d'écriture du tube
        processus_de_filtrage(descripteurTube[0]); // appel récursif pour le filtrage
    }
}

int main() {
    setupSignalHandling(); // configuration de la gestion des signaux
    int descripteurTube[2]; // descripteurs pour le tube principal
    int max_nombre = 10000; // nombre maximum pour la génération des nombres

    // création du tube principal
    if (pipe(descripteurTube) == -1) {
        printf("Erreur de création de tube.\n");
        return EXIT_FAILURE;
    }

    // création d'un processus fils
    pid_t pid = fork();
    if (pid == -1) {
        printf("Erreur de création du processus.\n");
        return EXIT_FAILURE;
    }

    // dans le processus père
    if (pid > 0) {
        close(descripteurTube[0]); // fermeture de l'extrémité de lecture du tube
        // boucle d'écriture des nombres dans le tube
        for (int i = 2; i <= max_nombre; i++) {
            // vérification de la réception du signal
            if (receptionsignal) {
                int fin = -1;
                write(descripteurTube[1], &fin, sizeof(int)); // écriture de la valeur de fin
                break;
            }
            write(descripteurTube[1], &i, sizeof(int)); // écriture du nombre dans le tube
        }
        close(descripteurTube[1]); // fermeture du tube après utilisation
        wait(NULL); // attente de la fin du processus fils
    } else {
        // dans le processus fils
        close(descripteurTube[1]); // fermeture de l'extrémité d'écriture du tube
        processus_de_filtrage(descripteurTube[0]); // commencement du processus de filtrage
    }

    return 0;
}
