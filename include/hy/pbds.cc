#include <bits/stdc++.h>
#include <bits/extc++.h>
using namespace std;
using namespace __gnu_pbds;
using namespace __gnu_cxx;

// 平衡树
template <typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// rb_tree_tag: 红黑树, splay_tree_tag: splay树
// 插入元素会去重，如果想实现multiset可以使用pair<T, int>，额外增加一个时间维度
// ordered_set tr
// tr.insert(x) 插入
// tr.erase(x) 删除
// tr.order_of_key(x)  x元素的排名 (0-indexed)
// tr.find_by_order(k) 第k大的元素的迭代器 (0-indexed)
// tr.lower_bound(x) >=x 最小元素的迭代器
// tr.upper_bound(x) >x 最小元素的迭代器
// tr1.join(tr2) 合并 (需要保证tr1与tr2不相交)
// tr1.split(x, tr2) 分裂，<=x的元素属于tr1, >x的元素属于tr2
// 可以用这道题练习用法 https://www.luogu.com.cn/problem/P3369


// 可持久化平衡树
rope<int> rt;
crope cr; // = rope<char>
// rt.push_back(x) 插入x
// rt.insert(pos, x) 在pos插入x
// rt.erase(pos, k) 从pos开始删除长度k
// rt.substr(pos, k) 从pos开始长度为k的字串
// 可持久化：
//    rope<int> *f[N];
//    f[i] = new rope<int>(*f[i-1])