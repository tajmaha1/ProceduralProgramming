#include <iostream>
#include <iomanip>
#include <cassert>
#include <vector>
#include "fibonacci.h"

using namespace std;

const vector<uint64_t> KNOWN_FIB = {
    0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610,
    987, 1597, 2584, 4181, 6765, 10946, 17711, 28657, 46368, 75025
};

void testCorrectness() {
    cout << "=== CORRECTNESS TESTING ===\n\n";
    
    StepCounter counter;
    
    for (size_t n = 0; n < KNOWN_FIB.size(); ++n) {
        uint64_t expected = KNOWN_FIB[n];
        
        uint64_t res1 = fibIterative(n, counter);
        uint64_t res2 = fibMatrixIterative(n, counter);
        uint64_t res3 = fibRecursiveLinear(n, counter);
        uint64_t res4 = fibRecursiveFast(n, counter);
        
        assert(res1 == expected && "Iterative function");
        assert(res2 == expected && "Matrix iterative");
        assert(res3 == expected && "Recursive linear");
        assert(res4 == expected && "Fast recursive");
    }
    
    cout << "All " << KNOWN_FIB.size() << " tests passed successfully!\n\n";
}

void printHeader() {
    cout << setw(5) << "n" << " | "
         << setw(20) << "Fibonacci(n)" << " | "
         << setw(10) << "Iter." << " | "
         << setw(10) << "Matrix" << " | "
         << setw(10) << "Recurs." << " | "
         << setw(10) << "Fast Rec." << "\n";
    cout << string(85, '-') << "\n";
}

void comparePerformance() {
    cout << "=== EXECUTION PROTOCOL AND COMPARISON ===\n\n";
    
    vector<int> testCases = {5, 10, 15, 20, 25, 30, 35, 40};
    StepCounter counter;
    
    printHeader();
    
    for (int n : testCases) {
        uint64_t result = fibIterative(n, counter);
        uint64_t steps1 = counter.steps;
        
        fibMatrixIterative(n, counter);
        uint64_t steps2 = counter.steps;
        
        fibRecursiveLinear(n, counter);
        uint64_t steps3 = counter.steps;
        
        fibRecursiveFast(n, counter);
        uint64_t steps4 = counter.steps;
        
        cout << setw(5) << n << " | "
             << setw(20) << result << " | "
             << setw(10) << steps1 << " | "
             << setw(10) << steps2 << " | "
             << setw(10) << steps3 << " | "
             << setw(10) << steps4 << "\n";
    }
    
    cout << "\nColumn labels:\n";
    cout << "  Iter.     - iterative function (steps)\n";
    cout << "  Matrix    - matrix iterative (steps)\n";
    cout << "  Recurs.   - recursive linear (steps)\n";
    cout << "  Fast Rec. - fast recursive (steps)\n";
}

void printAnalysis() {
    cout << "\n=== RESULTS ANALYSIS ===\n\n";
    
    cout << "1. ITERATIVE FUNCTION:\n";
    cout << "   • Complexity: O(n)\n";
    cout << "   • Steps: n-1 for n≥2\n";
    cout << "   • Advantages: simple, efficient for small n\n";
    cout << "   • Disadvantages: slow for large n\n\n";
    
    cout << "2. MATRIX ITERATIVE:\n";
    cout << "   • Complexity: O(log n)\n";
    cout << "   • Steps: ~2*log₂(n)\n";
    cout << "   • Advantages: very fast for large n\n";
    cout << "   • Disadvantages: more complex implementation\n\n";
    
    cout << "3. RECURSIVE LINEAR:\n";
    cout << "   • Complexity: O(n)\n";
    cout << "   • Steps: n+1\n";
    cout << "   • Advantages: elegant, tail recursion\n";
    cout << "   • Disadvantages: function call overhead\n\n";
    
    cout << "4. FAST RECURSIVE:\n";
    cout << "   • Complexity: O(log n)\n";
    cout << "   • Steps: ~3*log₂(n)\n";
    cout << "   • Advantages: fast for large n\n";
    cout << "   • Disadvantages: redundant calculations without memoization\n\n";
    
    cout << "CONCLUSION:\n";
    cout << "For n < 30: iterative is most efficient\n";
    cout << "For n ≥ 30: matrix iterative is optimal\n";
    cout << "Recursive methods are elegant but less practical\n";
}

int main() {
    cout << "╔════════════════════════════════════════════╗\n";
    cout << "║  FIBONACCI NUMBERS COMPUTATION - 4 METHODS ║\n";
    cout << "╚════════════════════════════════════════════╝\n\n";
    
    testCorrectness();
    comparePerformance();
    printAnalysis();
    
    return 0;
}