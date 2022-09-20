#include "polynom.h"
using namespace std;

//Создание списка с мономами по строке
list<monom> polynom::CreateInstance(string ipm)
{
	list<monom> res;
	int d[3] = { 100,10,1 };
	while (ipm.length())
	{
		string part;
		monom temp;
		int pos = 1;
		while (pos < (int)ipm.length() && ipm[pos] != '+' && ipm[pos] != '-')
			pos++;
		part = ipm.substr(0, pos);
		ipm.erase(0, pos);
		pos = 0;
		while (part[pos] != 'x' && part[pos] != 'y' && part[pos] != 'z' && pos < (int)part.length())
			pos++;

		string coef = part.substr(0, pos);
		if (coef == "+" || coef.length() == 0)
			temp.cf = 1;
		else if (coef == "-")
			temp.cf = -1;
		else temp.cf = stod(coef);

		if (abs(temp.cf) > EPS)
		{
			part.erase(0, pos);
			part += ' ';

			for (int i = 0; i < 3; i++)
			{
				pos = part.find((char)(OFFSET + i));
				if (pos > -1)
				{
					if (part[pos + 1] != '^')
						part.insert(pos + 1, "^1");
					temp.abc += d[i] * stoi(part.substr(pos + 2, 1));
					part.erase(pos, 3);
				}
			}

			res.InsertInOrder(temp);
		}
	}
	return res;
}

//Конструктор по строке
polynom::polynom(string ipm)
{
	pmlist = CreateInstance(ipm);
}

//Оператор сложения полиномов
polynom polynom::operator+(const polynom& pmr) const
{
	polynom res;
	polynom left = *this;
	polynom right = pmr;
	while (!left.pmlist.IsEnded() && !right.pmlist.IsEnded()) 
	{
		if (left.pmlist.GetCurr()->data < right.pmlist.GetCurr()->data)
		{
			res.pmlist.InsertAfter(res.pmlist.GetCurr(), left.pmlist.GetCurr()->data);
			left.pmlist.Move();
			res.pmlist.Move();
		}
		else if (left.pmlist.GetCurr()->data > right.pmlist.GetCurr()->data)
		{
			res.pmlist.InsertAfter(res.pmlist.GetCurr(), right.pmlist.GetCurr()->data);
			right.pmlist.Move();
			res.pmlist.Move();
		}
		else
		{
			double coef = left.pmlist.GetCurr()->data.cf + right.pmlist.GetCurr()->data.cf;
			if (abs(coef) > EPS)
			{
				res.pmlist.InsertAfter(res.pmlist.GetCurr(),  monom(coef,left.pmlist.GetCurr()->data.abc));
				res.pmlist.Move();
			}
			left.pmlist.Move();
			right.pmlist.Move();
		}
	}
	while (!left.pmlist.IsEnded())
	{
		res.pmlist.InsertAfter(res.pmlist.GetCurr(), left.pmlist.GetCurr()->data);
		left.pmlist.Move();
		res.pmlist.Move();
	}
	while (!right.pmlist.IsEnded())
	{
		res.pmlist.InsertAfter(res.pmlist.GetCurr(), right.pmlist.GetCurr()->data);
		right.pmlist.Move();
		res.pmlist.Move();
	}
	return res;
}

//Умножение на константу
polynom polynom::operator*(const double mp) const
{
	polynom res;
	if (abs(mp) > EPS)
	{
		res = *this;
		while (!res.pmlist.IsEnded())
		{
			res.pmlist.GetCurr()->data.cf *= mp;
			res.pmlist.Move();
		}
	}
	return res;
}

//Оператор умножения полиномов
polynom polynom::operator*(const polynom& pmr) const
{
	polynom res;
	polynom right = pmr;

	while (!right.pmlist.IsEnded())
	{
		polynom temp(*this);
		while (!temp.pmlist.IsEnded())
		{
			temp.pmlist.GetCurr()->data.cf *= right.pmlist.GetCurr()->data.cf;
			int nabc = temp.pmlist.GetCurr()->data.abc + right.pmlist.GetCurr()->data.abc;
			if (nabc / 100 < 10 && nabc / 10 % 10 < 10 && nabc % 10 < 10)
				temp.pmlist.GetCurr()->data.abc = nabc;
			else
				throw "Too large exponent";
			temp.pmlist.Move();
		}
		res = res + temp;
		right.pmlist.Move();
	}
	return res;
}

//Оператор вставки в поток
ostream& operator<<(ostream &ostr,const polynom& pm)
{
	polynom pmt = pm;
	while (!pmt.pmlist.IsEnded())
	{
		monom temp = pmt.pmlist.GetCurr()->data;

		if (abs(temp.cf - 1) > EPS && abs(temp.cf + 1) > EPS || temp.abc == 0)
			ostr << temp.cf;
		else if (abs(temp.cf + 1) < EPS && abs(temp.cf - 1) > EPS)
			ostr << '-';
		int p = temp.abc / 100;
		if(p>1)
			ostr << "x^" << p;
		else if (p == 1) ostr << "x";
		p = temp.abc / 10 % 10;
		if(p>1)
			ostr << "y^" << p;
		else if (p == 1) ostr << "y";
		p = temp.abc % 10;
		if(p>1)
			ostr<< "z^" << p;
		else if (p == 1) ostr << "z";
		pmt.pmlist.Move();
		if(!pmt.pmlist.IsEnded() && pmt.pmlist.GetCurr()->data.cf>0)
			ostr << "+";
	}
	return ostr;
}
