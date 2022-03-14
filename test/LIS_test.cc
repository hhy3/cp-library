#include <vector>

#include "gtest/gtest.h"
#include "hy/LIS.hpp"

TEST(LISTest, LIS) {
  std::vector<int> v = {1, 4, 2, 3, 5, 6, 3, 6, 7};
  std::vector<int> lis;

  int len = hy::dp::LIS(v, lis);
  EXPECT_EQ(len, 6);
  EXPECT_EQ(len, (int)lis.size());
  for (int i = 1; i < (int)lis.size(); ++i) {
    EXPECT_EQ(lis[i-1] <= lis[i], true);
  }
}

// int main(int argc, char *argv[]) {
//   ::testing::InitGoogleTest(&argc, argv);
//   return RUN_ALL_TESTS();
// }
