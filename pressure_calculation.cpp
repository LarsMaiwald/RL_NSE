#include <iostream>
#include "Grid.h"
using namespace std;

void pressure_deriv(Grid &p, Grid &dpdx, Grid &dpdy, float dx, float dy){
    for(int i = 0; i < p.i_max + p.i_g; i++){ // is the range correct? --> no
        for(int j = 0; j < p.j_max + p.j_g; j++){ // is the range correct? --> no
            dpdx.grid[i][j] = (p.grid[i+1][j] - p.grid[i][j])/dx;
            dpdy.grid[i][j] = (p.grid[i][j+1] - p.grid[i][j])/dy;
        }
    }
}
