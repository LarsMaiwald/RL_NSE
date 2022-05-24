#include <iostream>
#include <string>
#include "Grid.h"
#include "input_output.h"
#include "initialization.h"
#include "memory_management.h"
#include "time_stepping.h"
#include "pressure_calculation.h"
#include "boundary_conditions.h"

using namespace std;

int main()
{
    // Initialization (shouldn't this be in "initialization.cpp"?)
    int i_max, j_max, boundary_condition, norm;
    float a, b, Re, tau, g_x, g_y, u_in, v_in, w, eps, pre, t_final;

    cout << "Numerical Solution of the Navier-Stokes Equations (Research Lab, TPI Jena) by Lars Maiwald and Kevin Siebert" << "\n";

    // Loading input from parameter file "config.cgf"
    load_config(a, b, i_max, j_max, boundary_condition, u_in, v_in, Re, tau, g_x, g_y, w, eps, norm, pre, t_final);

    // Testing input parameters, grid creation and printing
//    cout << "a = " << a << "\n";
//    cout << "b = " << a << "\n";
//    cout << "i_max = " << i_max << "\n";
//    cout << "j_max = " << j_max << "\n";
//    cout << "boundary_condition = " << boundary_condition << "\n";
//    cout << "u_in = " << u_in << "\n";
//    cout << "v_in = " << v_in << "\n";
//    cout << "Re = " << Re << "\n";
//    cout << "tau = " << tau << "\n";
//    cout << "g_x = " << g_x << "\n";
//    cout << "g_y = " << g_y << "\n";
//    cout << "w = " << w << "\n";
//    cout << "eps = " << eps << "\n";
//    cout << "norm = " << norm << "\n";
//    cout << "pre = " << pre << "\n";
//    cout << "t_final = " << t_final << "\n";
//    cout << "\n";
//    Grid u(i_max, j_max, 1, 2);
//    Grid v(i_max, j_max, 2, 1);
//    Grid p(i_max, j_max, 2, 2);
//    u.print();
//    cout << "\n";
//    grid_init(u, a, b);
//    grid_init(v, a, b);
//    grid_init(p, a, b);
//    u.print();
//    grid2file(u, "../RL_NSE/u.csv");
//    grid2file(v, "../RL_NSE/v.csv");
//    grid2file(p, "../RL_NSE/p.csv");

    // Creating all grids
    Grid p(i_max, j_max, 2, 2);
    Grid p_new(i_max, j_max, 2, 2);
    Grid p_init(i_max, j_max, 2, 2);
    Grid r(i_max, j_max, 2, 2);
    Grid RHS(i_max, j_max, 2, 2);
    Grid dpdx(i_max, j_max, 1, 2);
    Grid u(i_max, j_max, 1, 2);
    Grid F(i_max, j_max, 1, 2);
    Grid d2udx2(i_max, j_max, 1, 2);
    Grid d2udy2(i_max, j_max, 1, 2);
    Grid du2dx(i_max, j_max, 1, 2);
    Grid duvdy(i_max, j_max, 1, 2);
    Grid dpdy(i_max, j_max, 2, 1);
    Grid v(i_max, j_max, 2, 1);
    Grid G(i_max, j_max, 2, 1);
    Grid d2vdx2(i_max, j_max, 2, 1);
    Grid d2vdy2(i_max, j_max, 2, 1);
    Grid duvdx(i_max, j_max, 2, 1);
    Grid dv2dy(i_max, j_max, 2, 1);

    // Time evolution loop
    float t = 0;
    int counter = 0;
    float dx = a/i_max; // is this correct?
    float dy = b/j_max; // is this correct?
    while(t < t_final){
        counter += 1;
        cout << "Starting time step" << counter << "\n";
        // Choosing time step
        float dt = time_step(u, v, tau, Re, dx, dy);
        t += dt;

        // Filling ghost cells according to boundary condition
        if(boundary_condition == 0){
            bc_noslip(u, v);
        }
        else if(boundary_condition == 1){
            bc_outflow(u, v);
        }
        else if(boundary_condition == 2){
            bc_inflow(u, v, u_in, v_in);
        }

        // Computing F and G
        float gamma = get_gamma(u, v, dx, dy, dt, pre);
        derivative_stencils(u, v, d2udx2, d2udy2, du2dx, duvdy, d2vdx2, d2vdy2, duvdx, dv2dy, dx, dy, gamma);
        F_and_G(F, G, u, v, d2udx2, d2udy2, du2dx, duvdy, d2vdx2, d2vdy2, duvdx, dv2dy, dt, Re, g_x, g_y);

        // Calculate RHS of pressure eq.
        calc_RHS(RHS, F, G, dx, dy, dt);

        // SOR iteration loop
        bool check = false;
        while(!check){
            set_pressure_boundaries(p, p_new);
            for(int i = 0; i < p.i_max + p.i_g; i++){
                for(int j = 0; j < p.j_max + p.j_g; j++){
                    p_init.grid[i][j] = p.grid[i][j];
                }
            }
            pressure(p, p_new, RHS, dx, dy, w);
            residual(r, p, RHS, dx, dy);
            check = tolerance_check(p, p_init, eps, norm);
        }

        // Compute the new velocity components u and v
        iterate(u, v, F, G, dpdx, dpdy, tau, Re, dx, dy, dt);
    }

    // Output
    grid2file(u, "../RL_NSE/u.csv");
    grid2file(v, "../RL_NSE/v.csv");
    grid2file(p, "../RL_NSE/p.csv");
}
