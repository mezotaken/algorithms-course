#include <string>
// Класс исключений
class stexcp :public std::exception
{
private:
	std::string errmsg;
public:
	stexcp(const std::string &msg) { errmsg = msg; }
};

// Шаблон класса Стек
template<class sType>
class Stack
{
private:
	int Size;							//Максимальный размер стека
	int top;							//Индекс текущего
	sType* StMem;						//Указатель на эл-ты стека

public:
	Stack(int s = 1000);							    // Конструктор без параметров
	~Stack();											// Деструктор
	Stack(const Stack<sType>& src);						// Конструктор копирования
	int GetSize() const { return Size; }				// Размер стека
	int GetInd() const { return top + 1; }
	void push(const sType& val);						// Положить элемент на вершину стека
	sType pop();										// Доступ к вершине стека с удалением 
	sType peek() const;								    // Доступ к вершине стека без удаления
	bool empty() const { return top == -1; }			// Стек пуст
};

// Реализация шаблона класса Стек
template<class sType>			// Конструктор без параметров
Stack<sType>::Stack(int s) : Size(s)
{
	top = -1;
	StMem = new sType[Size];
}

template<class sType>			// Деструктор
Stack<sType>::~Stack()
{
	delete[] StMem;
}

template<class sType>			// Конструктор копирования
Stack<sType>::Stack(const Stack<sType>& src)
{
	Size = src.Size;
	StMem = new sType[Size];
	for (int i = 0; i < top+1; i++)
		StMem[i] = src.StMem[i];
	
}

template<class sType>			// Положить элемент на вершину стека
void Stack<sType>::push(const sType& val)
{
	if (top == Size - 1)
	{
		Size *=2;
		sType* temp = new sType[Size];
		for (int i = 0; i < top + 1; i++)
			temp[i] = StMem[i];
		delete[] StMem;
		StMem = temp;

	}
		StMem[++top] = val;
}

template<class sType>			// Доступ к вершине стека без удаления
sType Stack<sType>::peek() const
{
	if (!empty())
		return StMem[top];
	else
		throw stexcp("Stack is empty");
}
template<class sType>			// Доступ к вершине стека c удаленем
sType Stack<sType>::pop()
{
	if (!empty())
		return StMem[top--];
	else
		throw stexcp("Stack is empty");
}
