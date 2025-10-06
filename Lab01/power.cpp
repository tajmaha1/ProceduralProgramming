#include "power.h"
#include <iostream>
#include <iomanip>
#include <cmath>
#include <cassert>

using namespace std;

double power(double base, int exp, int& steps) {
    steps = 0;
    if (exp == 0) return 1.0;
    if (exp < 0) return 1.0 / power(base, -exp, steps);
    
    double result = 1.0;
    for (int i = 0; i < exp; i++) {
        result *= base;
        steps++;
    }
    return result;
}

double quickPower(double base, int exp, int& steps) {
    steps = 0;
    if (exp == 0) return 1.0;
    if (exp < 0) return 1.0 / quickPower(base, -exp, steps);
    
    double result = 1.0;
    double curr = base;
    
    while (exp > 0) {
        if (exp % 2 == 1) result *= curr;
        curr *= curr;
        exp /= 2;
        steps++;
    }
    return result;
}

double power_rec(double base, int exp, int& steps) {
    steps++;
    if (exp == 0) return 1.0;
    if (exp == 1) return base;
    if (exp < 0) return 1.0 / power_rec(base, -exp, steps);
    return base * power_rec(base, exp - 1, steps);
}

double quickPower_rec(double base, int exp, int& steps) {
    steps++;
    if (exp == 0) return 1.0;
    if (exp == 1) return base;
    if (exp < 0) return 1.0 / quickPower_rec(base, -exp, steps);
    
    if (exp % 2 == 0) {
        double half = quickPower_rec(base, exp / 2, steps);
        return half * half;
    }
    return base * quickPower_rec(base, exp - 1, steps);
}

void compareAll(double base, int exp) {
    int s1, s2, s3, s4;
    
    cout << "\n" << string(60, '=') << endl;
    cout << "Обчислення: " << base << "^" << exp << endl;
    cout << string(60, '=') << endl;
    
    double r1 = power(base, exp, s1);
    double r2 = quickPower(base, exp, s2);
    double r3 = power_rec(base, exp, s3);
    double r4 = quickPower_rec(base, exp, s4);
    
    cout << fixed << setprecision(6);
    cout << "\nРезультат: " << r1 << "\n" << endl;
    
    cout << left << setw(30) << "Алгоритм" << setw(15) << "Кроків" << "Тип" << endl;
    cout << string(60, '-') << endl;
    cout << setw(30) << "power()" << setw(15) << s1 << "ітеративний O(n)" << endl;
    cout << setw(30) << "quickPower()" << setw(15) << s2 << "ітеративний O(log n)" << endl;
    cout << setw(30) << "power_rec()" << setw(15) << s3 << "рекурсивний O(n)" << endl;
    cout << setw(30) << "quickPower_rec()" << setw(15) << s4 << "рекурсивний O(log n)" << endl;
    
    cout << "\nПорівняння ефективності:" << endl;
    cout << "  Прискорення quick vs звичайний: " << setprecision(2) 
         << (double)s1/s2 << "x" << endl;
    cout << "  Рекурсія/Ітерація (звичайні):  " << (double)s3/s1 << "x" << endl;
    cout << "  Рекурсія/Ітерація (швидкі):    " << (double)s4/s2 << "x" << endl;
    
    const double eps = 1e-9;
    assert(fabs(r1 - r2) < eps && "quickPower дає інший результат!");
    assert(fabs(r1 - r3) < eps && "power_rec дає інший результат!");
    assert(fabs(r1 - r4) < eps && "quickPower_rec дає інший результат!");
    cout << "\n✓ Всі алгоритми дають однаковий результат (assert passed)" << endl;
}

void runAllTests() {
    cout << "\n" << string(60, '=') << endl;
    cout << "АВТОМАТИЧНЕ ТЕСТУВАННЯ (з assert)" << endl;
    cout << string(60, '=') << endl;
    
    struct TestCase { double base; int exp; };
    TestCase tests[] = {
        {2.0, 0}, {2.0, 1}, {2.0, 10}, {3.0, 5}, 
        {2.5, 6}, {10.0, 3}, {1.5, 8}, {7.0, 4}
    };
    
    const double eps = 1e-9;
    int numTests = sizeof(tests) / sizeof(tests[0]);
    
    for (int i = 0; i < numTests; i++) {
        int s1, s2, s3, s4;
        double base = tests[i].base;
        int exp = tests[i].exp;
        
        double r1 = power(base, exp, s1);
        double r2 = quickPower(base, exp, s2);
        double r3 = power_rec(base, exp, s3);
        double r4 = quickPower_rec(base, exp, s4);
        double expected = pow(base, exp);
        
        assert(fabs(r1 - expected) < eps);
        assert(fabs(r2 - expected) < eps);
        assert(fabs(r3 - expected) < eps);
        assert(fabs(r4 - expected) < eps);
        
        cout << "Тест " << (i+1) << ": " << base << "^" << exp 
             << " = " << fixed << setprecision(2) << r1 
             << " ✓ PASSED" << endl;
    }
    
    cout << "\n✓ Всі " << numTests << " тестів пройдено успішно!" << endl;
}