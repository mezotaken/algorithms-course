#include <gtest.h>
#include "list.h"

TEST(lists, can_create_empty_list)
{
	ASSERT_NO_THROW(list<int> m);
}

class ExList : public ::testing::Test {
protected:
	list<int> emp;
	list<int> fil;

public:
	ExList()
	{
		fil.InsertInOrder(10);
		fil.InsertInOrder(1);
	}

	~ExList() {}
};

//Тесты для пустых списков

TEST_F(ExList, created_empty_list_is_correct)
{
	EXPECT_EQ(true, emp.IsEnded());
}

TEST_F(ExList, can_copy_empty_list)
{
	ASSERT_NO_THROW(list<int> m(emp));
}

TEST_F(ExList, copied_empty_list_is_correct)
{
	list<int> m(emp);
	EXPECT_EQ(true, m.IsEnded());
	EXPECT_NE(m.GetCurr(),emp.GetCurr());
}

TEST_F(ExList,can_assign_empty_list)
{
	ASSERT_NO_THROW(list<int> m = emp);
}

TEST_F(ExList, assigned_empty_list_is_correct)
{
	list<int> m = emp;
	EXPECT_EQ(true, m.IsEnded());
	EXPECT_NE(m.GetCurr(), emp.GetCurr());
}

TEST_F(ExList, can_insert_in_empty_list)
{
	ASSERT_NO_THROW(emp.InsertInOrder(5));
}

TEST_F(ExList, insert_in_empty_list_is_correct)
{
	emp.InsertInOrder(5);
	emp.Reset();
	EXPECT_EQ(5, emp.GetCurr()->data);
	EXPECT_EQ(emp.GetCurr()->next->next, emp.GetCurr());
}

TEST_F(ExList, can_compare_list_with_itself)
{
	EXPECT_EQ(true, emp==emp);
}

TEST_F(ExList, empty_lists_are_equal)
{
	list<int> m(emp);
	EXPECT_EQ(true, m == emp);
}

//Тесты для непустых списков

TEST_F(ExList, can_copy_filled_list)
{
	ASSERT_NO_THROW(list<int> m(fil));
}

TEST_F(ExList, copied_filled_list_is_correct)
{
	list<int> m(fil);
	m.Reset();
	EXPECT_EQ(1, m.GetCurr()->data);
	EXPECT_EQ(10, m.GetCurr()->next->data);
	EXPECT_EQ(m.GetCurr(), m.GetCurr()->next->next->next);
	m.Reset(); fil.Reset();
	EXPECT_NE(m.GetCurr()->next->next, fil.GetCurr()->next->next);
}

TEST_F(ExList, can_assign_filled_list)
{
	ASSERT_NO_THROW(list<int> m = fil);
}

TEST_F(ExList, assigned_filled_list_is_correct)
{
	list<int> m = fil;
	EXPECT_EQ(1, m.GetCurr()->data);
	EXPECT_EQ(10, m.GetCurr()->next->data);
	EXPECT_EQ(m.GetCurr(), m.GetCurr()->next->next->next);
	m.Reset(); fil.Reset();
	EXPECT_NE(m.GetCurr()->next->next, fil.GetCurr()->next->next);
}

TEST_F(ExList, insert_in_the_beginning)
{
	fil.InsertInOrder(0);
	fil.Reset();
	EXPECT_EQ(0, fil.GetCurr()->data);
	EXPECT_EQ(1, fil.GetCurr()->next->data);
	EXPECT_EQ(10,fil.GetCurr()->next->next->data);
	EXPECT_EQ(emp.GetCurr()->next->next->next->next, emp.GetCurr());
}

TEST_F(ExList, insert_in_the_middle)
{
	fil.InsertInOrder(5);
	fil.Reset();
	EXPECT_EQ(1, fil.GetCurr()->data);
	EXPECT_EQ(5, fil.GetCurr()->next->data);
	EXPECT_EQ(10, fil.GetCurr()->next->next->data);
	EXPECT_EQ(emp.GetCurr()->next->next->next->next, emp.GetCurr());
}

TEST_F(ExList, insert_in_the_end)
{
	fil.InsertInOrder(15);
	fil.Reset();
	EXPECT_EQ(1, fil.GetCurr()->data);
	EXPECT_EQ(10, fil.GetCurr()->next->data);
	EXPECT_EQ(15, fil.GetCurr()->next->next->data);
	EXPECT_EQ(emp.GetCurr()->next->next->next->next, emp.GetCurr());
}

TEST_F(ExList, filled_lists_are_equal)
{
	list<int> m(fil);
	EXPECT_EQ(true, m == fil);
}

TEST_F(ExList, empty_and_filled_lists_are_not_equal)
{
	EXPECT_EQ(false, fil == emp);
}

TEST_F(ExList, lists_with_different_sizes_and_same_beginnings_are_not_equal)
{
	emp.InsertInOrder(1);
	EXPECT_EQ(false, fil == emp);
}