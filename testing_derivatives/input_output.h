#ifndef INPUT_OUTPUT_H
#define INPUT_OUTPUT_H

#include <string>
#include "Grid.h"
using namespace std;

int load_config(int i_max, int j_max, float x_min, float x_max, float y_min, float y_max);
void grid2file(Grid &u, string filename);
void array2file(float u[], int i_max, string filename);

#endif // INPUT_OUTPUT_H
