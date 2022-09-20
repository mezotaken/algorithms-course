// Заголовочный файл класса множество

#include "bitfield.h"
#define MAXSETPWR MAXBFSIZE
class Set
{

private:
  int MaxPower;       // Максимальная мощность множества
  BitField ChVect;    // Битовое поле для хранения характеристического вектора
public:
  Set(int mp);
  Set(const Set &s);			// Конструктор копирования
  Set(const BitField &bf);		// Конструктор преобразования типа
  operator BitField();			// Преобразование типа к битовому полю
  int GetMaxPower() const;      // Максимальная мощность множества
// Доступ к битам
  void InsElem(const int Elem);				// Включить элемент в множество
  void DelElem(const int Elem);				// Удалить элемент из множества
  bool IsMember(const int Elem) const;		// Проверить наличие элемента в множестве
// Теоретико-множественные операции
  int GetPower();							// Мощность подмножества
  bool operator== (const Set &s) const;		// Сравнение
  bool operator!= (const Set &s) const;		// Cравнение
  Set& operator= (const Set &s);			// присваивание
  Set operator+ (const int Elem);		    // Объединение с элементом, элемент должен быть из того же универса
  Set operator- (const int Elem);			// Разность с элементом, элемент должен быть из того же универса
  Set operator+ (const Set &s);				// Объединение
  Set operator* (const Set &s);				// Пересечение
  Set operator~ ();							// Дополнение
// Ввод-Вывод
  friend std::istream &operator>>(std::istream &istr, Set &bf);
  friend std::ostream &operator<<(std::ostream &ostr, const Set &bf);
};
