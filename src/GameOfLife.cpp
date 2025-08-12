#include "GameOfLife.h"
#include <random>
#include <chrono>

GameOfLife::GameOfLife(int width, int height, int cellSize)
    : width(width), height(height), cellSize(cellSize),
      rows(height / cellSize), cols(width / cellSize),
      grid(rows, std::vector<bool>(cols, false)),
      nextGrid(rows, std::vector<bool>(cols, false)),
      running(false) {
}

GameOfLife::~GameOfLife() {
}

void GameOfLife::initRandom() {
    std::default_random_engine generator(std::chrono::system_clock::now().time_since_epoch().count());
    std::uniform_int_distribution<int> distribution(0, 1);

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = distribution(generator);
        }
    }
}

void GameOfLife::update() {
    if (!running) {
        return;
    }

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            int liveNeighbors = countLiveNeighbors(i, j);

            if (grid[i][j]) { // Cell is alive
                if (liveNeighbors < 2 || liveNeighbors > 3) {
                    nextGrid[i][j] = false; // Underpopulation or Overpopulation
                } else {
                    nextGrid[i][j] = true; // Stays alive
                }
            } else { // Cell is dead
                if (liveNeighbors == 3) {
                    nextGrid[i][j] = true; // Reproduction
                } else {
                    nextGrid[i][j] = false; // Stays dead
                }
            }
        }
    }
    grid = nextGrid;
}

void GameOfLife::render(SDL_Renderer* renderer) {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White for live cells
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            if (grid[i][j]) {
                SDL_Rect cellRect = {j * cellSize, i * cellSize, cellSize, cellSize};
                SDL_RenderFillRect(renderer, &cellRect);
            }
        }
    }
    SDL_RenderPresent(renderer);
}

void GameOfLife::toggleCell(int mouseX, int mouseY) {
    int col = mouseX / cellSize;
    int row = mouseY / cellSize;

    if (row >= 0 && row < rows && col >= 0 && col < cols) {
        grid[row][col] = !grid[row][col];
    }
}

void GameOfLife::reset() {
    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            grid[i][j] = false;
        }
    }
    running = false;
}

int GameOfLife::countLiveNeighbors(int r, int c) {
    int liveNeighbors = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            if (i == 0 && j == 0) continue; // Don't count self

            int neighborRow = r + i;
            int neighborCol = c + j;

            // Wrap around edges (toroidal array)
            if (neighborRow < 0) neighborRow = rows - 1;
            if (neighborRow >= rows) neighborRow = 0;
            if (neighborCol < 0) neighborCol = cols - 1;
            if (neighborCol >= cols) neighborCol = 0;

            if (grid[neighborRow][neighborCol]) {
                liveNeighbors++;
            }
        }
    }
    return liveNeighbors;
}
