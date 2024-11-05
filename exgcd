template <typename T>
T exgcd(T a, T b, T& x, T& y) {
  if (b == 0) {
    x = 1; y = 0;
    return a;
  }
  T t = a / b;
  T d = exgcd(b, a - t * b, y, x);
  y -= t * x;
  return d;
}

