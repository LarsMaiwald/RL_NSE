#ifndef BOUNDARY_CONDITIONS_H
#define BOUNDARY_CONDITIONS_H

#include "Grid.h"
void bc_noslip(Grid &u, Grid &v);
void bc_outflow(Grid &u, Grid &v);
void bc_inflow(Grid &u, Grid &v, float u_in, float v_in);
void bc_upper(Grid &u, float u_in);

#endif // BOUNDARY_CONDITIONS_H
