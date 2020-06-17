#include "gtest/gtest.h"
#include "SmallInteger.h"
#include <type_traits>

typedef ::testing::Types<
	SmallInteger_sioimath,
	SmallInteger_1,
	SmallInteger_2,
	SmallInteger_3> TestTypes;

template <class T>
class TestSI : public testing::Test {

};

TYPED_TEST_SUITE(TestSI, TestTypes);

TYPED_TEST(TestSI, CreateZero) {
  TypeParam Zero;
  EXPECT_TRUE(Zero.isZero());
}

TYPED_TEST(TestSI, CreateOne) {
  TypeParam One;
  One = 1;
  EXPECT_FALSE(One.isZero());
  One = 0;
  EXPECT_TRUE(One.isZero());
}

TYPED_TEST(TestSI, Add) {
  TypeParam One;
  One = 1;
  TypeParam NegOne;
  NegOne = -1;
  EXPECT_TRUE((One + NegOne).isZero());
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
