#ifndef GRID_H_INCLUDED
#define GRID_H_INCLUDED

class Grid
{
  public:
    int i_max;
    int j_max;
    float ** grid;
    Grid(int i, int j);
    ~Grid();
};

#endif // GRID_H
