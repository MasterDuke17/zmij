#include <stdint.h>

using uint128_t = unsigned __int128;

constexpr uint64_t not_found = ~uint64_t();

// Finds the smallest n >= 0 such that (n * step) % mod is in [lower, upper].
// This is a standard algorithm for linear congruential inequalities.
inline auto find_min_n(uint64_t step, uint128_t mod, uint64_t lower,
                       uint64_t upper) -> uint64_t {
  if (lower > upper) return not_found;

  if (lower == 0) return 0;  // Current position is already a hit.

  step = uint64_t(step % mod);
  if (step == 0) return not_found;

  // Check for direct hit without wrapping.
  uint128_t n = (lower + step - 1) / step;
  if (n * step <= upper) return uint64_t(n);

  // Euclidean recursion.
  uint64_t result =
      find_min_n(mod % step, step, (step - upper % step) % step,
                 (step - lower % step) % step);
  if (result == not_found) return not_found;

  // Numerator can exceed 128 bits but for mod = 2**64, uint128_t handles the
  // intermediate (resulr * m + L + step128 - 1) before the / step128.
  return uint64_t((uint128_t(result) * mod + lower + step - 1) / step);
}
