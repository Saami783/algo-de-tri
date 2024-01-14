#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <limits.h>
#include "../include/sorting/sorting_algorithms.h"
#include "../include/benchmark/benchmarks.h"
#include "../include/utilities/utility_functions.h"

typedef void (*TriFunction)(int *, int);
typedef void (*GenerationFunction)(int *, int, int, int);

typedef struct {
    char *nom;
    TriFunction fonction;
} AlgorithmeTri;

typedef struct {
    char *nom;
    GenerationFunction fonction;
} GenerationTab;

GenerationTab * get_benchmarks(int *size);
AlgorithmeTri * get_algorithms(int *size);

typedef struct {
    char *name; // Nom de l'algorithme de tri
    TriFunction sortFunc; // Pointeur vers la fonction de tri
    float minTime;
    float maxTime;
    float totalTime; // Temps d'exécution total accumulé pour le calcul de la moyenne
    int executions; // Nombre total d'exécutions effectuées pour le calcul de la moyenne
    double times[10]; // Temps d'exécution pour chaque itération
} PerformanceStats;

PerformanceStats init_performance_stats(const char *name, TriFunction func);
void record_execution_time(PerformanceStats *stats, double time);
float calculate_average_time(PerformanceStats *stats);
void mesure_temps(PerformanceStats *stats, GenerationFunction genFunc, int size, int min, int max, const char* genName);
void execute_and_write(GenerationFunction benchmarkFunction, int *tab, int size, int min, int max, const char *benchmarkName);
void write_to_file(int *tab, int size, const char *benchmarkName);
int *lire_fichier_benchmark(const char *nom_fichier, int *taille);
GenerationTab *get_benchmarks(int *size);
AlgorithmeTri *get_algorithms(int *size);
void reset_performance_stats(PerformanceStats *stats);


int main() {
    srand(time(NULL));

    int min = 0; // Valeur minimale que les éléments du tableau peuvent prendre.
    int max = INT_MAX; // valeur maximale que les éléments du tableau peuvent prendre.
    int tailleMax = 20000; // La taille max des tableaux.
    int increment = 2000; // La taille additionnée des benchmarks à chaque itération.
    int nbAlgorithmes, nbGenerateurs;
    FILE *fichier;

    // Obtention des algorithmes et des générateurs.
    AlgorithmeTri *algorithmes = get_algorithms(&nbAlgorithmes);
    GenerationTab *generateurs = get_benchmarks(&nbGenerateurs);
    PerformanceStats *stats = malloc(nbAlgorithmes * sizeof(PerformanceStats));

    // Initialisation des structures de PerformanceStats.
    for (int i = 0; i < nbAlgorithmes; i++) {
        stats[i] = init_performance_stats(algorithmes[i].nom, algorithmes[i].fonction);
    }

    // Ouverture du fichier de résultats.
    fichier = fopen("../output/resultats.csv", "w");
    if (fichier == NULL) {
        perror("Erreur lors de l'ouverture du fichier");
        free(stats);
        return EXIT_FAILURE;
    }
    fprintf(fichier, "Taille, Type de Tableau, Algorithme, Temps Min, Temps Moyen, Temps Max\n");

    // Boucle principale pour exécuter les benchmarks.
    for (int currentSize = 10000; currentSize <= tailleMax; currentSize += increment) {
        int *tabOriginal = creation_tableau(currentSize);

        for (int i = 0; i < nbGenerateurs; i++) {
            generateurs[i].fonction(tabOriginal, currentSize, min, max);
            for (int j = 0; j < nbAlgorithmes; j++) {
                mesure_temps(&stats[j], generateurs[i].fonction, currentSize, min, max, generateurs[i].nom);

                // Calcul et enregistrement des statistiques.
                float tempsMoyen = calculate_average_time(&stats[j]);
                fprintf(fichier, "%d, %s, %s, %f, %f, %f\n", currentSize, generateurs[i].nom, stats[j].name, stats[j].minTime, tempsMoyen, stats[j].maxTime);

                // Réinitialiser les statistiques pour la prochaine série de mesures.
                reset_performance_stats(&stats[j]);
            }
        }

        free(tabOriginal);
    }

    // Nettoyage.
    fclose(fichier);
    for (int i = 0; i < nbAlgorithmes; i++) {
        free(stats[i].name);
    }
    free(stats);
    free(generateurs);
    free(algorithmes);
    python_script();

    return EXIT_SUCCESS;
}

// Cette fonction devrait avoir la signature correspondant à la déclaration

void mesure_temps(PerformanceStats *stats, GenerationFunction genFunc, int size, int min, int max, const char* genName) {
    printf("Debut de la mesure pour l'algorithme %s avec une taille de %d et un type de tableau %s.\n", stats->name, size, genName);
    reset_performance_stats(stats);

    for (int i = 0; i < 10; i++) {
        printf("Iteration %d...\n", i + 1);

        int *tabOriginal = creation_tableau(size);
        if (tabOriginal == NULL) {
            perror("Erreur d'allocation de memoire pour tabOriginal");
            exit(EXIT_FAILURE);
        }

        genFunc(tabOriginal, size, min, max);  // Generer des donnees pour le tableau.
        printf("Tableau genere par %s.\n", genName);

        int *tabCopy = malloc(size * sizeof(int));
        if (tabCopy == NULL) {
            perror("Erreur d'allocation de memoire pour tab");
            free(tabOriginal);
            exit(EXIT_FAILURE);
        }
        copie_tableau(tabOriginal, tabCopy, size);
        printf("Tableau copie pour le tri %s.\n", stats->name);

        // printf("\n Tableau avant le tri : \n");
        // affichage_tableau(tabCopy, size);

        struct timespec start, end;
        clock_gettime(CLOCK_MONOTONIC, &start);

        stats->sortFunc(tabCopy, size); // Execute l'algorithme de tri

        clock_gettime(CLOCK_MONOTONIC, &end);
        printf("Tri termine pour l'algortihme %s.\n",stats->name);

        if (!is_sorted(tabCopy, size)) {
            fprintf(stderr, "Erreur: le tableau n'est pas trie correctement.\n");
        } else {
            printf("Le tableau a tete trie correctement.\n");
        }

        double time_taken = (end.tv_sec - start.tv_sec) + (end.tv_nsec - start.tv_nsec) / 1e9;
        printf("Temps pris pour l'iteration %d : %f secondes.\n", i + 1, time_taken);
        record_execution_time(stats, time_taken);

        // printf("\n Tableau apres le tri : \n");
        // affichage_tableau(tabCopy, size);

        free(tabOriginal);
        free(tabCopy);
    }

    printf("Mesures terminees pour l'algorithme %s avec un type de tableau %s.\n", stats->name, genName);
}


// Fonction wrapper pour exécuter les benchmarks et écrire les résultats
void execute_and_write(GenerationFunction benchmarkFunction, int *tab, int size, int min, int max, const char *benchmarkName) {
    benchmarkFunction(tab, size, min, max);
    write_to_file(tab, size, benchmarkName);
}

void read_file(int *tab, int size, const char *filename) {
    FILE *fp = fopen(filename, "r");
    if (fp != NULL) {
        for (int i = 0; i < size; i++) {
            fscanf(fp, "%d", &tab[i]);
        }
        fclose(fp);
    }
}

void write_to_file(int *tab, int size, const char *benchmarkName) {
    char filename[100];
    sprintf(filename, "../output/tableau/%s_%d.txt", benchmarkName, size);
    FILE *fp = fopen(filename, "w");
    if (fp != NULL) {
        for (int i = 0; i < size; i++) {
            fprintf(fp, "%d ", tab[i]);
        }
        fclose(fp);
    }
}

GenerationTab *get_benchmarks(int *size) {
    *size = 10;

    GenerationTab *generation_tab = malloc(*size * sizeof(GenerationTab));
    if (generation_tab == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour les benchmarks de tri");
        return NULL;
    }

    generation_tab[0] = (GenerationTab){"Tableau aleatoire", initialisation_aleatoire};
    generation_tab[1] = (GenerationTab){"Tableau croissant", benchmark_constant};
    generation_tab[2] = (GenerationTab){"Tableau decroissant", benchmark_decroissant};
    generation_tab[3] = (GenerationTab){"Tableau constant", benchmark_constant};
    generation_tab[4] = (GenerationTab){"Tableau pair", benchmark_pair};
    generation_tab[5] = (GenerationTab){"Tableau impair", benchmark_impair};
    generation_tab[6] = (GenerationTab){"Tableau aleatoire de 0 a 20", benchmark_aleatoire_0_20};
    generation_tab[7] = (GenerationTab){"Tableau aleatoire de 0 a int_max", benchmark_aleatoire_0_INT_MAX};
    generation_tab[8] = (GenerationTab){"Tableau puissance de 2", benchmark_puissances_de_2};
    generation_tab[9] = (GenerationTab){"Tableau nombre premiers", benchmark_nombres_premiers};

    return generation_tab;
}

AlgorithmeTri *get_algorithms(int *size) {
    *size = 9;

    AlgorithmeTri *algorithmes = malloc(*size * sizeof(AlgorithmeTri));
    if (algorithmes == NULL) {
        perror("Erreur lors de l'allocation de mémoire pour les algorithmes de tri");
        return NULL;
    }

    algorithmes[0] = (AlgorithmeTri){"Bubble Sort", bubble_sort};
    algorithmes[1] = (AlgorithmeTri){"Selection Sort", selection_sort};
    algorithmes[2] = (AlgorithmeTri){"Gnome Sort", gnome_sort};
    algorithmes[3] = (AlgorithmeTri){"Bubble Sort Opt", bubble_sort_opt};
    algorithmes[4] = (AlgorithmeTri){"Insertion Sort", insertion_sort};
    algorithmes[5] = (AlgorithmeTri){"Shell Sort", shell_sort};
    algorithmes[6] = (AlgorithmeTri){"Exchange Sort", exchange_sort};
    algorithmes[7] = (AlgorithmeTri){"Heap Sort", iterative_heap_sort};
    algorithmes[8] = (AlgorithmeTri){"Merge Sort", merge_sort};

    return algorithmes;
}

// Fonction pour initialiser la structure avec un algorithme spécifique
PerformanceStats init_performance_stats(const char *name, TriFunction func) {
    PerformanceStats stats;
    stats.name = strdup(name);
    stats.sortFunc = func;
    stats.minTime = FLT_MAX;
    stats.maxTime = 0.0f;
    stats.totalTime = 0.0f;
    stats.executions = 0;
    memset(stats.times, 0, sizeof(stats.times));
    return stats;
}


// Fonction pour enregistrer le temps d'une exécution
void record_execution_time(PerformanceStats *stats, double time) {
    stats->times[stats->executions % 10] = time;
    if (time < stats->minTime) stats->minTime = time;
    if (time > stats->maxTime) stats->maxTime = time;
    stats->totalTime += time;
    stats->executions++;
}

float calculate_average_time(PerformanceStats *stats) {
    if (stats->executions == 0) return 0.0f;
    float average = stats->totalTime / stats->executions;
    stats->totalTime = 0; // Réinitialise pour la prochaine série de tests
    stats->executions = 0;
    return average;
}

void reset_performance_stats(PerformanceStats *stats) {
    stats->minTime = FLT_MAX;
    stats->maxTime = 0.0f;
    stats->totalTime = 0.0f;
    stats->executions = 0;
    memset(stats->times, 0, sizeof(stats->times));
}
