#ifndef FIBONACCI_H
#define FIBONACCI_H

#include <cstdint>

struct StepCounter {
    uint64_t steps = 0;
    void reset() { steps = 0; }
};

uint64_t fibIterative(int n, StepCounter& counter);

uint64_t fibMatrixIterative(int n, StepCounter& counter);

uint64_t fibRecursiveLinear(int n, StepCounter& counter);

uint64_t fibRecursiveFast(int n, StepCounter& counter);

void multiplyMatrix(uint64_t F[2][2], const uint64_t M[2][2]);
void powerMatrix(uint64_t F[2][2], int n, StepCounter& counter);

#endif 