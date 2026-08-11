// competitive-verifier: STANDALONE

#include "../../template/template.hpp"

#include "../../math/number-theory/is-prime.hpp"

int main() {
  assert(!is_prime(0));
  assert(!is_prime(1));
  assert(is_prime(2));
  assert(is_prime(3));
  assert(!is_prime(4));
  assert(is_prime(999999937));
  assert(!is_prime(1000000000));
}
