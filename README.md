# C++ Polymorphism Example

This project is created for educational purposes only.  
The code might be interesting for C and C++ developers, who wonders how C++ classes really works behind the C++ syntax.  
For example, it might help some developers to understand, what the key word *virtual* does.

The project's goal is to show the concept, how one of the basic object-oriented
programming (OOP) principles, a polymorphism, can work under the hood.

The example is represented by two code pieces.  
The first one (**oop_cpp**) is written in C++ and contains several polymorphic classes.  
The second one (**oop_c**) is written in pure C. The represents the same program as the first one does.
It shows, which mechanisms are automatically created during the compilation of C++ classes (simplified, of course).

Compilation of the C++ example:
```bash
cd oop_cpp
mkdir -p build && cd build
cmake ..
cmake --build .
# The result executable is oop_cpp
```
Compilation of the C example:
```bash
cd oop_c
mkdir -p build && cd build
cmake ..
cmake --build .
# The result executable is oop_c
```

Barashkov A.A, 2020