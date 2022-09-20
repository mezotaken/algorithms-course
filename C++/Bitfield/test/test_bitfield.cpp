#include "bitfield.h"
#include <gtest.h>

TEST(BitField, can_create_bitfield_with_positive_length)
{
  ASSERT_NO_THROW(BitField bf(3));
}


TEST(BitField, can_get_length)
{
  BitField bf(3);
  EXPECT_EQ(3, bf.GetLength());
}

TEST(BitField, new_bitfield_is_set_to_zero)
{
  BitField bf(100);
  int sum = 0;
  for (int i = 0; i < bf.GetLength(); i++)
  {
    sum += bf.GetBit(i);
  }

  EXPECT_EQ(0, sum);
}

TEST(BitField, can_set_bit)
{
  BitField bf(10);

  EXPECT_EQ(0, bf.GetBit(3));

  bf.SetBit(3);
  EXPECT_NE(0, bf.GetBit(3));
}

TEST(BitField, can_clear_bit)
{
  BitField bf(10);

  bf.SetBit(3);
  EXPECT_NE(0, bf.GetBit(3));

  bf.ClrBit(3);
  EXPECT_EQ(0, bf.GetBit(3));
}

TEST(BitField, throws_when_create_bitfield_with_negative_length)
{
  ASSERT_ANY_THROW(BitField bf(-3););
}

TEST(BitField, throws_when_set_bit_with_negative_index)
{
  BitField bf(10);
  ASSERT_ANY_THROW(bf.SetBit(-3));
}

TEST(BitField, throws_when_set_bit_with_too_large_index)
{
  BitField bf(10);
  ASSERT_ANY_THROW(bf.SetBit(11));
}


TEST(BitField, throws_when_get_bit_with_negative_index)
{
  BitField bf(10);

  ASSERT_ANY_THROW(bf.GetBit(-3));
}

TEST(BitField, throws_when_get_bit_with_too_large_index)
{
  BitField bf(10);

  ASSERT_ANY_THROW(bf.GetBit(11));
}

TEST(BitField, throws_when_clear_bit_with_negative_index)
{
  BitField bf(10);

  ASSERT_ANY_THROW(bf.ClrBit(-3));
}

TEST(BitField, throws_when_clear_bit_with_too_large_index)
{
  BitField bf(10);

  ASSERT_ANY_THROW(bf.ClrBit(11));
}

TEST(BitField, can_assign_bitfields_of_equal_size)
{
  const int size = 2;
  BitField bf1(size), bf2(size);
  for (int i = 0; i < size; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_NE(0, bf2.GetBit(0));
  EXPECT_NE(0, bf2.GetBit(1));
}

TEST(BitField, assign_operator_changes_bitfield_size)
{
  const int size1 = 2, size2 = 5;
  BitField bf1(size1), bf2(size2);
  for (int i = 0; i < size1; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_EQ(2, bf2.GetLength());
}

TEST(BitField, can_assign_bitfields_of_non_equal_size)
{
  const int size1 = 2, size2 = 5;
  BitField bf1(size1), bf2(size2);
  for (int i = 0; i < size1; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_NE(0, bf2.GetBit(0));
  EXPECT_NE(0, bf2.GetBit(1));
}

TEST(BitField, compare_equal_bitfields_of_equal_size)
{
  const int size = 2;
  BitField bf1(size), bf2(size);
  for (int i = 0; i < size; i++)
  {
    bf1.SetBit(i);
  }
  bf2 = bf1;

  EXPECT_EQ(bf1, bf2);
}

TEST(BitField, or_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  BitField bf1(size), bf2(size), expBf(size);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 0101
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 0111
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(BitField, or_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 4, size2 = 5;
  BitField bf1(size1), bf2(size2), expBf(size2);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 01010
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 01110
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(BitField, and_operator_applied_to_bitfields_of_equal_size)
{
  const int size = 4;
  BitField bf1(size), bf2(size), expBf(size);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 0101
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 0001
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 & bf2);
}

TEST(BitField, and_operator_applied_to_bitfields_of_non_equal_size)
{
  const int size1 = 4, size2 = 5;
  BitField bf1(size1), bf2(size2), expBf(size2);
  // bf1 = 0011
  bf1.SetBit(2);
  bf1.SetBit(3);
  // bf2 = 01010
  bf2.SetBit(1);
  bf2.SetBit(3);

  // expBf = 00010
  expBf.SetBit(1);
  expBf.SetBit(2);
  expBf.SetBit(3);

  EXPECT_EQ(expBf, bf1 | bf2);
}

TEST(BitField, can_invert_bitfield)
{
  const int size = 2;
  BitField bf(size), negBf(size), expNegBf(size);
  // bf = 01
  bf.SetBit(1);
  negBf = ~bf;

  // expNegBf = 10
  expNegBf.SetBit(0);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(BitField, can_invert_large_bitfield)
{
  const int size = 38;
  BitField bf(size) , negBf(size), expNegBf(size);
  bf.SetBit(35);
  negBf = ~bf;

  for(int i = 0; i < size; i++)
    expNegBf.SetBit(i);
  expNegBf.ClrBit(35);
  EXPECT_EQ(expNegBf, negBf);
}

TEST(BitField, can_invert_many_random_bits_bitfield)
{
  const int size = 38;
  BitField bf(size), negBf(size), expNegBf(size);

  std::vector<int> bits;
  bits.push_back(0);
  bits.push_back(1);
  bits.push_back(14);
  bits.push_back(16);
  bits.push_back(33);
  bits.push_back(37);

  for (unsigned int i = 0; i < bits.size(); i++)
    bf.SetBit(bits[i]);

  negBf = ~bf;

  for(int i = 0; i < size; i++)
    expNegBf.SetBit(i);
  for (unsigned int i = 0; i < bits.size(); i++)
    expNegBf.ClrBit(bits[i]);

  EXPECT_EQ(expNegBf, negBf);
}

TEST(BitField, bitfields_with_different_bits_are_not_equal)
{
  const int size = 4;
  BitField bf1(size), bf2(size);

  bf1.SetBit(1);
  bf1.SetBit(3);

  bf2.SetBit(1);
  bf2.SetBit(2);

  EXPECT_NE(bf1, bf2);
}
TEST(BitField, can_combine_large_bitfields)
{
	BitField bf1(115), bf2(42),bf3(1);
	bf1.SetBit(100);
	bf2.SetBit(40);
	bf3 = bf1 | bf2;
	EXPECT_EQ(2, bf3.GetBit(100)+ bf3.GetBit(40));
}
TEST(BitField, can_intersect_large_bitfields)
{
	BitField bf1(255), bf2(107), bf3(1);
	bf1.SetBit(61);
	bf1.SetBit(220);
	bf2.SetBit(74);
	bf3 = bf1 | bf2;
	EXPECT_EQ(2, bf3.GetBit(61) + bf3.GetBit(74));
}
TEST(BitField, can_apply_multiple_operators)
{
	BitField bf1(17), bf2(37), bf3(60);
	bf1.SetBit(13);
	bf2.SetBit(36);
	bf3.SetBit(36);
	bf3.SetBit(11);
		bf1 = (~bf1 | bf2) & bf3;
	EXPECT_EQ(2, bf1.GetBitSum());
}