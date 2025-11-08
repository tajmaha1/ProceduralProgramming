    #include "math_methods.h"
    #include <sstream>
    #include <iomanip>
    #include <cmath>
    #include <cassert>
    
    Result<double> solve(
        std::function<double(double)> f,
        double a,
        double b,
        double eps
    ) {
        Result<double> res = { 0.0, 0, false, "" };
        std::ostringstream protocol;
    
        assert(a < b && "Start of interval must be less than end");
        assert(eps > 0 && "Precision must be positive");
    
        double fa = f(a), fb = f(b);
        assert(fa * fb < 0 && "Function must have different signs at endpoints");
    
        protocol << "=== BISECTION METHOD ===\n";
        protocol << "Interval: [" << a << ", " << b << "]\n";
        protocol << "Precision: " << eps << "\n\n";
    
        double left = a, right = b, mid;
        int steps = 0;
    
        while ((right - left) > eps) {
            mid = (left + right) / 2.0;
            double fmid = f(mid);
    
            steps++;
            protocol << "Step " << steps << ":\n";
            protocol << "  Interval: [" << std::fixed << std::setprecision(6)
                << left << ", " << right << "]\n";
            protocol << "  Midpoint: " << mid << "\n";
            protocol << "  f(midpoint): " << fmid << "\n";
            protocol << "  Length: " << (right - left) << "\n\n";
    
            if (std::abs(fmid) < eps) {
                res.value = mid;
                res.success = true;
                break;
            }
    
            if (f(left) * fmid < 0)
                right = mid;
            else
                left = mid;
        }
    
        res.value = (left + right) / 2.0;
        res.steps = steps;
        res.success = true;
        res.protocol = protocol.str();
    
        return res;
    }
    
    Result<double> integrate(
        std::function<double(double)> f,
        double a,
        double b,
        int n
    ) {
        Result<double> res = { 0.0, 0, false, "" };
        std::ostringstream protocol;
    
        assert(a < b && "Start must be less than end");
        assert(n > 0 && n % 2 == 0 && "Number of intervals must be even");
    
        protocol << "=== SIMPSON'S METHOD ===\n";
        protocol << "Interval: [" << a << ", " << b << "]\n";
        protocol << "Number of divisions: " << n << "\n\n";
    
        double h = (b - a) / n;
        double sum = f(a) + f(b);
    
        protocol << "Step h = " << std::fixed << std::setprecision(6)
            << h << "\n\n";
        protocol << "Computing values:\n";
        protocol << "f(" << a << ") = " << f(a) << "\n";
    
        for (int i = 1; i < n; i += 2) {
            double x = a + i * h;
            double fx = f(x);
            sum += 4 * fx;
            if (i <= 5 || i >= n - 5)
                protocol << "f(" << x << ") * 4 = " << fx << " * 4\n";
        }
    
        if (n > 10) protocol << "...\n";
        for (int i = 2; i < n; i += 2) {
            double x = a + i * h;
            double fx = f(x);
            sum += 2 * fx;
            if (i <= 4 || i >= n - 4)
                protocol << "f(" << x << ") * 2 = " << fx << " * 2\n";
        }
    
        protocol << "f(" << b << ") = " << f(b) << "\n\n";
    
        res.value = (h / 3.0) * sum;
        res.steps = n;
        res.success = true;
        res.protocol = protocol.str();
    
        return res;
    }