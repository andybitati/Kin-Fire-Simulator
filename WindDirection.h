#ifndef WINDDIRECTION_H
#define WINDDIRECTION_H

#include <string>

// Enum pour les directions cardinales
enum WindDir { NONE = 0, NORTH, SOUTH, EAST, WEST };

// Classe représentant la direction et l'effet du vent
class WindDirection {
private:
    WindDir direction;   // Direction du vent
    double factor;       // Intensité (ex : 1.5 signifie 50% de chance en plus)

public:
    // Constructeur avec direction et facteur
    WindDirection(WindDir dir = NONE, double f = 1.0) : direction(dir), factor(f) {}

    // Retourne le facteur à appliquer selon la direction du vent
    double getFactor(int dx, int dy) const {
        switch (direction) {
            case NORTH: return (dx == -1 && dy == 0) ? factor : 1.0;
            case SOUTH: return (dx == 1 && dy == 0) ? factor : 1.0;
            case EAST:  return (dx == 0 && dy == 1) ? factor : 1.0;
            case WEST:  return (dx == 0 && dy == -1) ? factor : 1.0;
            default:    return 1.0;
        }
    }

    // Nom textuel de la direction (pour debug ou affichage)
    std::string getDirectionName() const {
        switch (direction) {
            case NORTH: return "NORD";
            case SOUTH: return "SUD";
            case EAST:  return "EST";
            case WEST:  return "OUEST";
            default:    return "AUCUN";
        }
    }

    WindDir getDirection() const {
        return direction;
    }
};

#endif
