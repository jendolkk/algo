std::vector<Mint> fact{1};
std::vector<Mint> inv_fact{1};
 
Mint C(int n, int k) {
  if (k < 0 || k > n) {
    return 0;
  }
  if (fact.size() <= n) {
    int m = fact.size();
    int new_sz = n + n / 2 + 1;
    fact.resize(new_sz);
    inv_fact.resize(new_sz);
    for (int i = m; i < new_sz; i++) {
      fact[i] = fact[i - 1] * i;
    }
    inv_fact.back() = fact.back().inv();
    for (int i = new_sz - 1; i > m; i--) {
      inv_fact[i - 1] = inv_fact[i] * i;
    }
  }
  return fact[n] * inv_fact[k] * inv_fact[n - k];
}

