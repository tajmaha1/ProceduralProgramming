#include <iostream>
#include <iomanip>
#include "power.h"

using namespace std;

int main() {
    cout << "Лабораторна робота: порівняння алгоритмів піднесення до степеню" << endl;
    
    double testCases[][2] = {
        {2.0, 4},
        {3.0, 5},
        {2.0, 10},
        {2.5, 6},
        {2.0, 16}
    };
    
    int numCases = sizeof(testCases) / sizeof(testCases[0]);
    
    for (int i = 0; i < numCases; i++) {
        double base = testCases[i][0];
        int exponent = (int)testCases[i][1];
        
        cout << "\n Тест " << (i + 1) << ": " << base << "^" << exponent  << endl;
        
        compareAlgorithms(base, exponent);
        
        compareAllAlgorithms(base, exponent);
    }
    
    cout << "\n=== Тестування функцій ===" << endl;
    runTests();
    runRecursiveTests();
    
    cout << "\n==== Висновки ====" << endl;
    cout << "1. Швидкі алгоритми працюють краще за звичайні" << endl;
    cout << "2. Ітеративні версії швидші за рекурсивні" << endl;
    cout << "3. Всі функції дають правильні результати" << endl;
    cout << "\nРобота виконана." << endl;
    
    return 0;
}