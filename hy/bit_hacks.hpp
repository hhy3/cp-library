#pragma once

// compute the sign of an int
#define SIGN(x) (1 | ((x) >> (sizeof(x)-1)))

// detect if two ints have opposite sign
#define OPSIGN(x, y) (((x) ^ (y)) < 0)

// max and min
#define MAX(x, y) ((y) ^ ((x) ^ (y)) & -((x) - (y)))
#define MIN(x, y) ((x) ^ ((x) ^ (y)) & -((x) - (y)))

// test if an int is power of 2
#define IS_POWER2(x) ((x) & ((x) == ((x) & -(x))))

// swap ith and jth bit of an int
template <typename T> T swap_bits(T x, int i, int j) {
  T mask = ((x >> i) ^ (x >> j)) & 1;
  return x ^ ((mask << i) | (mask << j));
}

// lexicographically next bit permutation
unsigned nextp(unsigned x) {
  unsigned t = x | (x - 1);
  return (t + 1) | (((~t & -(~t)) - 1) >> (__builtin_ctz(x) + 1));
}