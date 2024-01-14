//
// Created by Sami Letellier on 24/12/2023.
//
#include "../include/sorting/sorting_algorithms.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <time.h>
#include <float.h>

void swap(int *x, int *y) {
    int tmp = *x;
    *x = *y;
    *y = tmp;
}

void bubble_sort(int *tab, int taille) {
    for (int i = 0; i < taille; i++) {
        for (int j = 0; j < taille - 1; j++) {
            if (tab[j] > tab[j + 1]) swap(&tab[j], &tab[j + 1]);
        }
    }
}

void selection_sort(int *tab, int taille) {
    int i, j, min_idx;
    for (i = 0; i < taille - 1; i++) {
        min_idx = i;
        for (j = i + 1; j < taille; j++)
            if (tab[j] < tab[min_idx])
                min_idx = j;
        swap(&tab[min_idx], &tab[i]);
    }
}

void gnome_sort(int *tab, int taille) {
    int index = 0;
    while (index < taille) {
        if (index == 0)
            index++;
        if (tab[index] >= tab[index - 1])
            index++;
        else {
            swap(&tab[index], &tab[index - 1]);
            index--;
        }
    }
}

void bubble_sort_opt(int *tab, int taille) {
    int i, j;
    int swapped;

    for (i = 0; i < taille - 1; i++) {
        swapped = 0; // Aucun échange n'a été fait pour l'instant

        for (j = 0; j < taille - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                swap(&tab[j], &tab[j + 1]);
                swapped = 1; // Indique qu'un échange a été effectué
            }
        }

        // Si aucun échange n'a été effectué pendant cette itération,
        // le tableau est déjà trié, donc on peut sortir du boucle
        if (swapped == 0) {
            break;
        }
    }
}

void insertion_sort(int *tab, int taille) {
    int i, j, key;

    for (i = 1; i < taille; i++) {
        key = tab[i];
        j = i - 1;

        while (j >= 0 && tab[j] > key) {
            swap(&tab[j], &tab[j + 1]);
            j--;
        }
    }
}

void shell_sort(int *tab, int taille) {
    int intervalle, i, j, temp;

    for (intervalle = taille / 2; intervalle > 0; intervalle /= 2) {
        for (i = intervalle; i < taille; i++) {
            temp = tab[i];

            for (j = i; j >= intervalle && tab[j - intervalle] > temp; j -= intervalle) {
                swap(&tab[j], &tab[j - intervalle]);
            }

            tab[j] = temp;
        }
    }
}

void exchange_sort(int *tab, int taille) {
    int i, j;

    for (i = 0; i < taille - 1; i++) {
        for (j = 0; j < taille - i - 1; j++) {
            if (tab[j] > tab[j + 1]) {
                swap(&tab[j], &tab[j + 1]);
            }
        }
    }
}

void merge(int *a, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = a[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = a[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            a[k] = L[i];
            i++;
        } else {
            a[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        a[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        a[k] = R[j];
        j++;
        k++;
    }
}

int min(int x, int y) {
    return x < y ? x : y;
}

void merge_sort(int *a, int n) {
    for (int curr_size = 1; curr_size <= n - 1; curr_size = 2 * curr_size) {
        for (int left_start = 0; left_start < n - 1; left_start += 2 * curr_size) {
            int mid = (left_start + curr_size - 1 < n - 1) ? left_start + curr_size - 1 : n - 1;
            int right_end = (left_start + 2 * curr_size - 1 < n - 1) ? left_start + 2 * curr_size - 1 : n - 1;
            merge(a, left_start, mid, right_end);
        }
    }
}

void heapify(int *array, int n, int i) {
    int largest = i;
    int l = 2 * i + 1; // gauche
    int r = 2 * i + 2; // droite

    // Si le fils gauche est plus grand que la racine
    if (l < n && array[l] > array[largest])
        largest = l;

    // Si le fils droit est plus grand que la racine
    if (r < n && array[r] > array[largest])
        largest = r;

    // Si la racine n'est pas la plus grande
    if (largest != i) {
        int swap = array[i];
        array[i] = array[largest];
        array[largest] = swap;

        // Ré-appliquer heapify au sous-arbre affecté
        heapify(array, n, largest);
    }
}

void iterative_heap_sort(int *array, int size) {
    // Construire le tas (réarranger le tableau)
    for (int i = size / 2 - 1; i >= 0; i--)
        heapify(array, size, i);

    // Extraire un par un les éléments du tas
    for (int i = size - 1; i >= 0; i--) {
        // Déplacer la racine courante à la fin
        int temp = array[0];
        array[0] = array[i];
        array[i] = temp;

        // Appeler heapify sur le tas réduit
        heapify(array, i, 0);
    }
}
