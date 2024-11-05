template <typename T>
class scc {
 public:
  const std::vector<std::vector<T>>& g;
  std::vector<int> stk, pos, bel;
  std::vector<std::vector<int>> res;
  
  scc(const std::vector<std::vector<T>>& t) : g(t), pos(t.size(), -1), bel(t.size(), -1) {
    run();
  }
  
  int dfs(int u) {
    int low = pos[u] = stk.size();
    stk.push_back(u);
    for (const auto j : g[u]) {
      int v;
      if constexpr (std::is_integral_v<std::decay_t<decltype(j)>>) {
        v = j;
      } else {
        v = std::get<0>(j);
      }
      if (bel[v] == -1) {
        low = std::min(low, pos[v] == -1 ? dfs(v) : pos[v]);
      }
    }
    if (pos[u] == low) {
      res.emplace_back(stk.begin() + low, stk.end());
      for (const int v : res.back()) {
        bel[v] = int(res.size()) - 1;
      }
      stk.resize(low);
    }
    return low;
  }
  
  void run() {
    for (int i = 0; i < g.size(); i++) {
      if (pos[i] == -1) {
        dfs(i);
      }
    }
    std::swap(pos, bel);
  }
};

