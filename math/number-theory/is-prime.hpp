bool is_prime(int64_t x) {
  if (x < 2) return false;
  for (int64_t i = 2; i * i <= x; i++) {
    if (x % i == 0) return false;
  }
  return true;
}
