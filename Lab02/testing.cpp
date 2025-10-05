#include "testing.h"
#include "mathfunctions.h"
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

void printResult(const char* funcName, double x, double myResult, double stdResult) {
    double absError = fabs(myResult - stdResult);
    double relError = (stdResult != 0) ? fabs((myResult - stdResult) / stdResult) * 100 : 0;
    
    cout << funcName << "(" << setw(10) << x << ") = " 
         << setw(18) << setprecision(12) << myResult 
         << " | Еталон: " << setw(18) << stdResult
         << " | Похибка: " << scientific << setw(12) << absError
         << " (" << fixed << setprecision(6) << relError << "%)" << endl;
}

void runTests() {
    cout << fixed << setprecision(12);
    cout << "============================================================" << endl;
    cout << "  Тестування елементарних функцій" << endl;
    cout << "============================================================" << endl << endl;
    
    // Тестові значення для тригонометричних функцій
    double trigValues[] = {0.0, 0.5, 1.0, 2.0, 3.14159, 10.0, 50.0, 100.0, 500.0, 1000.0, -5.0, -100.0};
    int trigCount = sizeof(trigValues) / sizeof(trigValues[0]);
    
    cout << "--- СИНУС ---" << endl;
    for (int i = 0; i < trigCount; i++) {
        double x = trigValues[i];
        printResult("sin", x, mySin(x), sin(x));
    }
    
    cout << endl << "--- КОСІНУС ---" << endl;
    for (int i = 0; i < trigCount; i++) {
        double x = trigValues[i];
        printResult("cos", x, myCos(x), cos(x));
    }
    
    cout << endl << "--- ТАНГЕНС ---" << endl;
    for (int i = 0; i < trigCount; i++) {
        double x = trigValues[i];
        double cosVal = cos(x);
        if (fabs(cosVal) > EPSILON) {
            printResult("tan", x, myTan(x), tan(x));
        } else {
            cout << "tan(" << setw(10) << x << ") = не визначений (cos(x) ≈ 0)" << endl;
        }
    }
    
    // Тестові значення для експоненти
    double expValues[] = {0.0, 0.5, 1.0, 2.0, 5.0, 10.0, 20.0, -0.5, -1.0, -5.0, -10.0, -20.0};
    int expCount = sizeof(expValues) / sizeof(expValues[0]);
    
    cout << endl << "--- ЕКСПОНЕНТА ---" << endl;
    for (int i = 0; i < expCount; i++) {
        double x = expValues[i];
        printResult("exp", x, myExp(x), exp(x));
    }
    
    cout << endl << "============================================================" << endl;
    cout << "  Примітка: Абсолютна похибка < 10^-10 вважається відмінною" << endl;
    cout << "============================================================" << endl;
}