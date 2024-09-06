// regula falsi method
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

vector<int> ask_coefficients(int degree)
{
    cout << "Enter the coefficients for the polynomial equation:\n";
    vector<int> coefficients(degree + 1);
    for (int i = degree; i >= 0; i--)
    {
        cout << "    x^" << i << " - ";
        cin >> coefficients[i];
    }
    return coefficients;
}

void print_polynomial(const vector<int> &coefficients, int degree)
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

double compute_function(const vector<int> &coefficients, int degree, double value)
{
    double ans = 0;
    for (int i = 0; i <= degree; i++)
    {
        ans += coefficients[degree - i] * pow(value, degree - i);
    }
    return ans;
}

void print_table(const vector<vector<double>> &table_data, const vector<string> &headers)
{
    cout << "Summary Table:\n";
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

    print_line(headers.size(), width);
    cout << "|";
    for (const auto &header : headers)
    {
        cout << setw(width) << left << header << "|";
    }
    cout << "\n";
    print_line(headers.size(), width);

    for (const auto &row : table_data)
    {
        cout << "|";
        for (const auto &elem : row)
        {
            cout << setw(width) << left << elem << "|";
        }
        cout << "\n";
        print_line(headers.size(), width);
    }
}

void regula_falsi(int degree, const vector<int> &coefficients, int iterations, double x0, double x1, double tolerance)
{
    if (compute_function(coefficients, degree, x0) * compute_function(coefficients, degree, x1) > 0)
    {
        cout << "The provided interval does not bracket the root.\n";
        return;
    }

    double x2;
    double prev_root = x1;
    int step = 0;
    vector<vector<double>> table_data;
    vector<string> headers = {"Iteration", "x0", "x1", "x2", "f(x0)", "f(x1)", "f(x2)"};
    do
    {
        ++step;
        double f0 = compute_function(coefficients, degree, x0);
        double f1 = compute_function(coefficients, degree, x1);
        double first_exp = (x1 - x0) / (f1 - f0);

        x2 = x1 - (f1 * first_exp);
        double f2 = compute_function(coefficients, degree, x2);

        table_data.push_back({static_cast<double>(step), x0, x1, x2, f0, f1, f2});

        cout << "Iteration " << step << ":\n";
        cout << "We have x" << step - 1 << " = " << x0 << " and x" << step << " = " << x1;
        cout << "\nAlso, f" << step - 1 << " = " << f0 << " and f" << step << " = " << f1;
        cout << "\nThen,\n";
        cout << "    x" << step + 1 << " = x" << step << " - (f(x" << step << ") * (x" << step << " - x" << step - 1 << ")) / (f(x" << step << ") - f(x" << step - 1 << "))\n";
        cout << "       = " << x1 << " - (" << f1 << " * (" << x1 << " - " << x0 << ")) / (" << f1 << " - " << f0 << ")\n";
        cout << "       = " << x2 << "\n";

        if (f2 == 0.0)
        {
            cout << "Since, f(x" << step + 1 << ") = f(" << x2 << ") = " << f2 << "\n";
            cout << "As f" << step + 1 << " = 0\nHence, Exact root of the equation is:\n    x = " << x2 << "\n\n";
            break;
        }

        if (fabs(x2 - prev_root) < tolerance)
        {
            cout << "Since,\n    |" << x2 << " - " << prev_root << "| = " << fabs(x2 - prev_root) << " < " << tolerance;
            cout << "\nHence, we have got the root with desired tolerance level\n\n";
            break;
        }
        prev_root = x2;
        cout << "Since, f(x" << step + 1 << ") = f(" << x2 << ") = " << f2 << "\n";

        if ((f0 > 0 && f2 < 0) || (f0 < 0 && f2 > 0))
        {
            cout << "And f" << step - 1 << ".f" << step + 1 << " < 0\n";
            x1 = x2;
            cout << "Thus, Root lies in the interval (" << x0 << ", " << x1 << ")\n\n";
        }
        else
        {

            cout << "And f" << step << ".f" << step + 1 << " < 0\n";
            x0 = x2;
            cout << "Thus, Root lies in the interval (" << x0 << ", " << x1 << ")\n\n";
        }
    } while (step < iterations && fabs(compute_function(coefficients, degree, x2)) > 1e-6);

    print_table(table_data, headers);
    cout << "\nThe approximation to the root is:\n ";
    cout << "    x = " << x2 << "\n\n";
}

int main()
{
    cout << "\nRegula-Falsi Method\n\n";
    int degree = 3;
    cout << "Degree of Equation: ";
    cin >> degree;

    vector<int> coeffs = ask_coefficients(degree);
    double LBP = 0;
    double UBP = 1;
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
    cout << endl;
    print_polynomial(coeffs, degree);
    cout << "For x0 = " << LBP << " and x1 = " << UBP << ":\n";
    cout << "    f(x0) = " << compute_function(coeffs, degree, LBP) << " and f(x1) = " << compute_function(coeffs, degree, UBP) << "\n";
    cout << "Since,\n    f(x0).f(x1) < 0\nRoot lies in the interval (" << LBP << ", " << UBP << ")\n\n";
    regula_falsi(degree, coeffs, maxIterations, LBP, UBP, Error_Tolerance);

    return 0;
}