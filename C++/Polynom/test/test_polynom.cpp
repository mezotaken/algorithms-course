#include <gtest.h>
#include "polynom.h"
#include <vector>

using namespace std;

struct parse_test
{
	string str;
	polynom res;
	parse_test(string istr, const vector<monom> &ms)
	{
		str = istr;
		list<monom> temp;
		for (int i = 0; i < (int)ms.size(); i++)
			temp.InsertInOrder(ms[i]);
		res = polynom(temp);
	}
};

class pol_parse : public ::testing::TestWithParam<parse_test>
{
protected: polynom a_test;
public:
	pol_parse() : a_test(GetParam().str)
	{
	}
	~pol_parse() {}
};

TEST_P(pol_parse, correct_parse_of_polynom_strings)
{
	EXPECT_EQ(GetParam().res, a_test);
}
//
//INSTANTIATE_TEST_CASE_P(Inst1,
//	pol_parse,
//	::testing::Values(
////		parse_test("", vector<monom> {}),
////		parse_test("1", vector<monom> {monom(1,0)}),
////		parse_test("1.5", vector<monom> {monom(1.5,0)}),
////		parse_test("-3.57", vector<monom> {monom(-3.57, 0)}),
////		parse_test("15xyz", vector<monom> {monom(15, 111)}),
////		parse_test("-zyx", vector<monom> {monom(-1, 111)}),
////		parse_test("-x^2", vector<monom> {monom(-1, 200)}),
////		parse_test("z^2+x^2+y^2", vector<monom> {monom(1,2), monom(1,20), monom(1,200)}),
////		parse_test("x^9y^9z^9-3.22xyz", vector<monom> {monom(1,999), monom(-3.22,111)}),
////		parse_test("1-2x+3xy-4xyz", vector<monom> {monom(1,0), monom(-2,100), monom(3,110), monom(-4,111)})
////		//parse_test("0", vector<monom> {})
//	));




struct calc_test
{
	string left;
	string right;
	double c;
	string res;
	calc_test(string ires, string il, string ir = "", double ic = 0)
	{
		left = il;
		right = ir;
		c = ic;
		res = ires;
	}
};




class pol_plus : public ::testing::TestWithParam<calc_test>
{
protected: polynom pl, pr, pres;
public:
	pol_plus() : pl(GetParam().left), pr(GetParam().right), pres(GetParam().res)
	{
	}
	~pol_plus() {}
};

TEST_P(pol_plus, polynom_plus_polynom)
{
	EXPECT_EQ(pres, pl+pr);
}

INSTANTIATE_TEST_CASE_P(Inst2,
	pol_plus,
	::testing::Values(
		calc_test("x+y","x","y"),
		calc_test("5x","5x", ""),
		calc_test("2x", "-3x", "5x"),
		calc_test("", "-6.1xy", "6.1xy"),
		calc_test("5xy^2", "3x^2y", "5xy^2-3x^2y"),
		calc_test("1+2y+3z", "1+x+2y", "3z-x"),
		calc_test("", "1.1", "-1.1"),
		calc_test("", "0", "0"),
		calc_test("0", "1.8z", "-1.8z"),
		calc_test("16x-7y+3", "15x", "-7y+3+x")
	));

TEST(polynom, power_is_more_than_9_while_mult)
{
	polynom a("x^5"), b("x^5");
	ASSERT_ANY_THROW(a*b);
}




class pol_mult : public ::testing::TestWithParam<calc_test>
{
protected: polynom pl, pr, pres;
public:
	pol_mult() : pl(GetParam().left), pr(GetParam().right), pres(GetParam().res)
	{
	}
	~pol_mult() {}
};

TEST_P(pol_mult, polynom_mult_polynom)
{
	EXPECT_EQ(pres, pl * pr);
}

INSTANTIATE_TEST_CASE_P(Inst3,
	pol_mult,
	::testing::Values(
		calc_test("xy","x", "y"),
		calc_test("16","4", "4"),
		calc_test("12xy^2", "4y^2", "3x"),
		calc_test("3x+3y^2+3x^2-3xy^2-6y^4", "3+3x-6y^2", "x+y^2"),
		calc_test("x^2y^2", "-x^2", "-y^2"),
		calc_test("x^2y^2z+x^2y^2z^2","xyz", "xyz+xy"),
		calc_test("9-x^2", "3-x", "3+x"),
		calc_test("xy+x^2y^2+x^3+y^3","x^2+y", "x+y^2")
	));




class c_mult : public ::testing::TestWithParam<calc_test>
{
protected: polynom p, pres; double cn;
public:
	c_mult() : p(GetParam().left), pres(GetParam().res)
	{
		cn = GetParam().c;
	}
	~c_mult() {}
};

TEST_P(c_mult, polynom_mult_const)
{
	EXPECT_EQ(pres, p * cn);
}

INSTANTIATE_TEST_CASE_P(Inst4,
	c_mult,
	::testing::Values(
		calc_test("3x", "x", "", 3),
		calc_test("6xy+3x^2", "-2xy-x^2", "", -3),
		calc_test("xy+yz", "0.1xy+0.1yz", "", 10),
		calc_test("0", "x", "", 0)
	));