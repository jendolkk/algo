template <typename T>
std::vector<int> topsort(const std::vector<std::vector<T>>& g) {
  int n = g.size();
  std::vector<int> deg(n);
  std::vector<int> q;
  for (const auto& x : g) {
    for (const auto y : x) {
      int v;
      if constexpr (std::integral<T>) {
        v = y;
      } else {
        v = std::get<0>(y);
      }
      deg[v]++;
    }
  }
  for (int i = 0; i < n; i++) {
    if (deg[i] == 0) {
      q.push_back(i);
    }
  }
  for (int i = 0; i < q.size(); i++) {
    for (const auto j : g[q[i]]) {
      int v;
      if constexpr (std::integral<T>) {
        v = j;
      } else {
        v = std::get<0>(j);
      }
      if (--deg[v] == 0) {
        q.push_back(v);
      }
    }
  }
  if (int(q.size()) != n) return {};
  return q;
}

