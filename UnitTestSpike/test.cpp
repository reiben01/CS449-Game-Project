#include "pch.h"
#include "gtest/gtest.h"
#include "calculator.h"

TEST(CalculatorTest, AddsTwoPositiveNumbers) {
	Calculator calc;
	EXPECT_EQ(calc.Add(2, 3), 5);
}

TEST(CalculatorTest, SubtractsCorrectly) {
	Calculator calc;
	EXPECT_EQ(calc.Subtract(10, 4), 6);
}

TEST(CalculatorTest, MultipliesCorrectly) {
	Calculator calc;
	EXPECT_EQ(calc.Multiply(6, 7), 42);
}

TEST(CalculatorTest, IdentifiesEvenAndOddNumbers) {
	Calculator calc;
	EXPECT_TRUE(calc.IsEven(4));
	EXPECT_FALSE(calc.IsEven(7));
}