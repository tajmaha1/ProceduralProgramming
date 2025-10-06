#include <iostream>
#include "power.h"

using namespace std;

int main() {
    cout << "ЛАБОРАТОРНА РОБОТА: Порівняння алгоритмів піднесення до степеню\n" << endl;
    
    compareAll(2.0, 10);
    compareAll(3.0, 7);
    compareAll(2.0, 16);
    compareAll(2.5, 6);
    
    runAllTests();
    
    cout << "\n" << string(60, '=') << endl;
    cout << "ВИСНОВКИ:" << endl;
    cout << string(60, '=') << endl;
    cout << "1. Швидкі алгоритми (O(log n)) значно ефективніші за звичайні (O(n))" << endl;
    cout << "2. Ітеративні версії мають менше операцій ніж рекурсивні" << endl;
    cout << "3. Для великих степенів різниця особливо помітна" << endl;
    cout << "4. Всі алгоритми дають коректні результати (перевірено assert)\n" << endl;
    
    return 0;
}