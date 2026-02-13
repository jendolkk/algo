std::vector<int> least, primes, phi;
void sieve(int n) {
  least.assign(n + 1, 0);
  primes.clear();
  phi.assign(n + 1, 0);
  phi[1] = 1;
  for (int i = 2; i <= n; i++) {
    if (least[i] == 0) {
      least[i] = i;
      primes.push_back(i);
      phi[i] = i - 1;
    }
    for (auto p : primes) {
      if (i * p > n) break;
      least[i * p] = p;
      if (p == least[i]) {
        phi[i * p] = phi[i] * p;
        break;
      }
      phi[i * p] = phi[i] * (p - 1);
    }
  }
}

