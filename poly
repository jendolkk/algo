template <typename T>
std::vector<T>& operator+=(std::vector<T>& a, const std::vector<T>& b) {
  if (a.size() < b.size()) {
    a.resize(b.size());
  }
  for (int i = 0; i < b.size(); i++) {
    a[i] += b[i];
  }
  return a;
}

template <typename T>
std::vector<T> operator+(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> c = a;
  return c += b;
}

template <typename T>
std::vector<T>& operator-=(std::vector<T>& a, const std::vector<T>& b) {
  if (a.size() < b.size()) {
    a.resize(b.size());
  }
  for (int i = 0; i < b.size(); i++) {
    a[i] -= b[i];
  }
  return a;
}

template <typename T>
std::vector<T> operator-(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> c = a;
  return c -= b;
}

template <typename T>
std::vector<T> operator-(const std::vector<T>& a) {
  std::vector<T> c = a;
  for (auto& x : c) {
    x = -x;
  }
  return c;
}

template <typename T>
std::vector<T> operator*(const std::vector<T>& a, const std::vector<T>& b) {
  if (a.empty() || b.empty()) {
    return {};
  }
  int n = a.size(), m = b.size();
  if (n < 150 || m < 150) {
    std::vector<T> c(n + m - 1, 0);
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        c[i + j] += a[i] * b[j];
      }
    }
    return c;
  }
  return mul(a, b);
}

template <typename T>
std::vector<T>& operator*=(std::vector<T>& a, const std::vector<T>& b) {
  return a = a * b;
}

template <typename T>
std::vector<T> inverse(const std::vector<T>& a) {
  assert(!a.empty());
  std::vector<T> b = {1 / a[0]};
  int n = a.size(), s = 1;
  while (s < n) {
    s *= 2;
    std::vector<T> t = b * b * std::vector<T>(a.begin(), a.begin() + std::min(n, s));
    b.resize(s);
    for (int i = s / 2; i < std::min(int(t.size()), s); i++) {
      b[i] = -t[i];
    }
  }
  b.resize(n);
  return b;
}

template <typename T>
std::vector<T>& operator/=(std::vector<T>& a, const std::vector<T>& b) {
  int n = a.size(), m = b.size();
  if (n < m) {
    a.clear();
  } else {
    std::vector<T> d = b;
    std::reverse(a.begin(), a.end());
    std::reverse(d.begin(), d.end());
    d.resize(n - m + 1);
    a *= inverse(d);
    a.erase(a.begin() + n - m + 1, a.end());
    std::reverse(a.begin(), a.end());
  }
  return a;
}

template <typename T>
std::vector<T> operator/(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> c = a;
  return c /= b;
}

template <typename T>
std::vector<T>& operator%=(std::vector<T>& a, const std::vector<T>& b) {
  int n = a.size(), m = b.size();
  if (n >= m) {
    std::vector<T> c = (a / b) * b;
    a.resize(m - 1);
    for (int i = 0; i < m - 1; i++) {
      a[i] -= c[i];
    }
  }
  return a;
}

template <typename T>
std::vector<T> operator%(const std::vector<T>& a, const std::vector<T>& b) {
  std::vector<T> c = a;
  return c %= b;
}

template <typename T>
std::vector<T> derivative(const std::vector<T>& a) {
  std::vector<T> c = a;
  for (int i = 0; i < c.size(); i++) {
    c[i] *= i;
  }
  if (!c.empty()) {
    c.erase(c.begin());
  }
  return c;
}

template <typename T>
std::vector<T> primitive(const std::vector<T>& a) {
  std::vector<T> c = a;
  c.insert(c.begin(), 0);
  for (int i = 1; i < c.size(); i++) {
    c[i] /= i;
  }
  return c;
}

template <typename T>
std::vector<T> logarithm(const std::vector<T>& a) {
  assert(!a.empty() && a[0] == 1);
  std::vector<T> b = primitive(derivative(a) * inverse(a));
  b.resize(a.size());
  return b;
}

template <typename T>
std::vector<T> exponent(const std::vector<T>& a) {
  assert(!a.empty() && a[0] == 0);
  int n = a.size(), s = 1;
  std::vector<T> b{1};
  while (s < n) {
    s *= 2;
    std::vector<T> x(a.begin(), a.begin() + std::min(n, s));
    x[0] += 1;
    std::vector<T> old_b = b;
    b.resize(s);
    x -= logarithm(b);
    x *= old_b;
    for (int i = s / 2; i < std::min(x.size(), b.size()); i++) {
      b[i] = x[i];
    }
  }
  b.resize(n);
  return b;
}

template <typename T>
std::vector<T> sqrt(const std::vector<T>& a) {
  assert(!a.empty() && a[0] == 1);
  int n = a.size(), s = 1;
  std::vector<T> b {1};
  T inv2 = 1 / static_cast<T>(2);
  while (s < n) {
    s *= 2;
    b.resize(s);
    std::vector<T> x = std::vector<T>(a.begin(), a.begin() + std::min(n, s)) * inverse(b);
    for (int i = s / 2; i < std::min(n, s); i++) {
      b[i] = x[i] * inv2;
    }
  }
  b.resize(n);
  return b;
}

template <typename T>
std::vector<T> multiply(const std::vector<std::vector<T>>& a) {
  if (a.empty()) {
    return {0};
  }
  std::function<std::vector<T>(int, int)> mult = [&](int l, int r) {
    if (l == r) {
      return a[l];
    }
    int y = (l + r) >> 1;
    return mult(l, y) * mult(y + 1, r);
  };
  return mult(0, (int) a.size() - 1);
}

template <typename T>
T evaluate(const std::vector<T>& a, const T& x) {
  T res = 0;
  for (int i = int(a.size()) - 1; i >= 0; i--) {
    res = res * x + a[i];
  }
  return res;
}

template <typename T>
std::vector<T> power(const std::vector<T>& a, int64_t k) {
  int n = a.size();
  if (k == 0) {
    std::vector<T> res(n, 0);
    res[0] = 1;
    return res;
  }
  int s = 0;
  while (s < n && a[s] == 0) {
    s++;
  }
  if (s == n || s >= (n + k - 1) / k) {
    return std::vector<T>(n, 0);
  }
  std::vector<T> b(a.begin() + s, a.end());
  b.resize(n);
  Mint inv = b[0].inv();
  for (int i = 0; i < n - s; i++) {
    b[i] *= inv;
  }
  b = logarithm(b);
  for (int i = 0; i < n; i++) {
    b[i] *= k;
  }
  b = exponent(b);
  inv = power(inv.inv(), k);
  for (int i = 0; i < n; i++) {
    b[i] *= inv;
  }
  std::vector<T> res(s * k, 0);
  b.resize(n - s * k);
  for (int i = s * k; i < n; i++) {
    res.push_back(b[i]);
  }
  return res;
}
// to be continued..

