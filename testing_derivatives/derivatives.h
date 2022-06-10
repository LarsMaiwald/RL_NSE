#ifndef TIME_STEPPING_H
#define TIME_STEPPING_H

#include "Grid.h"
void derivative_stencils(Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dx, float dy, float gamma);
float get_gamma(Grid &u, Grid &v, float dx, float dy, float dt, float pre);
#endif // TIME_STEPPING_H
