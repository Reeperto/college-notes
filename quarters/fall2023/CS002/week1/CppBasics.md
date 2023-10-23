---
title: C++ Basics Worksheet
author: Eli Griffiths and Sophie Chen (checked by group 13 and 5)
---

# Declaration and Initialization

1. Give the declaration for two variables called feet and inches. Both variables are of type int and both are to be initialized to zero in the declaration. Use both initialization alternatives.

```cpp
// Normal initialization
int feet = 0;
int inches = 0;

// Alternative initialization
int feet(0);
int inches(0);
```

2. Give the declaration for two variables called count and distance. count is of type int and is initialized to zero. distance is of type double and is initialized to 1.5.

```cpp
int count = 0;
double distance = 1.5;
```

# Assignment

3. Give a C++ statement that will change the value of the variable sum to the sum
of the values in the variables n1 and n2. The variables are all of type int.

```cpp
sum = n1 + n2;
```

4. Give a C++ statement that will increase the value of the variable length by 8.3. The variable length is of type double.

```cpp
length = length + 8.3;
```

5. Give a C++ statement that will change the value of the variable product to its old value multiplied by the value of the variable n. The variables are all of type int.

```cpp
product = product * n;
```

6. Which of the following are valid C++ assignment statements? Assume that i, x, and percent are double variables.

    * A and C are the only valid statements.

# Identifiers and Reserved Words (Keywords)

7. Which of the following are valid identifiers:

    - file23 and New_File

8. Give good variable names for each of the following:

    a) `speed`
    b) `pay_rate`
    c) `max_score`

9. Which of the following is a reserved word (keyword) in C++?

    - `return`, `void`, and `int`

10. What is the difference between a keyword and a user-defined identifier?

    - A keyword has a special and unchanging meaning in C++
    - A user-defined identifier is a name made up by a programmer that is not a part of the language that has meaning or usage defined by the programmer

# Input and Output

11. Give an output statement that will produce the following message on the screen: 

> The answer to the question of
>
> Life, the Universe, and Everything is 42.

```cpp
cout << "The answer to the question of\nLife, the Universe, and Everything is 42.\n";
```

12. Give an input statement that will fill the variable the_number (of type int) with a number typed in at the keyboard. Precede the input statement with a prompt statement asking the user to enter a whole number.

```cpp
cout << "Please enter a whole number:\n";
cin >> the_number;
```

13. Give an output statement that produces the new-line character and a tab character.

```cpp
cout << "\n\t";
```

14. What is the output of the following program lines when embedded in a correct program that declares all variables to be of type char?
```cpp
a = 'b';
b = 'c';
c = a;
cout << a << b  << 'c';
```
The program lines would output:

> bcc

# Math in C++

15. Convert each of the following mathematical formulas to a C++ expression:
    
    a.) $3x$
    ```cpp
    3 * x
    ```
    b.) $3x + y$
    ```cpp
    3 * x + y
    ```
    c.) $\cfrac{x+y}{2}$
    ```cpp
    (x + y) / 2
    ```
    d.) $7z^3 + 2$
    ```cpp
    7 * ( z * z * z ) + 2
    ```

16. Evaluate: 30-5/2.0

    > 27.5

17. Evaluate: 19+7%3-4

    > 16

# Writing Simple Programs

18. Write a complete C++ program that writes the phrase “Hello world” to the screen. The program does nothing else.

```cpp
#include <iostream>
using namespace std;

int main()
{
    cout << "Hello world\n";
    return 0;   
}
```

19. Write a complete C++ program that reads in two whole numbers and outputs their sum. Be sure to prompt for input, echo input, and label all output.

```cpp
!include "basics19.cpp"
```

20. Write a program that contains statements that output the value of five or six variables that have been declared, but not initialized. Compile and run the program. What is the output? Check the program on a different environment or with another student. Do you get the same results? Explain.

```cpp
!include "basics20.cpp"
```

Running the program 3 times results in:

```txt
Boolean: 0
Integer: 1
Double : 2.14438e-314
Char   :
String :
```

```txt
Boolean: 0
Integer: 1
Double : 2.14584e-314
Char   :
String :
```

```txt
Boolean: 0
Integer: 1
Double : 2.15885e-314
Char   :
String :
```

The value of the double is different between successive runs. This is because reading the value of an uninitialized variable results in undefined behavior due to it reading leftover 1's and 0's left in the memory.
