#ifndef FORET_H
#define FORET_H

#include <vector>     // Pour utiliser std::vector
#include <random>     // Pour la génération aléatoire
#include <iostream>   // Pour l'affichage avec std::cout

// ───────────────────────────────────────────────
// Enumération représentant les différents états
// qu'une cellule de la forêt peut avoir.
// ───────────────────────────────────────────────
enum CellState {
    TREE,    // Arbre sain (non en feu)
    FIRE,    // Arbre en feu (sera utilisé plus tard)
    ASH,     // Cendre (après combustion)
    EMPTY    // Espace vide (pas d'arbre)
};

// ───────────────────────────────────────────────
// Classe Forest : représente une grille 2D
// modélisant une forêt dans laquelle le feu
// peut se propager. Cette version contient
// seulement l'initialisation de base et
// l'affichage.
// ───────────────────────────────────────────────
class Forest {
private:
    int rows; // Nombre de lignes de la grille
    int cols; // Nombre de colonnes de la grille

    // Grille principale représentant l'état de chaque cellule
    std::vector<std::vector<CellState>> grid;

public:
    // Constructeur : initialise une grille vide de taille rows x cols
    Forest(int r, int c);

    // Remplit la grille avec des arbres ou des espaces vides,
    // selon une densité donnée (entre 0.0 et 1.0)
    void initialize(double treeDensity);

    // Affiche la grille dans la console avec des symboles :
    // T = arbre, F = feu, C = cendre, . = vide
    void display() const;
};

#endif // FOREST_H

// ───────────────────────────────────────────────
// Implémentation des méthodes (directement ici
// pour simplification, mais peut être déplacée
// dans forest.cpp plus tard)
// ───────────────────────────────────────────────

Forest::Forest(int r, int c) : rows(r), cols(c), grid(r, std::vector<CellState>(c, EMPTY)) {
    // Toutes les cellules sont initialisées à "EMPTY" (vide)
}

void Forest::initialize(double treeDensity) {
    // Générateur de nombres aléatoires basé sur le matériel (bon pour simulation)
    std::random_device rd;
    std::mt19937 gen(rd());  // Mersenne Twister (pseudo-aléatoire)
    std::uniform_real_distribution<> dis(0.0, 1.0); // Distribution [0.0, 1.0)

    // Parcours de toute la grille pour remplir chaque cellule
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Si la valeur aléatoire < densité d'arbre, on place un arbre
            // Sinon, on laisse la cellule vide
            grid[i][j] = (dis(gen) < treeDensity) ? TREE : EMPTY;
        }
    }
}

void Forest::display() const {
    // Affichage ligne par ligne
    for (const auto& row : grid) {
        for (CellState cell : row) {
            // On choisit un caractère distinct pour représenter chaque état
            char symbol;
            switch (cell) {
            case TREE: symbol = 'A'; break;   // Arbre sain
            case FIRE: symbol = 'F'; break;   // En feu
            case ASH:  symbol = 'C'; break;   // Cendre (Consumed)
            case EMPTY: symbol = '.'; break;  // Vide
            }
            std::cout << symbol;
        }
        std::cout << "\n"; // Nouvelle ligne après chaque rangée
    }
}
