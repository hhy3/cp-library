#pragma once

#include <algorithm>
#include <array>
#include <cstring>
#include <memory>
#include <type_traits>

namespace hy {

// Inspired by https://github.com/ecnerwala/cp-book/blob/master/src/tensor.hpp
// with minor modification for more intuitive use.

template <typename T, int NDIMS> struct TensorView {
  std::array<int, NDIMS> shape, strides;
  T *data;

  TensorView() = default;

  TensorView(T *data_, const std::array<int, NDIMS> &shape_,
             const std::array<int, NDIMS> &strides_)
      : shape(shape_), strides(strides_), data(data_) {}

  template <int D = NDIMS, typename std::enable_if<(D > 1)>::type * = nullptr>
  TensorView<T, NDIMS - 1> operator[](int idx) const {
    std::array<int, NDIMS - 1> nshape;
    std::memcpy(&nshape[0], &shape[1], sizeof(shape[0]) * (NDIMS - 1));
    std::array<int, NDIMS - 1> nstrides;
    std::memcpy(&nstrides[0], &strides[1], sizeof(shape[0]) * (NDIMS - 1));
    T *ndata = data + strides[0] + idx;
    return TensorView<T, NDIMS - 1>(ndata, nshape, nstrides);
  }

  template <int D = NDIMS, typename std::enable_if<(D == 1)>::type * = nullptr>
  T &operator[](int idx) const {
    return data[idx];
  }
};

template <typename T, int NDIMS> struct Tensor {
  std::array<T, NDIMS> shape, strides;
  int len;
  std::unique_ptr<T[]> data;

  Tensor() = default;

  explicit Tensor(const std::array<int, NDIMS> &shape_, const T &x = T())
      : shape(shape_) {
    len = 1;
    for (int i = NDIMS - 1; i >= 0; --i) {
      strides[i] = len;
      len *= shape[i];
    }
    data = std::make_unique<T[]>(len);
    std::fill(data.get(), data.get() + len, x);
  }

  Tensor(const Tensor &rhs)
      : len(rhs.len), shape(rhs.shape), strides(rhs.strides),
        data(std::make_unique<T[]>(len)) {
    for (int i = 0; i < len; ++i) {
      data[i] = rhs.data[i];
    }
  }

  friend void swap(Tensor &lhs, Tensor &rhs) {
    using std::swap;
    swap(lhs.shape, rhs.shape);
    swap(lhs.strides, rhs.strides);
    swap(lhs.len, rhs.len);
    swap(lhs.data, rhs.data);
  }

  Tensor(Tensor &&rhs) noexcept { swap(*this, rhs); }

  Tensor &operator=(Tensor rhs) {
    swap(*this, rhs);
    return *this;
  }

  TensorView<T, NDIMS> view() {
    return TensorView<T, NDIMS>(data.get(), shape, strides);
  }

  template <int D = NDIMS, typename std::enable_if<(D > 1)>::type * = nullptr>
  TensorView<T, NDIMS - 1> operator[](int idx) {
    return view()[idx];
  }

  template <int D = NDIMS, typename std::enable_if<(D == 1)>::type * = nullptr>
  T &operator[](int idx) {
    return data[idx];
  }
};

} // namespace hy
