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
    Grid x(i_max, j_max, 1,);
    Grid u(i_max, j_max, 1, 2);
    Grid d2udx2(i_max, j_max, 1, 2);
    Grid d2udy2(i_max, j_max, 1, 2);
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
    grid2file(u, "../RL_NSE/outputs/u_final.csv");
    grid2file(d2udx2, "../RL_NSE/outputs/d2udx2_final.csv");
    grid2file(d2udy2, "../RL_NSE/outputs/d2udy2_final.csv");
    grid2file(du2dx, "../RL_NSE/outputs/du2dx_final.csv");
    grid2file(duvdy, "../RL_NSE/outputs/duvdy_final.csv");
    grid2file(d2vdx2, "../RL_NSE/outputs/d2vdx2_final.csv");
    grid2file(d2vdy2, "../RL_NSE/outputs/d2vdy2_final.csv");
    grid2file(duvdx, "../RL_NSE/outputs/duvdx_final.csv");
    grid2file(dv2dy, "../RL_NSE/outputs/dv2dy_final.csv");
    grid2file(v, "../RL_NSE/outputs/v_final.csv");

}
