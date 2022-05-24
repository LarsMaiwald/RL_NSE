#ifndef TIME_STEPPING_H
#define TIME_STEPPING_H

#include "Grid.h"
float time_step(Grid &u, Grid &v, float tau, float Re, float dx, float dy);
void iterate(Grid &u, Grid &v, Grid &F, Grid &G, Grid &dpdx, Grid &dpdy, float tau, int Re, float dx, float dy, float dt);
void F_and_G(Grid &F, Grid &G, Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dt, float Re, float g_x, float g_y);
void derivative_stencils(Grid &u, Grid &v, Grid &d2udx2, Grid &d2udy2, Grid &du2dx, Grid &duvdy, Grid &d2vdx2, Grid &d2vdy2, Grid &duvdx, Grid &dv2dy, float dx, float dy, float gamma);
float get_gamma(Grid &u, Grid &v, float dx, float dy, float dt, float pre);

#endif // TIME_STEPPING_H
