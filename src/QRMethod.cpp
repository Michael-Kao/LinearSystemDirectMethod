#include "QRMethod.h"


void QRMethod::solver(std::vector< std::vector<double> > Mtx, std::vector<double> _b) {
    UpTriMtx = Mtx;
    b = _b;
    res = std::vector<double>(b.size(), 0);
    QR_reflection();
    {
        backSub t;
        t.back_substitution(UpTriMtx, res, b, UpTriMtx[0].size());
    }
}

void QRMethod::householder_vec(int i, int j, std::vector<double> &vec, int size) {
    double norm2 = 0.0;
    for(int k = i; k < size; ++k) {
        norm2 += UpTriMtx[k][i] * UpTriMtx[k][i];
    }
    norm2 = sqrt(norm2);

    /* https://ccjou.wordpress.com/2009/09/14/%E7%89%B9%E6%AE%8A%E7%9F%A9%E9%99%A3-%E5%9B%9B%EF%BC%9Ahouseholder-%E7%9F%A9%E9%99%A3/ */
    /*
        purpose: make calculation more stable
    */
    if(UpTriMtx[i][j] >= 0.0)  vec[i] = UpTriMtx[i][j] + norm2;
    else    vec[i] = UpTriMtx[i][j] - norm2;
    //v[i] = UpTriMtx[i][j] - norm2;

    for(int k = i + 1; k < size; ++k) {
        vec[k] = UpTriMtx[k][j];
    }
}

void QRMethod::QR_reflection() {
    int colSize = UpTriMtx[0].size();
    int rowSize = UpTriMtx.size();
    for(int i = 0; i < colSize - 1; ++i) {
        std::vector<double> vec(rowSize, 0);
        householder_vec(i, i, vec, rowSize);
        double vv = 0;
        //inner product
        for(int j = 0; j < vec.size(); ++j)
            vv += vec[j] * vec[j];
        
        for(int j = i; j < colSize; ++j) {
            double vx = 0.0;
            for(int k = i; k < rowSize; ++k) 
                vx += UpTriMtx[k][j] * vec[k];

            for(int k = i; k < rowSize; ++k) 
                UpTriMtx[k][j] -= 2 * (vx / vv) * vec[k];
        }

        double vx = 0.0;
        //inner product
        for(int j = 0; j < vec.size(); ++j) {
            vx += vec[j] * b[j];
        }
        for(int j = i; j < rowSize; ++j) {
            b[j] -= 2 * (vx / vv) * vec[j];
        }
    }
}