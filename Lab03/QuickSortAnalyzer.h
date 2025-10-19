#ifndef QUICKSORT_ANALYZER_H
#define QUICKSORT_ANALYZER_H

#include <vector>
#include <string>

extern std::vector<int> arr;
extern std::vector<int> original;
extern int comparisons;
extern int swaps;
extern int steps;
extern int recursionLevel;

void quickSort(int left, int right, int level);
void printArray(const std::vector<int>& a, const std::string& label);
void printStep(const std::string& action, int left, int right, int level);
bool verifySorted();
bool verifySameElements();
void runTest(std::vector<int> data, int testNum, const std::string& description);

bool checkPartitionInvariant(int left, int i, int j, int right, int pivot);
bool checkSortedRange(int left, int right);
bool checkAllElementsInRange(int left, int right);
bool checkArraySorted();

#endif