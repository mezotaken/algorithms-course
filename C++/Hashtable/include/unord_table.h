#pragma once
#include "table.h"
#include "ord_table.h"

template<class KeyType, class DataType>
class unord_table : public table <KeyType, DataType>
{
private:
	void Realloc() override;
public:
	unord_table(int i_size = MIN_SIZE) : table(i_size) {}
	~unord_table() {}

	void Insert(const KeyType& key, const DataType& data) override;
	DataType* Find(const KeyType& key) const override;
	void Delete(const KeyType& key) override;

	template<class KeyType,class DataType> friend class ord_table;

	template<class K, class D>
	friend std::ostream& operator<<(std::ostream& os, unord_table<K, D> & tab);
};


template <class KeyType, class DataType>
std::ostream& operator<<(std::ostream &ostr, unord_table<KeyType, DataType> & tab)
{
	if (tab.GetCurSize() != 0)
	{
		tab.Reset();
		ostr << tab.GetCurr().key << "     " << tab.GetCurr().data << endl;
		while (!tab.IsEnded())
		{
			tab.Move();
			ostr << tab.GetCurr().key << "     " << tab.GetCurr().data << endl;
		}
	}
	return ostr;
}



template <class KeyType, class DataType>
void unord_table<KeyType, DataType>::Realloc()
{
	int nSize = (int)((MaxSize + 10)*GROWTHCOEF);
	row <KeyType, DataType>* temp = new row<KeyType, DataType>[nSize];
	for (int i = 0; i < CurSize; i++)
		temp[i] = mt[i];
	delete mt;
	mt = temp;
	MaxSize = nSize;
}

template <class KeyType, class DataType>
void unord_table<KeyType, DataType>::Insert(const KeyType& key, const DataType& data)
{
	if (CurSize == MaxSize)
		Realloc();
	int i = 0;
	while (mt[i].key != key && i<CurSize)
		i++;
	if (key != mt[i].key && i==CurSize)
	{
		mt[CurSize] = row<KeyType, DataType>(key, data);
		CurSize++;
	}
	else
		throw "Duplicated key";
}

template <class KeyType, class DataType>
DataType* unord_table<KeyType, DataType>::Find(const KeyType& key) const
{
	int i = 0;
	while (mt[i].key != key && i<CurSize)
		i++;
	if (i < CurSize)
		return &mt[i].data;
	else
		throw "Data doesn't exist";
}

template <class KeyType, class DataType>
void unord_table<KeyType, DataType>::Delete(const KeyType& key)
{
	int i = 0;
	while (mt[i].key != key && i<CurSize)
		i++;
	if (i < CurSize)
	{
		mt[CurSize - 1] = row<KeyType,DataType>();
		mt[i] = mt[CurSize-1];
		CurSize--;
	}
	else
		throw "Data doesn't exist";
}