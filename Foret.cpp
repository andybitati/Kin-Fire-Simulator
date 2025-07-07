#include "Foret.h"

Forest::Forest(int r, int c, double prob, const WindDirection& windDir)
    : rows(r), cols(c), spreadProb(prob), wind(windDir),
      currentGrid(r, std::vector<CellState>(c, EMPTY)),
      nextGrid(r, std::vector<CellState>(c, EMPTY)),
      rng(std::random_device{}()), dist(0.0, 1.0) {}

void Forest::initialize(double treeDensity, double obstacleDensity) {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            double roll = dist(rng);
            if (roll < obstacleDensity)
                currentGrid[i][j] = OBSTACLE;
            else if (roll < obstacleDensity + treeDensity)
                currentGrid[i][j] = TREE;
            else
                currentGrid[i][j] = EMPTY;
        }
    }
}

void Forest::ignite(int x, int y) {
    if (x >= 0 && x < rows && y >= 0 && y < cols && currentGrid[x][y] == TREE)
        currentGrid[x][y] = FIRE;
}

void Forest::simulateStep() {
    #pragma omp parallel for collapse(2)
    for (int i = 0; i < rows; ++i)
        for (int j = 0; j < cols; ++j)
            nextGrid[i][j] = updateCell(i, j);

    std::swap(currentGrid, nextGrid);
}

CellState Forest::updateCell(int x, int y) const {
    CellState current = currentGrid[x][y];
    if (current == FIRE) return ASH;
    if (current != TREE) return current;

    int dx = 0, dy = 0;
    if (hasBurningNeighbor(x, y, dx, dy)) {
        double prob = spreadProb * wind.getFactor(dx, dy);
        if (dist(rng) < prob) return FIRE;
    }

    return current;
}

bool Forest::hasBurningNeighbor(int x, int y, int& dx, int& dy) const {
    const int directions[4][2] = {{-1,0}, {1,0}, {0,1}, {0,-1}}; // N, S, E, W
    for (auto& dir : directions) {
        int nx = x + dir[0], ny = y + dir[1];
        if (nx >= 0 && nx < rows && ny >= 0 && ny < cols) {
            if (currentGrid[nx][ny] == FIRE && currentGrid[x][y] != OBSTACLE) {
                dx = dir[0];
                dy = dir[1];
                return true;
            }
        }
    }
    return false;
}

void Forest::display() const {
    for (const auto& row : currentGrid) {
        for (CellState cell : row) {
            char symbol;
            switch (cell) {
                case TREE: symbol = 'T'; break;
                case FIRE: symbol = 'F'; break;
                case ASH: symbol = 'C'; break;
                case EMPTY: symbol = '.'; break;
                case OBSTACLE: symbol = '#'; break;
                default: symbol = '?';
            }
            std::cout << symbol << " ";
        }
        std::cout << "\n";
    }
}

void Forest::displayStats() const {
    int tree = 0, fire = 0, ash = 0, empty = 0, obstacle = 0;
    for (const auto& row : currentGrid) {
        for (CellState cell : row) {
            switch (cell) {
                case TREE: tree++; break;
                case FIRE: fire++; break;
                case ASH: ash++; break;
                case EMPTY: empty++; break;
                case OBSTACLE: obstacle++; break;
                default: break;
            }
        }
    }
    std::cout << "\n[Stats] Arbres: " << tree << "  Feu: " << fire
              << "  Cendres: " << ash << "  Vides: " << empty
              << "  Obstacles: " << obstacle << "\n";
}
