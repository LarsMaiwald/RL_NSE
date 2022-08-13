#include <iostream>
#include <cmath>
#include<bits/stdc++.h>
#include "Grid.h"
using namespace std;

// Compute the pressure derivatives
void pressure_deriv(Grid &p, Grid &dpdx, Grid &dpdy, float dx, float dy){
    for(int i = 1; i < dpdx.i_max; i++){
        for(int j = 1; j < dpdx.j_max + 1; j++){
            dpdx.grid[i][j] = (p.grid[i+1][j] - p.grid[i][j])/dx;
        }
    }
    for(int i = 1; i < dpdy.i_max + 1; i++){
        for(int j = 1; j < dpdy.j_max; j++){
            dpdy.grid[i][j] = (p.grid[i][j+1] - p.grid[i][j])/dy;
        }
    }
}

// Compute the RHS
void calc_RHS(Grid &RHS, Grid &F, Grid &G, float dx, float dy, float dt){
    for(int i = 1; i < RHS.i_max + 1; i++){
        for(int j = 1; j < RHS.j_max + 1; j++){
            RHS.grid[i][j] = ((F.grid[i][j] - F.grid[i-1][j])/dx + (G.grid[i][j] - G.grid[i][j-1])/dy)/dt;
        }
    }
}

// Iterate the pressure
void pressure(Grid &p, Grid &p_new, Grid &RHS, float dx, float dy, float w){
    for(int i = 1; i < p.i_max + 1; i++){
        for(int j = 1; j < p.j_max + 1; j++){
            p_new.grid[i][j] = (1 - w)*p.grid[i][j] + (w/(2*(1/(dx*dx) + 1/(dy*dy))))*((p.grid[i+1][j] + p_new.grid[i-1][j])/(dx*dx) + (p.grid[i][j+1] + p_new.grid[i][j-1])/(dy*dy) - RHS.grid[i][j]);
        }
    }
    for(int i = 0; i < p.i_max + p.i_g; i++){
        for(int j = 0; j < p.j_max + p.j_g; j++){
            p.grid[i][j] = p_new.grid[i][j];
        }
    }
}

// Compute the residual for the pressure Poisson equation
void residual(Grid &r, Grid &p, Grid &RHS, float dx, float dy){
    for(int i = 1; i < r.i_max + 1; i++){
        for(int j = 1; j < r.j_max + 1; j++){
            r.grid[i][j] = (p.grid[i+1][j] - 2*p.grid[i][j] + p.grid[i-1][j])/(dx*dx) + (p.grid[i][j+1] - 2*p.grid[i][j] + p.grid[i][j-1])/(dy*dy) - RHS.grid[i][j];
        }
    }
}


// Apply L2 norm to a grid
float L2_norm(Grid &r){
    float sum = 0;
    for(int i = 1; i < r.i_max + 1; i++){
        for(int j = 1; j < r.j_max + 1; j++){
            sum += r.grid[i][j]*r.grid[i][j];
        }
    }
    float L2_norm = sqrt(sum/(r.i_max*r.j_max));
    return L2_norm;
}

// Apply max norm to a grid
float max_norm(Grid &r){
    float max_norm = abs(r.grid[1][1]);
    for(int i = 1; i < r.i_max + 1; i++){
        for(int j = 1; j < r.j_max + 1; j++){
            max_norm = max(max_norm, abs(r.grid[i][j]));
        }
    }
    return max_norm;
}

// Check if SOR converged to given tolerance
bool tolerance_check(Grid &r, Grid &p_init, float eps, int norm, float chi){
    bool check = false;
    if(norm == 0){ // max_norm
        cout << "SOR: max_norm(r) = " << setprecision(6) << max_norm(r) << "\r";
        if(max_norm(p_init) == 0){
            check = (max_norm(r) < eps*max_norm(p_init) + chi);
        }
        else{
            check = (max_norm(r) < eps*max_norm(p_init));
        }
    }
    else if(norm == 1){ // L2_norm
        cout << "SOR: max_norm(r) = " << setprecision(6) << max_norm(r) << "\r";
        if(max_norm(p_init) == 0){
            check = (L2_norm(r) < eps*L2_norm(p_init) + chi);
        }
        else{
            check = (L2_norm(r) < eps*L2_norm(p_init));
        }
    }
    if(check){cout << "SOR: final max_norm(r) = " << setprecision(6) << max_norm(r) << "\n"; }
    return check;
}

// Apply pressure boundary condition
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
