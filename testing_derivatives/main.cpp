#include <iostream>
#include <string>
#include <stdlib.h>
#include "Grid.h"
#include "initialization.h"
#include "time_stepping.h"


using namespace std;

int main()
{
    // Initializatio

    // Creating all grid
    Grid x(i_max, j_max, 2, 2);
    Grid u(i_max, j_max, 2, 2);
    Grid d2udx2(i_max, j_max, 2, 2);
    Grid d2udy2(i_max, j_max, 2, 2);
    Grid du2dx(i_max, j_max, 1, 2);
    Grid duvdy(i_max, j_max, 1, 2);
    Grid v(i_max, j_max, 2, 1);
    Grid d2vdx2(i_max, j_max, 2, 1);
    Grid d2vdy2(i_max, j_max, 2, 1);
    Grid duvdx(i_max, j_max, 2, 1);
    Grid dv2dy(i_max, j_max, 2, 1);

    // Time evolution loop
    float t = 0;
    int counter = 0;
    int c = 0;
    float dx = a/i_max; // is this correct?
    float dy = b/j_max; // is this correct?

    float gamma = get_gamma(u, v, dx, dy, dt, pre);
//        cout << "Computing derivative stencils \n";
    derivative_stencils(u, v, d2udx2, d2udy2, du2dx, duvdy, d2vdx2, d2vdy2, duvdx, dv2dy, dx, dy, gamma);
    // Final output
//    cout << "Outputting grids \n";
    grid2file(u, "../testing_derivatives/outputs/u.csv");
    grid2file(d2udx2, "../testing_derivatives/outputs/d2udx2.csv");
    grid2file(d2udy2, "../testing_derivatives/outputs/d2udy2.csv");
    grid2file(du2dx, "../testing_derivatives/outputs/du2dx.csv");
    grid2file(duvdy, "../testing_derivatives/outputs/duvdy.csv");
    grid2file(d2vdx2, "../testing_derivatives/outputs/d2vdx2.csv");
    grid2file(d2vdy2, "../testing_derivatives/outputs/d2vdy2.csv");
    grid2file(duvdx, "../testing_derivatives/outputs/duvdx.csv");
    grid2file(dv2dy, "../testing_derivatives/outputs/dv2dy.csv");
    grid2file(v, "../testing_derivatives/outputs/v.csv");

}
