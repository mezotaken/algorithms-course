#pragma once
#include <cmath>
#include <iostream>
#define MIN_SIZE 50
#define GROWTHCOEF 1.7

template <class KeyType, class DataType>
struct row
{
	KeyType key;
	DataType data;
	row(const KeyType& i_key, const DataType& i_data) 
	{
	key = i_key; 
	data = i_data;
	}
	row() { key = KeyType(); data = DataType(); }
	row(const row& src) 
	{ 
		key = src.key; 
		data = src.data; 
	}
	row& operator=(const row& src) 
	{ 

			key = src.key; 
			data = src.data; 
			return *this; 
	}

	~row() { }
};


template<class KeyType, class DataType>
class table
{
protected:
	row <KeyType, DataType>* mt;
	int MaxSize;
	int CurSize;
	virtual void Realloc() = 0;
	int Curr;
public:
	table(int i_size = MIN_SIZE);
	virtual ~table() { delete[] mt; }

	virtual void Insert(const KeyType& key, const DataType& data) = 0;
	virtual DataType* Find(const KeyType& key) const = 0;
	virtual void Delete(const KeyType& key) = 0;

	virtual void Reset();
	virtual bool IsEnded() const; 
	virtual void Move();
	virtual row<KeyType, DataType> GetCurr() const;

	virtual bool IsFull() const {return CurSize >= MaxSize; }
	int GetCurSize() const { return CurSize; }
	int GetMaxSize() const { return MaxSize; }
	bool IsEmpty() const { return CurSize == 0; }
	
};


template <class KeyType, class DataType>
table<KeyType, DataType>::table(int i_size)
{
	CurSize = 0;
	MaxSize = i_size;
	mt = new row<KeyType, DataType>[MaxSize];
}

template <class KeyType, class DataType>
void table<KeyType, DataType>::Reset() 
{
	if (CurSize == 0)
		Curr = -1;
	else
		Curr = 0;
}

template <class KeyType, class DataType>
bool table<KeyType, DataType>::IsEnded() const
{
	return(Curr >= CurSize - 1);
}

template <class KeyType, class DataType>
void table<KeyType, DataType>::Move()
{
	Curr++;
	if (Curr == CurSize)
		Reset();
}

template <class KeyType, class DataType>
row<KeyType, DataType> table<KeyType, DataType>::GetCurr() const
{
		if (Curr < CurSize && Curr > -1)
			return mt[Curr];
		else throw "Element doesn't exist";
}