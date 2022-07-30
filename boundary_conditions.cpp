#include <iostream>
#include "Grid.h"
#include "input_output.h"
using namespace std;

//No-Slip condition applied to two Grid type objects
void bc_noslip(Grid &u, Grid &v)
{
    for (int j = 1; j < u.j_max + 1; j++)
    {
      u.grid[0][j] = 0;
      u.grid[u.i_max][j] = 0;
    }
    for (int i = 1; i < v.i_max + 1; i++)
    {
      v.grid[i][0] = 0;
      v.grid[i][v.j_max] = 0;
    }
    for (int j = 1; j < v.j_max + 1; j++)
    {
      v.grid[0][j] = -v.grid[1][j];
      v.grid[u.i_max+1][j] = -v.grid[u.i_max][j];
    }
    for (int i = 1; i < u.i_max + 1; i++)
    {
      u.grid[i][0] = -u.grid[i][1];
      u.grid[i][v.j_max+1] = -u.grid[i][v.j_max];
    }
}

// Outflow condition applied to two Grid type objects
void bc_outflow(Grid &u, Grid &v)
{
    for (int j = 1; j < u.j_max + 1; j++)
    {
        u.grid[0][j] = u.grid[1][j];
        v.grid[0][j] = v.grid[1][j];
        u.grid[u.i_max][j] = u.grid[u.i_max-1][j];
        v.grid[v.i_max+1][j] = v.grid[v.i_max][j];
    }
    for (int i = 1; i < u.i_max + 1; i++)
    {
        u.grid[i][0] = u.grid[i][1];
        v.grid[i][0] = v.grid[i][1];
        u.grid[i][u.j_max+1] = u.grid[i][u.j_max];
        v.grid[i][v.j_max] = v.grid[i][v.j_max-1];
    }
}

// Inflow condition applied to two Grid type objects given the inflow velocities
void bc_inflow(Grid &u, Grid &v, float u_in, float v_in)
{
    for (int j = 1; j < u.j_max + 1; j++)
    {
      u.grid[0][j] = u_in;
      u.grid[u.i_max][j] = u_in;
    }
    for (int i = 1; i < v.i_max + 1; i++)
    {
      v.grid[i][0] = v_in;
      v.grid[i][v.j_max] = v_in;
    }
    // Is this the correct averaging?
    for (int j = 1; j < v.j_max + 1; j++)
    {
      v.grid[0][j] = 2*v_in - v.grid[1][j];
      v.grid[u.i_max+1][j] = 2*v_in - v.grid[u.i_max][j];
    }
    for (int i = 1; i < u.i_max + 1; i++)
    {
      u.grid[i][0] = 2*u_in - u.grid[i][1];
      u.grid[i][v.j_max+1] = 2*u_in - u.grid[i][v.j_max];
    }
}

void bc_upper(Grid &u, float u_in)
{
    for (int i = 1; i < u.i_max + 1; i++)
    {
      u.grid[i][0] = 2*u_in - u.grid[i][1];
    }
}

void bc_shape_in_box(Grid &shape, Grid &u, Grid &v, int i_max, int j_max, string filename)
{
    file2grid(shape, "../RL_NSE/shapes/"+filename);
    for (int i = 0; i < i_max; i++)
    {
        for (int j = 0; j < j_max; j++)
        {
            if(shape.grid[i][j] != 0)
            {
                u.grid[i][j] = -u.grid[i+1][j];
                v.grid[i][j] = -v.grid[i][j+1];
            }
        }
    }
//    grid2file(shape, "../RL_NSE/shapes/returned_1.csv");
}
