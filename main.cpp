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
    float a, b, Re, tau, g_x, g_y, u_in, v_in, w, eps, pre;

    cout << "Numerical Solution of the Navier-Stokes Equations (Research Lab, TPI Jena) by Lars Maiwald and Kevin Siebert" << "\n";

    // Loading input from parameter file "config.cgf"
    load_config(a, b, i_max, j_max, boundary_condition, u_in, v_in, Re, tau, g_x, g_y, w, eps, norm, pre);

    // Testing input parameters
    cout << "a = " << a << "\n";
    cout << "b = " << a << "\n";
    cout << "i_max = " << i_max << "\n";
    cout << "j_max = " << j_max << "\n";
    cout << "boundary_condition = " << boundary_condition << "\n";
    cout << "u_in = " << u_in << "\n";
    cout << "v_in = " << v_in << "\n";
    cout << "Re = " << Re << "\n";
    cout << "tau = " << tau << "\n";
    cout << "g_x = " << g_x << "\n";
    cout << "g_y = " << g_y << "\n";
    cout << "w = " << w << "\n";
    cout << "eps = " << eps << "\n";
    cout << "norm = " << norm << "\n";
    cout << "pre = " << pre << "\n";
    cout << "\n";
    Grid u(i_max, j_max, 1, 2);
    Grid v(i_max, j_max, 2, 1);
    Grid p(i_max, j_max, 2, 2);
    u.print();
    cout << "\n";
    grid_init(u, a, b);
    grid_init(v, a, b);
    grid_init(p, a, b);
    u.print();
    grid2file(u, "../RL_NSE/u.csv");
    grid2file(v, "../RL_NSE/v.csv");
    grid2file(p, "../RL_NSE/p.csv");
}
