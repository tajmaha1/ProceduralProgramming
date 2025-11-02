#include "fibonacci.h"

uint64_t fibIterative(int n, StepCounter& counter) {
    counter.reset();
    
    if (n <= 1) {
        counter.steps = 1;
        return n;
    }
    
    uint64_t prev = 0, curr = 1;
    
    for (int i = 2; i <= n; ++i) {
        uint64_t next = prev + curr;
        prev = curr;
        curr = next;
        counter.steps++;
    }
    
    return curr;
}

void multiplyMatrix(uint64_t F[2][2], const uint64_t M[2][2]) {
    uint64_t x = F[0][0] * M[0][0] + F[0][1] * M[1][0];
    uint64_t y = F[0][0] * M[0][1] + F[0][1] * M[1][1];
    uint64_t z = F[1][0] * M[0][0] + F[1][1] * M[1][0];
    uint64_t w = F[1][0] * M[0][1] + F[1][1] * M[1][1];
    
    F[0][0] = x;
    F[0][1] = y;
    F[1][0] = z;
    F[1][1] = w;
}

void powerMatrix(uint64_t F[2][2], int n, StepCounter& counter) {
    if (n <= 1) return;
    
    uint64_t M[2][2] = {{1, 1}, {1, 0}};
    powerMatrix(F, n / 2, counter);
    multiplyMatrix(F, F);
    counter.steps++;
    
    if (n % 2 != 0) {
        multiplyMatrix(F, M);
        counter.steps++;
    }
}

uint64_t fibMatrixIterative(int n, StepCounter& counter) {
    counter.reset();
    
    if (n <= 1) {
        counter.steps = 1;
        return n;
    }
    
    uint64_t F[2][2] = {{1, 1}, {1, 0}};
    powerMatrix(F, n - 1, counter);
    
    return F[0][0];
}

static uint64_t fibRecHelper(int n, uint64_t prev, uint64_t curr, StepCounter& counter) {
    counter.steps++;
    
    if (n == 0) return prev;
    if (n == 1) return curr;
    return fibRecHelper(n - 1, curr, prev + curr, counter);
}

uint64_t fibRecursiveLinear(int n, StepCounter& counter) {
    counter.reset();
    return fibRecHelper(n, 0, 1, counter);
}

static uint64_t fibFastHelper(int n, StepCounter& counter) {
    counter.steps++;
    
    if (n <= 1) return n;
    if (n == 2) return 1;
    
    if (n % 2 == 0) {
        uint64_t k = n / 2;
        uint64_t fk = fibFastHelper(k, counter);
        uint64_t fk1 = fibFastHelper(k - 1, counter);
        return fk * (2 * fk1 + fk);
    } else {
        uint64_t k = (n + 1) / 2;
        uint64_t fk = fibFastHelper(k, counter);
        uint64_t fk1 = fibFastHelper(k - 1, counter);
        return fk * fk + fk1 * fk1;
    }
}

uint64_t fibRecursiveFast(int n, StepCounter& counter) {
    counter.reset();
    return fibFastHelper(n, counter);
}