template <typename T>
std::vector<int> suffix_array(const T& s) {
  int n = s.size();
  std::vector<int> sa(n), rk(n), cnt(n), rk_by_second(n);
  if constexpr (std::is_same<T, string>::value) {
    std::vector<int> cnt(128);
    for (auto i : s) {
      cnt[i]++;
    }
    std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    for (int i = n - 1; i >= 0; i--) {
      sa[--cnt[s[i]]] = i;
    }
  } else {
    std::iota(sa.begin(), sa.end(), 0);
    std::sort(sa.begin(), sa.end(), [&](auto i, auto j) { return s[i] < s[j]; });
  }
  rk[sa[0]] = 0;
  for (int i = 1; i < n; i++) {
    rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);
  }
  for (int step = 1; rk[sa[n - 1]] < n - 1; step <<= 1) {
    rk_by_second.clear();
    for (int i = n - step; i < n; i++) {
      rk_by_second.push_back(i);
    }
    for (auto i : sa) {
      if (i >= step) {
        rk_by_second.push_back(i - step);
      }
    }
    std::fill(cnt.begin(), cnt.end(), 0);
    for (int i = 0; i < n; i++) {
      cnt[rk[i]]++;
    }
    std::partial_sum(cnt.begin(), cnt.end(), cnt.begin());
    for (int i = n - 1; i >= 0; i--) {
      int t = rk_by_second[i];
      sa[--cnt[rk[t]]] = t;
    }
    std::swap(rk, rk_by_second);
    rk[sa[0]] = 0;
    for (int i = 1; i < n; i++) {
      rk[sa[i]] = rk[sa[i - 1]]
       + (rk_by_second[sa[i - 1]] < rk_by_second[sa[i]]
          || sa[i - 1] + step == n
          || rk_by_second[sa[i - 1] + step] < rk_by_second[sa[i] + step]);
    }
  }
  return sa;
}

template <typename T>
std::vector<int> build_lcp(const T& s, const std::vector<int>& sa) {
  int n = s.size();
  std::vector<int> rk(n);
  for (int i = 0; i < n; i++) {
    rk[sa[i]] = i;
  }
  std::vector<int> lcp(std::max(n - 1, 0));
  for (int i = 0, k = 0; i < n; i++) {
    if (k > 0) k--;
    if (rk[i] == 0) continue;
    int j = sa[rk[i] - 1];
    while (j + k != n && i + k != n && s[j + k] == s[i + k]) k++;
    lcp[rk[i] - 1] = k;
  }
  return lcp;
}

