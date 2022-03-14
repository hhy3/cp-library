#include "gtest/gtest.h"
#include "hy/union_find.hpp"


TEST(UnionFindTest, TestInit) {
	hy::ds::union_find uf(10);
	for (int i = 1; i <= 10; ++i) {
		EXPECT_EQ(uf.find(i), i);
		EXPECT_EQ(uf.size(i), 1);
	}
}


TEST(UnionFindTest, TestMerge) {
	hy::ds::union_find uf(10);
	uf.merge(1, 2);
	uf.merge(2, 5);
	uf.merge(3, 4);
	uf.merge(4, 10);
	EXPECT_EQ(uf.is_connected(1, 5), true);
	EXPECT_EQ(uf.is_connected(3, 10), true);
}

TEST(UnionFindTest, TestSize) {
	hy::ds::union_find uf(10);
	uf.merge(1, 2);
	uf.merge(2, 5);
	uf.merge(3, 4);
	uf.merge(4, 10);
	EXPECT_EQ(uf.size(2), 3);
	uf.merge(10, 9);
	EXPECT_EQ(uf.size(10), 4);
	uf.merge(2, 9);
	EXPECT_EQ(uf.size(1), 7);
}
