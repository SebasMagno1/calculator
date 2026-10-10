
#include <windows.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cstdlib>

using namespace std;

// Control identifiers
#define ID_NUM1       101
#define ID_NUM2       102
#define ID_ADD        201
#define ID_SUB        202
#define ID_MUL        203
#define ID_DIV        204
#define ID_CLEAR      205
#define ID_HISTORY    206
#define ID_HISTORYBOX 207

// Global Windows controls
HWND input1;
HWND input2;
HWND resultLabel;
HWND historyBox;
HWND statusLabel;

// ==================================================
// Calculator class
// ==================================================

class Calculator {
private:
    vector<string> history;
    string filename;

    // Load saved calculations from the file
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

    // Save one calculation to the file
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

    // Read and validate a number from a text field
    bool readNumber(HWND control, double& number) {
        char buffer[256];

        GetWindowTextA(control, buffer, sizeof(buffer));

        string text = buffer;
        stringstream ss(text);
        char extra;

        if (!(ss >> number) || (ss >> extra)) {
            return false;
        }

        return true;
    }

    // Refresh the history list displayed in the window
    void updateHistoryWindow() {
        SendMessageA(
            historyBox, LB_RESETCONTENT, 0, 0
        );

        int i;

        for (i = 0; i < (int)history.size(); i++) {
            SendMessageA(
                historyBox,
                LB_ADDSTRING,
                0,
                (LPARAM)history[i].c_str()
            );
        }
    }

    // Calculate and display the result
    void calculate(int operation, HWND hwnd) {
        double a;
        double b;
        double result = 0;
        string symbol;

        if (!readNumber(input1, a) ||
            !readNumber(input2, b)) {

            MessageBoxA(
                hwnd,
                "Please enter valid numbers in both fields.",
                "Invalid Input",
                MB_OK | MB_ICONWARNING
            );

            return;
        }

        switch (operation) {
            case ID_ADD:
                result = add(a, b);
                symbol = "+";
                break;

            case ID_SUB:
                result = subtract(a, b);
                symbol = "-";
                break;

            case ID_MUL:
                result = multiply(a, b);
                symbol = "*";
                break;

            case ID_DIV:
                if (b == 0) {
                    MessageBoxA(
                        hwnd,
                        "Division by zero is not allowed.",
                        "Calculation Error",
                        MB_OK | MB_ICONERROR
                    );

                    return;
                }

                result = divide(a, b);
                symbol = "/";
                break;

            default:
                return;
        }

        // Format the result
        stringstream output;
        output << setprecision(12) << result;

        string resultText = output.str();

        SetWindowTextA(
            resultLabel, resultText.c_str()
        );

        // Build the history record
        stringstream record;
        record << setprecision(12)
               << a << " " << symbol << " "
               << b << " = " << result;

        // Save the record and refresh the history
        if (saveHistory(record.str())) {
            updateHistoryWindow();

            SetWindowTextA(
                statusLabel,
                "Calculation completed and saved."
            );
        } else {
            SetWindowTextA(
                statusLabel,
                "Result calculated, but file saving failed."
            );

            MessageBoxA(
                hwnd,
                "The result was calculated, but history.txt "
                "could not be updated.",
                "File Error",
                MB_OK | MB_ICONWARNING
            );
        }
    }

    // Clear the input fields
    void clearFields() {
        SetWindowTextA(input1, "");
        SetWindowTextA(input2, "");
        SetWindowTextA(resultLabel, "Result");
        SetWindowTextA(statusLabel, "Ready");

        SetFocus(input1);
    }
};

// Global calculator object
Calculator calculator;

// ==================================================
// Create a Windows control
// ==================================================

HWND createControl(
    HWND parent,
    const char* className,
    const char* text,
    DWORD style,
    int x,
    int y,
    int width,
    int height,
    int id
) {
    return CreateWindowA(
        className,
        text,
        WS_CHILD | WS_VISIBLE | style,
        x, y, width, height,
        parent,
        (HMENU)id,
        GetModuleHandleA(NULL),
        NULL
    );
}

// ==================================================
// Main window procedure
// ==================================================

LRESULT CALLBACK WindowProcedure(
    HWND hwnd,
    UINT message,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (message) {

        case WM_CREATE:
        {
            // Section title
            createControl(
                hwnd, "STATIC",
                "Enter two numbers:",
                SS_LEFT,
                20, 15, 330, 25, 301
            );

            // First number
            createControl(
                hwnd, "STATIC", "First number:",
                SS_LEFT,
                20, 48, 105, 24, 302
            );

            input1 = createControl(
                hwnd, "EDIT", "",
                WS_BORDER | ES_AUTOHSCROLL,
                130, 45, 210, 27, ID_NUM1
            );

            // Second number
            createControl(
                hwnd, "STATIC", "Second number:",
                SS_LEFT,
                20, 83, 105, 24, 303
            );

            input2 = createControl(
                hwnd, "EDIT", "",
                WS_BORDER | ES_AUTOHSCROLL,
                130, 80, 210, 27, ID_NUM2
            );

            // Arithmetic buttons
            createControl(
                hwnd, "BUTTON", "Add (+)",
                BS_PUSHBUTTON,
                20, 120, 150, 35, ID_ADD
            );

            createControl(
                hwnd, "BUTTON", "Subtract (-)",
                BS_PUSHBUTTON,
                190, 120, 150, 35, ID_SUB
            );

            createControl(
                hwnd, "BUTTON", "Multiply (*)",
                BS_PUSHBUTTON,
                20, 163, 150, 35, ID_MUL
            );

            createControl(
                hwnd, "BUTTON", "Divide (/)",
                BS_PUSHBUTTON,
                190, 163, 150, 35, ID_DIV
            );

            // Result area
            createControl(
                hwnd, "STATIC", "Result:",
                SS_LEFT,
                20, 210, 70, 25, 304
            );

            resultLabel = createControl(
                hwnd, "STATIC", "Result",
                SS_LEFT | SS_SUNKEN,
                90, 207, 250, 30, 305
            );

            // History section
            createControl(
                hwnd, "STATIC", "Calculation History:",
                SS_LEFT,
                20, 250, 320, 24, 306
            );

            historyBox = createControl(
                hwnd, "LISTBOX", "",
                WS_BORDER | WS_VSCROLL |
                LBS_NOTIFY | LBS_NOINTEGRALHEIGHT,
                20, 275, 320, 115, ID_HISTORYBOX
            );

            // Bottom buttons
            createControl(
                hwnd, "BUTTON", "Clear",
                BS_PUSHBUTTON,
                20, 405, 150, 32, ID_CLEAR
            );

            createControl(
                hwnd, "BUTTON", "Refresh History",
                BS_PUSHBUTTON,
                190, 405, 150, 32, ID_HISTORY
            );

            // Status message
            statusLabel = createControl(
                hwnd, "STATIC", "Ready",
                SS_LEFT,
                20, 450, 320, 22, 307
            );

            // Display previously saved calculations
            calculator.updateHistoryWindow();

            break;
        }

        case WM_COMMAND:
        {
            int id = LOWORD(wParam);

            switch (id) {
                case ID_ADD:
                case ID_SUB:
                case ID_MUL:
                case ID_DIV:
                    calculator.calculate(id, hwnd);
                    break;

                case ID_CLEAR:
                    calculator.clearFields();
                    break;

                case ID_HISTORY:
                    calculator.updateHistoryWindow();

                    SetWindowTextA(
                        statusLabel,
                        "History refreshed."
                    );
                    break;
            }

            break;
        }

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProcA(
                hwnd, message, wParam, lParam
            );
    }

    return 0;
}

// ==================================================
// Windows application entry point
// ==================================================

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    const char CLASS_NAME[] = "ClassicCalculatorWindow";

    WNDCLASSA wc;
    ZeroMemory(&wc, sizeof(wc));

    wc.lpfnWndProc = WindowProcedure;
    wc.hInstance = hInstance;
    wc.lpszClassName = CLASS_NAME;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = (HBRUSH)(COLOR_BTNFACE + 1);

    if (!RegisterClassA(&wc)) {
        MessageBoxA(
            NULL,
            "Could not register the window class.",
            "Startup Error",
            MB_OK | MB_ICONERROR
        );

        return 1;
    }

    HWND hwnd = CreateWindowA(
        CLASS_NAME,
        "C++ Calculator - Classic Windows",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        390,
        535,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (hwnd == NULL) {
        MessageBoxA(
            NULL,
            "Could not create the application window.",
            "Startup Error",
            MB_OK | MB_ICONERROR
        );

        return 1;
    }

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}

