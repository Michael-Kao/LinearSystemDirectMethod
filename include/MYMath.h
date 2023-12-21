#pragma once

#include <iostream>
#include <vector>
#include <cmath>

struct Math { 
    double TwoNorm(std::vector<double> a, std::vector<double> b);
    double InfiniteNorm(std::vector<double> a, std::vector<double> b);
};