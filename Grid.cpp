#include "Grid.h"
#include <iostream>
using namespace std;

Grid::Grid(int i, int j)
{
  i_max = i;
  j_max = j;

  float** u = new float*[i_max];
  for (int i = 0; i < i_max; i++) {
      u[i] = new float[j_max];
  }
  for (int i = 0; i < i_max; i++) {
      for (int j = 0; j < j_max; j++) {
          u[i][j] = 0;
      }
  grid = u;
  }
}

Grid::~Grid()
{
  for(int i=0; i < i_max; i++)
  {
      delete [] grid[i];
  }
  delete [] grid;
}

void Grid::print()
{
  for (int i = 0; i < i_max; i++) {
      for (int j = 0; j < j_max; j++) {
          cout << grid[i][j] << " ";
      }
      cout << "\n";
}
}
