#ifndef BENCHMARKS_H
#define BENCHMARKS_H

/* Prototypes des benchmarks */
void benchmark_croissant(int *tab, int, int, int);
void benchmark_decroissant(int *tab, int, int, int);
void benchmark_constant(int *tab, int, int, int);
void benchmark_pair(int *tab, int, int, int);
void benchmark_impair(int *tab, int, int, int);
void initialisation_aleatoire(int *tab, int, int, int);
void benchmark_aleatoire_0_20(int *tab, int, int, int);
void benchmark_aleatoire_0_INT_MAX(int *tab, int, int, int);
void benchmark_puissances_de_2(int *tab, int, int, int);
void benchmark_nombres_premiers(int *tab, int, int, int);

#endif