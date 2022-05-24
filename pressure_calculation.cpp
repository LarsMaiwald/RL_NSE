#include <iostream>
#include <cmath>
#include "Grid.h"
using namespace std;

void pressure_deriv(Grid &p, Grid &dpdx, Grid &dpdy, float dx, float dy){
    for(int i = int(p.i_g/2); i < p.i_max + 1; i++){ // is the range correct?
        for(int j = int(p.j_g/2); j < p.j_max + 1; j++){ // is the range correct?
            dpdx.grid[i][j] = (p.grid[i+1][j] - p.grid[i][j])/dx;
            dpdy.grid[i][j] = (p.grid[i][j+1] - p.grid[i][j])/dy;
        }
    }
}

void calc_RHS(Grid &RHS, Grid &F, Grid &G, float dx, float dy, float dt){
    for(int i = int(RHS.i_g/2); i < RHS.i_max + 1; i++){ // is the range correct?
        for(int j = int(RHS.j_g/2); j < RHS.j_max + 1; j++){ // is the range correct?
            RHS.grid[i][j] = ((F.grid[i][j] - F.grid[i-1][j])/dx + (G.grid[i][j] - G.grid[i][j-1])/dy)/dt;
        }
    }
}

void pressure(Grid &p, Grid &p_new, Grid &RHS, float dx, float dy, float w){
    for(int i = int(p.i_g/2); i < p.i_max + 1; i++){ // is the range correct?
        for(int j = int(p.j_g/2); j < p.j_max + 1; j++){ // is the range correct?
            p_new.grid[i][j] = (1 - w)*p.grid[i][j] + (w/(2*(1/(dx*dx) + 1/(dy*dy))))*((p.grid[i+1][j] + p_new.grid[i-1][j])/(dx*dx) + (p.grid[i][j+1] + p_new.grid[i][j-1])/(dy*dy) - RHS.grid[i][j]);
            p.grid[i][j] = p_new.grid[i][j]; // should we do an extra loop for this?
        }
    }
}

void residual(Grid &r, Grid &p, Grid &RHS, float dx, float dy){
    // Attention: RHS should here be one iteration older than p!
    for(int i = int(r.i_g/2); i < r.i_max + 1; i++){ // is the range correct?
        for(int j = int(r.j_g/2); j < r.j_max + 1; j++){ // is the range correct?
            r.grid[i][j] = (p.grid[i+1][j] - 2*p.grid[i][j] + p.grid[i-1][j])/(dx*dx) + (p.grid[i][j+1] - 2*p.grid[i][j] + p.grid[i][j-1])/(dy*dy) - RHS.grid[i][j];
        }
    }
}

float L2_norm(Grid &r){
    float sum = 0;
    for(int i = int(r.i_g/2); i < r.i_max + 1; i++){ // is the range correct?
        for(int j = int(r.j_g/2); j < r.j_max + 1; j++){ // is the range correct?
            sum += r.grid[i][j]*r.grid[i][j];
        }
    }
    float L2_norm = sqrt(sum/(r.i_max*r.j_max));
    return L2_norm;
}

float max_norm(Grid &r){
    float max_norm = abs(r.grid[1][1]);
    for(int i = int(r.i_g/2); i < r.i_max + 1; i++){ // is the range correct?
        for(int j = int(r.j_g/2); j < r.j_max + 1; j++){ // is the range correct?
            max_norm = max(max_norm, abs(r.grid[i][j]));
        }
    }
    return max_norm;
}

bool tolerance_check(Grid &p, Grid &p_init, float eps, int norm){
    bool check = false;
    if(norm == 0){ // max_norm
        check = (max_norm(p) < eps*max_norm(p_init));
    }
    else if(norm == 1){ // L2_norm
        check = (L2_norm(p) < eps*L2_norm(p_init));
    }
    return check;
}

void set_pressure_boundaries(Grid &p, Grid &p_new){
    for(int i = 0; i < p_new.i_max + p_new.i_g; i++){
        p_new.grid[i][0] = p.grid[i][1];
        p_new.grid[i][p_new.j_max+1] = p.grid[i][p.j_max];
    }
    for(int j = 0; j < p_new.j_max + p_new.j_g; j++){
        p_new.grid[0][j] = p.grid[1][j];
        p_new.grid[p_new.i_max+1][j] = p.grid[p.i_max][j];
    }
}
