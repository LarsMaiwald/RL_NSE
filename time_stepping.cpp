#include <iostream>
#include <algorithm>
#include <math.h>
#include "Grid.h"

using namespace std;

float grid_max(Grid &a){
    float grid_max = a.grid[0][0];
    for(int i = int(a.i_g/2); i < a.i_max + 1; i++){ // is the range correct?
        for(int j = int(a.j_g/2); j < a.j_max + 1; j++){ // is the range correct?
            grid_max = max(grid_max, a.grid[i][j]);
        }
    }
    return grid_max;
}

float grid_max_abs(Grid &a){
    float grid_max = abs(a.grid[int(a.i_g/2)][int(a.j_g/2)]);
    for(int i = int(a.i_g/2); i < a.i_max + 1; i++){ // is the range correct?
        for(int j = int(a.j_g/2); j < a.j_max + 1; j++){ // is the range correct?
            grid_max = max(grid_max, abs(a.grid[i][j]));
        }
    }
    return grid_max;
}

// Is it correct with max(abs(u)) or should it be abs(max(u))?
float time_step(Grid &u, Grid &v, float tau, float Re, float dx, float dy){
    float v1 = Re/(2*(1/(dx*dx) + 1/(dy*dy)));
    float v2 = dx/grid_max_abs(u);
    float v3 = dy/grid_max_abs(v);
    float dt = tau*min({v1, v2, v3});
    return dt;
}

void iterate(Grid &u, Grid &v, Grid &F, Grid &G, Grid &dpdx, Grid &dpdy, float tau, int Re, float dx, float dy, float dt){
    for(int i = int(u.i_g/2); i < u.i_max + 1; i++){ // is the range correct?
        for(int j = int(u.j_g/2); j < u.j_max + 1; j++){ // is the range correct?
            u.grid[i][j] = F.grid[i][j] - dt*dpdx.grid[i][j];
        }
    }
    for(int i = int(v.i_g/2); i < v.i_max + 1; i++){ // is the range correct?
        for(int j = int(v.i_g/2); j < v.j_max + 1; j++){ // is the range correct?
            v.grid[i][j] = G.grid[i][j] - dt*dpdy.grid[i][j];
        }
    }
}

void F_and_G(Grid &F, Grid &G, Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dt, float Re, float g_x, float g_y){
    // Do we need an extra loops for G?
    for(int i = int(F.i_g/2); i < F.i_max + 1; i++){ // is the range correct?
        for(int j = int(F.j_g/2); j < F.j_max + 1; j++){ // is the range correct?
            F.grid[i][j] = u.grid[i][j] + dt*((d2udx2.grid[i][j] + d2udy2.grid[i][j])/Re - du2dx.grid[i][j] - duvdy.grid[i][j] + g_x);
            G.grid[i][j] = v.grid[i][j] + dt*((d2vdx2.grid[i][j] + d2vdy2.grid[i][j])/Re - duvdx.grid[i][j] - dv2dy.grid[i][j] + g_y);
        }
    }
}

void derivative_stencils(Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dx, float dy, float gamma){
    // Do we need an extra loops for v?
    for(int i = int(u.i_g/2); i < u.i_max + 1; i++){ // is the range correct?
        for(int j = int(u.j_g/2); j < u.j_max + 1; j++){ // is the range correct?
            // second derivatives of the linear terms
            d2udx2.grid[i][j] = (u.grid[i+1][j] - 2*u.grid[i][j] + u.grid[i-1][j])/(dx*dx);
            d2vdx2.grid[i][j] = (v.grid[i+1][j] - 2*v.grid[i][j] + v.grid[i-1][j])/(dx*dx);
            d2udy2.grid[i][j] = (u.grid[i][j+1] - 2*u.grid[i][j] + u.grid[i][j-1])/(dy*dy);
            d2vdy2.grid[i][j] = (v.grid[i][j+1] - 2*v.grid[i][j] + v.grid[i][j-1])/(dy*dy);

            // nonlinear derivatives
            du2dx.grid[i][j] = (((u.grid[i][j] + u.grid[i+1][j])/2)*((u.grid[i][j] + u.grid[i+1][j])/2) - ((u.grid[i-1][j] + u.grid[i][j])/2)*((u.grid[i-1][j] + u.grid[i][j])/2))/dx
                    + gamma*(abs(u.grid[i][j] + u.grid[i+1][j])*(u.grid[i][j] - u.grid[i+1][j])/4 - abs(u.grid[i-1][j] + u.grid[i][j])*(u.grid[i-1][j] - u.grid[i][j])/4)/dx;

            duvdy.grid[i][j] = ((v.grid[i][j] + v.grid[i+1][j])*(u.grid[i][j] + u.grid[i][j+1])/4 - (v.grid[i][j-1] + v.grid[i+1][j-1])*(u.grid[i][j-1] + u.grid[i][j])/4)/dy
                    + gamma*(abs(v.grid[i][j] + v.grid[i+1][j])*(u.grid[i][j] - u.grid[i][j+1])/4 - abs(v.grid[i][j-1] + v.grid[i+1][j-1])*(u.grid[i][j-1] - u.grid[i][j])/4)/dy;

            dv2dy.grid[i][j] = (((v.grid[i][j] + v.grid[i][j+1])/2)*((v.grid[i][j] + v.grid[i][j+1])/2) - ((v.grid[i][j-1] + v.grid[i][j])/2)*((v.grid[i][j-1] + v.grid[i][j])/2))/dx
                    + gamma*(abs(v.grid[i][j] + v.grid[i][j+1])*(v.grid[i][j] - v.grid[i][j+1])/4 - abs(v.grid[i][j-1] + v.grid[i][j])*(v.grid[i][j-1] - v.grid[i][j])/4)/dx;

            duvdx.grid[i][j] = ((u.grid[i][j] + u.grid[i][j+1])*(v.grid[i][j] + v.grid[i+1][j])/4 - (u.grid[i-1][j] + u.grid[i-1][j+1])*(v.grid[i-1][j] + v.grid[i][j])/4)/dy
                    + gamma*(abs(u.grid[i][j] + u.grid[i][j+1])*(v.grid[i][j] - v.grid[i+1][j])/4 - abs(u.grid[i-1][j] + u.grid[i-1][j+1])*(v.grid[i-1][j] - v.grid[i][j])/4)/dy;
        }
    }
}

float gamma(Grid &u, Grid &v, float dx, float dy, float dt, float pre){
    float m1 = grid_max_abs(u);
    float m2 = grid_max_abs(v);
    float gamma = (1 + pre)*max(m1*dt/dx, m2*dt/dy);
    return gamma;
}
