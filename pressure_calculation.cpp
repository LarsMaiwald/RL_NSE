#include <iostream>
#include <cmath>
#include<bits/stdc++.h>
#include "Grid.h"
using namespace std;

void pressure_deriv(Grid &p, Grid &dpdx, Grid &dpdy, float dx, float dy){
    for(int i = 1; i < dpdx.i_max; i++){ // is the range correct?
        for(int j = 1; j < dpdx.j_max + 1; j++){ // is the range correct?
            dpdx.grid[i][j] = (p.grid[i+1][j] - p.grid[i][j])/dx;
        }
    }
    for(int i = 1; i < dpdy.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < dpdy.j_max; j++){ // is the range correct?
            dpdy.grid[i][j] = (p.grid[i][j+1] - p.grid[i][j])/dy;
        }
    }
}

void calc_RHS(Grid &RHS, Grid &F, Grid &G, float dx, float dy, float dt){
    for(int i = 1; i < RHS.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < RHS.j_max + 1; j++){ // is the range correct?
            RHS.grid[i][j] = ((F.grid[i][j] - F.grid[i-1][j])/dx + (G.grid[i][j] - G.grid[i][j-1])/dy)/dt;
        }
    }
}

void pressure(Grid &p, Grid &p_new, Grid &RHS, float dx, float dy, float w){
    for(int i = 1; i < p.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < p.j_max + 1; j++){ // is the range correct?
            p_new.grid[i][j] = (1 - w)*p.grid[i][j] + (w/(2*(1/(dx*dx) + 1/(dy*dy))))*((p.grid[i+1][j] + p_new.grid[i-1][j])/(dx*dx) + (p.grid[i][j+1] + p_new.grid[i][j-1])/(dy*dy) - RHS.grid[i][j]);
        }
    }
    for(int i = 0; i < p.i_max + p.i_g; i++){ // is the range correct?
        for(int j = 0; j < p.j_max + p.j_g; j++){ // is the range correct?
            p.grid[i][j] = p_new.grid[i][j];
        }
    }
}

void residual(Grid &r, Grid &p, Grid &RHS, float dx, float dy){
    for(int i = 1; i < r.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < r.j_max + 1; j++){ // is the range correct?
            r.grid[i][j] = (p.grid[i+1][j] - 2*p.grid[i][j] + p.grid[i-1][j])/(dx*dx) + (p.grid[i][j+1] - 2*p.grid[i][j] + p.grid[i][j-1])/(dy*dy) - RHS.grid[i][j];
        }
    }
}

float L2_norm(Grid &r){
    // include boundary?
    float sum = 0;
    for(int i = 1; i < r.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < r.j_max + 1; j++){ // is the range correct?
            sum += r.grid[i][j]*r.grid[i][j];
        }
    }
    float L2_norm = sqrt(sum/(r.i_max*r.j_max));
    return L2_norm;
}

float max_norm(Grid &r){
    // include boundary?
    float max_norm = abs(r.grid[1][1]);
    for(int i = 1; i < r.i_max + 1; i++){ // is the range correct?
        for(int j = 1; j < r.j_max + 1; j++){ // is the range correct?
            max_norm = max(max_norm, abs(r.grid[i][j]));
        }
    }
    return max_norm;
}

bool tolerance_check(Grid &r, Grid &p_init, float eps, int norm, float chi){
    bool check = false;
    if(norm == 0){ // max_norm
//        cout << "max_norm(r) = " << max_norm(r) << "\n";
//        cout << "eps*max_norm(p_init) = " << eps*max_norm(p_init) << "\n";
        cout << "SOR: max_norm(r) = " << setprecision(6) << max_norm(r) << "\r";
        check = (max_norm(r) < eps*max_norm(p_init) + chi);
    }
    else if(norm == 1){ // L2_norm
//        cout << "L2_norm(r)= " << L2_norm(r) << "\n";
//        cout << "eps*L2_norm(p_init) = " << eps*L2_norm(p_init) << "\n";
        cout << "SOR: max_norm(r) = " << setprecision(6) << max_norm(r) << "\r";
        check = (L2_norm(r) < eps*L2_norm(p_init) + chi);
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
