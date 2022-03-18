#include "gtest/gtest.h"
#include "hy/AC.hpp"

using hy::ds::AC;

TEST(ACTest, TestInsert) {
  AC ac;
  ac.insert("hello");
  EXPECT_EQ(ac.nodes.size(), 6);
  EXPECT_EQ(ac.nodes[5].leaf, 1);
  EXPECT_EQ(ac.nodes[5].p, 4);
  EXPECT_EQ(ac.nodes[5].pch, 'o');
  ac.insert("heworld");
  EXPECT_EQ(ac.nodes.size(), 11);
  EXPECT_EQ(ac.nodes[6].p, 2);
  EXPECT_EQ(ac.nodes[6].pch, 'w');
}

TEST(ACTest, TestGetLink) {
  AC ac;
  ac.insert("hello");
  ac.insert("heworld");
  EXPECT_EQ(ac.get_link(0), 0);
  EXPECT_EQ(ac.get_link(1), 0);
  ac.insert("heworldhello");
  EXPECT_EQ(ac.get_link(15), 5);
  EXPECT_EQ(ac.get_link(11), 1);
}

TEST(ACTest, TestGo) {
  AC ac;
  ac.insert("hello");
  ac.insert("heworld");
  ac.insert("heworldhello");
  EXPECT_EQ(ac.go(0, 'h'), 1);
  EXPECT_EQ(ac.go(0, 'a'), 0);
  EXPECT_EQ(ac.go(1, 'a'), 0);
  EXPECT_EQ(ac.go(14, 'o'), 15);
  EXPECT_EQ(ac.go(12, 'w'), 6);
}

TEST(ACTest, TestCount) {
  AC ac;
  ac.insert("a");
  ac.insert("aa");
  ac.insert("aa");
  EXPECT_EQ(ac.count_pattern_in_text("aaa"), 3);
  ac = AC();
  ac.insert("a");
  ac.insert("ab");
  ac.insert("abc");
  ac.insert("ac");
  EXPECT_EQ(ac.count_pattern_in_text("abcd"), 3);
  ac = AC();
  ac.insert("dabce");
  ac.insert("abc");
  ac.insert("bc");
  EXPECT_EQ(ac.count_pattern_in_text("dabc"), 2);
}