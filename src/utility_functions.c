#include <stdlib.h>
#include <stdio.h>
#include "../include/utilities/utility_functions.h"

int *creation_tableau(int taille) {
    int *tab;
    tab = (int *) malloc(sizeof(int) * taille);
    return tab;
}

void copie_tableau(int *source, int *destination, int taille) {
    int i;
    for (i = 0; i < taille; i++) {
        destination[i] = source[i];
    }
}

void affichage_tableau(int *tab, int taille) {
    for (int i = 0; i < taille; i++) printf("%d|", tab[i]);
    printf("\n");
}

int is_sorted(int *tab, int taille) {
    for (int i = 0; i < taille - 1; i++) {
        if (tab[i] > tab[i + 1]) return 0; // non trié
    }
    return 1; // trié
}
int python_script() {
    int status;

    // Exécution du script Python si nécessaire
    status = system("python ../python/main.py");
    if (status == -1) {
        printf("Erreur lors de l'exécution de la commande\n");
        return -1;
    }

    // Suppression de tous les resultats en csv & xls
#ifdef _WIN32
    // status = system("del /Q \"benchmark\\*\"");
    // status = system("del /Q \"data\\csv\\*\"");
#else // Pour les autres systèmes, y compris macOS
    // status = system("rm -f benchmark/*");
#endif

    return status;
}