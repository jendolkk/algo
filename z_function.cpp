template <class T>
std::vector<int> z_function(const T &s) {
  int n = s.size();
  std::vector<int> z(n, n);
  for (int i = 1, l = 0, r = 0; i < n; i++) {
    z[i] = std::max(0, std::min(z[i - l], r - i + 1));
    if (i > r || z[i - l] == r - i + 1) {
      if (i > r) r = i - 1;
      while (r + 1 < n && s[r + 1] == s[r - i + 1]) {
        r++;
      }
      l = i;
      z[i] = r - i + 1;
    }
  }
  return z;
}

