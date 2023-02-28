# Overview
A cross-platform calculator application  that used the Shunting Yard Algorithm for order of operations, a Singleton class for processing, wxWidgets for cross platform GUI functionality, and implementation of unit tests for testing core functionality.

# Design
![image](https://user-images.githubusercontent.com/30331999/221715364-4a3adb85-d05f-4360-8946-d84a20294653.png)

# Shunting Yard Algorithm
Order of operations is followed by first translating the algebraic notation of the calculator into reverse polish notation. A problem with this approach was the handling of negative numbers. Specifically, whether a '-' should be treated as a minus symbol or a negate symbol. By testing whether the character to the left of the symbol is an operator, this problem is easily solved.
