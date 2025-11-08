#include "math_methods.h"
#include <iostream>
#include <cmath>

using namespace std;

void printResult(const Result<double>& r, const string& name) {
    cout << "\n" << string(50, '=') << "\n";
    cout << name << "\n";
    cout << string(50, '=') << "\n\n";
    cout << r.protocol;
    cout << "RESULT: " << r.value << "\n";
    cout << "Steps: " << r.steps << "\n";
    cout << "Success: " << (r.success ? "Yes" : "No") << "\n";
    cout << string(50, '=') << "\n\n";
}

int main() {
    cout << "Computational Methods: Bisection and Simpson\n";
    cout << "============================================\n\n";

    auto equation1 = [](double x) { return x * x * x - x - 2; };
    auto res1 = solve(equation1, 1.0, 2.0, 1e-5);
    printResult(res1, "Equation: x^3 - x - 2 = 0");

    auto equation2 = [](double x) { return cos(x) - x; };
    auto res2 = solve(equation2, 0.0, 1.0, 1e-6);
    printResult(res2, "Equation: cos(x) = x");

    auto func1 = [](double x) { return x * x; };
    auto res3 = integrate(func1, 0.0, 1.0, 100);
    printResult(res3, "Integral: x^2 dx from 0 to 1 (exact: 1/3 = 0.333333)");

    auto func2 = [](double x) { return sin(x); };
    auto res4 = integrate(func2, 0.0, 3.14159265358979323846, 100);
    printResult(res4, "Integral: sin(x) dx from 0 to pi (exact: 2)");

    auto func3 = [](double x) { return exp(x); };
    auto res5 = integrate(func3, 0.0, 1.0, 200);
    printResult(res5, "Integral: e^x dx from 0 to 1 (exact: e-1 = 1.718282)");

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}