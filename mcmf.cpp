template <typename T, typename U>
struct mcmf {
  static constexpr T eps = (T) 1e-9;

  struct edge {
    int from;
    int to;
    T c;
    T f;
    U cost;
    edge(int _from, int _to, T _c, T _f, U _cost): 
      from(_from), to(_to), c(_c), f(_f), cost(_cost) {}
  };

  int n, s, t;
  std::vector<edge> edges;
  std::vector<std::vector<int>> g;
  std::vector<int> q, pe;
  std::vector<bool> in_queue;
  std::vector<U> dist;
  T flow = 0;
  U cost = 0;

  mcmf() {}

  mcmf(int _n, int _s, int _t) {
    init(_n, _s, _t);
  }

  void init() {
    in_queue.resize(n);
    dist.resize(n);
    pe.resize(n);
    edges.clear();
    g.assign(n, {});
  }

  void init(int _n, int _s, int _t) {
    n = _n, s = _s, t = _t;
    init();
  }

  void add(int u, int v, T forward, T backward, U cost) {
    g[u].push_back((int) edges.size());
    edges.emplace_back(u, v, forward, 0, cost);
    g[v].push_back((int) edges.size());
    edges.emplace_back(v, u, backward, 0, -cost);
  }

  bool spfa() {
    std::fill(dist.begin(), dist.end(), std::numeric_limits<U>::max());
    int hh = 0, tt = 1;
    q.clear();
    q.push_back(s);
    in_queue[s] = true;
    dist[s] = 0;
    bool res = false;
    while (hh < tt) {
      int u = q[hh++];
      if (u == t) {
        res = true;
      }
      in_queue[u] = false;
      for (int id : g[u]) {
        const auto& e = edges[id];
        if (e.c - e.f > eps && dist[e.to] > dist[u] + e.cost) {
          dist[e.to] = dist[u] + e.cost;
          pe[e.to] = id;
          if (!in_queue[e.to]) {
            q.push_back(e.to);
            tt++;
            in_queue[e.to] = true;
          }
        }
      }
    }
    if (!res) return res;
    T push = std::numeric_limits<T>::max();
    int v = t;
    while (v != s) {
      const edge& e = edges[pe[v]];
      push = std::min(push, e.c - e.f);
      v = e.from;
    }
    v = t;
    while (v != s) {
      edge& e = edges[pe[v]];
      e.f += push;
      edge& back = edges[pe[v] ^ 1];
      back.f -= push;
      v = e.from;
    }
    flow += push;
    cost += push * dist[t];
    return res;
  }

  std::pair<T, U> run() {
    while (spfa());
    return {flow, cost};
  }
};

