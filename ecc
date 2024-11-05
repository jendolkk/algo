template <typename T>
std::vector<std::vector<int>> ecc(const std::vector<std::vector<T>>& g) {
  int n = g.size();
  std::vector<int> pos(n, -1), stk;
  std::vector<vector<int>> res;
  auto dfs = [&](auto self, int u, int p) -> int {
    int low = pos[u] = stk.size(), counter = 0;
    stk.push_back(u);
    for (const auto j : g[u]) {
      int v;
      if constexpr (std::is_integral_v<std::decay_t<decltype(j)>>) {
        v = j;
      } else {
        v = std::get<0>(j);
      }
      if (pos[v] != -1) {
        if (v != p || counter++) {
          low = std::min(low, pos[v]);
        }
      } else {
        low = std::min(low, self(self, v, u));
      }
    };
    if (low == pos[u]) {
      res.emplace_back(stk.begin() + low, stk.end());
      stk.resize(low);
    }
    return low;
  };
  for (int i = 0; i < n; i++) {
    if (pos[i] == -1) {
      dfs(dfs, i, -1);
    }
  }
  return res;
}

