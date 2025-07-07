#include "Foret.cpp"
#include <chrono>
#include <thread>     // Pour std::this_thread::sleep_for
#include <iomanip>    // Pour std::setprecision

int main() {
    int rows = 20;
    int cols = 20;
    double treeDensity = 0.7;
    double spreadProbability = 0.6;

    Forest forest(rows, cols, spreadProbability);
    forest.initialize(treeDensity);
    forest.ignite(rows / 2, cols / 2); // Feu au centre

    std::cout << "État initial:" << std::endl;
    forest.display();

    int steps = 15;

    auto start = std::chrono::high_resolution_clock::now();

    for (int i = 0; i < steps; ++i) {
        std::cout << "\nÉtape " << i + 1 << ":" << std::endl;
        forest.simulateStep();
        forest.display();

        // Optionnel : pause entre les étapes
        std::this_thread::sleep_for(std::chrono::milliseconds(400));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "\nTemps d'exécution total: " << std::setprecision(3) << elapsed.count() << "s\n";

    return 0;
}
