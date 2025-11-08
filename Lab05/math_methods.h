#ifndef MATH_METHODS_H
#define MATH_METHODS_H

#include <functional>
#include <string>

template<typename T>
struct Result {
    T value;
    int steps;
    bool success;
    std::string protocol;
};

Result<double> solve(
    std::function<double(double)> f,
    double a, 
    double b, 
    double eps = 1e-6
);

Result<double> integrate(
    std::function<double(double)> f,
    double a,
    double b,
    int n = 100
);

#endif