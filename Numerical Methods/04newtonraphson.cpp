//Newton Raphson Method
#include <iostream>
#include <cmath>
#include <vector>
#include <iomanip>

using namespace std;

vector<double> ask_coefficients(int degree)
{
    cout << "Enter the coefficients for the polynomial equation:\n";
    vector<double> coefficients(degree + 1);
    for (int i = degree; i >= 0; i--)
    {
        cout << "    x^" << i << " - ";
        cin >> coefficients[i];
    }
    return coefficients;
}

void print_polynomial(const vector<double> &coefficients, int degree, bool is_derivative)
{
    if (is_derivative)
        cout << "Then,\n    f'(x) = ";
    else
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

vector<double> find_derivative(const vector<double> &coefficients, int degree)
{
    vector<double> derivative(degree);
    for (int i = 1; i <= degree; i++)
    {
        derivative[i - 1] = i * coefficients[i];
    }
    return derivative;
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

void newton_raphson(double initial_guess, double tolerance, const vector<double> &f_of_x, const vector<double> &g_of_x, int degree, int max_iterations)
{
    double x0 = initial_guess, x1;
    int step = 0;
    vector<vector<double>> table_data;
    vector<string> headers = {"Iteration", "x0", "f(x0)", "f'(x0)", "x1"};

    cout << "Initial Guess for the Root:\n    x0 = " << x0 << "\n\n";

    do
    {
        ++step;
        double f_val = compute_function(f_of_x, degree, x0);
        double g_val = compute_function(g_of_x, degree - 1, x0);

        if (g_val == 0)
        {
            cout << "\nDerivative undefined for equation at x = " << x0 << endl
                 << endl;
            return;
        }

        x1 = x0 - (f_val / g_val);
        double f1 = compute_function(f_of_x, degree, x1);

        table_data.push_back({static_cast<double>(step), x0, f_val, g_val, x1});

        cout << "Iteration " << step << ":\n";
        cout << "We have x" << step - 1 << " = " << x0 << "\n";
        cout << "And,\n";
        cout << "    f" << step - 1 << " = " << f_val << "\n";
        cout << "    f'" << step - 1 << " = " << g_val << "\n";
        cout << "Then,\n";
        cout << "    x" << step << " = x" << step - 1 << " - (f" << step - 1 << " / f'" << step - 1 << ")\n";
        cout << "       = " << x0 << " - (" << f_val << " / " << g_val << ")\n";
        cout << "       = " << x1 << "\n";

        if (f1 == 0.0)
        {
            cout << "    f(x" << step << ") = f(" << x1 << ") = " << f1 << "\n";
            cout << "As f" << step << " = 0\nHence, Exact root of the equation is:\n    x = " << x1 << "\n\n";
            break;
        }

        if (fabs(f1) < tolerance)
        {
            cout << "Since, |f" << step << "| = |" << f1 << "| = " << fabs(f1) << " < " << tolerance << "\n";
            cout << "Hence, we have got the approximate root with desired tolerance level\n\n";
            break;
        }
        cout << "    f(x" << step << ") = f(" << x1 << ") = " << f1 << "\n\n";
        x0 = x1;

    } while (step < max_iterations);

    print_table(table_data, headers);
    cout << "\nThe approximation to the root is:\n";
    cout << "    x = " << x1 << "\n\n";
}

int main()
{
    cout << "\nNewton-Raphson Method\n\n";
    int degree = 3;
    cout << "Degree of Equation: ";
    cin >> degree;

    vector<double> coeffs = ask_coefficients(degree);
    vector<double> derivative = find_derivative(coeffs, degree);

    double initial_guess = 0.5;
    double tolerance = 0.0001;
    int max_iterations = 10;
    cout << "Initial Guess for the root: ";
    cin >> initial_guess;
    cout << "Input for Tolerance: ";
    cin >> tolerance;
    cout << "Maximum Iterations: ";
    cin >> max_iterations;
    cout << endl;

    print_polynomial(coeffs, degree, false);
    print_polynomial(derivative, degree - 1, true);
    newton_raphson(initial_guess, tolerance, coeffs, derivative, degree, max_iterations);

    return 0;
}