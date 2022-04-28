#include <iostream>
using namespace std;

float ** grid(int i_max, int j_max)
{
  // Array initialization (shouldn't this be in "initialization.cpp"?)
  float** u = new float*[i_max];
  for (int i = 0; i < i_max; i++) {
      u[i] = new float[j_max];
  }
  for (int i = 0; i < i_max; i++) {
      for (int j = 0; j < j_max; j++) {
          u[i][j] = 0;
      }
  }
  // Initialization
  for (int i = 0; i < i_max; i++) {
      for (int j = 0; j < j_max; j++) {
          cout << u[i][j] << " ";
      }
      cout << "\n";
  }
  return u;
}

void delete_grid(float ** u, int i_max, int j_max)
{
  for(int i=0; i < i_max; i++)
  {
      delete [] u[i];
  }
  delete [] u;
}
