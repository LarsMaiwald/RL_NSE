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

float time_step(Grid &u, Grid &v, float tau, float Re, float dx, float dy){
    float v1 = Re/(2*(1/(dx*dx) + 1/(dy*dy)));
    float v2 = dx/abs(grid_max(u));
    float v3 = dy/abs(grid_max(v));
    float dt = tau*min({v1, v2, v3});
    return dt;
}

//void iterate(float **u, float **v, float tau, int Re, float dx, float dy, int i_max, int j_max, int num_iter){
//    for(int k = 0; k < num_iter; k++){
//        float dt = time_step(u, v, tau, Re, dx, dy, i_max, j_max);
//        for(int i = 0; i < i_max; i++){
//            for(int j = 0; j < j_max; j++){
//                u[i][j] = F[i][j] - dt*dpdx[i][j];
//                v[i][j] = G[i][j] - dt*dpdy[i][j];
//            }
//        }
//    }
//}

void F_and_G(Grid &F, Grid &G, Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dt, float Re, float g_x, float g_y){
    for(int i = 0; i < u.i_max + u.i_g; i++){ // is the range correct? --> no
        for(int j = 0; j < u.j_max + u.j_g; j++){ // is the range correct? --> no
            F.grid[i][j] = u.grid[i][j] + dt*((d2udx2.grid[i][j] + d2udy2.grid[i][j])/Re - du2dx.grid[i][j] - duvdy.grid[i][j] + g_x);
            G.grid[i][j] = v.grid[i][j] + dt*((d2vdx2.grid[i][j] + d2vdy2.grid[i][j])/Re - duvdx.grid[i][j] - dv2dy.grid[i][j] + g_y);
        }
    }
}

void derivative_stencils(Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dx, float dy, float gamma){
    for(int i = 0; i < u.i_max + u.i_g; i++){ // is the range correct? --> no
        for(int j = 0; j < u.j_max + u.j_g; j++){ // is the range correct? --> no
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

//float gamma(Grid &u, Grid &v){
//    float m1 = grid_max()
//    float gamma = ;
//    return gamma;
//}
