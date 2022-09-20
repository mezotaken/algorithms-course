//Множество, реализация

#include "set.h"

Set::Set(int mp) : ChVect(mp) { MaxPower = mp; }	//Конструктор
Set::Set(const Set &s) : ChVect(s.ChVect)			//Конструктор копирования
{
	MaxPower = s.MaxPower;
}
Set::Set(const BitField &bf) : ChVect(bf) { MaxPower = bf.GetLength(); }			//Конструктор преобразования типа
Set::operator BitField()							//Преобр. типа к битовому полю
{
	return ChVect;
}

//Доступ к битам

int Set::GetMaxPower() const { return MaxPower; }								    // Получить макс. к-во эл-тов
void Set::InsElem(const int Elem) 													// Включение элемента множества
{
	if (Elem >= 0 && Elem < MaxPower)
		ChVect.SetBit(Elem);
	else
		throw bfexcp("Element out of range");
}
void Set::DelElem(const int Elem) 													// Исключение элемента множества
{
	if (Elem >= 0 && Elem < MaxPower)
		ChVect.ClrBit(Elem);
	else
		throw bfexcp("Element out of range");
}
bool Set::IsMember(const int Elem) const 											// Элемент множества?
{
	if (Elem >= 0 && Elem < MaxPower)
		return ChVect.GetBit(Elem);
	else
		throw bfexcp("Element out of range");
}

// Теоретико-множественные операции
int Set::GetPower()									// Мощность подмножества
{
	return ChVect.GetBitSum();
}
bool Set::operator==(const Set &s) const			// Сравнение
{
	return (ChVect == s.ChVect);
}
bool Set::operator!=(const Set &s) const			// Сравнение
{
	return (ChVect != s.ChVect);
}
Set& Set::operator=(const Set &s)					// Присваивание
{
	MaxPower = s.MaxPower;
	ChVect = s.ChVect;
	return *this;
}
Set Set::operator+(const int Elem)					// Объединение с элементом
{
	if (Elem >= 0 && Elem < MaxPower)
	{
		Set res = *this;
		res.ChVect.SetBit(Elem);
		return res;
	}
	else
		throw bfexcp("Element out of range");
}
Set Set::operator-(const int Elem)					// Разность с элементом
{
	if (Elem >= 0 && Elem < MaxPower)
	{
		Set res = *this;
		res.ChVect.ClrBit(Elem);
		return res;
	}
	else
		throw bfexcp("Element out of range");
}

Set Set::operator+(const Set &s)					// Объединение
{
	Set res(ChVect | s.ChVect);
	return res;
}

Set Set::operator*(const Set &s)					// Пересечение
{
	Set res(ChVect & s.ChVect);
	return res;
}

Set Set::operator~()								// Дополнение
{
	Set res(MaxPower);
	res.ChVect = ~ChVect;
	return res;
}

// Перегрузка ввода/вывода

std::istream &operator>>(std::istream &istr, Set &s) // Ввод
{
	istr >> s.ChVect;
	return istr;
}

std::ostream& operator<<(std::ostream &ostr, const Set &s) // Вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.ChVect.GetBit(i))
			ostr << i <<" ";
	ostr << std::endl;
	return ostr;
}
