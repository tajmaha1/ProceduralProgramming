#include "QuickSortAnalyzer.h"
#include <iostream>
#include <algorithm>
#include <map>

using namespace std;

vector<int> arr;
vector<int> original;
int comparisons = 0;
int swaps = 0;
int steps = 0;
int recursionLevel = 0;

void printStep(const string& action, int left, int right, int level) {
    steps++;
    cout << "  Крок " << steps << " [Рівень " << level << "]: " << action;
    cout << " (діапазон [" << left << ".." << right << "])";
    
    cout << " -> [";
    for (int i = left; i <= right && i < arr.size(); i++) {
        cout << arr[i];
        if (i < right) cout << ", ";
    }
    cout << "]\n";
}

int partition(int left, int right, int level) {
    printStep("Початок розподілу", left, right, level);
    
    int pivot = arr[right];
    cout << "    Опорний елемент: " << pivot << "\n";
    
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        comparisons++;
        if (arr[j] < pivot) {
            i++;
            if (i != j) {
                swap(arr[i], arr[j]);
                swaps++;
            }
        }
    }
    
    swap(arr[i + 1], arr[right]);
    swaps++;
    
    printStep("Завершено розподіл, pivot на позиції " + to_string(i + 1), left, right, level);
    
    return i + 1;
}

void quickSort(int left, int right, int level) {
    if (left < right) {
        printStep("Сортування підмасиву", left, right, level);
        
        int pivotIndex = partition(left, right, level);
        quickSort(left, pivotIndex - 1, level + 1);
        quickSort(pivotIndex + 1, right, level + 1);
    }
}

void printArray(const vector<int>& a, const string& label) {
    cout << label << ": [";
    for (size_t i = 0; i < a.size(); i++) {
        cout << a[i];
        if (i < a.size() - 1) cout << ", ";
    }
    cout << "]\n";
}

bool verifySorted() {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

bool verifySameElements() {
    map<int, int> originalCount, sortedCount;
    
    for (int val : original) {
        originalCount[val]++;
    }
    
    for (int val : arr) {
        sortedCount[val]++;
    }
    
    return originalCount == sortedCount;
}

void runTest(vector<int> data, int testNum, const string& description) {
    cout << "\n========================================\n";
    cout << "ТЕСТ " << testNum << ": " << description << "\n";
    cout << "========================================\n";
    
    arr = data;
    original = data;
    comparisons = 0;
    swaps = 0;
    steps = 0;
    recursionLevel = 0;
    
    printArray(original, "Початковий масив");
    
    cout << "\nПокроковий протокол виконання:\n";
    
    int n = arr.size();
    if (n > 1) {
        quickSort(0, n - 1, 1);
    } else {
        cout << "  Масив з " << n << " елемента - сортування не потрібне\n";
    }
    
    cout << "\n";
    printArray(arr, "Відсортований   ");
    
    cout << "\nСтатистика виконання:\n";
    cout << "  Розмір масиву: " << n << " елементів\n";
    cout << "  Всього кроків: " << steps << "\n";
    cout << "  Порівнянь: " << comparisons << "\n";
    cout << "  Обмінів: " << swaps << "\n";
    
    cout << "\nПеревірка коректності:\n";
    
    bool sorted = verifySorted();
    cout << "  [СУДЖЕННЯ 1] Елементи відсортовані за зростанням: ";
    cout << (sorted ? "[OK]" : "[FAIL]") << "\n";
    cout << "               Перевірка: arr[i] <= arr[i+1] для всіх i\n";
    
    bool sameElements = verifySameElements();
    cout << "  [СУДЖЕННЯ 2] Збережено всі елементи з початкового масиву: ";
    cout << (sameElements ? "[OK]" : "[FAIL]") << "\n";
    cout << "               Перевірка: multiset(original) = multiset(sorted)\n";
    
    if (sorted && sameElements) {
        cout << "\n  >>> ТЕСТ ПРОЙДЕНО УСПІШНО <<<\n";
    } else {
        cout << "\n  >>> ТЕСТ ПРОВАЛЕНО <<<\n";
    }
}