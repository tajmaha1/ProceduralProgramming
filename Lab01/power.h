#ifndef POWER_H
#define POWER_H

double power(double base, int exp, int& steps);
double quickPower(double base, int exp, int& steps);

double power_rec(double base, int exp, int& steps);
double quickPower_rec(double base, int exp, int& steps);

void compareAll(double base, int exp);
void runAllTests();

#endif
