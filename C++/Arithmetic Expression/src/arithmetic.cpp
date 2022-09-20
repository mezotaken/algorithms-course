#include "arithmetic.h"
using namespace std;
const string arithmetic::symb = "/*+-().0123456789abcdefghijklmnopqrstuvwxyz";

//Удаление пробелов в строке
void arithmetic::clrspace()
{
	int i = 0;
	while (i < expr.length())
	{
		if (expr[i] == ' ')
			expr.erase(i, 1);
		else i++;
	}
}

//Разбор на лексемы
void arithmetic::parse()
{

	int pos;
	lexem_type last,cur;
	if (expr != "")
	{
		nL++;
		pos = symb.find(expr[0]);
		if (pos != -1)
			if (pos < 4)
				last = OPERATOR;
			else if (pos < 5)
				last = LBRACKET;
			else if (pos < 6)
				last = RBRACKET;
			else if (pos < 17)
				last = NUMBER;
			else last = VARIABLE;
		else
			last = UNKNOWN;
		pLex[nL-1].str += expr[0];


		for (int i = 1; i < expr.length(); i++)
		{
			pos = symb.find(expr[i]);
			if (pos != -1)
				if (pos < 4)
					cur = OPERATOR;
				else if (pos < 5)
					cur = LBRACKET;
				else if (pos < 6)
					cur = RBRACKET;
				else if (pos < 17)
					cur = NUMBER;
				else cur = VARIABLE;
			else
				cur = UNKNOWN;

			if (cur != last || cur == OPERATOR || cur == LBRACKET|| cur == RBRACKET|| cur == VARIABLE)
			{
				pLex[nL-1].tp = last;
				nL++;
			}
			pLex[nL-1].str += expr[i];
			last = cur;
		}
		pLex[nL-1].tp = last;
	}
}

//Конструктор по выражению
arithmetic::arithmetic(const string i_expr)
{
	expr = i_expr;
	clrspace();
	pLex = new Lexem[expr.length()];
	nL = 0;
	parse();
}

//
arithmetic& arithmetic::operator=(const arithmetic& a)
{
	expr = a.expr;
	nL = a.nL;
	delete[] pLex;
	pLex = new Lexem[nL];
	for (int i = 0; i < nL; i++)
		pLex[i] = a.pLex[i];
	return *this;
}

//На недопустимые символы
bool arithmetic::check_symbols() const
{
	bool res = true;
	int k = 0;
	for (int i = 0; i < nL; i++)
	{
		k=0;
		if (pLex[i].tp == UNKNOWN)
		{
			if (res)
			{
				cout << "Unacessible symbols:\n";
				res = false;
			}
			cout << "  " << pLex[i].str << endl;
		}

		if (pLex[i].tp == NUMBER)
		{
			for (int j = 0; j < pLex[i].str.length(); j++)
				if (pLex[i].str[j] == '.')
					k++;
			if (k > 1 || pLex[i].str.front() == '.' || pLex[i].str.back() == '.')
			{
				if (res)
				{
					cout << "Unacessible symbols:\n";
					res = false;
				}
				cout << "  " << pLex[i].str << endl;
			}
		}
	}
	return res;
}

//На соответствие скобок
bool arithmetic::check_brackets() const
{
	bool res = true;
	Stack<int> bs(expr.length());
	for (int i = 0; i < expr.length(); i++)
	{
		if (expr[i] == '(')
			bs.push(i+1);
		if (expr[i] == ')')
			if (bs.empty())
			{
				if (res)
				{
					cout << "Brackets mismatch:\n";
					res = false;
				}
				cout << "  No openining bracket for " << i+1 << endl;
			}
			else
				bs.pop();
	}
	if (!bs.empty())
	{
		if (res)
		{
			cout << "Brackets mismatch:\n";
			res = false;
		}
		for (int i = 0; i < bs.GetInd(); i++)
			cout << "  No closing bracket for " << bs.pop() << endl;
	}
	return res;
}

//На пропущенные операции/операнды
bool arithmetic::check_opers() const
{
	int pos = -1;
	bool res = true;
	lexem_type cur = pLex[0].tp, next = cur;


	for (int i = 0; i < nL-1; i++)
	{	
		pos += pLex[i].str.length();
		next = pLex[i+1].tp;
		if (cur == OPERATOR && (next == OPERATOR || next == RBRACKET))
		{
			cout << "No operand between " << pos + 1 << " and " << pos + 2 << endl;
			res = false;
		}
		if ((cur == VARIABLE || cur == NUMBER) && (next == NUMBER || next == VARIABLE || next == LBRACKET))
		{
			cout << "No operator between " << pos + 1 << " and " << pos + 2 << endl;
			res = false;
		}
		if (cur == LBRACKET && ((next == OPERATOR && pLex[i + 1].str != "-") || next == RBRACKET))
		{
			cout << "No operand between " << pos + 1 << " and " << pos + 2 << endl;
			res = false;
		}
		if (cur == RBRACKET && (next != OPERATOR && next != RBRACKET))
		{
			cout << "No operator between " << pos + 1 << " and " << pos + 2 << endl;
			res = false;
		}

		cur = next;
	}

	if (next == LBRACKET || next == OPERATOR)
	{
		cout << "No operand after " << pos + 2<< endl;
		res = false;
	}
	if (pLex[0].str != "-" && pLex[0].tp != NUMBER && pLex[0].tp != VARIABLE && pLex[0].tp != LBRACKET)
	{
		cout << "No operand before 1"<< endl;
		res = false;
	}
	return res;
}

//Проверка на правильность
bool arithmetic::IsCorrect() const
{
	if (expr != "")
	{
		bool s, b, o;
		b = check_brackets();
		s = check_symbols();
		if (s)
			o = check_opers();

		return s&&b&&o;
	}
	else
	{
		cout << "Empty expression!\n";
			return false;
	}
}

//Перевод в ОПН
int arithmetic::toRPN(Lexem* out) const 
{
	Lexem zero;
	zero.str = "0";
	zero.tp = NUMBER;

	lexem_type cur;
	int j = 0;
	Stack<Lexem> temp(2*nL);
	for (int i = 0; i < nL; i++)
	{
		cur = pLex[i].tp;
		if (cur == NUMBER || cur == VARIABLE)
			out[j++] = pLex[i];
		if (cur == LBRACKET)
			temp.push(pLex[i]);
		if (cur == RBRACKET)
		{
			while ((temp.peek()).tp != LBRACKET)
				out[j++] = temp.pop();
			temp.pop();
		}
		if (cur == OPERATOR)
		{
			if (pLex[i].str == "-")
				if (i == 0)
					out[j++] = zero;
				else if (pLex[i-1].tp == LBRACKET)
					out[j++] = zero;

			
			while (!temp.empty() && temp.peek().tp !=LBRACKET && priority(pLex[i],temp.peek()))
				out[j++] = temp.pop();

			temp.push(pLex[i]);
		}
	}
	while (!temp.empty())
		out[j++] = temp.pop();
	return j;
}

//True, если приоритет in <= чем top
bool arithmetic::priority(Lexem in, Lexem top) const
{
	int p1, p2;
	switch (in.str[0])
	{
	case '+': p1 = 0;
		break;
	case '-': p1 = 0;
		break;
	default: p1 = 1;
	}

	switch (top.str[0])
	{
	case '+': p2 = 0;
		break;
	case '-': p2 = 0;
		break;
	default: p2 = 1;
	}
	return p1 <= p2;
}

//Подсчёт значения
double arithmetic::Calc(istream& in)
{
	
	Lexem* Output = new Lexem[2 * nL];
	int fnL = toRPN(Output);
	Stack<double> res(2*fnL);
	for (int i = 0; i < fnL; i++)
	{
		if (Output[i].tp == NUMBER || Output[i].tp == VARIABLE)
			if (Output[i].tp == VARIABLE)
			{
				cout<<"Input "<<Output[i].str<<":";
				double val;
				in>>val;
				res.push(val);
				string cur = "";
				cur+=(" "+Output[i].str+" = "+to_string(val));
				vars.push(cur);
			}
			else
				res.push(stod(Output[i].str));

		if (Output[i].tp == OPERATOR)
		{
			double rop = res.pop(), lop = res.pop();
			switch (Output[i].str[0])
			{
			case '+': res.push(lop + rop);
				break;
			case '-': res.push(lop - rop);
				break;
			case '*': res.push(lop * rop);
				break;
			case '/': 
				{
					//if(rop<1e-25)
					res.push(lop / rop);
					//else
						//throw 0;
				}
				break;
			}
		}
	}

	return res.peek();
}
string arithmetic::getvars()
{
	string res = "";
	while(!vars.empty())
		res+=vars.pop();
	return res;
}