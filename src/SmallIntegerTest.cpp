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







#define FLAG (1ul << 62)

inline bool isl_sioimath_is_big_tobig(uint64_t val)
{

	    int64_t val_s;
        int64_t flag_s;
        uint64_t flag_u = FLAG;
        memcpy(&flag_s, &flag_u, 8);
        memcpy(&val_s, &val, 8);
        return val_s > std::numeric_limits<int32_t>::max();
}

inline uint64_t isl_sioimath_encode_small_tobig(int32_t val)
{
        uint32_t val_u;
        memcpy(&val_u, &val, 4);
        return ((uint64_t) val_u);
}


class SmallInteger_3 {
public:
  uint64_t val;

  SmallInteger_3() : val(0) {}

  bool isZero() { return val == 0; }

  bool isSmall() const {
	  return !isl_sioimath_is_big_tobig(val);
  }

  int64_t getSmallAs64() const {
    return (int64_t)(uint32_t)val;
  }

  SmallInteger_3 &operator=(int32_t that) {
    if (isSmall()) {
      val = isl_sioimath_encode_small_tobig(that);
      return *this;
    }

    unsupported("Not yet supported");
    return *this;
  }

  SmallInteger_3 &operator=(const SmallInteger_3 that) {
    if (isSmall() && that.isSmall()) {
      val = that.val;
      return *this;
    }

    unsupported("Not yet supported");
    return *this;
  }
};

SmallInteger_3 operator+(const SmallInteger_3 lhs, const SmallInteger_3 rhs)
{
  SmallInteger_3 res;

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
      if (A_I64[32 * i] != 0)
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
      if (!A_SI_sioimath[32 * i].isZero())
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
      if (!A_SI_1[32 * i].isZero())
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
      if (!A_SI_2[32 * i].isZero())
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
      if (!A_SI_3[32 * i].isZero())
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
