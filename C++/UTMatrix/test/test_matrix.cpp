#include "utmatrix.h"
#include <gtest.h>

TEST(Matrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(Matrix<int> m(5));
}

TEST(Matrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(Matrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(Matrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(Matrix<int> m(-5));
}

TEST(Matrix, can_create_copied_matrix)
{
  Matrix<int> m(5);
  ASSERT_NO_THROW(Matrix<int> m1(m));
}

TEST(Matrix, copied_matrix_is_equal_to_source_one)
{
	Matrix<int> m1(5);
	m1[1][1] = 2;
	Matrix<int> m2(m1);
	EXPECT_EQ(m1,m2);
}

TEST(Matrix, compare_equal_matrices_return_true)
{
	Matrix<int> m1(5);
	m1[1][1] = 2;
	Matrix<int> m2(5);
	m2[1][1] = 2;
	EXPECT_EQ(true, m1 == m2);
}

TEST(Matrix, compare_matrix_with_itself_return_true)
{
	Matrix<int> m1(5);
	EXPECT_EQ(true, m1 == m1);
}

TEST(Matrix, matrices_with_different_size_are_not_equal)
{
	Matrix<int> m1(5);
	m1[1][1] = 2;
	Matrix<int> m2(7);
	m2[1][1] = 2;
	EXPECT_EQ(true, m1 != m2);
}

TEST(Matrix, copied_matrix_has_its_own_memory)
{
	Matrix<int> m1(5);
	Matrix<int> m2(m1);
	EXPECT_NE(&m1[0],&m2[0]);
}

TEST(Matrix, can_get_size)
{
	Matrix<int> m(5);
	EXPECT_EQ(m.GetSize(),5);
}

TEST(Matrix, can_set_and_get_element)
{
	Matrix<int> m(5);
	m[2][2] = 3;
	EXPECT_EQ(m[2][2], 3);
}

TEST(Matrix, throws_when_set_element_with_negative_index)
{
	Matrix<int> m(5);
	ASSERT_ANY_THROW(m[-2][-2] = 3;);
}

TEST(Matrix, throws_when_set_element_with_too_large_index)
{
	Matrix<int> m(5);
	ASSERT_ANY_THROW(m[3][10] = 3;);
	ASSERT_ANY_THROW(m[7][1] = 3;);
}

TEST(Matrix, throws_when_set_element_from_lower_triangle)
{
	Matrix<int> m(5);
	ASSERT_ANY_THROW(m[2][0] = 3;);
}

TEST(Matrix, can_assign_matrix_to_itself)
{
  Matrix<int> m(5);
  m = m;
  EXPECT_EQ(m,m);
}

TEST(Matrix, can_assign_matrices_of_equal_size)
{
	Matrix<int> m1(5);
	m1[1][1] = 2;
	Matrix<int> m2(5);
	m2 = m1;
	EXPECT_EQ(m1,m2);
}

TEST(Matrix, assign_operator_change_matrix_size)
{
	Matrix<int> m1(7);
	m1[1][1] = 2;
	Matrix<int> m2(5);
	m2 = m1;
	EXPECT_EQ(m2.GetSize(), 7);
}

TEST(Matrix, can_assign_matrices_of_different_size)
{
	Matrix<int> m1(7);
	m1[1][1] = 2;
	Matrix<int> m2(5);
	m2 = m1;
	EXPECT_EQ(m2,m1);
}

TEST(Matrix, can_add_matrices_with_equal_size)
{
	Matrix<int> m1(5);
	m1[1][1] = 2;
	Matrix<int> m2(5);
	m2[1][1] = 2;
	Matrix<int> m3(m1+m2);
	EXPECT_EQ(m3[1][1], 4);
}

TEST(Matrix, cant_add_matrices_with_not_equal_size)
{
	Matrix<int> m1(5);
	Matrix<int> m2(8);
	ASSERT_ANY_THROW(Matrix<int> m3(m1 + m2););
}

TEST(Matrix, can_subtract_matrices_with_equal_size)
{
	Matrix<int> m1(5);
	m1[1][1] = 2;
	Matrix<int> m2(5);
	m2[1][1] = 2;
	Matrix<int> m3(m1 - m2);
	EXPECT_EQ(m3[1][1], 0);
}

TEST(Matrix, cant_subtract_matrixes_with_not_equal_size)
{
	Matrix<int> m1(5);
	Matrix<int> m2(8);
	ASSERT_ANY_THROW(Matrix<int> m3(m1 - m2););
}

