//secant method
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>
using namespace std;

vector<double> ask_coefficients(int degree)
{
    cout << "Enter the coefficient for: \n";
    vector<double> coefficients(degree + 1);
    for (int i = degree; i >= 0; i--)
    {
        cout << "    x^" << i << " - ";
        cin >> coefficients[i];
    }
    return coefficients;
}

double compute_function(const vector<double> &coefficients, int degree, double value)
{
    double ans = 0;
    for (int i = 0; i <= degree; i++)
    {
        ans += coefficients[degree - i] * pow(value, degree - i);
    }
    return ans;
}

void print_polynomial(const vector<double> &coefficients, int degree)
{
    cout << "Let\n    f(x) = ";
    for (int i = degree; i >= 0; i--)
    {
        if (coefficients[i] != 0)
        {
            if (i != degree && coefficients[i] > 0)
                cout << " + ";
            if (coefficients[i] < 0)
                cout << " - ";
            if (fabs(coefficients[i]) != 1 || i == 0)
                cout << fabs(coefficients[i]);
            if (i > 0)
                cout << "x";
            if (i > 1)
                cout << "^" << i;
        }
    }
    cout << "\n";
}

void print_table(const vector<vector<double>> &table_data)
{
    const int width = 15;
    auto print_line = [](int num_cols, int width)
    {
        cout << "+";
        for (int i = 0; i < num_cols; ++i)
        {
            cout << setw(width) << setfill('-') << ""
                 << "+";
        }
        cout << setfill(' ') << endl;
    };
    cout << "Summary Table:\n";
    print_line(7, width);
    cout << "|" << setw(width) << left << "Iteration"
         << "|" << setw(width) << left << "x0"
         << "|" << setw(width) << left << "x1"
         << "|" << setw(width) << left << "x2"
         << "|" << setw(width) << left << "f(x0)"
         << "|" << setw(width) << left << "f(x1)"
         << "|" << setw(width) << left << "f(x2)"
         << "|\n";
    print_line(7, width);
    for (const auto &row : table_data)
    {
        cout << "|" << setw(width) << left << row[0]
             << "|" << setw(width) << left << row[1]
             << "|" << setw(width) << left << row[2]
             << "|" << setw(width) << left << row[3]
             << "|" << setw(width) << left << row[4]
             << "|" << setw(width) << left << row[5]
             << "|" << setw(width) << left << row[6] << "|\n";
        print_line(7, width);
    }
}

void secant_method(const vector<double> &coefficients, int degree, double x0, double x1, int ITERATIONS, double tolerance)
{
    double x2;
    vector<vector<double>> table_data;
    for (int step = 1; step <= ITERATIONS; step++)
    {
        double f0 = compute_function(coefficients, degree, x0);
        double f1 = compute_function(coefficients, degree, x1);
        x2 = x1 - (f1 * (x1 - x0)) / (f1 - f0);
        double f2 = compute_function(coefficients, degree, x2);

        table_data.push_back({static_cast<double>(step), x0, x1, x2, f0, f1, f2});

        cout << "Iteration " << step << ":\n";
        cout << "We have x" << step - 1 << " = " << x0 << " and x" << step << " = " << x1;
        cout << "\nAlso, f" << step - 1 << " = " << f0 << " and f" << step << " = " << f1;
        cout << "\nThen,\n";
        cout << "    x" << step + 1 << " = x" << step << " - (f(x" << step << ") * (x" << step << " - x" << step - 1 << ")) / (f(x" << step << ") - f(x" << step - 1 << "))\n";
        cout << "       = " << x1 << " - (" << f1 << " * (" << x1 << " - " << x0 << ")) / (" << f1 << " - " << f0 << ")\n";
        cout << "       = " << x2 << "\n";
        cout << "    f(x" << step + 1 << ") = f(" << x2 << ") = " << f2 << "\n\n";
        x0 = x1;
        x1 = x2;
        if (fabs(x1 - x0) <= tolerance)
        {
            break;
        }
    }
    print_table(table_data);
    cout << endl;
    cout << "The approximation to the root is:\n";
    cout << "    x = " << x2 << endl
         << endl;
}

int main()
{
    cout << "\n6Secant Method\n\n";
    int degree = 3;
    cout << "Degree of Equation: ";
    cin >> degree;

    vector<double> coeffs = ask_coefficients(degree);
    double LBP = 0;
    double UBP = 1;
    cout << "Input for Root Interval: \n";
    cout << "    Lower Boundary Point: ";
    cin >> LBP;
    cout << "    Upper Boundary Point: ";
    cin >> UBP;
    double Error_Tolerance = 0.001;
    cout << "Error Tolerance: ";
    cin >> Error_Tolerance;
    int maxIterations = 10;
    cout << "Iteration count: ";
    cin >> maxIterations;
    cout << endl;
    print_polynomial(coeffs, degree);
    cout << "For x0 = " << LBP << " and x1 = " << UBP << ":\n";
    cout << "    f(x0) = " << compute_function(coeffs, degree, LBP) << " and f(x1) = " << compute_function(coeffs, degree, UBP) << "\n\n";
    secant_method(coeffs, degree, LBP, UBP, maxIterations, Error_Tolerance);
    return 0;
}