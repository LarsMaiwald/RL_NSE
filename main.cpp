#include <iostream>
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
    int a, b, i_max, j_max, boundary_condition;

    cout << "Numerical Solution of the Navier-Stokes Equations (Research Lab, TPI Jena) by Lars Maiwald and Kevin Siebert" << endl;

    // Loading input from parameter file "config.cgf"
    load_config(&a, &b, &i_max, &j_max, &boundary_condition);

    // Testing input parameters
    cout << "a = " << a << endl;
    cout << "b = " << a << endl;
    cout << "i_max = " << i_max << endl;
    cout << "j_max = " << j_max << endl;
    cout << "boundary_condition = " << boundary_condition << endl;


    return 0;
}
