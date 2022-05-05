#include "Grid.h"
#include <iostream>
using namespace std;

Grid::Grid(int i, int j, int i_ghost, int j_ghost)
{
    i_max = i;
    j_max = j;
    i_g = i_ghost;
    j_g = j_ghost;

    float** u = new float*[i_max + i_g];
    for (int i = 0; i < i_max + i_g; i++) {
        u[i] = new float[j_max + j_g];
    }
    for (int i = 0; i < i_max + i_g; i++) {
        for (int j = 0; j < j_max + j_g; j++) {
            u[i][j] = 0;
        }
    }
    grid = u;
}

Grid::~Grid()
{
    for(int i=0; i < i_max + i_g; i++)
    {
        delete [] grid[i];
    }
    delete [] grid;
}

void Grid::print() // Do we want to print the ghost cells?
{
    for (int i = 0; i < i_max + i_g; i++) {
        for (int j = 0; j < j_max + j_g; j++) {
            cout << grid[i][j] << " ";
        }
        cout << "\n";
    }
}
