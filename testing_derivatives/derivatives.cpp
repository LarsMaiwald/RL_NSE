#include <iostream>
#include <algorithm>
#include <math.h>
#include "Grid.h"

using namespace std;

float grid_max(Grid &a){
    float grid_max = a.grid[0][0];
    for(int i = 0; i < a.i_max + a.i_g; i++){
        for(int j = 0; j < a.j_max + a.j_g; j++){
            grid_max = max(grid_max, a.grid[i][j]);
        }
    }
    return grid_max;
}

float grid_max_abs(Grid &a){
    float grid_max = abs(a.grid[0][0]);
    for(int i = 0; i < a.i_max + a.i_g; i++){
        for(int j = 0; j < a.j_max + a.j_g; j++){
            grid_max = max(grid_max, abs(a.grid[i][j]));
        }
    }
    return grid_max;
}

void derivative_stencils(Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dx, float dy, float gamma){
    for(int i = 1; i < u.i_max; i++){
        for(int j = 1; j < u.j_max + 1; j++){
            // second derivatives of the linear terms
            d2udx2.grid[i][j] = (u.grid[i+1][j] - 2*u.grid[i][j] + u.grid[i-1][j])/(dx*dx);
            d2udy2.grid[i][j] = (u.grid[i][j+1] - 2*u.grid[i][j] + u.grid[i][j-1])/(dy*dy);

            // nonlinear derivatives
            du2dx.grid[i][j] = (((u.grid[i][j] + u.grid[i+1][j])/2)*((u.grid[i][j] + u.grid[i+1][j])/2) - ((u.grid[i-1][j] + u.grid[i][j])/2)*((u.grid[i-1][j] + u.grid[i][j])/2))/dx
                    + gamma*(abs(u.grid[i][j] + u.grid[i+1][j])*(u.grid[i][j] - u.grid[i+1][j])/4 - abs(u.grid[i-1][j] + u.grid[i][j])*(u.grid[i-1][j] - u.grid[i][j])/4)/dx;

            duvdy.grid[i][j] = ((v.grid[i][j] + v.grid[i+1][j])*(u.grid[i][j] + u.grid[i][j+1])/4 - (v.grid[i][j-1] + v.grid[i+1][j-1])*(u.grid[i][j-1] + u.grid[i][j])/4)/dy
                    + gamma*(abs(v.grid[i][j] + v.grid[i+1][j])*(u.grid[i][j] - u.grid[i][j+1])/4 - abs(v.grid[i][j-1] + v.grid[i+1][j-1])*(u.grid[i][j-1] - u.grid[i][j])/4)/dy;
        }
    }
    for(int i = 1; i < v.i_max + 1; i++){
            for(int j = 1; j < v.j_max; j++){
            // second derivatives of the linear terms
            d2vdx2.grid[i][j] = (v.grid[i+1][j] - 2*v.grid[i][j] + v.grid[i-1][j])/(dx*dx);
            d2vdy2.grid[i][j] = (v.grid[i][j+1] - 2*v.grid[i][j] + v.grid[i][j-1])/(dy*dy);

            // nonlinear derivatives
            dv2dy.grid[i][j] = (((v.grid[i][j] + v.grid[i][j+1])/2)*((v.grid[i][j] + v.grid[i][j+1])/2) - ((v.grid[i][j-1] + v.grid[i][j])/2)*((v.grid[i][j-1] + v.grid[i][j])/2))/dy
                    + gamma*(abs(v.grid[i][j] + v.grid[i][j+1])*(v.grid[i][j] - v.grid[i][j+1])/4 - abs(v.grid[i][j-1] + v.grid[i][j])*(v.grid[i][j-1] - v.grid[i][j])/4)/dy;

            duvdx.grid[i][j] = ((u.grid[i][j] + u.grid[i][j+1])*(v.grid[i][j] + v.grid[i+1][j])/4 - (u.grid[i-1][j] + u.grid[i-1][j+1])*(v.grid[i-1][j] + v.grid[i][j])/4)/dx
                    + gamma*(abs(u.grid[i][j] + u.grid[i][j+1])*(v.grid[i][j] - v.grid[i+1][j])/4 - abs(u.grid[i-1][j] + u.grid[i-1][j+1])*(v.grid[i-1][j] - v.grid[i][j])/4)/dx;
        }
    }
}

float get_gamma(Grid &u, Grid &v, float dx, float dy, float dt, float pre){
    float m1 = grid_max_abs(u);
    float m2 = grid_max_abs(v);
    float gamma = (1 + pre)*max(m1*dt/dx, m2*dt/dy);
    return gamma;
}
