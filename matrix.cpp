template <typename T>
using Matrix = std::vector<std::vector<T>>;

template <typename T>
Matrix<T> operator*(const Matrix<T>& a, const Matrix<T>& b) {
  if (a.empty() || b.empty()) {
    return {};
  }
  int n = a.size(), m = b[0].size();
  std::vector res(n, std::vector<T>(m));
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      for (int k = 0; k < b.size(); k++) {
        res[i][j] += a[i][k] * b[k][j];
      }
    }
  }
  return res;
}
 
template <typename T>
Matrix<T>& operator*=(Matrix<T>& a, const Matrix<T>& b) {
  return a = a * b;
}
 
template <typename T>
Matrix<T> power(Matrix<T> a, int64_t b) {
  assert(b >= 0 && a.size() == a[0].size());
  int n = a.size();
  std::vector res(n, std::vector<T>(n));
  for (int i = 0; i < n; i++) {
    res[i][i] = 1;
  }
  for (; b; b >>= 1, a *= a) {
    if (b & 1) {
      res *= a;
    }
  }
  return res;
}

