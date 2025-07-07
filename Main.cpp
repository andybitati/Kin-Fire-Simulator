#include "foret.h" // Inclusion de la définition de la classe Forest

int main() {
    // Définition des dimensions de la grille (modifiable selon les besoins)
    int rows = 40;
    int cols = 40;

    // Densité des arbres : ici, 60% de la grille sera initialisée avec des arbres
    double treeDensity = 0.7;

    // Création d'une instance de forêt avec les dimensions spécifiées
    Forest forest(rows, cols);

    // Remplissage de la forêt avec des arbres aléatoires selon la densité
    forest.initialize(treeDensity);

    // Affichage initial de la grille dans le terminal
    forest.display();

    return 0;
}
