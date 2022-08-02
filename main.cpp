#include <iostream>
#include <string>
#include <stdlib.h>
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
    // Initialization
    int i_max, j_max, boundary_condition, norm, save_step, shape_in_box, bc[4];
    float a, b, Re, tau, g_x, g_y, u_in, v_in, w, eps, pre, t_final, chi, u_in_c, v_in_c;
    bool in_c;

    cout << "Numerical Solution of the Navier-Stokes Equations (Research Lab, TPI Jena) by Lars Maiwald and Kevin Siebert" << "\n";

    // Loading input from parameter file "config.cgf"
    load_config(a, b, i_max, j_max, u_in, v_in, Re, tau, g_x, g_y, w, eps, norm, pre, t_final, chi, save_step, shape_in_box, bc, in_c);

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
//    cout << "chi = " << chi << "\n";
//    cout << "save_step = " << save_step << "\n";
//    cout << "shape_in_box = " << shape_in_box << "\n";
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

    // Cleaning output directory
    system("rm ../RL_NSE/outputs/* || echo Output directory already empty.");

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
    Grid shape(i_max, j_max, 0, 0);

    // Time evolution loop
    float t = 0;
    int counter = 0;
    int c = 0;
    float dx = a/i_max;
    float dy = b/j_max;
    while(t < t_final){
        counter += 1;
        cout << "Starting time step " << counter << " at time " << t << " of " << t_final << "\n";

        // Adjusting inflow velocities periodically
        if(in_c)
        {
            inflow_change(u_in_c, v_in_c, u_in, v_in, t);
        }
        else
        {
            u_in_c = u_in;
            v_in_c = v_in;
        }

        // Choosing time step
        float dt = time_step(u, v, tau, Re, dx, dy); // Should this be after the boundary conditions?
        t += dt;

        // Filling ghost cells according to boundary condition
        set_boundaries(u, v, u_in, v_in, bc);

        // Additional boundary condition
        if(shape_in_box != 0)
        {
            bc_shape_in_box(shape, u, v, i_max, j_max, to_string(shape_in_box)+".csv");
        }

        // Computing F and G
        float gamma = get_gamma(u, v, dx, dy, dt, pre);
        derivative_stencils(u, v, d2udx2, d2udy2, du2dx, duvdy, d2vdx2, d2vdy2, duvdx, dv2dy, dx, dy, gamma);
        F_and_G(F, G, u, v, d2udx2, d2udy2, du2dx, duvdy, d2vdx2, d2vdy2, duvdx, dv2dy, dt, Re, g_x, g_y);

        // Calculate RHS of pressure eq.
        calc_RHS(RHS, F, G, dx, dy, dt);

        // SOR iteration loop
        bool check = false;
        for(int i = 0; i < p.i_max + p.i_g; i++){
            for(int j = 0; j < p.j_max + p.j_g; j++){
                p_init.grid[i][j] = p.grid[i][j];
            }
        }
        int k = 0;
        while(!check){
            k += 1;
            if(k == 10000000000/(i_max*j_max)){
                cout << "SOR did not converge in given number of steps. \n";
                break;
            }
            set_pressure_boundaries(p, p_new);
            pressure(p, p_new, RHS, dx, dy, w);
            residual(r, p, RHS, dx, dy);
            check = tolerance_check(r, p_init, eps, norm, chi);
        }
        if(k == 10000000000/(i_max*j_max)){
            cout << "Stopping simulation. \n";
            break;
        }

        // Calculate the pressure derivatives
        pressure_deriv(p, dpdx, dpdy, dx, dy);

        // Compute the new velocity components u and v
        iterate(u, v, F, G, dpdx, dpdy, tau, Re, dx, dy, dt);

        // Output
        if(counter % save_step == 0){
            c += 1;
            time2file(t, "../RL_NSE/outputs/t_final.csv");
            grid2file(u, "../RL_NSE/outputs/u" + to_string(c) + ".csv");
            grid2file(v, "../RL_NSE/outputs/v" + to_string(c) + ".csv");
            grid2file(p, "../RL_NSE/outputs/p" + to_string(c) + ".csv");
        }
    }

    // Final output
    grid2file(u, "../RL_NSE/outputs/u_final.csv");
    grid2file(v, "../RL_NSE/outputs/v_final.csv");
    grid2file(p, "../RL_NSE/outputs/p_final.csv");
    cout << "Every " << save_step << "th time step was saved, which results in a total of " << c + 1 << " saved time steps. \n";

    grid2file(F, "../RL_NSE/outputs/F_final.csv");
    grid2file(G, "../RL_NSE/outputs/G_final.csv");
    grid2file(d2udx2, "../RL_NSE/outputs/d2udx2_final.csv");
    grid2file(d2udy2, "../RL_NSE/outputs/d2udy2_final.csv");
    grid2file(du2dx, "../RL_NSE/outputs/du2dx_final.csv");
    grid2file(duvdy, "../RL_NSE/outputs/duvdy_final.csv");
    grid2file(d2vdx2, "../RL_NSE/outputs/d2vdx2_final.csv");
    grid2file(d2vdy2, "../RL_NSE/outputs/d2vdy2_final.csv");
    grid2file(duvdx, "../RL_NSE/outputs/duvdx_final.csv");
    grid2file(dv2dy, "../RL_NSE/outputs/dv2dy_final.csv");
    grid2file(dpdx, "../RL_NSE/outputs/dpdx_final.csv");
    grid2file(dpdy, "../RL_NSE/outputs/dpdy_final.csv");
    grid2file(RHS, "../RL_NSE/outputs/RHS_final.csv");
}
