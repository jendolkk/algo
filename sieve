std::vector<int> least, primes;
void sieve(int n) {
  least.assign(n + 1, 0);
  primes.clear();
  for (int i = 2; i <= n; i++) {
    if (least[i] == 0) {
      least[i] = i;
      primes.push_back(i);
    }
    for (auto p : primes) {
      if (p > least[i] || i * p > n) break;
      least[i * p] = p;
    }
  }
}

