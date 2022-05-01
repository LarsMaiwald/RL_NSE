#include <iostream>
using namespace std;

//No-Slip condition applied to two Grid type objects
void bc_noslip(Grid u, Grid v)
{
    for (int j = 1, j < u.j_max + 1, j++)
    {
      u.grid[0][j] = 0;
      u.grid[u.i_max][j] = 0;
    }
    for (int i = 1, i < v.i_max + 1, i++)
    {
      v.grid[i][0] = 0;
      v.grid[i][v.j_max] = 0;
    }

    for (int j = 1, j < v.j_max + 1, j++)
    {
      v.grid[0][j] = -v.grid[1][j];
      v.grid[u.i_max+1][j] = -v.grid[u.i_max][j];
    }
    for (int i = 1, i < u.i_max + 1, i++)
    {
      u.grid[i][0] = -u.grid[i][1];
      u.grid[i][v.j_max+1] = -u.grid[i][v.j_max];
    }
}
