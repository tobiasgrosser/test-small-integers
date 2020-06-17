#include <benchmark/benchmark.h>
#include "SmallInteger.h"

#define ELEMENTS 16

int64_t A_I64[ELEMENTS * 32];
int64_t B_I64[ELEMENTS * 32];
int64_t C_I64[ELEMENTS * 32];

static void SparseCopy_I64(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    A_I64[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_I64[32 * i] = A_I64[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseCopy_I64);

static void SparseZeroCheck_I64(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    A_I64[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (__builtin_expect(A_I64[32 * i] != 0, false))
        printf("Unexpected non-zero encountered");
}

BENCHMARK(SparseZeroCheck_I64);

static void SparseAddPair_I64(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    A_I64[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      C_I64[32 * i] = A_I64[32 * i] + B_I64[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddPair_I64);



static void SparseAddOne_I64(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    A_I64[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      A_I64[32 * i] = A_I64[32 * i] + 1;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddOne_I64);







SmallInteger_sioimath A_SI_sioimath[ELEMENTS * 32];
SmallInteger_sioimath B_SI_sioimath[ELEMENTS * 32];
SmallInteger_sioimath C_SI_sioimath[ELEMENTS * 32];

static void SparseCopy_SI_sioimath(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_sioimath[i] = i;
    B_SI_sioimath[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_sioimath[32 * i] = A_SI_sioimath[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseCopy_SI_sioimath);

static void SparseZeroCheck_SI_sioimath(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    A_SI_sioimath[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!__builtin_expect(A_SI_sioimath[32 * i].isZero(), true))
        printf("Unexpected zero encountered");
}

BENCHMARK(SparseZeroCheck_SI_sioimath);

static void SparseAddPair_SI_sioimath(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_sioimath[i] = i;
    B_SI_sioimath[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_sioimath[32 * i] = A_SI_sioimath[32 * i] + A_SI_sioimath[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddPair_SI_sioimath);

static void SparseAddOne_SI_sioimath(benchmark::State &state) {
  SmallInteger_sioimath One;
  One = 1;

  for (int i = 0; i < ELEMENTS * 32; i++)
    A_SI_sioimath[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      A_SI_sioimath[32 * i] = A_SI_sioimath[32 * i] + One;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddOne_SI_sioimath);














SmallInteger_1 A_SI_1[ELEMENTS * 32];
SmallInteger_1 B_SI_1[ELEMENTS * 32];
SmallInteger_1 C_SI_1[ELEMENTS * 32];

static void SparseCopy_SI_1(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_1[i] = i;
    B_SI_1[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_1[32 * i] = A_SI_1[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseCopy_SI_1);

static void SparseZeroCheck_SI_1(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_1[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!__builtin_expect(A_SI_1[32 * i].isZero(), true))
        printf("Unexpected zero encountered");
}

BENCHMARK(SparseZeroCheck_SI_1);

static void SparseAddPair_SI_1(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_1[i] = i;
    B_SI_1[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_1[32 * i] = A_SI_1[32 * i] + A_SI_1[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddPair_SI_1);


static void SparseAddOne_SI_1(benchmark::State &state) {
  SmallInteger_1 One ;
  One = 1;

  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_1[i] = i;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      A_SI_1[32 * i] = A_SI_1[32 * i] + One;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddOne_SI_1);






SmallInteger_2 A_SI_2[ELEMENTS * 32];
SmallInteger_2 B_SI_2[ELEMENTS * 32];

static void SparseCopy_SI_2(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_2[i] = i;
    B_SI_2[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_2[32 * i] = A_SI_2[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseCopy_SI_2);

static void SparseZeroCheck_SI_2(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    A_SI_2[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!__builtin_expect(A_SI_2[32 * i].isZero(), true))
        printf("Unexpected zero encountered");
}

BENCHMARK(SparseZeroCheck_SI_2);

static void SparseAddPair_SI_2(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_2[i] = i;
    B_SI_2[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_2[32 * i] = A_SI_2[32 * i] + A_SI_2[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddPair_SI_2);


static void SparseAddOne_SI_2(benchmark::State &state) {
  SmallInteger_2 One ;
  One = 1;

  for (int i = 0; i < ELEMENTS * 32; i++)
    A_SI_2[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      A_SI_2[32 * i] = A_SI_2[32 * i] + One;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddOne_SI_2);






SmallInteger_3 A_SI_3[ELEMENTS * 32];
SmallInteger_3 B_SI_3[ELEMENTS * 32];
SmallInteger_3 C_SI_3[ELEMENTS * 32];

static void SparseCopy_SI_3(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_3[i] = i;
    B_SI_3[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_3[32 * i] = A_SI_3[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseCopy_SI_3);

static void SparseZeroCheck_SI_3(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    A_SI_3[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!__builtin_expect(A_SI_3[32 * i].isZero(), true))
        printf("Unexpected zero encountered");
}

BENCHMARK(SparseZeroCheck_SI_3);

static void SparseAddPair_SI_3(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    A_SI_3[i] = i;
    B_SI_3[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      B_SI_3[32 * i] = A_SI_3[32 * i] + A_SI_3[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddPair_SI_3);


static void SparseAddOne_SI_3(benchmark::State &state) {
  SmallInteger_3 One ;
  One = 1;

  for (int i = 0; i < ELEMENTS * 32; i++)
    A_SI_3[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      A_SI_3[32 * i] = A_SI_3[32 * i] + One;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SparseAddOne_SI_3);







BENCHMARK_MAIN();
