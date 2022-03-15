#include <string>

#include "gtest/gtest.h"
#include "hy/trie.hpp"

using hy::ds::trie;

TEST(TrieTest, TestInsert) {
  trie tr;
  EXPECT_EQ(tr.nodes.size(), 1);
  tr.insert("hello");
  EXPECT_EQ(tr.nodes.size(), 6);
  std::string s = "world";
  tr.insert(s);
  EXPECT_EQ(tr.nodes.size(), 11);
  EXPECT_EQ(tr.nodes[5].count, 1);
  EXPECT_EQ(tr.nodes[10].count, 1);
  EXPECT_EQ(tr.nodes[7].count, 0);
}

TEST(TrieTest, TestErase) {
  trie tr;
  tr.insert("hello");
  tr.insert("world");
  tr.insert("hello");
  tr.erase("hello");
  EXPECT_EQ(tr.count("hello"), 1);
  tr.erase("hello");
  EXPECT_EQ(tr.count("hello"), 0);
  tr.erase("world");
  EXPECT_EQ(tr.count("world"), 0);
}

TEST(TrieTest, TestCount) {
  trie tr;
  tr.insert("hello");
  tr.insert("world");
  tr.insert("hello");
  EXPECT_EQ(tr.count("hello"), 2);
  EXPECT_EQ(tr.count("world"), 1);
}

TEST(TrieTest, TestStartswith) {
  trie tr;
  EXPECT_FALSE(tr.startswith("he"));
  tr.insert("hello");
  EXPECT_TRUE(tr.startswith("he"));
  tr.insert("world");
  tr.insert("hello");
  EXPECT_TRUE(tr.startswith("world"));
}
