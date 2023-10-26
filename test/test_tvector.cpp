#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
    const size_t size = 10;
    TDynamicVector<int> v(size);
    for (size_t i = 0; i < size; i++)
        v[i] = i;

    TDynamicVector<int> v1(v);

    ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v(10);
    TDynamicVector<int> copy(v);
    copy[2] = 5;

    ASSERT_NE(copy[2], v[2]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(10);

    ASSERT_ANY_THROW(v[-1]);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(10);

    ASSERT_ANY_THROW(v[10]);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(10);

    ASSERT_NO_THROW(v = v);
    ASSERT_EQ(v, v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    const size_t size = 10;
    TDynamicVector<int> v1(size);
    TDynamicVector<int> v2(size);

    for (size_t i = 0; i < size; i++)
        v1[i] = v2[i] = i;

    ASSERT_NO_THROW(v1 = v2);
    ASSERT_EQ(v1, v2);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(10);
    TDynamicVector<int> v2(20);

    v1 = v2;

    ASSERT_EQ(20, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(10);
    TDynamicVector<int> v2(20);

    ASSERT_NO_THROW(v1 = v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    const size_t size = 10;
    TDynamicVector<int> v1(size);
    TDynamicVector<int> v2(size);

    for (size_t i = 0; i < size; i++)
        v1[i] = v2[i] = i;

    ASSERT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(10);
    ASSERT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(10);
    TDynamicVector<int> v2(20);
    ASSERT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v1(5);
    for (size_t i = 0; i < 5; i++)
        v1[i] = 1;

    TDynamicVector<int> v2(5);
    v2 = v1 + 1;

    for (size_t i = 0; i < 5; i++)
        ASSERT_EQ(2, v2[i]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v1(5);
    for (size_t i = 0; i < 5; i++)
        v1[i] = 5;

    TDynamicVector<int> v2(2);
    v2 = v1 - 4;

    for (size_t i = 0; i < 5; i++)
        ASSERT_EQ(1, v2[i]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v1(2), v2(2);
    v1[0] = v1[1] = 2;
    v2 = v1 * 3;

    ASSERT_EQ(6, v2[0]);
    ASSERT_EQ(6, v2[1]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(4), v2(4), v3(4);
    for (size_t i = 0; i < 4; i++)
    {
        v1[i] = i;
        v2[i] = i;
    }
    v3 = v1 + v2;
    for (size_t i = 0; i < 4; i++)
    {
        ASSERT_EQ(2 * i, v3[i]);
    }
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(5), v2(4);

    ASSERT_THROW(v1 + v2, std::out_of_range);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(4), v2(4), v3(4);
    for (size_t i = 0; i < 4; i++)
    {
        v1[i] = 5;
        v2[i] = 2;
    }
    v3 = v1 - v2;
    for (size_t i = 0; i < 4; i++)
    {
        ASSERT_EQ(3, v3[i]);
    }
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(5), v2(4);
    ASSERT_THROW(v1 - v2, std::out_of_range);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(4), v2(4), v3(4);
    for (size_t i = 0; i < 4; i++)
    {
        v1[i] = 5;
        v2[i] = 2;
    }
    v3 = v1 * v2;
    for (size_t i = 0; i < 4; i++)
    {
        ASSERT_EQ(10, v3[i]);
    }
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(5), v2(4);
    ASSERT_THROW(v1 * v2,out_of_range);
}

