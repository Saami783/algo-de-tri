#ifndef UTILITY_FUNCTIONS_H
#define UTILITY_FUNCTIONS_H

int *creation_tableau(int taille);
void copie_tableau(int *source, int *destination, int taille);
void affichage_tableau(int *tab, int taille);
int is_sorted(int *tab, int taille);
int python_script();

#endif