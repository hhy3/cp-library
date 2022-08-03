#include <bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include <fmt/format.h>
#include <fmt/ranges.h>
using fmt::print;
#else
#define print(...) 42
#endif


void solve() {

}


#define MULTIPLE_CASE 1
#define GOOGLE 0
int main() {
  ios::sync_with_stdio(0), cin.tie(0), cout.tie(0);
#if MULTIPLE_CASE
  int ncase; cin >> ncase;
  for (int i = 1; i <= ncase; ++i) {
#endif
#if GOOGLE
    cout << "Case #" << i << ": ";
#endif
    solve();
#if MULTIPLE_CASE
  }
#endif
}
