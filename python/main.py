import pandas as pd
import matplotlib.pyplot as plt
import os


file_path = '../output/resultats.csv'

if not os.path.exists(file_path):
    raise FileNotFoundError(f"Le fichier {file_path} n'existe pas. Veuillez charger le fichier.")

df = pd.read_csv(file_path)

df.columns = df.columns.str.strip()

# Obtenir les algorithmes et les types de tableaux uniques
algorithms = df['Algorithme'].unique()
table_types = df['Type de Tableau'].unique()

# Dossier pour enregistrer les graphiques
output_folder = '../output/graphics'
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# Fonction pour tracer les graphiques
def plot_graph(data, y_column, title_suffix, ylabel):
    for table_type in table_types:
        plt.figure(figsize=(10, 6))
        df_filtered = data[data['Type de Tableau'] == table_type]

        for algo in algorithms:
            df_algo = df_filtered[df_filtered['Algorithme'] == algo]
            plt.plot(df_algo['Taille'], df_algo[y_column], label=algo)

        plt.title(f"Temps {title_suffix} pour {table_type}")
        plt.xlabel('Taille du Tableau')
        plt.ylabel(ylabel)
        plt.legend()
        plt.grid(True)
        plt.savefig(os.path.join(output_folder, f"{table_type.replace(' ', '_')}_{y_column}.png"))
        plt.close()  # Ferme la figure actuelle pour libérer de la mémoire

# Tracer les graphiques pour le temps moyen, min et max
plot_graph(df, 'Temps Moyen', 'd\'exécution moyen', 'Temps Moyen (secondes)')
plot_graph(df, 'Temps Min', 'd\'exécution minimum', 'Temps Min (secondes)')
plot_graph(df, 'Temps Max', 'd\'exécution maximum', 'Temps Max (secondes)')
