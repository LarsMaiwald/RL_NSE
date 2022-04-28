#include <iostream>
#include <string>
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
    int a, b, i_max, j_max, boundary_condition, Re;
    float tau;

    cout << "Numerical Solution of the Navier-Stokes Equations (Research Lab, TPI Jena) by Lars Maiwald and Kevin Siebert" << "\n";

    // Loading input from parameter file "config.cgf"
    load_config(&a, &b, &i_max, &j_max, &boundary_condition, &Re, &tau);

    // Testing input parameters
    cout << "a = " << a << "\n";
    cout << "b = " << a << "\n";
    cout << "i_max = " << i_max << "\n";
    cout << "j_max = " << j_max << "\n";
    cout << "boundary_condition = " << boundary_condition << "\n";
    cout << "Re = " << Re << "\n";
    cout << "tau = " << tau << "\n";

    float ** u;

    u = grid(5, 5);
    delete_grid(u, 5, 5);
    return 0;
}
