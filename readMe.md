### Exécution du programme : 

1. Se rendre dans le dossier src avec le terminal
```
cd src/
```

2. Compiler le programme avec la commmande suivannte :
```
gcc main.c sorting_algorithms.c benchmarks.c utility_functions.c -o prog
```

## Affichage des tableaux

J'ai commenté les lignes qui permettent d'afficher les tableaux avant et après le tri.
Pour les afficher dans la console il faut deécommenter les lignes :
- 139 à 140.
- 160 à 161.

Dans le dossier `output` il y a déjà des donneées si vous souhaitez les consulter. <br>
Sinon, après exécution du programmes, vos graphes seront générés dans le dossier `output/graphics`


## Si le script python génère des erreurs à l'exécution du script :

Il faut utiliser l'environnement virutel de python en exécutant les commandes suivant dans le dossier `python/`
```
python3 -m venv venv
```

```
pip install pandas matplotlib
```
