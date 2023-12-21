#include "Gaussian.h"

void Gaussian::gaussian_elimination() {
    int n = UpTriMtx.size();
    for(int i = 0; i < n; ++i) {
        double maxRowVal = fabs(UpTriMtx[i][i]);
        int idx = i;
        for(int k = i; k < n; ++k) {
            if(fabs(UpTriMtx[k][i]) > maxRowVal) {
                idx = k;
                maxRowVal = fabs(UpTriMtx[k][i]);
            }
        }

        //partial pivoting
        if(idx != i) {
            for(int j = i; j < n; ++j) {
                double temp = UpTriMtx[i][j];
                UpTriMtx[i][j] = UpTriMtx[idx][j];
                UpTriMtx[idx][j] = temp;
            }
            double temp = b[i];
            b[i] = b[idx];
            b[idx] = temp;
        }

        //elimination
        for(int j = i + 1; j < n; ++j) {
            if(UpTriMtx[j][i] == 0.0)
                continue;
            double r = UpTriMtx[j][i] / UpTriMtx[i][i];
            for(int k = i; k < n; ++k) {
                UpTriMtx[j][k] -= r * UpTriMtx[i][k];
            }

            b[j] -= r * b[i];
        }
    }
}