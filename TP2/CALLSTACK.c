#include <stdarg.h>
#include <stdio.h>

int foo(int v, ...) {
    int somme = 0; // Variable pour stocker la somme
    int valeur; // Variable pour lire chaque paramètre

    // Initialisation de la liste de paramètres indéfinie
    va_list my_list_of_parameters;
    va_start(my_list_of_parameters, v);
    somme = v;
    //valeur = va_arg(my_list_of_parameters, int) ;
    // Boucle pour additionner les valeurs, s'arrête à 0
    while ((valeur = va_arg(my_list_of_parameters, int)) != 0) {
        somme += valeur; // Ajout de la valeur lue à la somme
        //valeur = va_arg(my_list_of_parameters, int) ;
    }

    // Fermeture de la liste de paramètres
    va_end(my_list_of_parameters);

    return somme; // Retourne la somme calculée
}

int main() {
    printf("out: %d\n", foo(5,0,2, 1, 0, 1,2)); 
    return(0);
}
