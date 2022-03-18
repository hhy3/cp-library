#include "gtest/gtest.h"
#include "hy/string.hpp"

using hy::string::prefix_function;
using hy::string::kmp;
using hy::string::string_hash;
using hy::string::Z;

TEST(StringTest, TestPrefixFunction) {
  auto pi = prefix_function("abcabcd");
  EXPECT_EQ(pi, (std::vector<int>{0, 0, 0, 0, 1, 2, 3, 0}));
  pi = prefix_function("aabaaab");
  EXPECT_EQ(pi, (std::vector<int>{0, 0, 1, 0, 1, 2, 2, 3}));
}

TEST(StringTest, TestKMP) {
  auto matches = kmp("ABABABC", "ABA");
  EXPECT_EQ(matches, (std::vector<int>{0, 2}));
}

TEST(StringTest, TestStringHash) {
  string_hash sh("hello hello world");
  EXPECT_EQ(sh.get(0, 4), sh.get(6, 10));
  EXPECT_NE(sh.get(0, 4), sh.get(12, 16));
}

TEST(StringTest, TestZ) {
  EXPECT_EQ(Z("aaaaa"), 
            (std::vector<int>{0, 4, 3, 2, 1}));
  EXPECT_EQ(Z("aaabaab"), 
            (std::vector<int>{0, 2, 1, 0, 2, 1, 0}));
  EXPECT_EQ(Z("abacaba"), 
            (std::vector<int>{0, 0, 1, 0, 3, 0, 1}));
}