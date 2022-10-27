#pragma once

#include <map>
#include <memory>
#include <vector>

namespace hy {

template <typename T = int> class PersistentStack {
public:
  PersistentStack() : root_(std::make_unique<Node>()), cur_(root_.get()) {
    root_->parent = root_.get();
  }

  void push(const T &x) {
    cur_->children.push_back(std::make_unique<Node>(x, cur_));
    cur_ = cur_->children.back().get();
  }

  void pop() { cur_ = cur_->parent; }

  void save(int version) { mp_[version] = cur_; }

  void load(int version) {
    if (!mp_.count(version)) {
      cur_ = root_.get();
    } else {
      cur_ = mp_[version];
    }
  }

  T &back() { return cur_->val; }

private:
  struct Node {
    T val;
    Node *parent;
    std::vector<std::unique_ptr<Node>> children;
    Node() = default;
    explicit Node(const T &x, Node *p = nullptr) : val(x), parent(p) {}
  };

  std::unique_ptr<Node> root_;
  Node *cur_;
  std::map<int, Node *> mp_;
};

} // namespace hy