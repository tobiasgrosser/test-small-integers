#include <benchmark/benchmark.h>
#include <string.h>
#include <cstdint>
#include <limits>
#include <stdio.h>

class SmallInteger_1 {
public:
  uint64_t data;

  SmallInteger_1() : data(0) {}

  bool isZero() { return data == 0; }

  bool isSmall() const {
    int64_t signed_data;
    memcpy(&signed_data, &data, 8);
    return signed_data <= std::numeric_limits<int32_t>::max();
  }

  int64_t getSmallAs64() const {
    int64_t signed_data;
    memcpy(&signed_data, &data, 8);
    return signed_data;
  }

  SmallInteger_1 &operator=(int32_t val) {

    if (isSmall()) {
      int64_t extended = val;
      memcpy(&data, &extended, 8);
      return *this;
    }

    printf("Not yet supported");
    return *this;
  }

  SmallInteger_1 &operator=(const SmallInteger_1 &val) {
    if (isSmall() && val.isSmall()) {
      data = val.data;
      return *this;
    }

    printf("Not yet supported");
    return *this;
  }
};

SmallInteger_1 operator+(const SmallInteger_1 lhs, const SmallInteger_1& rhs)
{
    SmallInteger_1 res;

    if (lhs.isSmall() && rhs.isSmall()) {
	int64_t lhs_small = lhs.getSmallAs64();
	int64_t rhs_small = rhs.getSmallAs64();
	int64_t res_small = lhs_small + rhs_small;

	res = res_small;
	return res;
    }
    printf("Not yet supported");
    return res;
}


#define ELEMENTS 16

int64_t I64_A[ELEMENTS * 32];
int64_t I64_B[ELEMENTS * 32];

static void I64_SparseCopy(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    I64_A[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      I64_B[32 * i] = I64_A[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(I64_SparseCopy);

static void I64_SparseZeroCheck(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    I64_A[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (I64_A[32 * i] != 0)
        printf("Unexpected non-zero encountered");
}

BENCHMARK(I64_SparseZeroCheck);

static void I64_SparseAdd(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    I64_A[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      I64_B[32 * i] = I64_A[32 * i] + I64_A[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(I64_SparseAdd);

SmallInteger_1 SI_1_A[ELEMENTS * 32];
SmallInteger_1 SI_1_B[ELEMENTS * 32];

static void SI_1_SparseCopy(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    SI_1_A[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_1_B[32 * i] = SI_1_A[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_1_SparseCopy);

static void SI_1_SparseZeroCheck(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    SI_1_A[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!SI_1_A[32 * i].isZero())
        printf("Unexpected zero encountered");
}

BENCHMARK(SI_1_SparseZeroCheck);

static void SI_1_SparseAdd(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    SI_1_A[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_1_B[32 * i] = SI_1_A[32 * i] + SI_1_A[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_1_SparseAdd);

BENCHMARK_MAIN();
