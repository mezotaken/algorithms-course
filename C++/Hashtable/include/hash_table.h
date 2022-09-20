#pragma once
#include "table.h"
#include <string>
#include <random>  
#define LOADFACTOR_LIMIT 0.75

template <typename KeyType> class Hash
{
public:
	static int get(const KeyType& key)
	{
		int res = 0;
		unsigned char* ptr = (unsigned char*)&key;
		for (int i = 0; i < sizeof(key); i++)
			res += ptr[i];
		return res;
	}
};


template<> class Hash<std::string>
{
public:
	static int get(const std::string& key)
	{
		int res = 0;
		for (int i = 0; i < (int)key.length(); i++)
			res += (unsigned char)key[i];
		return res;
	}
};


template<class KeyType, class DataType, class HashGen = Hash<KeyType>>
class hash_table : public table <KeyType, DataType>
{
private:
	char* exist;
	void Realloc() override;
	int rhash(const KeyType& key, bool fd) const;
public:
	hash_table(int i_size = MIN_SIZE) : table(i_size) {exist = new char[i_size](); }
	~hash_table() { delete[] exist; }

	void Insert(const KeyType& key, const DataType& data) override;
	DataType* Find(const KeyType& key) const override;
	void Delete(const KeyType& key) override;

	bool IsEnded() const override;
	void Reset() override;
	void Move() override;
	row<KeyType, DataType> GetCurr() const override;

	template<class K, class D,class H>
	friend std::ostream& operator<<(std::ostream& os, hash_table<K, D, H> & tab);
};

template <class KeyType, class DataType,class HashGen>
std::ostream& operator<<(std::ostream &ostr, hash_table<KeyType, DataType,HashGen> & tab)
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

template <class KeyType, class DataType,class HashGen>
void hash_table<KeyType, DataType, HashGen>::Move()
{
	do
	{
		Curr++;
	} while (Curr < MaxSize && exist[Curr] != 1);
	if (Curr == MaxSize)
		Reset();
}

template <class KeyType, class DataType, class HashGen>
row<KeyType, DataType> hash_table<KeyType, DataType,HashGen>::GetCurr() const
{
	if (exist[Curr] == 1)
		return mt[Curr];
	else throw "Element doesn't exist";
}


template <class KeyType, class DataType, class HashGen>
bool hash_table<KeyType, DataType, HashGen>::IsEnded() const
{	
	int t = Curr + 1;
	while (t < MaxSize && exist[t] != 1)
		t++;
	return t == MaxSize;
}

template <class KeyType, class DataType, class HashGen>
void hash_table<KeyType, DataType, HashGen>::Reset()
{
	if (CurSize == 0)
		Curr = -1;
	else
	{
		Curr = 0;
		while (exist[Curr] != 1)
			Curr++;
	}
}

template <class KeyType, class DataType, class HashGen>
int hash_table<KeyType, DataType, HashGen>::rhash(const KeyType& key, bool fd) const
{
	std::mt19937 gen;
	int ind, val=HashGen::get(key);
	gen.seed(val);
	if (!fd)
		do
			ind = gen() % MaxSize;
		while (exist[ind] == 1 && mt[ind].key != key);
	else
		do
			ind = gen() % MaxSize;
		while (exist[ind] !=0 && mt[ind].key != key);
	return ind;
}

template <class KeyType, class DataType, class HashGen>
void hash_table<KeyType, DataType, HashGen>::Insert(const KeyType& key, const DataType& data)
{
	if ((double)CurSize / MaxSize > LOADFACTOR_LIMIT)
		Realloc();
	int ind = rhash(key,false);
	if (mt[ind].key != key)
	{
		mt[ind] = row<KeyType, DataType>(key, data);
		exist[ind] = 1;
		CurSize++;
	}
	else
		throw "Duplicate key";
}

template <class KeyType, class DataType, class HashGen>
DataType* hash_table<KeyType, DataType, HashGen>::Find(const KeyType& key) const
{
	int ind = rhash(key,true);
	if (exist[ind] == 1)
		return &mt[ind].data;
	else
		throw "Data doesn't exist";
	
}
template <class KeyType, class DataType, class HashGen>
void hash_table<KeyType, DataType, HashGen>::Delete(const KeyType& key)
{
	int ind = rhash(key, true);
	if (mt[ind].key == key)
	{
		mt[ind] = row<KeyType, DataType>();
		CurSize--;
		exist[ind] = -1;
	}
	else
		throw "Data doesn't exist";
}


template <class KeyType, class DataType, class HashGen>
void hash_table<KeyType, DataType, HashGen>::Realloc()
{
	int oldSize = MaxSize;
	MaxSize = (int)((MaxSize + 10)*GROWTHCOEF);
	row <KeyType, DataType>* oldmt = mt;
	char* oldEx = exist;
	exist = new char[MaxSize]();
	mt = new row<KeyType, DataType>[MaxSize];
	for (int i = 0; i < oldSize; i++)
		if (oldEx[i] == 1)
			Insert(oldmt[i].key, oldmt[i].data);
	delete[] oldmt;
	delete[] oldEx;
}
