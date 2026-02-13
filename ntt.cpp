namespace NTT {

int max_base = 0, base = 0;
Mint root;
std::vector<int> rev;
std::vector<Mint> roots;

void init() {
  auto tmp = md - 1;
  max_base = 0;
  while (tmp % 2 == 0) {
    tmp /= 2;
    max_base++;
  }
  root = 2;
  while (power(root, (md - 1) >> 1) == 1) {
    root++;
  }
  assert(power(root, md - 1) == 1);
  root = power(root, (md - 1) >> max_base);
  base = 1;
  rev = {0, 1};
  roots = {0, 1};
}

void ensure_base(int nbase) {
  if (roots.empty()) {
    init();
  }
  if (nbase <= base) {
    return;
  }
  assert(nbase <= max_base);
  rev.resize(1 << nbase);
  for (int i = 0; i < (1 << nbase); i++) {
    rev[i] = (rev[i >> 1] >> 1) + ((i & 1) << (nbase - 1));
  }
  roots.resize(1 << nbase);
  while (base < nbase) {
    Mint z = power(root, 1 << (max_base - 1 - base));
    for (int i = 1 << (base - 1); i < (1 << base); i++) {
      roots[i << 1] = roots[i];
      roots[(i << 1) + 1] = roots[i] * z;
    }
    base++;
  }
}

void fft(std::vector<Mint>& a) {
  int n = a.size();
  int zeros = __builtin_ctz(n);
  ensure_base(zeros);
  int shift = base - zeros;
  for (int i = 0; i < n; i++) {
    if (i < (rev[i] >> shift)) {
      std::swap(a[i], a[rev[i] >> shift]);
    }
  }
  for (int k = 1; k < n; k <<= 1) {
    for (int i = 0; i < n; i += k << 1) {
      for (int j = 0; j < k; j++) {
        Mint z = a[i + j + k] * roots[j + k];
        a[i + j + k] = a[i + j] - z;
        a[i + j] = a[i + j] + z;
      }
    }
  }
}
  
std::vector<Mint> mul(std::vector<Mint> a, std::vector<Mint> b) {
  int need = (int) a.size() + (int) b.size() - 1;
  int nbase = 0;
  while ((1 << nbase) < need) nbase++;
  ensure_base(nbase);
  int sz = 1 << nbase;
  bool eq = (a == b);
  a.resize(sz);
  b.resize(sz);
  fft(a);
  if (eq) b = a; else fft(b);
  Mint inv = Mint(sz).inv();
  for (int i = 0; i < sz; i++) {
    a[i] *= b[i] * inv;
  }
  std::reverse(a.begin() + 1, a.end());
  fft(a);
  a.resize(need);
  return a;
}
} // namespace NTT
using namespace NTT;

