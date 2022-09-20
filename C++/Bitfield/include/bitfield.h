#include <iostream>
#include <string>
#include <algorithm>

//#define 
typedef unsigned int BLTYPE;
#define BLSIZE (sizeof(BLTYPE)*8)
#define MAXBFSIZE (32768*BLSIZE)

//Класс исключений


class bfexcp :public std::exception
{
private:
	std::string errmsg;
public:
	bfexcp(const std::string &msg) { errmsg = msg; }
	void errprnt() { std::cout << errmsg << std::endl; }
};


class BitField
{
private:
  int  BitLen;								// Длина битового поля - макс. к-во битов
  int  BlockNum;							// к-во блоков для представления бит.поля
  BLTYPE *pBlock;							// Память для представления битового поля
  //Методы реализации      
  static BLTYPE GetBitMask (const int n);	// Битовая маска для бита n  
public:
  BitField(int len);              //                                   
  BitField(const BitField &bf);   //                                   
  ~BitField();                    //     
  //Доступ к битам
  int GetLength() const;		  // Получить длину битовой маски     
  void SetBit(const int n);       // Установить бит 
  int  GetBit(const int n) const; // Получить значение бита  
  void ClrBit(const int n);       // Очистить бит                                      
  int GetBitSum();

  friend std::istream &operator>>(std::istream &istr, BitField &bf);            
  friend std::ostream &operator<<(std::ostream &ostr, const BitField &bf);
  
  // Операции над битовыми полями
  BitField& operator=(const BitField &bf);	 // Присваивание
  bool operator==(const BitField &bf) const; // Cравнение
  bool operator!=(const BitField &bf) const; // Cравнение
  BitField  operator~() const;			     // Отрицание   
  BitField  operator|(const BitField &bf);   // Операция "OR"  
  BitField  operator&(const BitField &bf);   // операция "AND"  
};

