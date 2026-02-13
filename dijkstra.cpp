template <typename T>
std::vector<T> dij(const std::vector<std::vector<std::pair<int, T>>>& g, int st) {
  assert(0 <= st && st < g.size());
  int n = g.size();
  std::vector<T> d(n, std::numeric_limits<T>::max());
  using pti = std::pair<T, int>;
  std::priority_queue<pti, std::vector<pti>, std::greater<pti>> h;
  h.emplace(0, st);
  d[st] = 0;
  while (!h.empty()) {
    auto [dist, u] = h.top();
    h.pop();
    if (d[u] != dist) {
      continue;
    }
    for (auto [v, cost] : g[u]) {
      if (d[v] > dist + cost) {
        d[v] = dist + cost;
        h.emplace(d[v], v);
      }
    }
  }
  return d;
}

