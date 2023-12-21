#include "Generator.h"

void generator::gem_ans(int degree, double x_start, double x_gap) {
    //initialize mtx
    mtx = std::vector< std::vector<double> >(15, std::vector<double>(degree + 1, 0));
    y = std::vector<double>(15, 0);

    // std::cout << std::setw(10);
    for(int i = 0; i < 15; ++i) {
        double x = x_start + x_gap * i;
        double x_n = 1;
        double sum = 0.0;
        for(int j = 0; j < degree + 1; ++j) {
            std::cout << x_n;
            if(j != degree) std::cout << std::setw(10);
            else std::cout << std::setw(5);
            mtx[i][j] = x_n;
            sum = 1 + x * sum;
            x_n *= x;
        }
        std::cout << "|" << std::setw(10) << sum << "\n";
        y[i] = sum;
    }
    std::cout << "------\n";

    // for(int i = 0; i < 15; ++i) {
    //     double x = x_start + x_gap * i;
    //     double sum = 0.0;
    //     for(int j = 0; j < degree + 1; ++j) {
    //         mtx[i][j] = pow(x, j);
    //         sum += pow(x, j);
    //     }
    //     y[i] = sum;
    // }

    transpose();
}

void generator::transpose() {
    mtxT = std::vector< std::vector<double> >(mtx[0].size(), std::vector<double>(mtx.size(), 0));

    for(int i = 0; i < mtx.size(); ++i) {
        for(int j = 0; j < mtx[0].size(); ++j) {
            mtxT[j][i] = mtx[i][j];
        }
    }
    genB();
}

void generator::genB() {
    mtxB = std::vector< std::vector<double> >(mtxT.size(), std::vector<double>(mtx[0].size(), 0));
    yB = std::vector<double>(mtxB.size(), 0);

    for(int i = 0; i < mtxB.size(); ++i) {
        for(int j = 0; j < mtxB[0].size(); ++j) {
            double sum = 0;
            for(int k = 0; k < mtxT[0].size(); ++k) {
                sum += mtxT[i][k] * mtx[k][j];
            }
            mtxB[i][j] = sum;
        }
    }

    for(int i = 0; i < yB.size(); ++i) {
        double sum = 0;
        for(int j = 0; j < mtxT[0].size(); ++j) {
            sum += mtxT[i][j] * y[j];
        }
        yB[i] = sum;
    }
}