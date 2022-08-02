#include <iostream>
#include <cmath>
#include "Grid.h"
using namespace std;

// Initialization of grid (a x b) values with predefined example function
void grid_init_cos_sin(Grid &u, int a, int b)
{
    for (int i = 0; i < u.i_max + u.i_g; i++) {
        for (int j = 0; j < u.j_max + u.j_g; j++) {
            u.grid[i][j] = cos(i*a/(u.i_max+u.i_g))*sin(j*b/(u.j_max+u.j_g));
        }
    }
}

void grid_init_val(Grid &u, float val)
{
    for (int i = 0; i < u.i_max + u.i_g; i++) {
        for (int j = 0; j < u.j_max + u.j_g; j++) {
            u.grid[i][j] = val;
        }
    }
}

