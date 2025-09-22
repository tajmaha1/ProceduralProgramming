#ifndef POWER_H
#define POWER_H

double power(double base, int exponent, int& steps);
double quickPower(double base, int exponent, int& steps);

double power_rec(double base, int exponent, int& steps);
double quickPower_rec(double base, int exponent, int& steps);

bool testQuickPower(double base, int exponent);
bool testRecursiveFunctions(double base, int exponent);
void compareAlgorithms(double base, int exponent);
void compareAllAlgorithms(double base, int exponent);
void runTests();
void runRecursiveTests();

#endif