#include <gtest/gtest.h>
#include "Arithmetic.h"
#include "Stack.h"

TEST(RPN, empty_string)
{
	char act[] = "";
	EXPECT_NO_THROW(Arithmetic str(act));
}

TEST(RPN, incorrect_brackets)
{
	char act[] = "(4+(5)-3";
	EXPECT_ANY_THROW(Arithmetic str(act));
}

TEST(RPN, incorrect_module_sign_and_brackets)
{
	char act[] = "(4+|5)-3|";
	EXPECT_ANY_THROW(Arithmetic str(act));
}

TEST(RPN, throw_if_first_symbol_is_operator)
{
	char act[] = "+3-2";
	EXPECT_ANY_THROW(Arithmetic str(act));
}

TEST(RPN, correct_RPN)
{
	char act[] = "1+|(2-3)*4|/5^6";
	char exp[] = "1 2 3 - 4 * || 5 6 ^ / +";
	Arithmetic str(act);
	char *RPN = str.getRPN();
	int i = 0;
	while (RPN[i++] != '\0')
		EXPECT_TRUE(exp[i] == RPN[i]);
}

TEST(Calculation, not_enough_operands_for_operation)
{
	char act[] = "4+";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	EXPECT_ANY_THROW(str.calculation(RPN, 0, 2););
}

TEST(Calculation, can_use_variables)
{
	const int n = 2;

	Variable v[n];
	v[0].name = 'x';
	v[0].value = 2;

	v[1].name = 'y';
	v[1].value = 3;

	char act[] = "(x+y)^2";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double res = str.calculation(RPN, v, n);

	EXPECT_EQ(res, 25);
}

TEST(Calculation, unknown_variable)
{
	const int n = 1;

	Variable v[n];
	v[0].name = 'x';
	v[0].value = 10;

	char act[] = "|y|^2";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	EXPECT_ANY_THROW(str.calculation(RPN, v, n));
}

TEST(Calculation, operation_addition)
{
	char act[] = "4+5";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, 9);
}

TEST(Calculation, operation_subtraction)
{
	char act[] = "4-5";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, -1);
}

TEST(Calculation, operation_mult)
{
	char act[] = "4*5";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, 20);
}

TEST(Calculation, operation_div)
{
	char act[] = "4/5";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, 0.8);
}

TEST(Calculation, operation_pow)
{
	char act[] = "4^5";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, 1024);
}

TEST(Calculation, double_pow)
{
	char act[] = "4^3^2";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, pow(4,9));
}

TEST(Calculation, double_pow_with_brackets)
{
	char act[] = "(4^3)^2";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, pow(64, 2));
}

TEST(Calculation, operation_module)
{
	char act[] = "|1-3|";
	Arithmetic str(act);
	char* RPN = str.getRPN();
	double exp = str.calculation(RPN, 0, 0);

	EXPECT_EQ(exp, 2);
}

TEST(Calculation, division_by_zero)
{
	const int n = 1;

	Variable v[n];
	v[0].name = 'x';
	v[0].value = 3;

	char act[] = "5/(3-x)";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	EXPECT_ANY_THROW(str.calculation(RPN, v, n));
}

TEST(Calculation, easy_calculation)
{
	char act[] = "2+3*4";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	double res = str.calculation(RPN, 0, 0);

	EXPECT_EQ(res, 14);
}

TEST(Calculation, easy_calculation_2)
{
	char act[] = "(5-4*3)/7";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	double res = str.calculation(RPN, 0, 0);

	EXPECT_EQ(res, -1);
}

TEST(Calculation, easy_calculation_3)
{
	char act[] = "|2-10|-15/5";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	double res = str.calculation(RPN, 0, 0);

	EXPECT_EQ(res, 5);
}

TEST(Calculation, complicated_calculation_1)
{
	char act[] = "(6+3-5)/2*9";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	double res = str.calculation(RPN, 0, 0);

	EXPECT_EQ(res, 18);
}

TEST(Calculation, complicated_calculation_2)
{
	Variable v[1]; 
	v[0].name = 'x';
	v[0].value = 7;

	char act[] = "3+15*x/21";
	Arithmetic str(act);
	char* RPN = str.getRPN();

	double res = str.calculation(RPN, v, 1);

	EXPECT_EQ(res, 8);
}

TEST(Calculation, complicated_calculation_3)
{
	Variable v[1];
	v[0].name = 'x';
	v[0].value = 5;

	char act[] = "|1-x|^2*5/8";
	Arithmetic str(act);

	char* RPN = str.getRPN();
	double res = str.calculation(RPN,v,1);
	
	EXPECT_EQ(res, 10);
}

TEST(Calculation, hard_calculation_1)
{
	char act[] = "(|(5-10)*24|/30)^2";
	Arithmetic str(act);

	char* RPN = str.getRPN();
	double res = str.calculation(RPN, 0, 0);

	EXPECT_EQ(res, 16);
}

TEST(Calculation, hard_calculation_2)
{
	Variable v[2];
	v[0].name = 'x';
	v[0].value = 7;

	v[1].name = 'y';
	v[1].value = 10;

	char act[] = "(|x-11|+8/4+2^2)^3";
	Arithmetic str(act);

	char* RPN = str.getRPN();
	double res = str.calculation(RPN, v, 2);

	EXPECT_EQ(res, 1000);
}

TEST(Calculation, hard_calculation_3)
{
	Variable v[3];
	v[0].name = 'a';
	v[0].value = 3;

	v[1].name = 'b';
	v[1].value = 5;

	v[2].name = 'c';
	v[2].value = 10;

	char act[] = "|a+b-c|^a*c/(c*b-(a+b+c))";
	Arithmetic str(act);

	char* RPN = str.getRPN();
	double res = str.calculation(RPN, v, 3);

	EXPECT_EQ(res, 2.5);
}

int main(int ac, char* av[])
{
	testing::InitGoogleTest(&ac, av);
	return RUN_ALL_TESTS();
}