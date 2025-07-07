#ifndef FORET_H
#define FORET_H

// Inclusion des bibliothèques nécessaires
#include <vector>           // Pour utiliser les tableaux 2D dynamiques
#include <random>           // Pour la génération aléatoire (propagation du feu)
#include <iostream>         // Pour l'affichage de la forêt
#include <omp.h>            // Pour la parallélisation avec OpenMP

// Enumération des états possibles d'une cellule dans la forêt
enum CellState {
    TREE,   // Arbre sain
    FIRE,   // Arbre en feu
    ASH,    // Arbre réduit en cendre
    EMPTY   // Cellule vide (sans arbre)
};

// Classe représentant la forêt
class Forest {
private:
    int rows;   // Nombre de lignes de la forêt
    int cols;   // Nombre de colonnes de la forêt

    // Grille actuelle représentant l’état de chaque cellule (forêt actuelle)
    std::vector<std::vector<CellState>> currentGrid;

    // Grille temporaire pour stocker les états futurs des cellules
    std::vector<std::vector<CellState>> nextGrid;

    double spreadProb;  // Probabilité que le feu se propage à un arbre voisin

    // Générateur de nombres aléatoires pour la propagation
    mutable std::mt19937 rng; // Générateur Mersenne Twister (mutable pour être utilisable dans les méthodes const)
    mutable std::uniform_real_distribution<> spreadDist; // Distribution uniforme entre 0 et 1

public:
    // Constructeur : initialise la forêt avec dimensions et probabilité de propagation du feu
    Forest(int r, int c, double prob = 0.5);

    // Initialise la forêt avec une certaine densité d'arbres (entre 0 et 1)
    void initialize(double treeDensity);

    // Allume un feu à une position donnée (x, y)
    void ignite(int x, int y);

    // Simule une étape de propagation du feu
    void simulateStep();

    // Affiche la grille actuelle de la forêt dans la console
    void display() const;

private:
    // Met à jour l’état d’une cellule donnée (selon les voisins et la probabilité)
    CellState updateCell(int x, int y) const;

    // Vérifie si la cellule a un voisin en feu (nécessaire pour propager le feu)
    bool hasBurningNeighbor(int x, int y) const;
};

#endif // FORET_H
