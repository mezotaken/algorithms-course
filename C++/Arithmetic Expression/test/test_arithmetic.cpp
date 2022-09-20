#include "arithmetic.h"
#include "gtest.h"
#include "sstream"
using namespace std;
#define EPS 10e-15
struct check_test
{
	string str;
	bool res;
	check_test(string istr, bool ires)
	{
		str = istr;
		res = ires;
	}
};

struct calc_test
{
	string str;
	string vars;
	double res;
	calc_test(string istr,string ivars, double ires)
	{
		str = istr;
		res = ires;
		vars = ivars;
	}
};

class arithm_check : public ::testing::TestWithParam<check_test>
{
protected: arithmetic a_test;
public:
	arithm_check(): a_test(GetParam().str)
	{
	}
	~arithm_check() {}
};

class arithm_calc : public ::testing::TestWithParam<calc_test>
{
protected: arithmetic b_test;
		   istringstream input;
public:
	arithm_calc() : b_test(GetParam().str), input(GetParam().vars)
	{
	}
	~arithm_calc() {}
};


TEST_P(arithm_check, can_check_for_correct)
{
	EXPECT_EQ(GetParam().res,a_test.IsCorrect());
}

TEST_P(arithm_calc, can_calculate_expressions)
{
	EXPECT_GE(EPS, abs(GetParam().res - b_test.Calc(input)));
}
INSTANTIATE_TEST_CASE_P(Inst1,
	arithm_check,
	::testing::Values(
		check_test("22+3.77/t*(-a)", true),
		check_test("5+(a-b*3.7)", true),
		check_test("-7.674*(g+3)", true),
		check_test("(a*b)-(3.65 +6.578)/37", true),
		check_test("-+353", false),
		check_test(")56+7(", false),
		check_test("(15/2)-54)", false),
		check_test("(15/)", false),
		check_test("3.66.+71", false),
		check_test("%65-7", false),
		check_test("(1+6.5)(661)", false),
		check_test("+5/(5+6)", false),
		check_test("xyz", false),
		check_test("+.-", false),
		check_test("1+6(42-3)", false)
	));

INSTANTIATE_TEST_CASE_P(Inst2,
	arithm_calc,
	::testing::Values(
		calc_test("a+b","15\r3.8",18.8),
		calc_test("(-35-x)/y + 7.1","-5\r6",2.1),
		calc_test("x-s+1-2+3/(-65+64)", "1.8\r-3.2",1.0 ),
		calc_test("18.5+6.16+3.9/x", "3.9",25.66 ),
		calc_test("z*c/(17.9-7.9)", "10\r3.78",3.78 ),
		calc_test("1+2+3+4+5+6-1-3-5-2-4-6+x", "127.789",127.789 ),
		calc_test("17*x-3*y/5", "0.1\r0.5",1.4 )
	));

TEST(arithmethic, can_parse_expression)
{
	arithmetic expr("-x+67*(-3.1/&)");
	Lexem cmp[11];
	Lexem* src = expr.GetLexems();
	cmp[0] = Lexem("-",OPERATOR);
	cmp[1] = Lexem("x", VARIABLE);
	cmp[2] = Lexem("+", OPERATOR);
	cmp[3] = Lexem("67", NUMBER);
	cmp[4] = Lexem("*", OPERATOR);
	cmp[5] = Lexem("(", LBRACKET);
	cmp[6] = Lexem("-", OPERATOR);
	cmp[7] = Lexem("3.1", NUMBER);
	cmp[8] = Lexem("/", OPERATOR);
	cmp[9] = Lexem("&", UNKNOWN);
	cmp[10] = Lexem(")", RBRACKET);
	bool res = true;
	for (int i = 0; i < expr.GetNLex(); i++)
		if (cmp[i] != src[i])
			res = false;

	EXPECT_EQ(true,res);
	ASSERT_NO_THROW(expr = arithmetic(""));
	EXPECT_EQ(0,expr.GetNLex());
}


TEST(arithmetic,can_transform_to_rpn)
{
	arithmetic expr("- 3 + 4.7 * 2 / (1 - x)"); //0 3 - 4.7 2 * 1 x - / +
	Lexem src[11];
	expr.toRPN_test(src);
	Lexem cmp[11];
	cmp[0] = Lexem("0", NUMBER);
	cmp[1] = Lexem("3", NUMBER);
	cmp[2] = Lexem("-", OPERATOR);
	cmp[3] = Lexem("4.7", NUMBER);
	cmp[4] = Lexem("2", NUMBER);
	cmp[5] = Lexem("*", OPERATOR);
	cmp[6] = Lexem("1", NUMBER);
	cmp[7] = Lexem("x", VARIABLE);
	cmp[8] = Lexem("-", OPERATOR);
	cmp[9] = Lexem("/", OPERATOR);
	cmp[10] = Lexem("+", OPERATOR);
	bool res = true;
	for (int i = 0; i < 11; i++)
		if (cmp[i] != src[i])
		{
			cout << src[i].str << "   " << cmp[i].str << endl;
			res = false;
		}
	EXPECT_EQ(true,res);
}