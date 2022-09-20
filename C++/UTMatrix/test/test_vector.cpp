#include "utmatrix.h"
#include <gtest.h>

TEST(Vector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(Vector<int> v(5));
}

TEST(Vector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(Vector<int> v(MAX_VECT_SIZE + 1));
}

TEST(Vector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(Vector<int> v(-5));
}

TEST(Vector, throws_when_create_vector_with_negative_startindex)
{
  ASSERT_ANY_THROW(Vector<int> v(5, -2));
}

TEST(Vector, can_create_copied_vector)
{
  Vector<int> v(10);
  ASSERT_NO_THROW(Vector<int> v1(v));
}

TEST(Vector, set_to_zero_on_creation)
{
	int s=0;
	Vector<int> v(16);
	for (int i = 0; i < 16; i++)
		s += v[i];
	EXPECT_EQ(0,s);
}

TEST(Vector, copied_vector_is_equal_to_source_one)
{
	Vector<int> v1(5);
	v1[1] = 36;
	v1[4] = 15;
	Vector<int> v2(v1);
	EXPECT_EQ(v1, v2);
}

TEST(Vector, copied_vector_has_its_own_memory)
{
	Vector<int> v1(5);
	Vector<int> v2(v1);
	EXPECT_NE(&v1[0],&v2[0]);
}

TEST(Vector, can_get_size)
{
  Vector<int> v(4);
  EXPECT_EQ(4, v.GetSize());
}

TEST(Vector, can_get_start_index)
{
  Vector<int> v(4, 2);
  EXPECT_EQ(2, v.GetStInd());
}

TEST(Vector, can_set_and_get_element)
{
  Vector<int> v(4);
  v[0] = 4;
  EXPECT_EQ(4, v[0]);
}

TEST(Vector, throws_when_set_element_with_negative_index)
{
	Vector<int> v(5);
	ASSERT_ANY_THROW(v[-5]);
}

TEST(Vector, throws_when_set_element_with_too_large_index)
{
Vector<int> v(5,3);
  ASSERT_ANY_THROW(v[8]);
}

TEST(Vector, compare_equal_vectors_return_true)
{
	Vector<int> v1(5);
	v1[3] = 17;
	Vector<int> v2(v1);
	EXPECT_EQ(v2,v1);
}

TEST(Vector, compare_vector_with_itself_return_true)
{
	Vector<int> v1(150);
	v1[3] = 19;
	EXPECT_EQ(v1,v1);
}

TEST(Vector, compare_vectors_with_different_size_return_false)
{
	Vector <int> v1(5);
	Vector <int> v2(10);
	EXPECT_NE(v1, v2);
}

TEST(Vector, can_assign_vector_to_itself)
{
	Vector<int> v(5);
	v[2] = 22;
	v = v;
	EXPECT_EQ(v,v);
}

TEST(Vector, can_assign_vectors_of_equal_size)
{
	Vector<int> v1(5);
	Vector<int> v2(5);
	v2[4] = 54;
	v1 = v2;
	EXPECT_EQ(v1,v2);
}

TEST(Vector, assign_operator_change_vector_size)
{
	Vector<int> v1(5);
	Vector<int> v2(10);
	v1 = v2;
	EXPECT_EQ(v1.GetSize(), 10);
}

TEST(Vector, can_assign_vectors_of_different_size)
{
	Vector<int> v1(5);
	v1[3] = 4;
	Vector<int> v2(10);
	v2 = v1;
	EXPECT_EQ(v1,v2);
}

TEST(Vector, can_fill_vector_with_value)
{
	Vector<int> v(5);
	v.Fill(10);
	int s = 0;
	for (int i = 0; i < 5; i++)
		s += v[i];
	EXPECT_EQ(50,s);
}

TEST(Vector, can_add_scalar_to_vector)
{
  Vector <int> v(5);
  v = v + 5;
  int s = 0;
  for (int i = 0; i < 5; i++)
	  s += v[i];
  EXPECT_EQ(25, s);
}

TEST(Vector, can_subtract_scalar_from_vector)
{
	Vector <int> v(5);
	v = v - 7;
	int s = 0;
	for (int i = 0; i < 5; i++)
		s += v[i];
	EXPECT_EQ(-35, s);
}

TEST(Vector, can_multiply_scalar_by_vector)
{
	Vector<int> v(5);
	v.Fill(1);
	v = v * 3;
	int s = 0;
	for (int i = 0; i < 5; i++)
		s += v[i];
	EXPECT_EQ(15,s);
}

TEST(Vector, can_add_vectors_with_equal_size)
{
	Vector<int> v1(5);
	Vector<int> v2(5);
	v1.Fill(7);
	v2.Fill(3);
	Vector<int> v3(v1 + v2);
	int s = 0;
	for (int i = 0; i < 5; i++)
		s += v3[i];
	EXPECT_EQ(50,s);
}

TEST(Vector, cant_add_vectors_with_not_equal_size)
{
	Vector<int> v1(7);
	Vector<int> v2(5); 
	ASSERT_ANY_THROW(Vector<int> v3(v1 + v2););
}

TEST(Vector, can_subtract_vectors_with_equal_size)
{
	Vector<int> v1(5);
	Vector<int> v2(5);
	v1.Fill(7);
	v2.Fill(3);
	Vector<int> v3(v1 - v2);
	int s = 0;
	for (int i = 0; i < 5; i++)
		s += v3[i];
	EXPECT_EQ(20, s);
}

TEST(Vector, cant_subtract_vectors_with_not_equal_size)
{
	Vector<int> v1(7);
	Vector<int> v2(5);
	ASSERT_ANY_THROW(Vector<int> v3(v1 - v2););
}

TEST(Vector, can_multiply_vectors_with_equal_size)
{
	Vector<int> v1(5);
	Vector<int> v2(5);
	v1.Fill(-2);
	v2.Fill(1);
	int sc = v1*v2;
	EXPECT_EQ(-10, sc);
}

TEST(Vector, cant_multiply_vectors_with_not_equal_size)
{
  Vector<int> v1(7);
  Vector<int> v2(5);
  ASSERT_ANY_THROW(int a = v1*v2);
}