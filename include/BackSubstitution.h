#pragma once
#include <iostream>
#include <vector>

/*

    UpMtx * res = b
    already know UpMtx and b, need to solve res;

*/

struct backSub{
    void back_substitution(std::vector< std::vector<double> > &UpTriMtx, std::vector<double> &res, 
                            std::vector<double> &b, int n) {
        res = std::vector<double>(UpTriMtx[0].size(), 0);
        for(int i = n - 1; i > -1; --i) {
            res[i] = b[i] / UpTriMtx[i][i];
            for(int j = i - 1; j > -1; --j) {
                b[j] = b[j] - UpTriMtx[j][i] * res[i];
            }
        }
    }
};