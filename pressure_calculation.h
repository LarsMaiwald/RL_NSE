#ifndef PRESSURE_CALCULATION_H
#define PRESSURE_CALCULATION_H

#include "Grid.h"
void pressure_deriv(Grid &p, Grid &dpdx, Grid &dpdy, float dx, float dy);
void calc_RHS(Grid &RHS, Grid &F, Grid &G, float dx, float dy, float dt);
void pressure(Grid &p, Grid &p_new, Grid &RHS, float dx, float dy, float w);
void residual(Grid &r, Grid &p, Grid &RHS, float dx, float dy);
bool tolerance_check(Grid &p, Grid &p_init, float eps, int norm);
void set_pressure_boundaries(Grid &p, Grid &p_new);

#endif // PRESSURE_CALCULATION_H
