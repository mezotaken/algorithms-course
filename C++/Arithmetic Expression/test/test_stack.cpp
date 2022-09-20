#include "stack.h"
#include "gtest.h"
TEST(Stack, can_create_empty_stack)
{
	ASSERT_NO_THROW(Stack<int> a;);
}
TEST(Stack, can_push_value)
{
	Stack<int> a;
	a.push(5);
	EXPECT_EQ(a.peek(),5);
}
TEST(Stack, can_pop_and_peek_value)
{
	Stack<int> a;
	a.push(6);
	a.push(17);
	EXPECT_EQ(a.pop(),17);
	EXPECT_EQ(a.peek(), 6);
}
TEST(Stack, can_get_size)
{
	Stack<int> a(10);
	EXPECT_EQ(a.GetSize(), 10);
}
TEST(Stack, can_check_stack_state)
{
	Stack<int> a(1);
	EXPECT_EQ(a.empty(), true);
}
TEST(Stack, expands_when_push_full_stack)
{
	Stack<int> a(1);
	a.push(1);
	EXPECT_EQ(1, a.GetSize());
	ASSERT_NO_THROW(a.push(2));
	EXPECT_EQ(2, a.GetSize());
}
TEST(Stack, throws_when_peek_or_pop_empty_stack)
{
	Stack<int> a;
	ASSERT_ANY_THROW(a.peek());
	ASSERT_ANY_THROW(a.pop());
}