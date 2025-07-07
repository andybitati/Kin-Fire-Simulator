#include "Foret.h"               // Déclaration de la classe Forest
#include "WindDirection.h"       // Déclaration de la classe WindDirection

#include <iostream>              // Pour std::cout, std::cin
#include <iomanip>               // Pour std::setprecision
#include <thread>                // Pour std::this_thread::sleep_for
#include <chrono>                // Pour std::chrono::high_resolution_clock

int main() {
    // Variables de configuration
    int rows, cols;
    double treeDensity;
    double spreadProbability;
    double obstacleDensity;
    int windChoice;
    double windFactor;

    // Interface utilisateur pour la configuration de la simulation
    std::cout << "\n=== Configuration de la simulation ===\n";
    std::cout << "Taille de la forêt (lignes colonnes) : ";
    std::cin >> rows >> cols;

    std::cout << "Densité d'arbres (0.0 à 1.0) : ";
    std::cin >> treeDensity;

    std::cout << "Densité d'obstacles (0.0 à 1.0) : ";
    std::cin >> obstacleDensity;

    std::cout << "Probabilité de propagation (0.0 à 1.0) : ";
    std::cin >> spreadProbability;

    std::cout << "Direction du vent (0: NONE, 1: NORD, 2: SUD, 3: EST, 4: OUEST) : ";
    std::cin >> windChoice;

    std::cout << "Facteur d'effet du vent (> 1.0 pour renforcer la propagation) : ";
    std::cin >> windFactor;

    // Création de la direction du vent à partir des saisies
    WindDirection wind(static_cast<WindDir>(windChoice), windFactor);

    // Création de la forêt avec les paramètres saisis
    Forest forest(rows, cols, spreadProbability, wind);
    forest.initialize(treeDensity, obstacleDensity);
    forest.ignite(rows / 2, cols / 2); // Allumer le feu au centre

    std::cout << "\n\033[1m\033[32m\033[4mSimulation de feu de forêt\033[0m\n\n";
    forest.display(); // Affiche l’état initial

    int steps = 15;
    auto start = std::chrono::high_resolution_clock::now(); // Démarre le chrono

    // Boucle principale de simulation
    for (int i = 0; i < steps; ++i) {
        std::cout << "\nÉtape " << (i + 1) << " :\n";
        forest.simulateStep();
        forest.display();
        forest.displayStats();
        //std::this_thread::sleep_for(std::chrono::milliseconds(400)); // Pause
    }

    auto end = std::chrono::high_resolution_clock::now(); // Fin chrono
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nTemps d'exécution total: " << std::fixed << std::setprecision(3) << elapsed.count() << "s\n";

    return 0;
}
