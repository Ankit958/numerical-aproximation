#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

void printColor(const string &text, int colorCode)
{
    cout << "\033[" << colorCode << "m" << text << "\033[0m";
}

void printHeader()
{
    cout << "\033[1;34m";
    cout << "==========================================================\n";
    cout << "     Numerical Ninjas: A Numerical Approximation Tool     \n";
    cout << "==========================================================\n";
    cout << "\033[0m";
}

void printMenu()
{
    cout << "\033[1;32m";
    cout << "Choose the method you want to run:\n";
    cout << "\033[0m";
    cout << "\033[1;36m";
    cout << "1. Bisection Method\n";
    cout << "2. Secant Method\n";
    cout << "3. Regula Falsi Method\n";
    cout << "4. Newton Raphson Method\n";
    cout << "5. Gauss Elimination Method\n";
    cout << "6. Gauss Jordan Method\n";
    cout << "7. Gauss Jacobi Method\n";
    cout << "8. Gauss Seidel Method\n";
    cout << "\033[0m";
    printColor("Enter your choice (1-8): ", 33);
}

int main()
{
    int choice;

    printHeader();
    printColor("\nWelcome to Numerical Ninjas, where we solve equations like a pro!\n", 36);
    printColor("This tool offers various numerical methods to approximate solutions.\n", 36);
    printColor("Select a method from the menu below to get started.\n\n", 36);
    printMenu();

    cin >> choice;

    switch (choice)
    {
    case 1:
        system("01bisection.exe");
        break;
    case 2:
        system("02secant.exe");
        break;
    case 3:
        system("03regulafalsi.exe");
        break;
    case 4:
        system("04newtonraphson.exe");
        break;
    case 5:
        system("05gausselimination.exe");
        break;
    case 6:
        system("06gaussjordan.exe");
        break;
    case 7:
        system("07gaussjacobi.exe");
        break;
    case 8:
        system("08gausssiedel.exe");
        break;
    default:
        printColor("\nInvalid choice! Please run the program again and choose a number between 1 and 8.\n", 31);
        return 0;
    }

    printColor("\nThank you for using Numerical Ninjas. Have a great day!\n\n", 32);

    return 0;
}