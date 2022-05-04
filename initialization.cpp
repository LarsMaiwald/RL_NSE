#include <iostream>
#include <cmath>
#include "Grid.h"
using namespace std;

// Initialization of grid (a x b) values with predefined example function
void grid_init(Grid u, int a, int b)
{
    for (int i = 0; i < u.i_max + 2; i++) {
        for (int j = 0; j < u.j_max + 2; j++) {
            u.grid[i][j] = cos(i*a/(u.i_max+2))*sin(j*b/(u.j_max+2));
        }
    }
}
