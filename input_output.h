#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <string>
#include "Grid.h"
using namespace std;

int load_config(float &a, float &b, int &i_max, int &j_max, float &u_in, float &v_in, float &Re, float &tau, float &g_x, float &g_y, float &w, float &eps, int &norm, float &pre, float &t_final, float &chi, int &save_step, int &shape_in_box, int bc[4], bool &in_c, float &SOR_max_iter, int &output_num);
void grid2file(Grid &u, string filename);
void time2file(float t, string filename);
void file2grid(Grid &u, string filename);

#endif // INPUT_OUTPUT_H
