        
template <typename T>
struct maxflow {
  static constexpr T eps = (T) 1e-9;

  struct edge {
    int from;
    int to;
    T c;
    T f;
    edge(int _from, int _to, T _c, T _f): from(_from), to(_to), c(_c), f(_f) {}
  };

  int n, s, t;
  std::vector<edge> edges;
  std::vector<std::vector<int>> g;
  std::vector<int> d, cur, q;
  T flow = 0;

  maxflow() {}

  maxflow(int _n, int _s, int _t) {
    init(_n, _s, _t);
  }

  void init() {
    d.resize(n);
    q.resize(n);
    cur.resize(n);
    edges.clear();
    g.assign(n, {});
  }

  void init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t;
    init();
  }

  void add(int u, int v, T forward, T backward) {
    g[u].push_back((int) edges.size());
    edges.emplace_back(u, v, forward, 0);
    g[v].push_back((int) edges.size());
    edges.emplace_back(v, u, backward, 0);
  }

  bool bfs() {
    int hh = 0, tt = 0;
    q[tt++] = s;
    std::fill(d.begin(), d.end(), -1);
    std::fill(cur.begin(), cur.end(), 0);
    d[s] = 0;
    while (hh < tt) {
      int ver = q[hh++];
      for (int id : g[ver]) {
        auto [from, to, c, f] = edges[id];
        if (d[to] == -1 && c - f > eps) {
          d[to] = d[ver] + 1;
          if (to == t) return true;
          q[tt++] = to;
        }
      }
    }
    return false;
  }

  T dfs(int u, T limit) {
    if (u == t) return limit;
    T flow {};
    for (int i = cur[u]; i < g[u].size() && flow < limit; cur[u] = i++) {
      auto &[from, to, c, f] = edges[g[u][i]];
      if (d[to] == d[u] + 1 && c - f > eps) {
        T temp = dfs(to, std::min(c - f, limit - flow));
        f += temp, edges[g[u][i] ^ 1].f -= temp, flow += temp;
        if (temp <= eps) d[to] = -1;
      }
    }
    return flow;
  }

  T mf() {
    while (bfs()) {
      flow += dfs(s, std::numeric_limits<T>::max());
    }
    return flow;
  }

  std::vector<int> mc() {
    mf();
    std::vector<bool> ret(n);
    for (int i = 0; i < n; i++) {
      ret[i] = (d[i] != -1);
    }
    return ret;
  }
};

