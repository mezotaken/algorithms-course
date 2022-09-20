#include <iostream>
#include <string>
using namespace std;
 
#define MAX_MATRIX_SIZE  10000
#define MAX_VECT_SIZE    100000000
 
// Класс исключений
class mexcp :public exception
{
private:
    string errmsg;
public:
    mexcp(const string &msg) { errmsg = msg; }
};
 
// Шаблон вектора
template <class ValType>
class Vector
{
protected:
    ValType *pVect;     // Память под вектор
    int Size;           // Размер вектора
    int StInd;          // Индекс первого элемента вектора
public:
    Vector(int s = 0, int si = 0);          // Конструктор с пар-ми по умолч.
    Vector(const Vector &v);                // Конструктор копирования
    ~Vector();                              // Деструктор
    int GetSize() { return Size; }          // Размер вектора
    int GetStInd() { return StInd; }        // Индекс первого элемента
    ValType& operator[](int pos);           // Доступ
    bool operator==(const Vector &v) const; // Сравнение
    bool operator!=(const Vector &v) const; // Сравнение
    Vector& operator=(const Vector &v);     // Присваивание
    void Fill(const ValType &val);          // Заполнить значением
// Скалярные операции
    Vector operator+(const ValType &val) const; // Прибавить скаляр
    Vector operator-(const ValType &val) const; // Вычесть скаляр
    Vector operator*(const ValType &val) const; // Умножить на скаляр
// Векторные операции
  Vector operator+(const Vector &v) const;      // Сложение
  Vector operator-(const Vector &v) const;      // Вычитание
  ValType operator*(const Vector &v) const;     // Скалярное произведение
// Ввод - вывод
  friend istream& operator>>(istream &in, Vector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVect[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const Vector &v)
  {
    for (int i = 0; i < v.Size; i++)
      out << v.pVect[i] << ' ';
    return out;
  }
};
 
// Шаблон верхнетреугольной матрицы
template <class ValType>
class Matrix : public Vector<Vector<ValType>>
{
public:
  Matrix(int s);                                // Конструктор
  Matrix(const Matrix &mt);                     // Копирование
  Matrix(const Vector<Vector<ValType> > &mt);   // Преобразование типа
  bool operator==(const Matrix &mt) const;      // Сравнение
  bool operator!=(const Matrix &mt) const;      // Сравнение
  Matrix& operator= (const Matrix &mt);         // Присваивание
  Matrix  operator+ (const Matrix &mt) const;   // Сложение
  Matrix  operator- (const Matrix &mt) const;   // Вычитание
 
// Ввод - вывод
  friend istream& operator>>(istream &in, Matrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVect[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const Matrix &mt)
  {
      for (int i = 0; i < mt.Size; i++)
      {
          for (int j = 0; j < i; j++)
              out << 0 <<' ';
          out << mt.pVect[i] << endl;
      }
    return out;
  }
};
 
//----------------------------Реализация шаблона класса вектора----------------------------
template <class ValType>                                    // Конструктор
Vector<ValType>::Vector(int s, int si)
{
    if (s >= 0 && si >= 0 && s <= MAX_VECT_SIZE && si <= MAX_VECT_SIZE - s)
    {
        Size = s;
        StInd = si;
        pVect = new ValType[Size];
        memset(pVect,0,Size*sizeof(ValType));               //????????????????????
    }
    else
        throw mexcp("Invalid Args");
}
 
template <class ValType>                                    // Конструктор копирования
Vector<ValType>::Vector(const Vector<ValType> &v)
{
    Size = v.Size;
    StInd = v.StInd;
    pVect = new ValType[Size];
    for (int i = 0; i < Size; i++)
        pVect[i] = v.pVect[i];
}
 
template <class ValType>                                    // Деструктор
Vector<ValType>::~Vector()
{
    delete[] pVect;
}
 
template <class ValType>                                    // Доступ
ValType& Vector<ValType>::operator[](int pos)
{
    if (pos >= StInd && pos < StInd + Size)
        return pVect[pos-StInd];
    else
        throw mexcp("Invalid Index");
}
 
template <class ValType>                                    // Сравнение
bool Vector<ValType>::operator==(const Vector &v) const
{
    bool eq = true;
    if (Size != v.Size || StInd!=v.StInd)
        eq = false;
    else
    {
        for (int i = 0; i < Size && eq; i++)
            if (pVect[i] != v.pVect[i])
                eq = false;
    }
 
    return eq;
}
 
template <class ValType>                                    // Сравнение
bool Vector<ValType>::operator!=(const Vector &v) const
{
    return !(v == *this);
}
 
template <class ValType>                                    // Присваивание
Vector<ValType>& Vector<ValType>::operator=(const Vector<ValType> &v)
{
    if (this != &v)
    {
        delete[] pVect;
        Size = v.Size;
        StInd = v.StInd;
        pVect = new ValType[Size];
        for (int i = 0; i < Size; i++)
            pVect[i] = v.pVect[i];
    }
    return *this;
}  
 
template <class ValType>                                    // Заполнить значением
void Vector<ValType>::Fill(const ValType &val)
{
    for (int i = 0; i < Size; i++)
        pVect[i] = val;
}
 
template <class ValType>                                    // Прибавить скаляр
Vector<ValType> Vector<ValType>::operator+(const ValType &val) const
{
    Vector<ValType> res(*this);
    for (int i = 0; i < Size; i++)
        res.pVect[i] += val;
    return res;
}
 
template <class ValType>                                    // Вычесть скаляр
Vector<ValType> Vector<ValType>::operator-(const ValType &val) const
{
    Vector<ValType> res(*this + (-val));
    return res;
}
 
template <class ValType>                                    // Умножить на скаляр
Vector<ValType> Vector<ValType>::operator*(const ValType &val) const
{
    Vector<ValType> res(*this);
    for (int i = 0; i < Size; i++)
        res.pVect[i] *= val;
    return res;
}
 
template <class ValType>                                    // Сложение
Vector<ValType> Vector<ValType>::operator+(const Vector<ValType> &v) const
{
    if (Size == v.Size && StInd == v.StInd)
    {
        Vector<ValType> res(*this);
        for (int i = 0; i < Size; i++)
            res.pVect[i] = res.pVect[i] + v.pVect[i];
        return res;
    }
    else
        throw mexcp("Incompatible size");
}
 
template <class ValType>                                    // Вычитание
Vector<ValType> Vector<ValType>::operator-(const Vector<ValType> &v) const
{
    if (Size == v.Size && StInd == v.StInd)
    {
        Vector<ValType> res(*this);
        for (int i = 0; i < Size; i++)
            res.pVect[i] = res.pVect[i] - v.pVect[i];
        return res;
    }
    else
        throw mexcp("Incompatible size");
}
 
template <class ValType>                                    // Скалярное произведение
ValType Vector<ValType>::operator*(const Vector<ValType> &v) const
{
    if (Size == v.Size && StInd ==  v.StInd)
    {
        ValType res = 0;
        for (int i = 0; i < Size; i++)
            res = res + (pVect[i] * v.pVect[i]);
        return res;
    }
    else
        throw mexcp("Incompatible size");
}
//-----------------------------------------------------------------------------------------
                                                                                           
//---------------------------Реализация шаблона верхнетр. матр.----------------------------
template <class ValType>                                        // Конструктор                      
Matrix<ValType>::Matrix(int s)
{
    if (s <= MAX_MATRIX_SIZE && s >= 0)
    {
        Size = s;
        StInd = 0;
        pVect = new Vector<ValType>[Size];
        for (int i = 0; i < Size; i++)
            pVect[i] = Vector<ValType>(Size - i, i);
    }
    else
        throw mexcp("Invalid Index");
}
 
template <class ValType>                                        // Конструктор копирования
Matrix<ValType>::Matrix(const Matrix<ValType> &mt) :
    Vector<Vector<ValType>>(mt) {}
 
template <class ValType>                                        // Конструктор преобразования типа
Matrix<ValType>::Matrix(const Vector<Vector<ValType>> &mt) :
    Vector<Vector<ValType>>(mt) {}
 
template <class ValType>                                        // Сравнение
bool Matrix<ValType>::operator==(const Matrix<ValType> &mt) const
{
    return Vector<Vector<ValType>>::operator==(mt);
}
 
template <class ValType>                                        // Сравнение
bool Matrix<ValType>::operator!=(const Matrix<ValType> &mt) const
{
    return !(*this == mt);
}
 
template <class ValType>                                        // Присваивание
Matrix<ValType>& Matrix<ValType>::operator=(const Matrix<ValType> &mt)
{
    if (this != &mt)
    {
        delete[] pVect;
        Size = mt.Size;
        pVect = new Vector<ValType>[Size];
        for (int i = 0; i < Size; i++)
            pVect[i] = mt.pVect[i];
    }
    return *this;
}
 
template <class ValType>                                        // Сложение
Matrix<ValType> Matrix<ValType>::operator+(const Matrix<ValType> &mt) const
{
    if (Size == mt.Size)
        return Vector<Vector<ValType>>::operator+(mt);
    else
        throw mexcp("Incompatible size");
}
 
template <class ValType>                                        // Вычитание
Matrix<ValType> Matrix<ValType>::operator-(const Matrix<ValType> &mt) const
{
    if (Size == mt.Size)
        return Vector<Vector<ValType>>::operator-(mt);
    else
        throw mexcp("Incompatible size");
}
//-----------------------------------------------------------------------------------------