#if !defined(PM_TYPE_)
#define PM_TYPE_H

#include "header.hpp"

namespace pm
{

enum class pm_type_kind
{
  I32,
  I64,
  U32,
  U64,
  CHAR,
  BOOL,
};

template <typename T, pm_type_kind _Type_Kind> class pm_type
{
private:
  T val;
  static constexpr pm_type_kind kind = _Type_Kind;

public:
  pm_type () = default;

  pm_type (T _Val) : val{ _Val } {}

  T
  get () const
  {
    return val;
  }

  void
  set (T _Val)
  {
    val = _Val;
  }

  bool
  operator== (const pm_type &other) const
  {
    return val == other.val;
  }

  bool
  operator!= (const pm_type &other) const
  {
    return val != other.val;
  }

  bool
  operator< (const pm_type &other) const
  {
    return val < other.val;
  }

  bool
  operator> (const pm_type &other) const
  {
    return val > other.val;
  }

  bool
  operator<= (const pm_type &other) const
  {
    return val <= other.val;
  }

  bool
  operator>= (const pm_type &other) const
  {
    return val >= other.val;
  }

  ~pm_type () {}
};

using i32 = pm_type<int32_t, pm_type_kind::I32>;
using i64 = pm_type<int64_t, pm_type_kind::I64>;
using u32 = pm_type<uint32_t, pm_type_kind::U32>;
using u64 = pm_type<uint64_t, pm_type_kind::U64>;
using chr = pm_type<char, pm_type_kind::CHAR>;
using boolean = pm_type<bool, pm_type_kind::BOOL>;
} // namespace pm

#endif // PM_TYPE_H
