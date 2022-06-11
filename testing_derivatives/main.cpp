#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <libconfig.h++>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "Grid.h"
#include "initialization.h"
#include "derivatives.h"
#include "input_output.h"


using namespace std;

int main()
{

    // Initializatio
    int i_max;
    int j_max;
    float x_max;
    float x_min;
    float y_max;
    float y_min;

    // Loading parameter file
    load_config(i_max, j_max, x_min, x_max, y_min, y_max);

    // Creating all grid
    float dx;
    float dy;
    float gamma;
    float x[i_max+2];
    float y[j_max+2];
    Grid u(i_max, j_max, 2, 2);
    Grid v(i_max, j_max, 2, 2);
    Grid d2udx2(i_max, j_max, 2, 2);
    Grid d2udy2(i_max, j_max, 2, 2);
    Grid du2dx(i_max, j_max, 2, 2);
    Grid duvdy(i_max, j_max, 2, 2);
    Grid d2vdx2(i_max, j_max, 2, 2);
    Grid d2vdy2(i_max, j_max, 2, 2);
    Grid duvdx(i_max, j_max, 2, 2);
    Grid dv2dy(i_max, j_max, 2, 2);

    load_config(i_max, j_max, x_min, x_max, y_min, y_max);


    dx = xy_init(x, i_max, x_min, x_max);
    dy = xy_init(y, j_max, y_min, y_max);


    grid_init(u, x, y);
    grid_init(v, x, y);
    gamma = get_gamma(u, v, dx, dy, 0.001, 0.1);

    derivative_stencils(u, v, d2udx2, d2udy2, du2dx, duvdy, d2vdx2, d2vdy2, duvdx, dv2dy, dx, dy, gamma);
    // Final output
//    cout << "Outputting grids \n";
    array2file(x, i_max, "../testing_derivatives/outputs/x.csv");
    array2file(y, j_max, "../testing_derivatives/outputs/y.csv");
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
