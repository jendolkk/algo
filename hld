struct hld {
  int n;
  std::vector<int> parent, depth, sz, top, pos, end, order;
  std::vector<std::vector<int>> g;
  
  hld(int _n) : n(_n), parent(n ,-1), depth(n), sz(n),
              top(n, -1), pos(n), end(n), g(n) {}

  void add(int from, int to) {
    assert(0 <= from && from < n && 0 <= to && to < n);
    g[from].push_back(to);
    g[to].push_back(from);
  }

  void build(int root = 0) {
    for (int k = 0; k < 2; k++) {
      dfs(root);
      if (k) break;
      for (int i = 0; i < n; i++) {
        if (!g[i].empty()) {
          int hs = 0, h = 0;
          for (int j = 0; j < static_cast<int>(g[i].size()); j++) {
            int t = g[i][j];
            if (parent[t] == i && sz[t] > h) {
              h = sz[t], hs = j;
            }
          }
          std::swap(g[i][0], g[i][hs]);
        }
      }
      order.clear();
    }
    for (int i = 0; i < n; i++) {
      top[i] = i;
    }
    for (int i = 0; i < n - 1; i++) {
      int x = order[i];
      int y = order[i + 1];
      if (parent[y] == x) {
        top[y] = top[x];
      }
    }
    assert(static_cast<int>(order.size()) == n);
  }

  void dfs(int u) {
    pos[u] = static_cast<int>(order.size());
    order.push_back(u);
    sz[u] = 1;
    for (int v : g[u]) {
      if (v != parent[u]) {
        parent[v] = u;
        depth[v] = depth[u] + 1;
        dfs(v);
        sz[u] += sz[v];
      }
    }
    end[u] = static_cast<int>(order.size());  // [pos, end)
  }

  bool anc(int u, int v) {
    return pos[u] <= pos[v] && end[v] <= end[u];
  }

  int lca(int u, int v) {
    if (anc(u, v)) return u;
    if (anc(v, u)) return v;
    while (top[u] != top[v]) {
      if (depth[top[u]] > depth[top[v]]) u = parent[top[u]];
      else v = parent[top[v]];
    }
    return depth[u] < depth[v] ? u : v;
  }
  
  int dist(int u, int v) {
    return depth[u] + depth[v] - 2 * depth[lca(u, v)];
  }
  
  int jump(int u, int k) {
    if (depth[u] < k) {
      return -1;
    }
    int d = depth[u] - k;
    while (depth[top[u]] > d) {
      u = parent[top[u]];
    }
    return order[pos[u] - depth[u] + d];
  }

  auto path(int u, int v, bool with_lca) {
    assert(!top.empty());
    std::vector<std::tuple<int, int, bool>> from_u_to_lca;
    std::vector<std::tuple<int, int, bool>> from_v_to_lca;
    while (top[u] != top[v]) {
      if (depth[top[u]] > depth[top[v]]) {
        from_u_to_lca.emplace_back(pos[top[u]], pos[u], true);
        u = parent[top[u]];
      } else {
        from_v_to_lca.emplace_back(pos[top[v]], pos[v], false);
        v = parent[top[v]];
      }
    }
    if (u == v) {
      if (with_lca) {
        from_u_to_lca.emplace_back(pos[u], pos[u], false);
      }
    } else if (depth[u] > depth[v]) {
      from_u_to_lca.emplace_back(pos[v] + !with_lca, pos[u], true);
    } else {
      from_v_to_lca.emplace_back(pos[u] + !with_lca, pos[v], false);
    }
    from_u_to_lca.insert(from_u_to_lca.end(), from_v_to_lca.rbegin(), from_v_to_lca.rend());
    return from_u_to_lca;
  }
};

