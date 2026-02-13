template <int CHARSET_SIZE = 26, int CHAR_BEG = 'a'>
class AhoCorasick {
 public:
  struct Node : std::array<int, CHARSET_SIZE> {
    int fail{};
    int pv{};
    Node() { this->fill(0); }
  };

  std::vector<Node> nodes;

  explicit AhoCorasick(): nodes(1) {}

  template <typename T>
  int add(const T& s) {
    int p = 0;
    for (auto c : s) {
      int u = c - CHAR_BEG;
      if (!nodes[p][u]) {
        nodes[p][u] = nodes.size();
        nodes.emplace_back();
        nodes.back().pv = p;
      }
      p = nodes[p][u];
    }
    return p;
  }

  std::vector<int> build() {
    std::vector<int> que;
    for (int i = 0; i < CHARSET_SIZE; i++) {
      if (nodes[0][i]) {
        que.push_back(nodes[0][i]);
      }
    }
    for (int i = 0; i < que.size(); i++) {
      int u = que[i];
      for (int j = 0; j < CHARSET_SIZE; j++) {
        int& p = nodes[u][j];
        (p ? que.push_back(p), nodes[p].fail : p) = nodes[nodes[u].fail][j];
      }
    }
    return que;
  }

  Node& operator[](int p) {
    return nodes[p];
  }

  int size() {
    return nodes.size();
  }
};

