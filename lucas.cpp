Mint lucas(int64_t n, int64_t k) {
  Mint ans = 1;
  while (n > 0) {
    ans *= C(n % md, k % md);
    n /= md;
    k /= md;
  }
  return ans;
}

