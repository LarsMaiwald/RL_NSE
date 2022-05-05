#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

int load_config(float *a, float *b, int *i_max, int *j_max, int *boundary_condition, float *u_in, float *v_in, float *Re, float *tau, float *g_x, float *g_y);

void print_grid(float ** u);

#endif // INPUT_OUTPUT_H
