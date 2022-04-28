#include <iostream>
#include <algorithm>
#include <math.h>

using namespace std;

float array_max(float **a, int i_max, int j_max){
    float array_max = a[0][0];
    for(int i = 0; i < i_max; i++){
        for(int j = 0; j < j_max; j++){
            array_max = max(array_max, a[i][j]);
        }
    }
    return array_max;
}

float time_step(float **u, float **v, float tau, int Re, float dx, float dy, int i_max, int j_max){
    float v1 = Re/(2*(1/(dx*dx) + 1/(dy*dy)));
    float v2 = dx/abs(array_max(u, i_max, j_max));
    float v3 = dy/abs(array_max(v, i_max, j_max));
    float dt = tau*min({v1, v2, v3});
    return dt;
}

//void iterate(float **u, float **v, float tau, int Re, float dx, float dy, int i_max, int j_max, int num_iter){
//    for(int k = 0; k < num_iter; k++){
//        float dt = time_step(u, v, tau, Re, dx, dy, i_max, j_max);
//        for(int i = 0; i < i_max; i++){
//            for(int j = 0; j < j_max; j++){
//                u[i][j] = F[i][j] - dt*dpdx[i][j];
//                v[i][j] = G[i][j] - dt*dpdy[i][j];
//            }
//        }
//    }
//}
