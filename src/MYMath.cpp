#include <MYMath.h>

double Math::TwoNorm(std::vector<double> a, std::vector<double> b) {
    if(a.size() != b.size()) {
        std::cout << "wrong input\n";
        return 0.0;
    }
    double res = 0.0;
    for(int i = 0; i < a.size(); ++i) {
        res += (a[i] - b[i]) * (a[i] - b[i]);
    }
    res = sqrt(res);
    return res;
}

double Math::InfiniteNorm(std::vector<double> a, std::vector<double> b) {
    if(a.size() != b.size()) {
        std::cout << "wrong input\n";
        return 0.0;
    }
    double max_num = DBL_MIN;
    for(int i = 0; i < a.size(); ++i) {
        double val = fabs(a[i] - b[i]);
        max_num = (max_num < val) ? val : max_num;
    }
    return max_num;
}