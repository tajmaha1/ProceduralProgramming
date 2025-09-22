#include "power.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <algorithm>

using namespace std;

double power(double base, int exponent, int& steps) {
    steps = 0;

    if (exponent == 0) {
        return 1.0;
    }

    if (exponent < 0) {
        double result = 1.0 / power(base, -exponent, steps);
        return result;
    }

    double result = 1.0;
    for (int i = 0; i < exponent; i++) {
        result *= base;
        steps++;
    }
    return result;
}

double quickPower(double base, int exponent, int& steps) {
    steps = 0;

    if (exponent == 0) {
        return 1.0;
    }

    if (exponent < 0) {
        double result = 1.0 / quickPower(base, -exponent, steps);
        return result;
    }

    double result = 1.0;
    double currentBase = base;
    int currentExponent = exponent;

    while (currentExponent > 0) {
        if (currentExponent % 2 == 1) {
            result *= currentBase;
        }
        currentBase *= currentBase;
        currentExponent /= 2;
        steps++;
    }

    return result;
}

double power_rec(double base, int exponent, int& steps) {
    if (steps == -1) steps = 0;
    steps++;

    if (exponent == 0) {
        return 1.0;
    }

    if (exponent == 1) {
        return base;
    }

    if (exponent < 0) {
        int tempSteps = 0;
        double result = 1.0 / power_rec(base, -exponent, tempSteps);
        steps += tempSteps;
        return result;
    }

    return base * power_rec(base, exponent - 1, steps);
}

double quickPower_rec(double base, int exponent, int& steps) {
    if (steps == -1) steps = 0;
    steps++;

    if (exponent == 0) {
        return 1.0;
    }

    if (exponent == 1) {
        return base;
    }

    if (exponent < 0) {
        int tempSteps = 0;
        double result = 1.0 / quickPower_rec(base, -exponent, tempSteps);
        steps += tempSteps;
        return result;
    }

    if (exponent % 2 == 0) {
        double half = quickPower_rec(base, exponent / 2, steps);
        return half * half;
    }
    else {
        return base * quickPower_rec(base, exponent - 1, steps);
    }
}

bool testQuickPower(double base, int exponent) {
    int steps1 = 0, steps2 = 0;

    double result1 = power(base, exponent, steps1);
    double result2 = quickPower(base, exponent, steps2);

    const double epsilon = 1e-10;
    return abs(result1 - result2) < epsilon;
}

bool testRecursiveFunctions(double base, int exponent) {
    int steps_iter = 0, steps_rec = -1, steps_quick_iter = 0, steps_quick_rec = -1;

    double result_iter = power(base, exponent, steps_iter);
    double result_rec = power_rec(base, exponent, steps_rec);
    double result_quick_iter = quickPower(base, exponent, steps_quick_iter);
    double result_quick_rec = quickPower_rec(base, exponent, steps_quick_rec);

    const double epsilon = 1e-10;

    bool test1 = abs(result_iter - result_rec) < epsilon;
    bool test2 = abs(result_iter - result_quick_iter) < epsilon;
    bool test3 = abs(result_iter - result_quick_rec) < epsilon;

    return test1 && test2 && test3;
}

void compareAlgorithms(double base, int exponent) {
    int steps1 = 0, steps2 = 0;

    cout << "\n" << string(50, '-') << endl;
    cout << "Comparison of iterative algorithms for " << base << "^" << exponent << endl;
    cout << string(50, '-') << endl;

    double result1 = power(base, exponent, steps1);
    double result2 = quickPower(base, exponent, steps2);

    cout << fixed << setprecision(6);
    cout << "power(" << base << ", " << exponent << "):" << endl;
    cout << "  Result: " << result1 << endl;
    cout << "  Steps: " << steps1 << endl;

    cout << "\nquickPower(" << base << ", " << exponent << "):" << endl;
    cout << "  Result: " << result2 << endl;
    cout << "  Steps: " << steps2 << endl;

    cout << "\nComparison:" << endl;
    cout << "  Result difference: " << abs(result1 - result2) << endl;
    cout << "  Steps saved: " << (steps1 - steps2) << endl;

    if (steps2 > 0) {
        cout << "  Speedup: " << fixed << setprecision(2)
            << (double)steps1 / steps2 << "x faster" << endl;
    }

    cout << "  Correctness test: " << (testQuickPower(base, exponent) ? "Passed" : "Failed") << endl;
}

void compareAllAlgorithms(double base, int exponent) {
    int steps_iter = 0, steps_rec = -1, steps_quick_iter = 0, steps_quick_rec = -1;

    cout << "\n" << string(50, '-') << endl;
    cout << "Full comparison of all algorithms for " << base << "^" << exponent << endl;
    cout << string(50, '-') << endl;

    double result_iter = power(base, exponent, steps_iter);
    double result_rec = power_rec(base, exponent, steps_rec);
    double result_quick_iter = quickPower(base, exponent, steps_quick_iter);
    double result_quick_rec = quickPower_rec(base, exponent, steps_quick_rec);

    cout << fixed << setprecision(8);

    cout << "\n1. ITERATIVE standard (power):" << endl;
    cout << "   Result: " << result_iter << endl;
    cout << "   Steps: " << steps_iter << endl;

    cout << "\n2. RECURSIVE standard (power_rec):" << endl;
    cout << "   Result: " << result_rec << endl;
    cout << "   Recursive calls: " << steps_rec << endl;

    cout << "\n3. ITERATIVE fast (quickPower):" << endl;
    cout << "   Result: " << result_quick_iter << endl;
    cout << "   Steps: " << steps_quick_iter << endl;

    cout << "\n4. RECURSIVE fast (quickPower_rec):" << endl;
    cout << "   Result: " << result_quick_rec << endl;
    cout << "   Recursive calls: " << steps_quick_rec << endl;

    cout << "\n" << string(30, '-') << endl;
    cout << "PERFORMANCE ANALYSIS:" << endl;
    cout << string(30, '-') << endl;

    cout << "Operation counts:" << endl;
    cout << "  Iterative standard:   " << steps_iter << " steps" << endl;
    cout << "  Recursive standard:   " << steps_rec << " calls" << endl;
    cout << "  Iterative fast:       " << steps_quick_iter << " steps" << endl;
    cout << "  Recursive fast:       " << steps_quick_rec << " calls" << endl;

    cout << "\nMethod comparisons:" << endl;
    if (steps_iter > 0) {
        cout << "  Recursive vs Iterative (standard): "
            << fixed << setprecision(2) << (double)steps_rec / steps_iter << ":1" << endl;
    }
    if (steps_quick_iter > 0) {
        cout << "  Recursive vs Iterative (fast): "
            << fixed << setprecision(2) << (double)steps_quick_rec / steps_quick_iter << ":1" << endl;
    }

    int min_steps = min({ steps_iter, steps_rec, steps_quick_iter, steps_quick_rec });
    cout << "\nFASTEST algorithm (" << min_steps << " operations): ";
    if (min_steps == steps_iter) cout << "Iterative standard" << endl;
    else if (min_steps == steps_rec) cout << "Recursive standard" << endl;
    else if (min_steps == steps_quick_iter) cout << "Iterative fast" << endl;
    else cout << "Recursive fast" << endl;

    cout << "\nCorrectness test: " << (testRecursiveFunctions(base, exponent) ? "ALL PASSED" : "FAILED") << endl;
}

void runTests() {
    cout << "\n" << string(45, '-') << endl;
    cout << "Automatic testing of iterative functions" << endl;
    cout << string(45, '-') << endl;

    double testCases[][2] = {
        {2.0, 0}, {5.0, 1}, {2.0, 8}, {3.0, 7}, {2.5, 4},
        {10.0, 3}, {1.5, 10}, {2.0, 16}, {7.0, 5}, {1.1, 20}
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int passedTests = 0;

    cout << "\nRunning " << numTests << " tests..." << endl;
    for (int i = 0; i < numTests; i++) {
        double base = testCases[i][0];
        int exponent = (int)testCases[i][1];

        bool testPassed = testQuickPower(base, exponent);

        cout << "Test " << (i + 1) << ": " << fixed << setprecision(2)
            << base << "^" << exponent;

        if (testPassed) {
            cout << " - Passed" << endl;
            passedTests++;
        }
        else {
            cout << " - Failed" << endl;
        }
    }

    cout << "\nIterative function test results:" << endl;
    cout << "Tests passed: " << passedTests << "/" << numTests << endl;
    if (passedTests == numTests) {
        cout << "All tests passed successfully!" << endl;
    }
}

void runRecursiveTests() {
    cout << "\n" << string(45, '-') << endl;
    cout << "Automatic testing of recursive functions" << endl;
    cout << string(45, '-') << endl;

    double testCases[][2] = {
        {2.0, 0}, {5.0, 1}, {2.0, 8}, {3.0, 7}, {2.5, 4},
        {10.0, 3}, {1.5, 10}, {2.0, 16}, {7.0, 5}, {1.1, 20}
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int passedTests = 0;

    cout << "\nRunning " << numTests << " recursive tests..." << endl;
    for (int i = 0; i < numTests; i++) {
        double base = testCases[i][0];
        int exponent = (int)testCases[i][1];

        bool testPassed = testRecursiveFunctions(base, exponent);

        cout << "Test " << (i + 1) << ": " << fixed << setprecision(2)
            << base << "^" << exponent;

        if (testPassed) {
            cout << " - Passed" << endl;
            passedTests++;
        }
        else {
            cout << " - Failed" << endl;
        }
    }

    cout << "\nRecursive function test results:" << endl;
    cout << "Tests passed: " << passedTests << "/" << numTests << endl;
    if (passedTests == numTests) {
        cout << "All recursive tests passed successfully!" << endl;
    }
}
