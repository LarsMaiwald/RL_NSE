#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

class Grid
{
  public:
    int i_max;
    int j_max;
    int i_g;
    int j_g;
    float ** grid;
    Grid(int i, int j, int i_ghost, int j_ghost);
    ~Grid();
    void print();
};

#endif // GRID_H
