template <typename T>
struct vcc {
  const std::vector<std::vector<T>>& g;
  std::vector<int> pos;
  std::vector<int> stk;
  std::vector<std::vector<int>> res;
  std::vector<bool> cut;

  vcc(const std::vector<std::vector<T>>& t): g(t), pos(int(t.size()), -1), cut(int(t.size())) {
    run();
  }

  int dfs(int u, int p) {
    int low = pos[u] = int(stk.size());
    int son = 0;
    stk.push_back(u);
    for (const auto j : g[u]) {
      int v;
      if constexpr (std::is_integral_v<std::decay_t<decltype(j)>>) {
        v = j;
      } else {
        v = std::get<0>(j);
      }
      if (v != p) {
        if (pos[v] != -1) {
          low = std::min(low, pos[v]);
        } else {
          int cur = int(stk.size());
          int low_v = dfs(v, u);
          low = std::min(low, low_v);
          if (low_v >= pos[u] && (p != -1 || son++)) {
            cut[u] = true;
            res.emplace_back(stk.begin() + cur, stk.end());
            res.back().push_back(u);
            stk.resize(cur);
          }
        }
      }
    }
    return low;
  }

  void run() {
    for (int i = 0; i < int(g.size()); i++) {
      if (pos[i] == -1) {
        dfs(i, -1);
        res.emplace_back(move(stk));
      }
    }
  }
};

