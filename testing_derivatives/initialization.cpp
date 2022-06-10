#include <iostream>
#include <cmath>
#include "Grid.h"
using namespace std;

// Initialization of grid (a x b) values with predefined example function
void grid_init(Grid &u, float x[], float y[])
{
    for (int i = 0; i < u.i_max + u.i_g; i++) {
        for (int j = 0; j < u.j_max + u.j_g; j++) {
            u.grid[i][j] = 2*cos(x[i])+ 3*sin(y[j]);
        }
    }
}

float xy_init(float x[], int i_max, int x_min, int x_max)
{
  cout << x_max;
  cout << x_min;
  int dx = abs(x_max-x_min)/i_max;
  cout << dx << endl;
  x[0] = x_min - dx;
  for  (int i = 1; i < i_max + 2; i++)
  {
    x[i] = x[i-1]+dx;
    //cout << x[i-1] << " - " << x[i] << endl;
  }
  return dx;
}
