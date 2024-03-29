#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include <string>
#include "Grid.h"
using namespace std;
void bc_noslip(Grid &u, Grid &v, int bc[4]);
void bc_outflow(Grid &u, Grid &v, int bc[4]);
void bc_inflow(Grid &u, Grid &v, float u_in, float v_in, int bc[4]);
void set_boundaries(Grid &u, Grid &v, float u_in, float v_in, int bc[4]);
void bc_shape_in_box(Grid &shape, Grid &u, Grid &v, int i_max, int j_max, string filename);
void inflow_change(float &u_in_c, float &v_in_c, float u_in, float v_in, float t);

#endif // BOUNDARY_CONDITIONS_H
