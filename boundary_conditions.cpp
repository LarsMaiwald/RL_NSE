#include <iostream>
#include <cmath>
#include "Grid.h"
#include "input_output.h"
using namespace std;

//No-Slip condition applied to two Grid type objects
void bc_noslip(Grid &u, Grid &v, int bc[4])
{
    if(bc[0] == 0) // bc[0] = upper boundary
    {
        for (int i = 1; i < u.i_max + 1; i++)
        {
          u.grid[i][0] = -u.grid[i][1];
        }
        for (int i = 1; i < v.i_max + 1; i++)
        {
          v.grid[i][0] = 0;
        }
    }
    if(bc[1] == 0) // bc[1] = left boundary
    {
        for (int j = 1; j < u.j_max + 1; j++)
        {
          u.grid[0][j] = 0;
        }
        for (int j = 1; j < v.j_max + 1; j++)
        {
          v.grid[0][j] = -v.grid[1][j];
        }
    }
    if(bc[2] == 0) // bc[2] = lower boundary
    {
        for (int i = 1; i < u.i_max + 1; i++)
        {
          u.grid[i][v.j_max+1] = -u.grid[i][v.j_max];
        }
        for (int i = 1; i < v.i_max + 1; i++)
        {
          v.grid[i][v.j_max] = 0;
        }
    }
    if(bc[3] == 0) // bc[3] = right boundary
    {
        for (int j = 1; j < u.j_max + 1; j++)
        {
          u.grid[u.i_max][j] = 0;
        }
        for (int j = 1; j < v.j_max + 1; j++)
        {
          v.grid[u.i_max+1][j] = -v.grid[u.i_max][j];
        }
    }
}

// Outflow condition applied to two Grid type objects
void bc_outflow(Grid &u, Grid &v, int bc[4])
{
    if(bc[0] == 1) // bc[0] = upper boundary
    {
        for (int i = 1; i < u.i_max + 1; i++)
        {
            u.grid[i][0] = u.grid[i][1];
        }
        for (int i = 1; i < v.i_max + 1; i++)
        {
            v.grid[i][0] = v.grid[i][1];
        }
    }
    if(bc[1] == 1) // bc[1] = left boundary
    {
        for (int j = 1; j < u.j_max + 1; j++)
        {
            u.grid[0][j] = u.grid[1][j];
        }
        for (int j = 1; j < v.j_max + 1; j++)
        {
            v.grid[0][j] = v.grid[1][j];
        }
    }
    if(bc[2] == 1) // bc[2] = lower boundary
    {
        for (int i = 1; i < u.i_max + 1; i++)
        {
            u.grid[i][u.j_max+1] = u.grid[i][u.j_max];
        }
        for (int i = 1; i < v.i_max + 1; i++)
        {
            v.grid[i][v.j_max] = v.grid[i][v.j_max-1];
        }
    }
    if(bc[3] == 1) // bc[3] = right boundary
    {
        for (int j = 1; j < u.j_max + 1; j++)
        {
            u.grid[u.i_max][j] = u.grid[u.i_max-1][j];
        }
        for (int j = 1; j < v.j_max + 1; j++)
        {
            v.grid[v.i_max+1][j] = v.grid[v.i_max][j];
        }
    }
}

// Inflow condition applied to two Grid type objects given the inflow velocities
void bc_inflow(Grid &u, Grid &v, float u_in, float v_in, int bc[4])
{
    if(bc[0] == 2) // bc[0] = upper boundary
    {
        for (int i = 1; i < u.i_max + 1; i++)
        {
          u.grid[i][0] = 2*u_in - u.grid[i][1];
        }
        for (int i = 1; i < v.i_max + 1; i++)
        {
          v.grid[i][0] = v_in;
        }
    }
    if(bc[1] == 2) // bc[1] = left boundary
    {
        for (int j = 1; j < u.j_max + 1; j++)
        {
          u.grid[0][j] = u_in;
        }
        for (int j = 1; j < v.j_max + 1; j++)
        {
          v.grid[0][j] = 2*v_in - v.grid[1][j];
        }
    }
    if(bc[2] == 2) // bc[2] = lower boundary
    {
        for (int i = 1; i < u.i_max + 1; i++)
        {
          u.grid[i][v.j_max+1] = 2*u_in - u.grid[i][v.j_max];
        }
        for (int i = 1; i < v.i_max + 1; i++)
        {
          v.grid[i][v.j_max] = v_in;
        }
    }
    if(bc[3] == 2) // bc[3] = right boundary
    {
        for (int j = 1; j < u.j_max + 1; j++)
        {
          u.grid[u.i_max][j] = u_in;
        }
        for (int j = 1; j < v.j_max + 1; j++)
        {
          v.grid[u.i_max+1][j] = 2*v_in - v.grid[u.i_max][j];
        }
    }
}

void set_boundaries(Grid &u, Grid &v, float u_in, float v_in, int bc[4])
{
    bc_noslip(u, v, bc);
    bc_inflow(u, v, u_in, v_in, bc);
    bc_outflow(u, v, bc);
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
}

void inflow_change(float &u_in_c, float &v_in_c, float u_in, float v_in, float t)
{
    u_in_c = u_in*cos(t);
    v_in_c = v_in*cos(t);
}
