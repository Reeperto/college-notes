---
title: Loops Worksheet II
author: Eli Griffiths (checked by groups 5 and )
---

# Code Trace - Nested Loops

## #1
```cpp
for (int k = 1; k <= 2; k++)
   for (int m = 1 ; m <= 3; m++)
      cout << k << ' ' << m << endl;

// -- OUTPUT --
1 1
1 2
1 3
2 1
2 2
2 3
```

## #2
```cpp
for (int d = 6; d >= 4; d--)
   for (int e = 2; e <= 4; e++)
      cout << d << ' ' << e << endl;

// -- OUTPUT --
6 2
6 3
6 4
5 2
5 3
5 4
4 2
4 3
4 4
```

## #3
```cpp
x = 1;
while (x <= 5)
{
    sum = 0;
    y = 1;
    while (y <= x)
    {
        sum += y;
        y++;
    }
    cout << sum << ' ';
    x++;
}

// -- OUTPUT --
1 3 6 10 15
```

## #4
```cpp
for (i = 1 ; i <= 5 ; i++)
{
   cout << i << endl;
   for (j = i ; j >= 1 ; j -= 2)
      cout << j << endl;
}

// -- OUTPUT --
1
1
2
2
3
3
1
4
4
2
5
5
3
1
```

## #5
```cpp
for (i = 1 ; i <= 3 ; i++)
    for (j = 1 ; j <= 3 ; j++)
    {
        for (k = i ; k <= j ; k++)
            cout << i << j << k << endl;
        cout << endl;
    }

// -- OUTPUT --
111

121
122

131
132
133


222

232
233



333

```

## #6
```cpp
for (i = 3 ; i > 0 ; i--)
   for (j = 1 ; j <= i ; j++)
      for (k = i ; k >= j ; k--)
         cout << i << j << k << endl;

// -- OUTPUT --
313
312
311
323
322
333
212
211
222
111
```

\newpage

# Nested Loops
7. Write statements that will read numbers and print out the sum of  the numbers. The program should stop when the user enters -999, or after reading 5 numbers, whichever comes first.

```cpp
int in_count = 0;
int sum = 0;
int number;

while (in_count < 5) {
	cin >> number;

	if (number == -999) {
		break;
	}

	sum += number;
	in_count++;
}

cout << sum << '\n';
```

8. Test your program from problem 7 with the following data: 
    ```10 20 30 -999```

```
60
```

9. Test your program from problem 7 with the following data:
    ```10 20 30 40 50 60 70```

```
150
```

10. Write a program segment using nested loops to create the following output:
```
*
**
***
****
*****
******
*******
********
*********
```

```cpp
for (int i = 1; i <= 9; ++i) {
	for (int j = 0; j < i; ++j) {
		cout << '*';
	}
	cout << '\n';
}
```

11. Write a program segment using nested loops to create the following output:

```
    *
   ***
  *****
 *******
*********
```

```cpp
int max_width = 9;

for (int i = 1; i <= max_width; i += 2) {
	for (int j = 0; j < (max_width - i) / 2; j++) {
		cout << ' ';
	}

	for (int k = 0; k < i; k++) {
		cout << '*';
	}

	cout << '\n';
}
```

# Input Validation
12. Prompt the user to enter y or n. If the user enters an invalid character, keep re-prompting until a valid character is entered. Use a while loop.

```cpp
char prompt;
while (prompt != 'y' && prompt != 'n')
{
    cout << "Please enter 'y' or 'n': ";
    cin >> prompt;
}
```

13. Redo problem 12 with a do-while loop.
```cpp
char prompt;
do {
    cout << "Please enter 'y' or 'n': ";
    cin >> prompt;
} while (prompt != 'y' && prompt != 'n');
```
