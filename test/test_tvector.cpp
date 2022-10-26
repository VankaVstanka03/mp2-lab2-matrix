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

TEST(TDynamicVector, copied_vector_is_equal_to_source_one){
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(v1);

	EXPECT_EQ(v1, v2);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory){
	TDynamicVector<int> v1(5);
	TDynamicVector<int> v2(v1);

	EXPECT_NE(&v1, &v2);
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
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(v.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);

	ASSERT_ANY_THROW(v.at(10) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself){
	TDynamicVector<int> v(4);

	ASSERT_NO_THROW(v = v);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(4);

	v1[0] = 5;
	v2[3] = 10;
	v1 = v2;

	EXPECT_EQ(10, v1[3]);
}

TEST(TDynamicVector, assign_operator_change_vector_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(6);

	int tmp = v1.size();
	v1 = v2;

	EXPECT_NE(tmp, v1.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(6);

	v1[0] = 5;
	v2[3] = 10;
	v1 = v2;

	EXPECT_EQ(v2.size(), v1.size());
	EXPECT_EQ(10, v1[3]);

}

TEST(TDynamicVector, compare_equal_vectors_return_true){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(4);

	v1[1] = 10;
	v2[1] = 10;
	v1[3] = 5;
	v2[3] = 5; 

	//v1: 0 10 0 5
	//v2: 0 10 0 5

	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true){
	TDynamicVector<int> v1(4);

	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(6);

	EXPECT_FALSE(v1 == v2);

}

TEST(TDynamicVector, can_add_scalar_to_vector){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2 = v1 + 1;
	TDynamicVector<int> exp_res(4);

	exp_res[0] = 1;
	exp_res[1] = 1;
	exp_res[2] = 1;
	exp_res[3] = 1;

	EXPECT_EQ(exp_res, v2);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2 = v1 - 1;
	TDynamicVector<int> exp_res(4);

	exp_res[0] = -1;
	exp_res[1] = -1;
	exp_res[2] = -1;
	exp_res[3] = -1;

	EXPECT_EQ(exp_res, v2);

}

TEST(TDynamicVector, can_multiply_scalar_by_vector){
	TDynamicVector<int> v1(5);
	v1[0] = 1;
	v1[1] = 1;
	v1[2] = 1;
	v1[3] = 1;
	v1[4] = 1;
	TDynamicVector<int> v2 = v1 * 5;
	TDynamicVector<int> exp_res(5);

	exp_res[0] = 5;
	exp_res[1] = 5;
	exp_res[2] = 5;
	exp_res[3] = 5;
	exp_res[4] = 5;

	EXPECT_EQ(exp_res, v2);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(4);
	TDynamicVector<int> exp_res(4);

	v1[0] = 3;
	v1[2] = 5;
	v2[1] = 7;
	v2[3] = 11;

	exp_res[0] = 3; //v1: 3 0 5 0
	exp_res[1] = 7; //v2: 0 7 0 11
	exp_res[2] = 5; //exp_res: 3 7 5 11
	exp_res[3] = 11;

	EXPECT_EQ(exp_res, v1 + v2);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(5);

	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(4);
	TDynamicVector<int> exp_res(4);

	v1[0] = 3;
	v1[2] = 5;
	v2[1] = 7;
	v2[3] = 11;

	exp_res[0] = 3; //v1: 3 0 5 0
	exp_res[1] = -7; //v2: 0 7 0 11
	exp_res[2] = 5; //exp_res: 3 -7 5 -11
	exp_res[3] = -11;

	EXPECT_EQ(exp_res, v1 - v2);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(5);

	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(4);
	int exp;

	v1[0] = 2;
	v1[1] = 1;
	v1[2] = 3;
	v1[3] = 4;
	v2[0] = 2;
	v2[1] = 1;
	v2[2] = 1; //v1: 2 1 3 4
	v2[3] = 4; //v2: 2 1 1 4
	exp = 24;

	EXPECT_EQ(exp, v1 * v2);
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size){
	TDynamicVector<int> v1(4);
	TDynamicVector<int> v2(5);

	ASSERT_ANY_THROW(v1 * v2);
}

