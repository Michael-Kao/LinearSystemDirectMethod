#pragma once

#include <iostream>
#include <iomanip>
#include <cmath>
#include <vector>

struct generator {
    std::vector< std::vector<double> > mtx;
    std::vector< std::vector<double> > mtxT;
    std::vector< std::vector<double> > mtxB;
    std::vector<double> y;
    std::vector<double> yB;
    void gem_ans(int degree, double x_start, double x_gap);
    std::vector< std::vector<double> > const get_mtx() { return mtx; }
    void transpose();
    void genB();
};