#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>

int main() {
    int descripteurTube[2]; // Descripteurs pour le tube
    pid_t pid;

    // Création d'un pipe
    if (pipe(descripteurTube) == -1) {
        perror("pipe"); // Erreur de création du pipe
        return 0;
    }

    // Duplication du processus
    pid = fork();
    if (pid == -1) {
        perror("fork"); // Erreur de duplication du processus
        return 0;
    }

    if (pid == 0) {
        dup2(descripteurTube[1], STDOUT_FILENO);
        //close(descripteurTube[0]); // Fermeture de la lecture du pipe
        //close(descripteurTube[1]); // Fermeture de l'écriture du pipe après la redirection

        // Exécution de /bin/ls
        execlp("/bin/ls", "ls", NULL);
        perror("execlp"); // Erreur si execlp échoue
        exit(EXIT_FAILURE);
    } else {
        dup2(descripteurTube[0], STDIN_FILENO);
        close(descripteurTube[1]); // Fermeture de l'écriture du pipe
        close(descripteurTube[0]); // Fermeture de la lecture du pipe après la redirection

        // Exécution de wc -l
        execlp("wc", "wc", "-l", NULL);
        perror("execlp"); // Erreur si execlp échoue
        exit(EXIT_FAILURE);
    }

    // Attente de la fin du processus fils
    wait(NULL);

    return 0;
}
