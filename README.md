# Overview
A cross-platform calculator application  that used the Shunting Yard Algorithm for order of operations, a Singleton class for processing, wxWidgets for cross platform GUI functionality, and implementation of unit tests for testing core functionality.

# Design
![image](https://user-images.githubusercontent.com/30331999/221715364-4a3adb85-d05f-4360-8946-d84a20294653.png)

# Shunting Yard Algorithm
Order of operations is followed by first translating the algebraic notation of the calculator into reverse polish notation. A problem with this approach was the handling of negative numbers. Specifically, whether a '-' should be treated as a minus symbol or a negate symbol. By testing whether the character to the left of the symbol is an operator, this problem is easily solved.

# Before Running
wxWidgets library should be installed and compiled at C:\wxWidgets

![image](https://user-images.githubusercontent.com/30331999/221719340-819184c5-6ab2-4a40-b5e1-a3090940c50c.png)

Open properties for Visual Studio project

![image](https://user-images.githubusercontent.com/30331999/221719479-9be7dfff-95bf-4830-850e-1b07f7901445.png)

Select C/C++ -> General -> Addition Include Directories

![image](https://user-images.githubusercontent.com/30331999/221719777-986b3a64-57f0-4f03-80d8-28f7f2cd6911.png)

"C:\wxWidgets\include;C:\wxWidgets\include\msvc"

![image](https://user-images.githubusercontent.com/30331999/221719921-e6bec511-1295-4ff0-b83a-6d77c86a9f49.png)

Select Linker -> Additional Library Dependencies

![image](https://user-images.githubusercontent.com/30331999/221720044-64586eaf-358d-415a-af2c-320e9549e8ea.png)

"C:\wxWidgets\lib\vc_lib;C:\wxWidgets\lib\vc_x64_lib"

![image](https://user-images.githubusercontent.com/30331999/221720159-f1081c97-2a1b-4cdb-a1d5-c49fb42e3b4f.png)

Select Linker -> System -> Subsystem

![image](https://user-images.githubusercontent.com/30331999/221720251-65133286-6c09-44bf-af78-e827100fd052.png)

Change from Console to Windows

![image](https://user-images.githubusercontent.com/30331999/221720330-241aedb0-3e0d-440d-91ec-92afd54b9067.png)

Make sure Visual Studio is running in Debug x86

![image](https://user-images.githubusercontent.com/30331999/221719197-ba8d152a-e5e1-47e2-a06b-dfd7386d2cd1.png)
