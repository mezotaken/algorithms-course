#pragma once
#include <cmath>
#define EPS 1e-15	//Для сравнения чисел с плавающей точкой

//Класс Моном

class monom
{
public:
	double cf;		//Коэффициент перед мономом
	int abc;		//Свёрнутая степень
	bool operator< (const monom& m) { return (abc<m.abc); }								//Операторы 
	bool operator> (const monom& m) { return (abc>m.abc); }								//сравнения
	bool operator==(const monom& m) { return (abs(abc - m.abc) < EPS && cf == m.cf); }	//
	bool operator!=(const monom& m) { return !(*this == m); }							//
	monom(double icf = 0, unsigned int iabc = 0) { cf = icf; abc = iabc; }				//Конструктор
	const monom& operator=(const monom& src) { cf = src.cf; abc = src.abc; return *this; }	//Оператор присваивания
};