#pragma once

#include <iostream>
#include <cmath>
#include <vector>

struct Gaussian{
    std::vector< std::vector<double> > UpTriMtx;
    std::vector<double> res;
    std::vector<double> b;
    void gaussian_elimination();
};