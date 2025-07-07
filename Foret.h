#ifndef FORET_H
#define FORET_H

#include <vector>
#include <random>
#include <iostream>
#include <omp.h>
#include "WindDirection.h"  // Pour intégrer le vent

// État d'une cellule
enum CellState {
    TREE,       // Arbre
    FIRE,       // En feu
    ASH,        // Cendre
    EMPTY,      // Vide
    OBSTACLE    // Roche, rivière...
};

// Classe Forest simulant la propagation
class Forest {
private:
    int rows, cols;  // Dimensions
    std::vector<std::vector<CellState>> currentGrid, nextGrid; // Grilles
    double spreadProb;  // Probabilité de propagation
    WindDirection wind; // Vent
    mutable std::mt19937 rng; // Générateur aléatoire
    mutable std::uniform_real_distribution<> dist;

public:
    Forest(int r, int c, double prob, const WindDirection& windDir);

    void initialize(double treeDensity, double obstacleDensity = 0.0);
    void ignite(int x, int y);
    void simulateStep();
    void display() const;
    void displayStats() const;

private:
    CellState updateCell(int x, int y) const;
    bool hasBurningNeighbor(int x, int y, int& dx, int& dy) const;
};

#endif
