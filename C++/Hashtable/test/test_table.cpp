#include <gtest.h>
#include <string>
#include <iostream>
#include "ord_table.h"
#include "unord_table.h"
#include "hash_table.h"
using namespace std;



//Тесты на возможность создания (Баг?)
//TEST(lists, can_create_empty_unord_table)
//{
//	ASSERT_NO_THROW(unord_table<int,int> t);
//}
//
//TEST(lists, can_create_ord_empty_table)
//{
//	ASSERT_NO_THROW(ord_table<int, int> t);
//}
//
//TEST(lists, can_create_hash_empty_table)
//{
//	ASSERT_NO_THROW(hash_table<int, int> t);
//}



//Набор таблиц для тестирования
class TestingSetTables: public ::testing::Test {
protected:
	unord_table<int, int> Uemp;
	unord_table<int, int> Ufil;
	ord_table<int, int> Oemp;
	ord_table<int, int> Ofil;
	hash_table<int, int> Hemp;
	hash_table<int, int> Hfil;
public:
	TestingSetTables() :Uemp(10), Ufil(10), Oemp(10), Ofil(10), Hemp(10), Hfil(10)
	{
		Ufil.Insert(11,22);
		Ufil.Insert(5,10);
		Ufil.Insert(7,3);

		Ofil.Insert(11, 22);
		Ofil.Insert(5, 10);
		Ofil.Insert(7, 3);

		Hfil.Insert(11, 22);
		Hfil.Insert(5, 10);
		Hfil.Insert(7, 3);
	}
	~TestingSetTables() {}
};

//Проверка Insert Find Delete в парах для всех таблиц

TEST_F(TestingSetTables, insert_find_in_unord_empty_table)
{
	Uemp.Insert(15, 30);
	Uemp.Insert(4, 22);
	EXPECT_EQ(30, *Uemp.Find(15));
	EXPECT_EQ(22, *Uemp.Find(4));
}

TEST_F(TestingSetTables, insert_delete_in_unord_empty_table)
{
	Uemp.Insert(15, 30);
	Uemp.Insert(4, 22);
	Uemp.Delete(15);
	Uemp.Delete(4);
	EXPECT_EQ(0,Uemp.GetCurSize());
}

TEST_F(TestingSetTables, delete_find_in_unord_filled_table)
{
	Ufil.Delete(5);
	Ufil.Delete(11);
	EXPECT_EQ(3, *Ufil.Find(7));
	EXPECT_EQ(1, Ufil.GetCurSize());
	ASSERT_ANY_THROW(*Ufil.Find(5));
	ASSERT_ANY_THROW(*Ufil.Find(11));
}

TEST_F(TestingSetTables, insert_find_in_ord_empty_table)
{
	Oemp.Insert(15, 30);
	Oemp.Insert(4, 22);
	EXPECT_EQ(30, *Oemp.Find(15));
	EXPECT_EQ(22, *Oemp.Find(4));
}

TEST_F(TestingSetTables, insert_delete_in_ord_empty_table)
{
	Oemp.Insert(15, 30);
	Oemp.Insert(4, 22);
	Oemp.Delete(15);
	Oemp.Delete(4);
	EXPECT_EQ(0, Oemp.GetCurSize());
}

TEST_F(TestingSetTables, delete_find_in_ord_filled_table)
{
	Ofil.Delete(5);
	Ofil.Delete(11);
	EXPECT_EQ(3, *Ofil.Find(7));
	EXPECT_EQ(1, Ofil.GetCurSize());
	ASSERT_ANY_THROW(*Ofil.Find(5));
	ASSERT_ANY_THROW(*Ofil.Find(11));
}

TEST_F(TestingSetTables, insert_find_in_hash_empty_table)
{
	Hemp.Insert(15, 30);
	Hemp.Insert(4, 22);
	EXPECT_EQ(30, *Hemp.Find(15));
	EXPECT_EQ(22, *Hemp.Find(4));
}

TEST_F(TestingSetTables, insert_delete_in_hash_empty_table)
{
	Hemp.Insert(15, 30);
	Hemp.Insert(4, 22);
	Hemp.Delete(15);
	Hemp.Delete(4);
	EXPECT_EQ(0, Hemp.GetCurSize());
}

TEST_F(TestingSetTables, delete_find_in_hash_filled_table)
{
	Hfil.Delete(5);
	Hfil.Delete(11);
	EXPECT_EQ(3, *Hfil.Find(7));
	EXPECT_EQ(1, Hfil.GetCurSize());
	ASSERT_ANY_THROW(*Hfil.Find(5));
	ASSERT_ANY_THROW(*Hfil.Find(11));
}

TEST_F(TestingSetTables, delete_throws_in_unord_empty_table)
{
	ASSERT_ANY_THROW(Uemp.Delete(5));
	ASSERT_ANY_THROW(Uemp.Delete(11));
}

TEST_F(TestingSetTables, delete_throws_in_ord_empty_table)
{
	ASSERT_ANY_THROW(Oemp.Delete(5));
	ASSERT_ANY_THROW(Oemp.Delete(11));
}

TEST_F(TestingSetTables, delete_throws_in_hash_empty_table)
{
	ASSERT_ANY_THROW(Hemp.Delete(5));
	ASSERT_ANY_THROW(Hemp.Delete(11));
}


//-------------Тестирование методов навигации------------


//На пустых
TEST_F(TestingSetTables, correct_navigation_on_empty_unord_table)
{
	ASSERT_NO_THROW(Uemp.Reset());
	ASSERT_NO_THROW(Uemp.Move());
	EXPECT_EQ(true, Uemp.IsEnded());
	ASSERT_ANY_THROW(Uemp.GetCurr());
}

TEST_F(TestingSetTables, correct_navigation_on_empty_ord_table)
{
	ASSERT_NO_THROW(Oemp.Reset());
	ASSERT_NO_THROW(Oemp.Move());
	EXPECT_EQ(true, Oemp.IsEnded());
	ASSERT_ANY_THROW(Oemp.GetCurr());
}
TEST_F(TestingSetTables, correct_navigation_on_empty_hash_table)
{
	ASSERT_NO_THROW(Hemp.Reset());
	ASSERT_NO_THROW(Hemp.Move());
	EXPECT_EQ(true, Hemp.IsEnded());
	ASSERT_ANY_THROW(Hemp.GetCurr());
}

//На непустых

TEST_F(TestingSetTables, correct_navigation_on_filled_unord_table)
{
	ASSERT_NO_THROW(Ufil.Reset());
	EXPECT_EQ(11, Ufil.GetCurr().key);
	EXPECT_EQ(22, *Ufil.GetCurr().data);

	ASSERT_NO_THROW(Ufil.Move());
	EXPECT_EQ(5, Ufil.GetCurr().key);
	EXPECT_EQ(10, *Ufil.GetCurr().data);

	ASSERT_NO_THROW(Ufil.Move());
	EXPECT_EQ(7, Ufil.GetCurr().key);
	EXPECT_EQ(3, *Ufil.GetCurr().data);

	ASSERT_NO_THROW(Ufil.IsEnded());
	EXPECT_EQ(true, Ufil.IsEnded());

	ASSERT_NO_THROW(Ufil.Move());
	EXPECT_EQ(11, Ufil.GetCurr().key);
	EXPECT_EQ(22, *Ufil.GetCurr().data);

}

TEST_F(TestingSetTables, correct_navigation_on_filled_ord_table)
{
	ASSERT_NO_THROW(Ofil.Reset());
	EXPECT_EQ(5, Ofil.GetCurr().key);
	EXPECT_EQ(10, *Ofil.GetCurr().data);

	ASSERT_NO_THROW(Ofil.Move());
	EXPECT_EQ(7, Ofil.GetCurr().key);
	EXPECT_EQ(3, *Ofil.GetCurr().data);

	ASSERT_NO_THROW(Ofil.Move());
	EXPECT_EQ(11, Ofil.GetCurr().key);
	EXPECT_EQ(22, *Ofil.GetCurr().data);

	ASSERT_NO_THROW(Ofil.IsEnded());
	EXPECT_EQ(true, Ofil.IsEnded());

	ASSERT_NO_THROW(Ofil.Move());
	EXPECT_EQ(5, Ofil.GetCurr().key);
	EXPECT_EQ(10, *Ofil.GetCurr().data);
}
TEST_F(TestingSetTables, correct_navigation_on_filled_hash_table)
{
	ASSERT_NO_THROW(Hfil.Reset());
	EXPECT_EQ(11, Hfil.GetCurr().key);
	EXPECT_EQ(22, *Hfil.GetCurr().data);

	ASSERT_NO_THROW(Hfil.Move());
	EXPECT_EQ(5, Hfil.GetCurr().key);
	EXPECT_EQ(10, *Hfil.GetCurr().data);

	ASSERT_NO_THROW(Hfil.Move());
	EXPECT_EQ(7, Hfil.GetCurr().key);
	EXPECT_EQ(3, *Hfil.GetCurr().data);

	ASSERT_NO_THROW(Hfil.IsEnded());
	EXPECT_EQ(true, Hfil.IsEnded());

	ASSERT_NO_THROW(Hfil.Move());
	EXPECT_EQ(11, Hfil.GetCurr().key);
	EXPECT_EQ(22, *Hfil.GetCurr().data);
}
