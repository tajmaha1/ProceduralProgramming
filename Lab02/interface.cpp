#include "interface.h"
#include "mathfunctions.h"
#include "testing.h"
#include <iostream>
#include <cmath>

using namespace std;

void runInteractiveMode() {
    cout << "\n=== Інтерактивне обчислення ===" << endl;
    char choice;
    double x;
    
    do {
        cout << "\nВиберіть функцію:" << endl;
        cout << "1 - sin(x)" << endl;
        cout << "2 - cos(x)" << endl;
        cout << "3 - tan(x)" << endl;
        cout << "4 - exp(x)" << endl;
        cout << "0 - Вихід" << endl;
        cout << "Ваш вибір: ";
        cin >> choice;
        
        if (choice >= '1' && choice <= '4') {
            cout << "Введіть значення x: ";
            cin >> x;
            cout << endl;
            
            switch (choice) {
                case '1':
                    testFunction("sin", x, mySin(x), sin(x));
                    break;
                case '2':
                    testFunction("cos", x, myCos(x), cos(x));
                    break;
                case '3':
                    testFunction("tan", x, myTan(x), tan(x));
                    break;
                case '4':
                    testFunction("exp", x, myExp(x), exp(x));
                    break;
            }
        }
    } while (choice != '0');
}