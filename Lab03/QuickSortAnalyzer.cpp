#include "QuickSortAnalyzer.h"
#include <iostream>
#include <algorithm>
#include <map>
#include <cassert>

using namespace std;

vector<int> arr;
vector<int> original;
int comparisons = 0;
int swaps = 0;
int steps = 0;
int recursionLevel = 0;

void printStep(const string& action, int left, int right, int level) {
    steps++;
    cout << "  Step " << steps << " [Level " << level << "]: " << action;
    cout << " (range [" << left << ".." << right << "])";
    
    cout << " -> [";
    for (int i = left; i <= right && i < static_cast<int>(arr.size()); i++) {
        cout << arr[i];
        if (i < right) cout << ", ";
    }
    cout << "]\n";
}

bool checkArraySorted() {
    for (size_t i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

bool checkPartitionInvariant(int left, int i, int j, int /* right */, int pivot) {
    for (int k = left; k <= i && k < static_cast<int>(arr.size()); k++) {
        if (arr[k] >= pivot) {
            return false;
        }
    }
    
    for (int k = i + 1; k < j && k < static_cast<int>(arr.size()); k++) {
        if (arr[k] < pivot) {
            return false;
        }
    }
    
    return true;
}

bool checkSortedRange(int left, int right) {
    if (arr.empty()) return true;
    for (int i = left; i < right && i < static_cast<int>(arr.size()) - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false;
        }
    }
    return true;
}

bool checkAllElementsInRange(int left, int right) {
    return left >= 0 && right < static_cast<int>(arr.size()) && left <= right;
}

int partition(int left, int right, int level) {
    assert(checkAllElementsInRange(left, right) && "Precondition partition: indices out of bounds");
    
    printStep("Start partitioning", left, right, level);
    
    int pivot = arr[right];
    cout << "    Pivot element: " << pivot << "\n";
    
    int i = left - 1;
    
    for (int j = left; j < right; j++) {
        #ifdef DEBUG_INVARIANTS
        assert(checkPartitionInvariant(left, i, j, right, pivot) && "Loop invariant partition violated");
        #endif
        
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
    
    int pivotIndex = i + 1;
    
    for (int k = left; k < pivotIndex; k++) {
        assert(arr[k] <= arr[pivotIndex] && "Postcondition partition: left element greater than pivot");
    }
    
    for (int k = pivotIndex + 1; k <= right; k++) {
        assert(arr[k] >= arr[pivotIndex] && "Postcondition partition: right element less than pivot");
    }
    
    printStep("Partitioning complete, pivot at position " + to_string(pivotIndex), left, right, level);
    
    return pivotIndex;
}

void quickSort(int left, int right, int level) {
    if (left >= right) {
        assert(checkSortedRange(left, right) && "Base case: array must be sorted");
        return;
    }
    
    assert(left < right && "Precondition quickSort: left must be less than right");
    assert(checkAllElementsInRange(left, right) && "Precondition quickSort: indices out of bounds");
    
    printStep("Sorting subarray", left, right, level);
    
    int pivotIndex = partition(left, right, level);
    
    quickSort(left, pivotIndex - 1, level + 1);
    
    assert(checkSortedRange(left, pivotIndex - 1) && "Invariant: left part must be sorted");
    
    quickSort(pivotIndex + 1, right, level + 1);
    
    assert(checkSortedRange(left, right) && "Postcondition quickSort: range must be sorted");
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
    cout << "TEST " << testNum << ": " << description << "\n";
    cout << "========================================\n";
    
    arr = data;
    original = data;
    comparisons = 0;
    swaps = 0;
    steps = 0;
    recursionLevel = 0;
    
    printArray(original, "Original array");
    
    cout << "\nExecution protocol:\n";
    
    int n = arr.size();
    if (n > 1) {
        quickSort(0, n - 1, 1);
    } else {
        cout << "  Array with " << n << " element - no sorting needed\n";
    }
    
    cout << "\n";
    printArray(arr, "Sorted array   ");
    
    cout << "\nExecution statistics:\n";
    cout << "  Array size: " << n << " elements\n";
    cout << "  Total steps: " << steps << "\n";
    cout << "  Comparisons: " << comparisons << "\n";
    cout << "  Swaps: " << swaps << "\n";
    
    cout << "\nCorrectness verification:\n";
    cout << "  STEP 1: Checking invariants\n";
    cout << "    - Partition invariant: pivot in correct position\n";
    cout << "    - QuickSort invariant: subarrays sorted\n";
    
    cout << "\n  STEP 2: Verification through asserts\n";
    
    bool sorted = verifySorted();
    bool sameElements = verifySameElements();
    
    cout << "    [ASSERT 1] arr[i] <= arr[i+1] for all i...\n";
    assert(sorted && "ASSERT FAIL: Array NOT sorted!");
    cout << "                 PASSED - Array is sorted\n";
    
    cout << "    [ASSERT 2] multiset(original) = multiset(sorted)...\n";
    assert(sameElements && "ASSERT FAIL: Elements lost or added!");
    cout << "                 PASSED - All elements preserved\n";
    
    cout << "\n  STEP 3: Mathematical proof by induction\n";
    cout << "    - Base case (n=1): array with 1 element is sorted\n";
    cout << "    - Inductive step: if subarrays are sorted\n";
    cout << "      and pivot is in correct position\n";
    cout << "      THEN entire array is sorted\n";
    
    cout << "\n  CONCLUSION: ARRAY IS SORTED (proven)\n";
}