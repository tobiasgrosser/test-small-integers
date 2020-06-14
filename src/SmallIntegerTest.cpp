#include <benchmark/benchmark.h>
#include <string.h>
#include <cstdint>
#include <limits>
#include <stdio.h>



#define unsupported(X)


class SmallInteger_sioimath {
public:
  uint64_t val;

  SmallInteger_sioimath() : val(1) {}

  bool isZero() { return val == 1; }

  bool isSmall() const {
	  return val & 0x00000001;
  }

  int64_t getSmallAs64() const {
	  return (int32_t)(val >> 32);
  }

  SmallInteger_sioimath &operator=(int32_t that) {
    if (isSmall()) {
      val = (((uint64_t)(uint32_t)that)  << 32) + 1;
      return *this;
    }

    unsupported("Not yet supported");
    return *this;
  }

  SmallInteger_sioimath &operator=(const SmallInteger_sioimath that) {
    if (isSmall() && that.isSmall()) {
      val = that.val;
      return *this;
    }

    unsupported("Not yet supported");
    return *this;
  }
};

SmallInteger_sioimath operator+(const SmallInteger_sioimath lhs, const SmallInteger_sioimath rhs)
{
  SmallInteger_sioimath res;

  if (lhs.isSmall() && rhs.isSmall()) {
	  int64_t lhs_small = lhs.getSmallAs64();
	  int64_t rhs_small = rhs.getSmallAs64();
	  int64_t res_small = lhs_small + rhs_small;

	  res = res_small;
	  return res;
  }
  unsupported("Not yet supported3");
  return res;
}









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

    unsupported("Not yet supported");
    return *this;
  }

  SmallInteger_1 &operator=(const SmallInteger_1 val) {
    if (isSmall() && val.isSmall()) {
      data = val.data;
      return *this;
    }

    unsupported("Not yet supported");
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
    
    unsupported("Not yet supported");
    return res;
}






class SmallInteger_2 {
public:
  uint64_t val;

  SmallInteger_2() : val(0) {}

  bool isZero() { return val == 0; }

  bool isSmall() const {
	  return !((val >> 32) & 0x00000001);
  }

  int64_t getSmallAs64() const {
    return (int64_t)(uint32_t)val;
  }

  SmallInteger_2 &operator=(int32_t that) {
    if (isSmall()) {
      val = (uint32_t)that;
      return *this;
    }

    unsupported("Not yet supported");
    return *this;
  }

  SmallInteger_2 &operator=(const SmallInteger_2 that) {
    if (isSmall() && that.isSmall()) {
      val = that.val;
      return *this;
    }

    unsupported("Not yet supported");
    return *this;
  }
};

SmallInteger_2 operator+(const SmallInteger_2 lhs, const SmallInteger_2 rhs)
{
  SmallInteger_2 res;

  if (lhs.isSmall() && rhs.isSmall()) {
	  int64_t lhs_small = lhs.getSmallAs64();
	  int64_t rhs_small = rhs.getSmallAs64();
	  int64_t res_small = lhs_small + rhs_small;

	  res = res_small;
	  return res;
  }
  
  unsupported("Not yet supported");
  return res;
}







#define ELEMENTS 16

int64_t I64_A[ELEMENTS * 32];
int64_t I64_B[ELEMENTS * 32];
int64_t I64_C[ELEMENTS * 32];

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
      I64_C[32 * i] = I64_A[32 * i] + I64_B[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(I64_SparseAdd);



static void I64_SparseAddOne(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    I64_A[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      I64_A[32 * i] = I64_A[32 * i] + 1;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(I64_SparseAddOne);







SmallInteger_sioimath SI_sioimath_A[ELEMENTS * 32];
SmallInteger_sioimath SI_sioimath_B[ELEMENTS * 32];
SmallInteger_sioimath SI_sioimath_C[ELEMENTS * 32];

static void SI_sioimath_SparseCopy(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_sioimath_A[i] = i;
    SI_sioimath_B[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_sioimath_B[32 * i] = SI_sioimath_A[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_sioimath_SparseCopy);

static void SI_sioimath_SparseZeroCheck(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    SI_sioimath_A[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!SI_sioimath_A[32 * i].isZero())
        printf("Unexpected zero encountered");
}

BENCHMARK(SI_sioimath_SparseZeroCheck);

static void SI_sioimath_SparseAdd(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_sioimath_A[i] = i;
    SI_sioimath_B[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_sioimath_B[32 * i] = SI_sioimath_A[32 * i] + SI_sioimath_A[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_sioimath_SparseAdd);

static void SI_sioimath_SparseAddOne(benchmark::State &state) {
  SmallInteger_sioimath One;
  One = 1;

  for (int i = 0; i < ELEMENTS * 32; i++)
    SI_sioimath_A[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_sioimath_A[32 * i] = SI_sioimath_A[32 * i] + One;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_sioimath_SparseAddOne);














SmallInteger_1 SI_1_A[ELEMENTS * 32];
SmallInteger_1 SI_1_B[ELEMENTS * 32];
SmallInteger_1 SI_1_C[ELEMENTS * 32];

static void SI_1_SparseCopy(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_1_A[i] = i;
    SI_1_B[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_1_B[32 * i] = SI_1_A[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_1_SparseCopy);

static void SI_1_SparseZeroCheck(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_1_A[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!SI_1_A[32 * i].isZero())
        printf("Unexpected zero encountered");
}

BENCHMARK(SI_1_SparseZeroCheck);

static void SI_1_SparseAdd(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_1_A[i] = i;
    SI_1_B[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_1_B[32 * i] = SI_1_A[32 * i] + SI_1_A[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_1_SparseAdd);


static void SI_1_SparseAddOne(benchmark::State &state) {
  SmallInteger_1 One ;
  One = 1;

  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_1_A[i] = i;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_1_A[32 * i] = SI_1_A[32 * i] + One;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_1_SparseAddOne);






SmallInteger_2 SI_2_A[ELEMENTS * 32];
SmallInteger_2 SI_2_B[ELEMENTS * 32];

static void SI_2_SparseCopy(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_2_A[i] = i;
    SI_2_B[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_2_B[32 * i] = SI_2_A[32 * i];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_2_SparseCopy);

static void SI_2_SparseZeroCheck(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++)
    SI_2_A[i] = 0;
  benchmark::ClobberMemory();

  for (auto _ : state)
    for (int i = 0; i < ELEMENTS; i++)
      if (!SI_2_A[32 * i].isZero())
        printf("Unexpected zero encountered");
}

BENCHMARK(SI_2_SparseZeroCheck);

static void SI_2_SparseAdd(benchmark::State &state) {
  for (int i = 0; i < ELEMENTS * 32; i++) {
    SI_2_A[i] = i;
    SI_2_B[i] = 0;
  }
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_2_B[32 * i] = SI_2_A[32 * i] + SI_2_A[32 * i + 1];
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_2_SparseAdd);


static void SI_2_SparseAddOne(benchmark::State &state) {
  SmallInteger_2 One ;
  One = 1;

  for (int i = 0; i < ELEMENTS * 32; i++)
    SI_2_A[i] = i;
  benchmark::ClobberMemory();

  for (auto _ : state) {
    for (int i = 0; i < ELEMENTS; i++)
      SI_2_A[32 * i] = SI_2_A[32 * i] + One;
    benchmark::ClobberMemory();
  }
}

BENCHMARK(SI_2_SparseAddOne);








BENCHMARK_MAIN();
