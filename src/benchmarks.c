#include <stdlib.h>
#include "../include/benchmark/benchmarks.h"


void benchmark_croissant(int *tab, int taille, int min, int max) {
    for (int i = 0; i < taille; i++) tab[i] = i;
}

void benchmark_decroissant(int *tab, int taille, int min, int max) {
    for (int i = 0; i < taille; i++) tab[i] = taille - i - 1;
}

void benchmark_constant(int *tab, int taille, int min, int max) {
    int val;
    val = rand() % (max - min) + min;
    for (int i = 0; i < taille; i++) tab[i] = val;
}

void benchmark_pair(int *tab, int taille, int min, int max) {
    for (int i = min; i <= max && (i - min) < taille; i++) {
        if (i % 2 == 0) {
            tab[i] = i;
        }
    }
}

void benchmark_impair(int *tab, int taille, int min, int max) {
    for (int i = 0; i < taille; i++) {
        tab[i] = 2 * i + 1;
    }
}

// remplissage d'un tableau avec des valeurs aléatoires comprises entre min et max
void initialisation_aleatoire(int *tab, int taille, int min, int max) {
    for (int i = 0; i < taille; i++) tab[i] = rand() % (max - min) + min;
}

void benchmark_aleatoire_0_INT_MAX(int *tab, int taille, int min, int max) {
    for (int i = 0; i < taille; i++) tab[i] = rand();
}

void benchmark_aleatoire_0_20(int *tab, int taille, int min, int max) {
    for (int i = 0; i < taille; i++) tab[i] = rand() % 21;
}

void benchmark_puissances_de_2(int *tab, int taille, int min, int max) {
    for (int i = 0; i < taille; i++) tab[i] = 1 << i; // 2^i
}

int est_premier(int n) {
    if (n <= 1) return 0;
    if (n <= 3) return 1;
    if (n % 2 == 0 || n % 3 == 0) return 0;
    for (int i = 5; i * i <= n; i += 6)
        if (n % i == 0 || n % (i + 2) == 0)
            return 0;
    return 1;
}

void benchmark_nombres_premiers(int *tab, int taille, int min, int max) {
    int count = 0;
    for (int i = 2; count < taille; i++) {
        if (est_premier(i)) {
            tab[count] = i;
            count++;
        }
    }
}