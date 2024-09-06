//bisection method
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

void print_equation(const vector<double> &coefficients, int degree)
{
    cout << "\nLet\n    f(x) = ";
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

double compute_function(const vector<double> &coefficients, int degree, double value)
{
    double ans = 0;
    for (int i = 0; i <= degree; i++)
    {
        ans += coefficients[degree - i] * pow(value, degree - i);
    }
    return ans;
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
         << "|" << setw(width) << left << "a"
         << "|" << setw(width) << left << "b"
         << "|" << setw(width) << left << "c"
         << "|" << setw(width) << left << "f(a)"
         << "|" << setw(width) << left << "f(b)"
         << "|" << setw(width) << left << "f(c)"
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

void bisection_method(int degree, const vector<double> &coefficients, double tolerance, double a, double b, int maxIteration)
{
    double c;
    int iteration = 0;
    vector<vector<double>> table_data;
    do
    {
        if (iteration == maxIteration)
        {
            break;
        }
        ++iteration;
        c = (a + b) / 2.0;

        double A = compute_function(coefficients, degree, a);
        double B = compute_function(coefficients, degree, b);
        double C = compute_function(coefficients, degree, c);

        table_data.push_back({static_cast<double>(iteration),
                              a, b, c, A, B, C});

        cout << "Iteration " << iteration << ":\n";
        cout << "Let a" << iteration - 1 << " = " << a << " and b" << iteration - 1 << " = " << b;
        cout << "\nThen,\n";
        cout << "    c" << iteration << " = (a" << iteration - 1 << " + b" << iteration - 1 << ") / 2 = (" << a << " + " << b << ") / 2 = " << c << "\n";
        cout << "Since, f(c" << iteration << ") = f(" << c << ") = " << C;

        if (C == 0.0)
        {
            cout << "\nAs f(c) = 0\nHence, Exact root of the equation is:\n    x = " << c << "\n\n";
            break;
        }
        else if ((A > 0 && C < 0) || (A < 0 && C > 0))
        {
            cout << "\nAnd f(a).f(c) < 0\n";
            b = c;
            cout << "Thus, Root lies in the interval (" << a << ", " << b << ")\n\n";
        }
        else
        {
            cout << "\nAnd f(b).f(c) < 0\n";
            a = c;
            cout << "Thus, Root lies in the interval (" << a << ", " << b << ")\n\n";
        }
    } while (fabs(b - a) / 2.0 > tolerance);
    print_table(table_data);
    cout << endl;
    cout << "The approximation to the root is:\n";
    cout << "    x = (" << a << " + " << b << ") / 2 = " << (a + b) / 2 << endl
         << endl;
}

int main()
{
    cout << "\nBisection Method\n\n";
    int degree = 3;
    cout << "Degree of Equation: ";
    cin >> degree;
    double LBP = 0;
    double UBP = 1;
    vector<double> coeffs = ask_coefficients(degree);
    cout << "Input for Root Interval: \n";
    cout << "    Lower Boundary Point: ";
    cin >> LBP;
    cout << "    Upper Boundary Point: ";
    cin >> UBP;
    while (compute_function(coeffs, degree, LBP) * compute_function(coeffs, degree, UBP) > 0)
    {
        cout << "\nRoot does not lie in the provided interval!\n";
        cout << "Input for Correct Root Interval: \n";
        cout << "    Lower Boundary Point: ";
        cin >> LBP;
        cout << "    Upper Boundary Point: ";
        cin >> UBP;
    }
    double Error_Tolerance = 0.001;
    cout << "Error Tolerance: ";
    cin >> Error_Tolerance;
    int maxIterations = 10;
    cout << "Iteration count: ";
    cin >> maxIterations;
    print_equation(coeffs, degree);
    cout << "For a = " << LBP << " and b = " << UBP << ":\n";
    cout << "    f(a) = " << compute_function(coeffs, degree, LBP) << " and f(b) = " << compute_function(coeffs, degree, UBP);
    cout << "\nSince,\n    f(a).f(b) < 0\nRoot lies in the interval (" << LBP << ", " << UBP << ")\n\n";
    bisection_method(degree, coeffs, Error_Tolerance, LBP, UBP, maxIterations);
    return 0;
}