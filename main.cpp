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

    // Array initialization (shouldn't this be in "initialization.cpp"?)
    float** u = new float*[i_max];
    for (int i = 0; i < i_max; i++) {
        u[i] = new float[j_max];
    }
    for (int i = 0; i < i_max; i++) {
        for (int j = 0; j < j_max; j++) {
            u[i][j] = 0;
        }
    }

    for (int i = 0; i < i_max; i++) {
        for (int j = 0; j < j_max; j++) {
            cout << u[i][j] << " ";
        }
        cout << "\n";
    }

    for(int i=0; i < i_max; i++)
    {
        delete [] u[i];
    }
    delete [] u;

    return 0;
}
