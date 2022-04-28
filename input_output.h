#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

int load_config(int *a, int *b, int *i_max, int *j_max, int *boundary_condition, int *Re, float *tau);

void print_grid(float ** u);

#endif // INPUT_OUTPUT_H
