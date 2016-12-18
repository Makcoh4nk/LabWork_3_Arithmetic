#include <gtest/gtest.h>
#include "Stack.h"

int main(int ac, char* av[])
{
  testing::InitGoogleTest(&ac, av);
  return RUN_ALL_TESTS();
}

TEST(RPN, correct_RPN)
{
	Variable var[2];

	var[0].name = 'x';
	var[0].value = 2;

	var[1].name = 'y';
	var[1].value = 3;

	char act[] = "x^y";
	char exp[] = "xy^";

	int size_res = 2 * strlen(act);

	char *res = new char[size_res];

	res = RPN(size_res, act, var);

	for (int i = 0; i < strlen(act); ++i)
		EXPECT_TRUE(res[i] == exp[i]);
}