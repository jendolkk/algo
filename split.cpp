vector<string> split(string_view s, char separator) {
  vector<string> ret;
  string t;
  for (auto c : s) {
    if (c == separator) {
      if (!t.empty()) ret.push_back(t);
      t.clear();
    } else {
      t.push_back(c);
    }
  }
  if (!t.empty()) ret.push_back(t);
  return ret;
}

