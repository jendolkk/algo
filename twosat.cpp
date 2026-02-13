class twosat {
 public:
  int n;
  bool ok = true;
  std::vector<int> ans;
  std::vector<std::vector<int>> g;

  explicit twosat(int _n) : n(_n), g(2 * _n), ans(n) {}

  void add(int u, int val1, int v, int val2) {
    g[2 * u + !val1].push_back(2 * v + val2);
    g[2 * v + !val2].push_back(2 * u + val1);
  }

  void build() {
    scc cc(g);
    for (int i = 0; i < n; i++) {
      if (cc.pos[2 * i] == cc.pos[2 * i + 1]) {
        ok = false;
      }
      ans[i] = cc.pos[2 * i] > cc.pos[2 * i + 1];
    }
  }
};

