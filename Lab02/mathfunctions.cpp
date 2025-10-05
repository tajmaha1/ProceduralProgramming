#include "mathfunctions.h"
#include <cmath>
#include <iostream>

using namespace std;

const double PI = 3.14159265358979323846;
const double EPSILON = 1e-10;

double normalizeAngle(double x) {
    x = fmod(x, 2 * PI);
    
    if (x > PI) {
        x -= 2 * PI;
    } else if (x < -PI) {
        x += 2 * PI;
    }
    
    return x;
}

double mySin(double x) {
    x = normalizeAngle(x);
    
    double term = x;
    double sum = x;
    int n = 1;
    
    while (fabs(term) > EPSILON) {
        term *= -x * x / ((2 * n) * (2 * n + 1));
        sum += term;
        n++;
    }
    
    return sum;
}

double myCos(double x) {
    x = normalizeAngle(x);
    
    double term = 1.0;
    double sum = 1.0;
    int n = 1;
    
    while (fabs(term) > EPSILON) {
        term *= -x * x / ((2 * n - 1) * (2 * n));
        sum += term;
        n++;
    }
    
    return sum;
}

double myTan(double x) {
    double cosValue = myCos(x);
    
    if (fabs(cosValue) < EPSILON) {
        return NAN;
    }
    
    return mySin(x) / cosValue;
}

double myExp(double x) {
    bool negative = false;
    if (x < 0) {
        negative = true;
        x = -x;
    }
    
    int scale = 0;
    while (x > 1.0) {
        x /= 2.0;
        scale++;
    }
    
    double term = 1.0;
    double sum = 1.0;
    int n = 1;
    
    while (fabs(term) > EPSILON) {
        term *= x / n;
        sum += term;
        n++;
    }
    
    while (scale > 0) {
        sum = sum * sum;
        scale--;
    }
    
    if (negative) {
        sum = 1.0 / sum;
    }
    
    return sum;
}
