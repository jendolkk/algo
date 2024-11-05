template <typename T>
std::vector<int> border(const T &s) {
  int n = static_cast<int>(s.size());
  std::vector<int> p(n);
  for (int i = 1, j = 0; i < n; i++) {
    while (j > 0 && s[i] != s[j]) j = p[j - 1];
    if (s[i] == s[j]) j++;
    p[i] = j;
  }
  return p;
}

template <typename T>
std::vector<int> search(const T& str, const T& pattern) {
  int n = static_cast<int>(str.size()), m = static_cast<int>(pattern.size());
  auto p = border(pattern);
  std::vector<int> res;
  for (int i = 0, j = 0; i < n; i++) {
    while (j > 0 && (j == m || str[i] != pattern[j])) j = p[j - 1];
    if (str[i] == pattern[j]) j++;
    if (j == m) res.push_back(i - m + 1);
  }
  return res;
}

