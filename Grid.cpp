#include "Grid.h"
#include <iostream>
using namespace std;

Grid::Grid(int i, int j)
{
  i_max = i;
  j_max = j;

  float** u = new float*[i_max + 2];
  for (int i = 0; i < i_max + 2; i++) {
      u[i] = new float[j_max + 2];
  }
  for (int i = 0; i < i_max + 2; i++) {
      for (int j = 0; j < j_max + 2; j++) {
          u[i][j] = 0;
      }
  grid = u;
  }
}

Grid::~Grid()
{
  for(int i=0; i < i_max + 2; i++)
  {
      delete [] grid[i];
  }
  delete [] grid;
}

void Grid::print()
{
  for (int i = 0; i < i_max + 2; i++) {
      for (int j = 0; j < j_max + 2; j++) {
          cout << grid[i][j] << " ";
      }
      cout << "\n";
}
}
