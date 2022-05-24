#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <string>
#include "Grid.h"
using namespace std;

int load_config(float &a, float &b, int &i_max, int &j_max, int &boundary_condition, float &u_in, float &v_in, float &Re, float &tau, float &g_x, float &g_y, float &w, float &eps, int &norm, float &pre);
void grid2file(Grid &u, string filename);

#endif // INPUT_OUTPUT_H
