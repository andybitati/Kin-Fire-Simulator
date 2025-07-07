#include "Foret.h" // Inclusion du header contenant la définition de la classe Forest

// Constructeur : initialise la grille avec les dimensions données et la probabilité de propagation
Forest::Forest(int r, int c, double prob)
    : rows(r), cols(c), spreadProb(prob),
      currentGrid(r, std::vector<CellState>(c, EMPTY)),  // Grille courante initialisée à VIDE
      nextGrid(r, std::vector<CellState>(c, EMPTY)),     // Grille suivante également initialisée à VIDE
      rng(std::random_device{}()), spreadDist(0.0, 1.0)  // Générateur aléatoire initialisé et distribution uniforme [0,1]
{}

// Initialise la grille avec des arbres selon une densité donnée
void Forest::initialize(double treeDensity) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            // Pour chaque cellule, si un nombre aléatoire est inférieur à la densité, on y met un arbre
            if (spreadDist(rng) < treeDensity) {
                currentGrid[i][j] = TREE;
            } else {
                currentGrid[i][j] = EMPTY;
            }
        }
    }
}

// Allume un feu à la position (x, y) si la cellule contient un arbre
void Forest::ignite(int x, int y) {
    if (x >= 0 && x < rows && y >= 0 && y < cols && currentGrid[x][y] == TREE) {
        currentGrid[x][y] = FIRE;
    }
}

// Simule une étape de propagation du feu dans toute la forêt
void Forest::simulateStep() {
    // Boucle parallèle sur toutes les cellules (2D) grâce à OpenMP pour améliorer les performances
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            nextGrid[i][j] = updateCell(i, j); // Mise à jour de l'état de chaque cellule
        }
    }

    // Échange des grilles : la grille suivante devient la grille courante
    std::swap(currentGrid, nextGrid);
}

// Détermine le nouvel état d'une cellule en fonction de son état actuel et de ses voisins
CellState Forest::updateCell(int x, int y) const {
    CellState current = currentGrid[x][y]; // Récupère l’état actuel

    if (current == FIRE) {
        return ASH; // Un arbre en feu devient de la cendre
    }

    // Si un arbre a un voisin en feu, il peut prendre feu selon une probabilité
    if (current == TREE && hasBurningNeighbor(x, y)) {
        if (spreadDist(rng) < spreadProb) {
            return FIRE;
        }
    }

    // Sinon, l'état reste le même
    return current;
}

// Vérifie si une cellule a au moins un voisin en feu (dans les 8 directions autour)
bool Forest::hasBurningNeighbor(int x, int y) const {
    // Tableaux de directions pour parcourir les 8 voisins (haut, bas, gauche, droite et diagonales)
    const int dx[] = {-1, -1, -1, 0, 0, 1, 1, 1};
    const int dy[] = {-1,  0,  1, -1, 1, -1, 0, 1};

    for (int i = 0; i < 8; ++i) {
        int nx = x + dx[i];
        int ny = y + dy[i];

        // Vérifie que le voisin est dans la grille et qu'il est en feu
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols && currentGrid[nx][ny] == FIRE) {
            return true;
        }
    }
    return false; // Aucun voisin en feu
}

// Affiche l'état actuel de la forêt dans la console (sous forme de symboles)
void Forest::display() const {
    for (const auto& row : currentGrid) {
        for (CellState cell : row) {
            char symbol;
            // Choix du caractère à afficher selon l'état de la cellule
            switch (cell) {
                case TREE: symbol = 'T'; break;   // Arbre
                case FIRE: symbol = 'F'; break;   // Feu
                case ASH:  symbol = 'C'; break;   // Cendre
                case EMPTY: symbol = '.'; break;  // Vide
                default:   symbol = '?';          // Inconnu (sécurité)
            }
            std::cout << symbol << " "; // Affiche le symbole avec un espace
        }
        std::cout << "\n"; // Saut de ligne après chaque ligne de la grille
    }
}
