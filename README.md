# Żmij

A double-to-string conversion algorithm based on [Schubfach](https://fmt.dev/papers/Schubfach4.pdf)

## Features

* Round trip guarantee
* Shortest decimal representation
* Correct rounding
* High [performance](#performance)
* Fast [compile time](#compile-time)
* Zero dependencies
* Small, clean codebase consisting of one [source file](
  https://github.com/vitaut/zmij/blob/main/zmij.cc) and one [header](https://github.com/vitaut/zmij/blob/main/zmij.h)
* Permissive [license](https://github.com/vitaut/zmij/blob/main/LICENSE)

## Usage

```c++
#include "zmij.h"
#include <stdio.h>

int main() {
  char buf[zmij::buffer_size];
  zmij::dtoa(6.62607015e-34, buf);
  puts(buf);
}
```

## Performance

More than 3x faster than [Ryu](https://github.com/ulfjack/ryu) used by multiple
C++ standard library implementations and ~2x faster than
[Schubfach](https://github.com/vitaut/schubfach)
on [dtoa-benchmark](https://github.com/fmtlib/dtoa-benchmark) run on Apple M1.

| Function      | Time (ns) | Speedup |
|--------------:|----------:|--------:|
| ostringstream | 874.752   | 1.00x   |
| sprintf       | 734.849   | 1.19x   |
| doubleconv    | 85.479    | 10.23x  |
| to_chars      | 42.709    | 20.48x  |
| ryu           | 37.404    | 23.39x  |
| schubfach     | 25.166    | 34.76x  |
| fmt           | 22.302    | 39.22x  |
| dragonbox     | 20.823    | 42.01x  |
| yy            | 14.016    | 62.41x  |
| zmij          | 12.259    | 71.36x  |
| null          | 0.929     | 941.19x |

<img width="783" height="354" alt="image"
     src="https://github.com/user-attachments/assets/7b65921b-af06-4ffa-ab31-e61e7f14abf8" />

<img width="888" height="675" alt="image"
     src="https://github.com/user-attachments/assets/96492ad2-c8b1-4963-8ad0-a89abac4bcc4" />


## Compile time

Compile time is ~60ms by default and ~68ms with optimizations enabled as measured by

```
% time c++ -c -std=c++20 zmij.cc [-O2]
```

taking the best of 3 runs.


## Differences from Schubfach

* Selection from 1-3 candidates instead of 2-4
* Fewer integer multiplications in the shorter case
* Faster logarithm approximations
* Faster division and modulo
* Fewer conditional branches
* More efficient significand and exponent output
* Simpler storage of powers of 10 significands
