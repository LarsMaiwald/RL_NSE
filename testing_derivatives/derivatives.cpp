#include <iostream>
#include <algorithm>
#include <math.h>
#include "Grid.h"

using namespace std;

float grid_max(Grid &a){
    float grid_max = a.grid[0][0];
    for(int i = 0; i < a.i_max + a.i_g; i++){ // is the range correct?
        for(int j = 0; j < a.j_max + a.j_g; j++){ // is the range correct?
            grid_max = max(grid_max, a.grid[i][j]);
        }
    }
    return grid_max;
}

float grid_max_abs(Grid &a){
    float grid_max = abs(a.grid[0][0]);
    for(int i = 0; i < a.i_max + a.i_g; i++){ // is the range correct?
        for(int j = 0; j < a.j_max + a.j_g; j++){ // is the range correct?
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
    for(int i = 1; i < u.i_max; i++){ // is the range correct?
        for(int j = 1; j < u.j_max + 1; j++){ // is the range correct?
            u.grid[i][j] = F.grid[i][j] - dt*dpdx.grid[i][j];
        }
    }
    for(int i = 1; i < v.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < v.j_max; j++){ // is the range correct?
            v.grid[i][j] = G.grid[i][j] - dt*dpdy.grid[i][j];
        }
    }
}

void F_and_G(Grid &F, Grid &G, Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dt, float Re, float g_x, float g_y){
    for(int i = 1; i < F.i_max; i++){ // is the range correct?
        for(int j = 1; j < F.j_max + 1; j++){ // is the range correct?
            F.grid[i][j] = u.grid[i][j] + dt*((d2udx2.grid[i][j] + d2udy2.grid[i][j])/Re - du2dx.grid[i][j] - duvdy.grid[i][j] + g_x);
        }
    }
    for(int i = 1; i < G.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < G.j_max; j++){ // is the range correct?
            G.grid[i][j] = v.grid[i][j] + dt*((d2vdx2.grid[i][j] + d2vdy2.grid[i][j])/Re - duvdx.grid[i][j] - dv2dy.grid[i][j] + g_y);
        }
    }
}

void derivative_stencils(Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dx, float dy, float gamma){
    for(int i = 1; i < u.i_max; i++){ // is the range correct?
        for(int j = 1; j < u.j_max + 1; j++){ // is the range correct?
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
    for(int i = 1; i < v.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < v.j_max; j++){ // is the range correct?
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
