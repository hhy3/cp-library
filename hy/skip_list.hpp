#pragma once

#include <vector>
#include <limits>
#include <cstdlib>

namespace hy {

template <typename T>
struct SkipList {
  struct Node {
    T val;
    std::vector<Node*> nxt, prv;
    Node(const T& x) : val(x) {}
  };
  Node *L, *R;

  SkipList() {
    L = new Node(std::numeric_limits<T>::min());
    R = new Node(std::numeric_limits<T>::max());
    L->nxt = {R};
    L->prv = {nullptr};
    R->prv = {L};
    R->nxt = {nullptr};
  }

  Node* lower_bound(const T& x) {
    Node* cur = L;
    for (int h = L->nxt.size(); h >= 0; h--) {
      while (h < cur->nxt.size() && cur->nxt[h]->val < x) cur = cur->nxt[h];
    }
    return cur->nxt[0];
  }

  void insert(const T& x) {
    Node* r = lower_bound(x);
    Node* l = r->prv[0];
    Node* it = new Node(x); 
    for (int h = 0; h == 0 || std::rand() % 2; h++) {
      if (h >= L->nxt.size()) {
        L->nxt.push_back(nullptr);
        L->prv.push_back(nullptr);
        R->nxt.push_back(nullptr);
        R->prv.push_back(nullptr);
      }
      while (h >= l->nxt.size()) l = l->prv[h-1];
      while (h >= r->nxt.size()) r = r->nxt[h-1];
      l->nxt[h] = it;
      r->prv[h] = it;
      it->nxt.push_back(r);
      it->prv.push_back(l);
    }
  }

  void erase(const T& x) {
    Node* it = find(x);
    if (it->val != x) return;
    for (int h = 0; h < it->nxt.size(); ++h) {
      it->nxt[h]->prv[h] = it->prv[h];
      it->prv[h]->nxt[h] = it->nxt[h];
    }
  }
  
  bool count(const T& x) {
    return lower_bound(x)->val == x;
  }
};

}  // namespace hy