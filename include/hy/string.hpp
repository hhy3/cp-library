#pragma once

#include <vector>
#include <string>
#include <string_view>


namespace hy {
namespace string {


/**
 * @brief 前缀函数
 *        pi[i]表示s长度为n的前缀中最长公共真前后缀
 *        即 pi[i] = max_{k=0}^{i-1} \{len : s[0...k-1] = s[i-k...i-1]\}
 *        
 *        简介: 
 *            https://cp-algorithms.com/string/prefix-function.html
 * 
 *        模板题:
 *            https://www.luogu.com.cn/problem/P3375      
 * 
 *        练习题: 
 *            https://codeforces.com/problemset/problem/126/B
 *            https://codeforces.com/problemset/problem/432/D
 * 
 *        Time Complexity: O(n)
 * 
 */
std::vector<int> prefix_function(std::string_view s) {
  int n = (int)s.size();
  std::vector<int> pi(n+1);
  for (int i = 1, j = 0; i < n; ++i) {
    while (j > 0 && s[i] != s[j]) {
      j = pi[j];
    }
    if (s[i] == s[j]) {
      j++;
    } 
    pi[i + 1] = j;
  }
  return pi;
}

/**
 * @brief kmp (Knuth–Morris–Pratt) 算法
 *        
 *        简介: 
 *            https://cp-algorithms.com/string/prefix-function.html
 *            
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P3375
 *        
 *        练习题:
 *            TODO
 * 
 *        Time Complexity: O(n + m)
 * 
 */
std::vector<int> kmp(std::string_view s, std::string_view p) {
  int n = s.size(), m = p.size();
  auto pi = prefix_function(p);
  std::vector<int> matches;
  for (int i = 0, j = 0; i < n; ++i) {
    while (j && s[i] != p[j]) {
      j = pi[j];
    }
    j += (s[i] == p[j]);
    if (j == m) {
      matches.push_back(i - m + 1);
      j = pi[j];
    }
  }
  return matches;
}

/**
 * @brief 字符串哈希
 * 
 *        简介: 
 *            https://oi-wiki.org/string/hash/
 *        
 *        模板题: 
 *            luogu.com.cn/problem/P3370
 * 
 */
template <uint64_t K=13331>
struct string_hash {

  int n;
  std::vector<uint64_t> h, power;


  /**
   * @brief Construct a new string hash object
   *
   *        Time Complexity: O(n)
   *  
   */
  string_hash(std::string_view s)
    : n((int)s.size()), h(n+1), power(n+1) {
    power[0] = 1;
    for (int i = 1; i <= n; ++i) {
      h[i] = h[i-1] * K + s[i-1];
      power[i] = power[i-1] * K;
    }  
  }

  /**
   * @brief Get hash value of substring s[l:r] 
   *        
   *        Time Complexity: O(1)
   * 
   */
  uint64_t get(int l, int r) {
    return h[r+1] - h[l] * power[r - l + 1];
  }

  /**
   * @brief Get hash value of the whole string s
   *        
   *        Time Complexity: O(1)
   * 
   */
  uint64_t get() {
    return get(0, n-1);
  }

};

/**
 * @brief Z函数 (扩展KMP)
 *        
 *        简介: 
 *            https://cp-algorithms.com/string/z-function.html
 *        
 *        模板题: 
 *            https://www.luogu.com.cn/problem/P5410
 *        
 *        练习题: 
 *            TODO
 *        
 *        Time Complexity: O(n)
 * 
 */
std::vector<int> Z(std::string_view s) {
  int n = (int)s.size();
  std::vector<int> z(n);
  for (int i = 1, l = 0, r = 0; i < n; ++i) {
    if (i <= r) {
      z[i] = std::min(z[i-l], r - i + 1);
    }
    while (i + z[i] < n && s[i+z[i]] == s[z[i]]) {
      z[i]++;
    }
    if (i + z[i] - 1 > r) {
      l = i, r = i + z[i] - 1;
    }
  }
  return z;

}



} // namespace string
} // namespace hy