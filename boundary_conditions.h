#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include <string>
#include "Grid.h"
void bc_noslip(Grid &u, Grid &v);
void bc_outflow(Grid &u, Grid &v);
void bc_inflow(Grid &u, Grid &v, float u_in, float v_in);
void bc_upper(Grid &u, float u_in);
void bc_shape_in_box(Grid &shape, Grid &u, Grid &v, int i_max, int j_max, string filename);

#endif // BOUNDARY_CONDITIONS_H
