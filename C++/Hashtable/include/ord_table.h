#pragma once
#include "table.h"
#include "unord_table.h"

template<class KeyType, class DataType>
class ord_table : public table <KeyType, DataType>
{
private:
	void Realloc() override;
	int binsearch(const KeyType& key) const;
public:
	~ord_table() {}
	ord_table(int i_size = MIN_SIZE) : table(i_size) {}

	ord_table(const unord_table<KeyType, DataType>& src);

	void Insert(const KeyType& key, const DataType& data) override;
	DataType* Find(const KeyType& key) const override;
	void Delete(const KeyType& key) override;

	template<class K, class D>
	friend std::ostream& operator<<(std::ostream& os, ord_table<K, D> & tab);
};

template <class KeyType, class DataType>
std::ostream& operator<<(std::ostream &ostr, ord_table<KeyType, DataType> & tab)
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
ord_table<KeyType, DataType>::ord_table(const unord_table<KeyType, DataType>& src) : table(src.MaxSize)
{
	for (int i = 0; i < src.CurSize; i++)
		Insert(src.mt[i].key, *(src.mt[i].data));
	Reset();
}


template <class KeyType, class DataType>
void ord_table<KeyType, DataType>::Realloc()
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
int ord_table<KeyType, DataType>::binsearch(const KeyType& key) const
{
	int st = 0;
	int fn = CurSize - 1;
	int mid;
	while (st <= fn)
	{
		mid = (st + fn) / 2;
		if (key > mt[mid].key)
			st = mid + 1;
		else 
			fn = mid - 1;
	}
	return st;
}

template <class KeyType, class DataType>
void ord_table<KeyType, DataType>::Insert(const KeyType& key, const DataType& data)
{
	if (CurSize == MaxSize)
		Realloc();

	int i = binsearch(key);

	if (mt[i].key != key)
	{
		for (int j = CurSize; j > i; j--)
			mt[j] = mt[j - 1];
		mt[i] = row<KeyType, DataType>(key, data);
		CurSize++;
	}
	else
		throw "Duplicated key";
}

template <class KeyType, class DataType>
DataType* ord_table<KeyType, DataType>::Find(const KeyType& key) const
{
	int res = binsearch(key);
	if (mt[res].key == key && res<CurSize)
		return &mt[res].data;
	else
		throw "Data doesn't exist";
}	

template <class KeyType, class DataType>
void ord_table<KeyType, DataType>::Delete(const KeyType& key)
{
	int del = binsearch(key);
	if (mt[del].key == key)
	{
		mt[del] = row<KeyType, DataType>();
		for (int i = del; i < CurSize - 1; i++)
			mt[i] = mt[i + 1];
		CurSize--;
	}
	else
		throw "Data doesn't exist";
}