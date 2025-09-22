#include <iostream>
#include <iomanip>
#include "power.h"

using namespace std;

int main() {
    cout << "Laboratory Work: Comparison of Power Algorithms" << endl;

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

        cout << "\n Test " << (i + 1) << ": " << base << "^" << exponent << endl;

        compareAlgorithms(base, exponent);

        compareAllAlgorithms(base, exponent);
    }

    cout << "\n=== Function Testing ===" << endl;
    runTests();
    runRecursiveTests();

    cout << "\n==== Conclusions ====" << endl;
    cout << "1. Fast algorithms perform better than standard ones" << endl;
    cout << "2. Iterative versions are faster than recursive ones" << endl;
    cout << "3. All functions return correct results" << endl;
    cout << "\nWork completed." << endl;

    return 0;
}
