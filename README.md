# C++ Console Calculator

## Overview

I developed a console calculator using C++ to improve my programming skills and learn more about object-oriented programming. The program allows users to perform basic mathematical operations, including addition, subtraction, multiplication, and division.

The calculator also includes input validation, error handling for division by zero, and a calculation history feature. It saves previous calculations in a text file called `history.txt`, so users can review their results later.

My purpose for creating this software was to practice C++ syntax and understand how different programming concepts work together. Through this project, I learned how to use variables, expressions, conditional statements, loops, functions, classes, vectors, and file input and output. I also practiced handling invalid user input and organizing code into reusable methods.



## Development Environment

I used the following tools to develop this software:

- **IDE:** Dev-C++
- **Compiler:** A C++ compiler compatible with Dev-C++
- **Language:** C++
- **File format:** `history.txt` for saving calculation records

The program uses standard C++ libraries:

- `iostream` for console input and output.
- `string` for working with text.
- `vector` for storing calculation history in memory.
- `fstream` for reading and writing the history file.
- `sstream` for validating user input and formatting calculation records.
- `iomanip` for controlling the precision of numerical output.

I used a `Calculator` class to organize the program's functionality. The class contains methods for mathematical operations, displaying history, validating input, and saving calculations. A `while` loop keeps the menu running until the user chooses to exit, and a `switch` statement selects the mathematical operation.

## Useful Websites

- [C++ Reference](https://en.cppreference.com/w/cpp.html) — Information about C++ syntax, functions, classes, and standard libraries.
- [W3Schools C++ Tutorial](https://www.w3schools.com/cpp/) — Tutorials and examples for learning C++ fundamentals.
- [GeeksforGeeks C++ Programming](https://www.geeksforgeeks.org/c-plus-plus/) — Examples of object-oriented programming, vectors, and file handling.
- [LearnCpp.com](https://www.learncpp.com/) — Lessons about C++ programming concepts and best practices.

## Future Work

- Add more mathematical operations, such as percentages, powers, and square roots.
- Improve the user interface and make the menu easier to navigate.
- Add an option to clear the calculation history.
- Improve error handling for unusual numerical values and file access problems.
- Add unit tests to verify that each mathematical operation works correctly.
