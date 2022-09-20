#include "stack.h"
#include <iostream>

enum lexem_type { OPERATOR, LBRACKET, RBRACKET, NUMBER, VARIABLE, UNKNOWN };	//Типы лексем
struct Lexem //Лексема
{ 
	std::string str; 
	lexem_type tp; 
	Lexem(std::string istr = "", lexem_type itp = OPERATOR)
	{
		str = istr;
		tp = itp;
	}
	bool operator!=(const Lexem& lop)
	{
		bool res = false;
		if (lop.str != str || lop.tp != tp)
			res = true;
		return res;
	}
};				

class arithmetic
{
	
private:
	static const std::string symb;				//Разрешённые символы
	std::string expr;							//Выражение
	Lexem* pLex;								//Массив лексем
	int nL;										//Количество лексем
	void clrspace();							//Удаление пробелов
	void parse();								//Разбор на лексемы
	bool check_symbols() const;					//Проверка на недопустимые символы
	bool check_brackets() const;				//Проверка на соответствие скобок
	bool check_opers() const;					//Проверка на пропущенные операции/операнды
	int toRPN(Lexem* out) const;				//Перевод в ОПН
	bool priority(Lexem in, Lexem top) const;	//Определение приоритета
	Stack<std::string> vars;
public:
	arithmetic(const std::string i_expr);		//Конструктор по данному выражению
	arithmetic& operator=(const arithmetic& a);	//
	~arithmetic() { delete[] pLex; }			//Деструктор
    bool IsCorrect() const;						//Проверка корректности выражения
	double Calc(std::istream& in) ;				//Подсчёт результата
	std::string getvars();

	//Для тестов
	Lexem* GetLexems() { return pLex; }
	int GetNLex() {	return nL; }
	int toRPN_test(Lexem* out) {return toRPN(out);}
};