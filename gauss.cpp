// constexpr double eps = 1e-9;
// bool isZero(double x) {
//   return std::abs(x) < eps;
// }

// constexpr Mint eps = 1;
// bool isZero(Mint x) {
//   return x == 0;
// }

template <typename T>
std::pair<int, T> gauss(std::vector<std::vector<T>>& a) {
  using namespace std;
  int rank = 0;
  T mul = 1;
  int n = a.size();
  if (n == 0) {
    return {rank, mul};
  }
  int m = a[0].size();
  for (int j = 0; j < m; j++) {
    int p = rank;
    for (int i = p + 1; i < n; i++) {
      if (abs(a[p][j]) < abs(a[i][j])) {
        p = i;
      }
    }
    if (isZero(a[p][j])) {
      continue;
    }
    if (p != rank) {
      swap(a[rank], a[p]);
      mul = -mul;
    }
    mul *= a[rank][j];
    T inv = 1 / a[rank][j];
    for (int i = 0; i < n; i++) {
      if (i != rank) {
        T coeff = a[i][j] * inv;
        for (int k = j; k < m; k++) {
          a[i][k] -= a[rank][k] * coeff;
        }
      }
    }
    for (int k = m - 1; k >= j; k--) {
      a[rank][k] *= inv;
    }
    if (j < m) {
      rank++;
    }
    if (rank == n) {
      break;
    }
  }
  return {rank, mul};
}

template <typename T>
T determinant(std::vector<std::vector<T>> a) {
  auto [rank, mul] = gauss(a);
  if (rank < a.size()) {
    return 0;
  } else {
    for (int i = 0; i < a.size(); i++) {
      mul *= a[i][i];
    }
    return mul;
  }
}

template <typename T>
std::vector<std::vector<T>> inverse(std::vector<std::vector<T>> a) {
  int n = a.size();
  for (int i = 0; i < n; i++) {
    a[i].resize(2 * n);
    a[i][i + n] = 1;
  }
  auto [rank, mul] = gauss(a);
  if (rank < n) {
    return {};
  }
  for (int i = 0; i < n; i++) {
    if (isZero(a[i][i])) {
      return {};
    }
  }
  std::vector<std::vector<T>> b(n);
  for (int i = 0; i < n; i++) {
    b[i] = std::vector(a[i].begin() + n, a[i].end());
  }
  return b;
}

