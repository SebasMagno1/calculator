
#include <iostream>

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;

class Calculator {
private:
    vector<string> history;
    string filename;

    // Load previous calculations from a file
    void loadHistory() {
        ifstream file(filename.c_str());
        string line;

        if (file.is_open()) {
            while (getline(file, line)) {
                history.push_back(line);
            }

            file.close();
        }
    }

    // Save a calculation to a file
    bool saveHistory(const string& record) {
        ofstream file(filename.c_str(), ios::app);

        if (!file.is_open()) {
            return false;
        }

        file << record << endl;
        file.close();

        if (!file) {
            return false;
        }

        history.push_back(record);
        return true;
    }

    // Read and validate a number
    double readNumber(const string& message) {
        string input;
        double number;

        while (true) {
            cout << message;
            getline(cin, input);

            stringstream ss(input);
            char extra;

            if ((ss >> number) && !(ss >> extra)) {
                return number;
            }

            cout << "Invalid input. Please enter a valid number."
                 << endl;
        }
    }

public:
    // Constructor
    Calculator() {
        filename = "history.txt";
        loadHistory();
    }

    // Arithmetic functions
    double add(double a, double b) {
        return a + b;
    }

    double subtract(double a, double b) {
        return a - b;
    }

    double multiply(double a, double b) {
        return a * b;
    }

    double divide(double a, double b) {
        return a / b;
    }

    // Perform a calculation
    void calculate(int choice) {
        double num1 = readNumber("Enter the first number: ");
        double num2 = readNumber("Enter the second number: ");
        double result = 0;
        string symbol;

        switch (choice) {
            case 1:
                result = add(num1, num2);
                symbol = "+";
                break;

            case 2:
                result = subtract(num1, num2);
                symbol = "-";
                break;

            case 3:
                result = multiply(num1, num2);
                symbol = "*";
                break;

            case 4:
                if (num2 == 0) {
                    cout << "Error: Division by zero is not allowed."
                         << endl;
                    return;
                }

                result = divide(num1, num2);
                symbol = "/";
                break;

            default:
                cout << "Invalid operation." << endl;
                return;
        }

        // Display the result
        cout << "Result: " << setprecision(12)
             << result << endl;

        // Create a history record
        stringstream record;

        record << setprecision(12)
               << num1 << " " << symbol << " "
               << num2 << " = " << result;

        // Save the calculation
        if (saveHistory(record.str())) {
            cout << "Calculation saved to history.txt."
                 << endl;
        } else {
            cout << "Warning: Could not save the history file."
                 << endl;
        }
    }

    // Display calculation history
    void showHistory() {
        cout << endl;
        cout << "========== CALCULATION HISTORY =========="
             << endl;

        if (history.empty()) {
            cout << "No calculations recorded yet." << endl;
        } else {
            for (size_t i = 0; i < history.size(); i++) {
                cout << i + 1 << ". "
                     << history[i] << endl;
            }
        }

        cout << "=========================================" << endl;
    }

    // Display the menu and run the application
    void run() {
        string input;
        int choice;

        while (true) {
            cout << endl;
            cout << "================================" << endl;
            cout << "       C++ CALCULATOR           " << endl;
            cout << "================================" << endl;
            cout << "1. Addition (+)" << endl;
            cout << "2. Subtraction (-)" << endl;
            cout << "3. Multiplication (*)" << endl;
            cout << "4. Division (/)" << endl;
            cout << "5. View History" << endl;
            cout << "0. Exit" << endl;
            cout << "================================" << endl;
            cout << "Choose an option: ";

            getline(cin, input);

            stringstream ss(input);
            char extra;

            if (!(ss >> choice) || (ss >> extra)) {
                cout << "Invalid input. Enter a menu number."
                     << endl;
                continue;
            }

            if (choice == 0) {
                cout << "Thank you for using the calculator!"
                     << endl;
                break;
            } else if (choice >= 1 && choice <= 4) {
                calculate(choice);
            } else if (choice == 5) {
                showHistory();
            } else {
                cout << "Invalid option. Please try again."
                     << endl;
            }
        }
    }
};

int main() {
    Calculator calculator;
    calculator.run();

    return 0;
}

