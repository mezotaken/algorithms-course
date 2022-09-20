// Битовое поле, реализация

#include "bitfield.h"

// Конструкторы/деструкторы

BitField::BitField(int len)						//Конструктор c параметром
{
	if (len >= 0 && len < MAXBFSIZE)
	{
		BitLen = len;
		BlockNum = (BitLen - 1) / BLSIZE + 1;
		pBlock = new BLTYPE[BlockNum];
		for (int i = 0; i < BlockNum; i++)
			pBlock[i] = 0;
	}
	else
		throw bfexcp("Invalid number");
}
BitField::~BitField()							//Деструктор
{
	delete[] pBlock;
}
BitField::BitField(const BitField &bf)			//Конструктор копирования
{
	BitLen = bf.BitLen;
	BlockNum = bf.BlockNum;
	pBlock = new BLTYPE[BlockNum];
	for (int i = 0; i < BlockNum; i++)
		pBlock[i] = bf.pBlock[i];
}

// Доступ к битам поля

int BitField::GetLength() const				//Получить длину битовой маски     
{
	return BitLen;
}
void BitField::SetBit(const int n)			// Установить бит
{
	if (n >= 0 && n < BitLen)
	{
		int TargBl = n / BLSIZE;
		BLTYPE Mask = GetBitMask(n);
		pBlock[TargBl] |= Mask;
	}
	else
		throw bfexcp("Invalid number");
}
int BitField::GetBit(const int n) const	   // Получить значение бита
{
	if (n >= 0 && n < BitLen)
	{
		int TargBl = n / BLSIZE;
		int Offset = BLSIZE - n % BLSIZE - 1;
		int BitVal = (pBlock[TargBl] >> (Offset)) & 1;
		return BitVal;
	}
	else
		throw bfexcp("Invalid number");
}
void BitField::ClrBit(const int n)			// Очистить бит
{
	if(n >= 0 && n < BitLen)
	{
		int TargBl = n / BLSIZE;
		BLTYPE Mask = GetBitMask(n);
		Mask = ~Mask;
		pBlock[TargBl] &= Mask;
	}
	else
		throw bfexcp("Invalid number");
}

// Внутренняя реализация

BLTYPE BitField::GetBitMask(const int n)	// Маска с единицей на n-ной позиции				
{
	int Offset = BLSIZE - n % BLSIZE - 1;
	BLTYPE temp = 1;
	temp <<= (Offset);
	return temp;
}

// Ввод/вывод

std::ostream &operator<<(std::ostream &ostr, const BitField &bf) // Вывод
{
	for (int i = 0; i < bf.BitLen; i++)
		ostr << bf.GetBit(i);
	ostr << std::endl;
	return ostr;
}
std::istream &operator>>(std::istream &istr, BitField &bf)		// Ввод
{
	std::string inbf;
	istr >> inbf;
	if (inbf.length() == bf.GetLength())
	{
		bool err = false;
		for (int i = 0; i < inbf.length() && !err; i++)
			if (inbf[i] != '0' && inbf[i] != '1')
				err = true;
		if (!err)
		{
			for (int j = 0; j < bf.GetLength(); j++)
				if (inbf[j] == '1')
					bf.SetBit(j);
			return istr;
		}
		else
			throw bfexcp("Unacceptable symbols");
	}
	else
		throw bfexcp("Wrong size");
}

// Операции над битовыми полями

BitField& BitField::operator=(const BitField &bf)				// Присваивание
{
	delete[] pBlock;
	BitLen = bf.BitLen;
	BlockNum = bf.BlockNum;
	pBlock = new BLTYPE[BlockNum];
	for (int i = 0; i < BlockNum; i++)
		pBlock[i] = bf.pBlock[i];
 	return *this;
}
bool BitField::operator==(const BitField &bf) const				// Сравнение
{
	bool eq = true;
	if (BitLen != bf.BitLen)
		eq = false;
	else
	{
		for (int i = 0; (i < BlockNum) && (eq); i++)
			if (pBlock[i] != bf.pBlock[i])
				eq = false;
	}
	return eq;
}
bool BitField::operator!=(const BitField &bf) const				// Сравнение
{
	return !(*this == bf);
}
BitField BitField::operator~() const							// Отрицание
{
	BitField res = *this;
	BLTYPE inv = 1;
	for (int i = BitLen; i < BlockNum*BLSIZE-1; i++)
	{
		inv <<= 1 ;
		inv += 1;
	}
	res.pBlock[BlockNum - 1] |= inv;
	for (int i = 0; i < BlockNum; i++)
		res.pBlock[i] = ~res.pBlock[i];
	return res;
}

BitField BitField::operator|(const BitField &bf)				// Операция "OR" 
{
	BitField res(std::max(BitLen, bf.BitLen));
	int ComBl = std::min(BlockNum, bf.BlockNum);
	for (int i = 0; i < ComBl;i++)
		res.pBlock[i] = pBlock[i] | bf.pBlock[i];

	for (int i = ComBl; i < BlockNum; i++)
		res.pBlock[i] = pBlock[i];
	for (int i = ComBl; i < bf.BlockNum; i++)
		res.pBlock[i] = bf.pBlock[i];
	return res;
}

BitField BitField::operator&(const BitField &bf)				// операция "AND"  
{
	BitField res(std::min(BitLen, bf.BitLen));
	for (int i = 0; i < res.BlockNum; i++)
		res.pBlock[i] = pBlock[i] & bf.pBlock[i];
	return res;
}

int BitField::GetBitSum()										//Получить сумму битов в поле
{
	int sum = 0;
	for (int i = 0; i < BlockNum; i++)
		for (int j = 0; j < BLSIZE; j++)
			sum += ((pBlock[i] >> j) & 1);
	return sum;
}