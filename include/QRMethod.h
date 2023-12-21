#pragma once

#include <iostream>
#include <vector>
#include <cmath>

#include "BackSubstitution.h"

struct QRMethod {
    std::vector< std::vector<double> > UpTriMtx;
    std::vector<double> b;
    std::vector<double> res;
    void householder_vec(int i, int j, std::vector<double> &vec, int size);
    void QR_reflection();
    void solver(std::vector< std::vector<double> > Mtx, std::vector<double> _b);
};