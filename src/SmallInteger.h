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
