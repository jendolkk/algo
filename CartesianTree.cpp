template <typename T, class Compare = std::less<T>>
class CartesianTree {
 public:
  std::vector<int> ls, rs, sz, lb, rb;
  int root = -1, n;

  CartesianTree(const std::vector<T>& a, Compare comp = Compare())
      : n(a.size()), ls(a.size(), -1), rs(a.size(), -1) {
    assert(!a.empty());
    std::vector<int> stk;
    for (int i = 0; i < n; i++) {
      int lst = -1;
      while (!stk.empty() && comp(a[i], a[stk.back()])) {
        lst = stk.back();
        stk.pop_back();
      }
      ls[i] = lst;
      if (!stk.empty()) {
        rs[stk.back()] = i;
      }
      stk.push_back(i);
    }
    root = stk.front();
  }

  std::vector<int> build_sz() {
    sz.assign(n, 1);
    lb.resize(n);
    rb.resize(n);
    auto dfs = [&](auto self, int u) -> int {
      lb[u] = rb[u] = u;
      if (ls[u] != -1) {
        sz[u] += self(self, ls[u]);
        lb[u] = lb[ls[u]];
      }
      if (rs[u] != -1) {
        sz[u] += self(self, rs[u]);
        rb[u] = rb[rs[u]];
      }
      return sz[u];
    };
    dfs(dfs, root);
    return sz;
  }
};

