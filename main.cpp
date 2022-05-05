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
    int i_max, j_max, boundary_condition;
    float a, b, Re, tau, g_x, g_y, u_in, v_in;

    cout << "Numerical Solution of the Navier-Stokes Equations (Research Lab, TPI Jena) by Lars Maiwald and Kevin Siebert" << "\n";

    // Loading input from parameter file "config.cgf"
    load_config(&a, &b, &i_max, &j_max, &boundary_condition, &u_in, &v_in, &Re, &tau, &g_x, &g_y);

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

    Grid u(i_max, j_max);
    u.print();
//    grid_init(u, a, b); // Crashes! There seems to be a problem with the destructor
//    u.print();
}
