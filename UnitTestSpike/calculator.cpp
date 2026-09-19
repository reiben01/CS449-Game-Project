#include "pch.h"
#include "calculator.h"

int Calculator::Add(int a, int b) const { return a + b; }
int Calculator::Subtract(int a, int b) const { return a - b; }
int Calculator::Multiply(int a, int b) const { return a * b; }
bool Calculator::IsEven(int n) const { return n % 2 == 0; }