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
        return 1.0 / power(base, -exponent, steps); 
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
        return 1.0 / quickPower(base, -exponent, steps); 
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
    steps++; 
    
    if (exponent == 0) {
        return 1.0;
    }
    
    if (exponent == 1) {
        return base;
    }
    
    if (exponent < 0) {
        return 1.0 / power_rec(base, -exponent, steps);
    }
    
    return base * power_rec(base, exponent - 1, steps);
}

double quickPower_rec(double base, int exponent, int& steps) {
    steps++;  
    
    if (exponent == 0) {
        return 1.0;
    }
    
    if (exponent == 1) {
        return base;
    }
    
    if (exponent < 0) {
        return 1.0 / quickPower_rec(base, -exponent, steps);
    }
    
    if (exponent % 2 == 0) {
        double half = quickPower_rec(base, exponent / 2, steps);
        return half * half;
    } else {
        return base * quickPower_rec(base, exponent - 1, steps);
    }
}


bool testQuickPower(double base, int exponent) {
    int steps1, steps2;

    double result1 = power(base, exponent, steps1);
    double result2 = quickPower(base, exponent, steps2);

    const double epsilon = 1e-10;
    return abs(result1 - result2) < epsilon;
}

bool testRecursiveFunctions(double base, int exponent) {
    int steps_iter, steps_rec, steps_quick_iter, steps_quick_rec;

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
    int steps1, steps2;

    cout << "\n" << string(50, '-') << endl;
    cout << "Порівняння ітеративних алгоритмів для " << base << "^" << exponent << endl;
    cout << string(50, '-') << endl;

    double result1 = power(base, exponent, steps1);
    cout << fixed << setprecision(6);
    cout << "power(" << base << ", " << exponent << "):" << endl;
    cout << "  Результат: " << result1 << endl;
    cout << "  Кількість кроків: " << steps1 << endl;

    double result2 = quickPower(base, exponent, steps2);
    cout << "\nquickPower(" << base << ", " << exponent << "):" << endl;
    cout << "  Результат: " << result2 << endl;
    cout << "  Кількість кроків: " << steps2 << endl;

    cout << "\nПорівняння:" << endl;
    cout << "  Різниця результатів: " << abs(result1 - result2) << endl;
    cout << "  Економія кроків: " << (steps1 - steps2) << endl;

    if (steps2 > 0) {
        cout << "  Прискорення: в " << fixed << setprecision(2) 
             << (double)steps1 / steps2 << " разів" << endl;
    }

    cout << " Тест правильності: " << (testQuickPower(base, exponent) ? "Пройдено" : "Не пройдено") << endl;
}

void compareAllAlgorithms(double base, int exponent) {
    int steps_iter, steps_rec, steps_quick_iter, steps_quick_rec;

    cout << "\n" << string(50, '-') << endl;
    cout << "Повне порівняння всіх алгоритмів для " << base << "^" << exponent << endl;
    cout << string(50, '-') << endl;

    double result_iter = power(base, exponent, steps_iter);
    double result_rec = power_rec(base, exponent, steps_rec);
    double result_quick_iter = quickPower(base, exponent, steps_quick_iter);
    double result_quick_rec = quickPower_rec(base, exponent, steps_quick_rec);

    cout << fixed << setprecision(8);
    
    cout << "\n1. ІТЕРАТИВНИЙ звичайний (power):" << endl;
    cout << "   Результат: " << result_iter << endl;
    cout << "   Кроків: " << steps_iter << endl;
    
    cout << "\n2. РЕКУРСИВНИЙ звичайний (power_rec):" << endl;
    cout << "   Результат: " << result_rec << endl;
    cout << "   Рекурсивних викликів: " << steps_rec << endl;
    
    cout << "\n3. ІТЕРАТИВНИЙ швидкий (quickPower):" << endl;
    cout << "   Результат: " << result_quick_iter << endl;
    cout << "   Кроків: " << steps_quick_iter << endl;
    
    cout << "\n4. РЕКУРСИВНИЙ швидкий (quickPower_rec):" << endl;
    cout << "   Результат: " << result_quick_rec << endl;
    cout << "   Рекурсивних викликів: " << steps_quick_rec << endl;

    cout << "\n" << string(30, '-') << endl;
    cout << "АНАЛІЗ ПРОДУКТИВНОСТІ:" << endl;
    cout << string(30, '-') << endl;
    
    cout << "Швидкість (кількість операцій):" << endl;
    cout << "  Ітеративний звичайний: " << steps_iter << " кроків" << endl;
    cout << "  Рекурсивний звичайний:  " << steps_rec << " викликів" << endl;
    cout << "  Ітеративний швидкий:   " << steps_quick_iter << " кроків" << endl;
    cout << "  Рекурсивний швидкий:    " << steps_quick_rec << " викликів" << endl;
    
    cout << "\nПорівняння методів:" << endl;
    if (steps_iter > 0) {
        cout << "  Рекурсія vs Ітерація (звичайні): " 
             << fixed << setprecision(2) << (double)steps_rec / steps_iter << ":1" << endl;
    }
    if (steps_quick_iter > 0) {
        cout << "  Рекурсія vs Ітерація (швидкі): " 
             << fixed << setprecision(2) << (double)steps_quick_rec / steps_quick_iter << ":1" << endl;
    }
    
    int min_steps = min({steps_iter, steps_rec, steps_quick_iter, steps_quick_rec});
    cout << "\nНАЙШВИДШИЙ алгоритм (" << min_steps << " операцій): ";
    if (min_steps == steps_iter) cout << "Ітеративний звичайний" << endl;
    else if (min_steps == steps_rec) cout << "Рекурсивний звичайний" << endl;
    else if (min_steps == steps_quick_iter) cout << "Ітеративний швидкий" << endl;
    else cout << "Рекурсивний швидкий" << endl;
    
    cout << "\nТест правильності: " << (testRecursiveFunctions(base, exponent) ? "ВСІ ПРОЙДЕНО" : "ПОМИЛКА") << endl;
}


void runTests() {
    cout << "\n" << string(45, '-') << endl;
    cout << "Автоматичне тестування ітеративних функцій" << endl;
    cout << string(45, '-') << endl;

    double testCases[][2] = {
        {2.0, 0}, {5.0, 1}, {2.0, 8}, {3.0, 7}, {2.5, 4},
        {10.0, 3}, {1.5, 10}, {2.0, 16}, {7.0, 5}, {1.1, 20}
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int passedTests = 0;

    cout << "\nВиконання " << numTests << " тестів..." << endl;
    for (int i = 0; i < numTests; i++) {
        double base = testCases[i][0];
        int exponent = (int)testCases[i][1];

        bool testPassed = testQuickPower(base, exponent);

        cout << "Тест " << (i + 1) << ": " << fixed << setprecision(2) 
             << base << "^" << exponent;

        if (testPassed) {
            cout << " - Пройдено" << endl;
            passedTests++;
        } else {
            cout << " - Не пройдено" << endl;
        }
    }
    
    cout << "\nРезультати тестування ітеративних функцій:" << endl;
    cout << "Пройдено тестів: " << passedTests << "/" << numTests << endl;
    if (passedTests == numTests) {
        cout << "Всі тести пройдено успішно!" << endl;
    }
}

void runRecursiveTests() {
    cout << "\n" << string(45, '-') << endl;
    cout << "Автоматичне тестування рекурсивних функцій" << endl;
    cout << string(45, '-') << endl;

    double testCases[][2] = {
        {2.0, 0}, {5.0, 1}, {2.0, 8}, {3.0, 7}, {2.5, 4},
        {10.0, 3}, {1.5, 10}, {2.0, 16}, {7.0, 5}, {1.1, 20}
    };

    int numTests = sizeof(testCases) / sizeof(testCases[0]);
    int passedTests = 0;

    cout << "\nВиконання " << numTests << " тестів рекурсивних функцій..." << endl;
    for (int i = 0; i < numTests; i++) {
        double base = testCases[i][0];
        int exponent = (int)testCases[i][1];

        bool testPassed = testRecursiveFunctions(base, exponent);

        cout << "Тест " << (i + 1) << ": " << fixed << setprecision(2) 
             << base << "^" << exponent;

        if (testPassed) {
            cout << " - Пройдено" << endl;
            passedTests++;
        } else {
            cout << " - Не пройдено" << endl;
        }
    }
    
    cout << "\nРезультати тестування рекурсивних функцій:" << endl;
    cout << "Пройдено тестів: " << passedTests << "/" << numTests << endl;
    if (passedTests == numTests) {
        cout << "Всі рекурсивні тести пройдено успішно!" << endl;
    }
}