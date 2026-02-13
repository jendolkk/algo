class dsu {
 public:
  explicit dsu(int _n) : p(_n, -1) {}

  int get(int x) {
    return p[x] < 0 ? x : p[x] = get(p[x]);
  }

  bool merge(int x, int y) {
    x = get(x); y = get(y);
    if (x != y) {
      p[x] += p[y];
      p[y] = x;
      return true;
    }
    return false;
  }

  bool same(int x, int y) {
    return get(x) == get(y);
  }
  
  int size(int x) {
    return -p[get(x)];
  }

 private:
  std::vector<int> p;
};

