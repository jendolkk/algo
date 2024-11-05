template <class node, auto push = nullptr>
struct segtree {
  int n;
  vector<node> tree;

  segtree(int _n) : n(_n), tree(4 << __lg(_n)) {
    build(1, 0, n - 1);
  }

  template <typename T>
  segtree(const vector<T> &v) : n(int(v.size())), tree(4 << __lg(n)) {
    build(1, 0, n - 1, v);
  }

  void pull(int id) {
    tree[id] = tree[id << 1] + tree[id << 1 | 1];
  }

  void build(int id, int l, int r) {
    if (l == r) {
      return;
    }
    int mid = l + r >> 1;
    build(id << 1, l, mid);
    build(id << 1 | 1, mid + 1, r);
    pull(id);
  }
 
  template <typename T>
  void build(int id, int l, int r, const vector<T>& a) {
    if (l == r) {
      tree[id].apply(l, r, a[l]);
      return;
    }
    int mid = l + r >> 1;
    build(id << 1, l, mid, a);
    build(id << 1 | 1, mid + 1, r, a);
    pull(id);
  }

  node get(int id, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) {
      return tree[id];
    }
    if constexpr (push != nullptr) {
      push(tree, id, l, r);
    }
    node res{};
    int mid = l + r >> 1;
    if (qr <= mid) {
      res = get(id << 1, l, mid, ql, qr);
    } else {
      if (ql > mid) {
        res = get(id << 1 | 1, mid + 1, r, ql, qr);
      } else {
        res = get(id << 1, l, mid, ql, qr) + get(id << 1 | 1, mid + 1, r, ql, qr);
      }
    }
    return res;
  }

  node get(int ql, int qr) {
    assert(0 <= ql && ql <= qr && qr <= n - 1);
    return get(1, 0, n - 1, ql, qr);
  }
 
  node get(int p) {
    assert(0 <= p && p <= n - 1);
    return get(1, 0, n - 1, p, p);
  }

  template <class... Ts>
  void modify(int id, int l, int r, int ql, int qr, const Ts&... v) {
    if (ql <= l && r <= qr) {
      tree[id].apply(l, r, v...);
      return;
    }
    int mid = l + r >> 1;
    if constexpr (push != nullptr) {
      push(tree, id, l, r);
    }
    if (ql <= mid) {
      modify(id << 1, l, mid, ql, qr, v...);
    }
    if (qr > mid) {
      modify(id << 1 | 1, mid + 1, r, ql, qr, v...);
    }
    pull(id);
  }

  template <class... Ts>
  void modify(int ql, int qr, const Ts&... v) {
    assert(0 <= ql && ql <= qr && qr <= n - 1);
    modify(1, 0, n - 1, ql, qr, v...);
  }

  int min_left(int id, int l, int r, int ql, int qr, const function<bool(const node&)>& verify) {
    if (qr < l || r < ql) {
      return -1;
    }
    if (ql <= l && r <= qr && !verify(tree[id])) {
      return -1;
    }
    if (l == r) {
      return l;
    }
    if constexpr (push != nullptr) {
      push(tree, id, l, r);
    }
    int mid = l + r >> 1;
    int res = min_left(id << 1, l, mid, ql, qr, verify);
    if (res == -1) {
      res = min_left(id << 1 | 1, mid + 1, r, ql, qr, verify);
    }
    return res;
  }

  int min_left(int ql, int qr, const function<bool(const node&)>& verify) {
    return min_left(1, 0, n - 1, ql, qr, verify);
  }

  int max_right(int id, int l, int r, int ql, int qr, const function<bool(const node&)>& verify) {
    if (qr < l || r < ql) {
      return -1;
    }
    if (ql <= l && r <= qr && !verify(tree[id])) {
      return -1;
    }
    if (l == r) {
      return l;
    }
    if constexpr (push != nullptr) {
      push(tree, id, l, r);
    }
    int mid = l + r >> 1;
    int res = max_right(id << 1 | 1, mid + 1, r, ql, qr, verify);
    if (res == -1) {
      res = max_right(id << 1, l, mid, ql, qr, verify);
    }
    return res;
  }

  int max_right(int ql, int qr, const function<bool(const node&)>& verify) {
    return max_right(1, 0, n - 1, ql, qr, verify);
  }
};

struct node {
  int64_t sum = 0;
  int64_t add = 0;
  
  void apply(int l, int r, int64_t v) {
    sum += v * (r - l + 1);
    add += v;
  }
};

node operator+(const node& a, const node& b) {
  node res{};
  res.sum = a.sum + b.sum;
  return res;
}

void push(vector<node>& tree, int id, int l, int r) {
  int mid = l + r >> 1;
  if (tree[id].add != 0) {
    tree[id << 1].apply(l, mid, tree[id].add);
    tree[id << 1 | 1].apply(mid + 1, r, tree[id].add);
    tree[id].add = 0;
  }
}

