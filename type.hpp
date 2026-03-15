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

template <pm_type_kind _Type_Kind> class pm_type;

template <> class pm_type<pm_type_kind::I32>
{
public:
  using storage_type = int32_t;
  static constexpr pm_type_kind kind = pm_type_kind::I32;

private:
  storage_type val;

public:
  pm_type () = default;

  pm_type (storage_type _Val) : val{ _Val } {}

  storage_type
  get () const
  {
    return val;
  }

  bool
  operator== (const pm_type &other) const
  {
    return val == other.val;
  }

  bool
  operator< (const pm_type &other) const
  {
    return val < other.val;
  }
};

template <> class pm_type<pm_type_kind::I64>
{
public:
  using storage_type = int64_t;
  static constexpr pm_type_kind kind = pm_type_kind::I64;

private:
  storage_type val;

public:
  pm_type () = default;

  pm_type (storage_type _Val) : val{ _Val } {}

  storage_type
  get () const
  {
    return val;
  }

  bool
  operator== (const pm_type &other) const
  {
    return val == other.val;
  }

  bool
  operator< (const pm_type &other) const
  {
    return val < other.val;
  }
};

template <> class pm_type<pm_type_kind::BOOL>
{
public:
  using storage_type = bool;
  static constexpr pm_type_kind kind = pm_type_kind::BOOL;

private:
  storage_type val;

public:
  pm_type () = default;
  pm_type (storage_type _Val) : val{ _Val } {}

  storage_type
  get () const
  {
    return val;
  }
};

template <> class pm_type<pm_type_kind::U32>
{
public:
  using storage_type = uint32_t;
  static constexpr pm_type_kind kind = pm_type_kind::U32;

private:
  storage_type val;

public:
  pm_type () = default;

  pm_type (storage_type _Val) : val{ _Val } {}

  storage_type
  get () const
  {
    return val;
  }

  bool
  operator== (const pm_type &other) const
  {
    return val == other.val;
  }

  bool
  operator< (const pm_type &other) const
  {
    return val < other.val;
  }
};

template <> class pm_type<pm_type_kind::U64>
{
public:
  using storage_type = uint64_t;
  static constexpr pm_type_kind kind = pm_type_kind::U64;

private:
  storage_type val;

public:
  pm_type () = default;

  pm_type (storage_type _Val) : val{ _Val } {}

  storage_type
  get () const
  {
    return val;
  }

  bool
  operator== (const pm_type &other) const
  {
    return val == other.val;
  }

  bool
  operator< (const pm_type &other) const
  {
    return val < other.val;
  }
};

} // namespace pm

#endif // PM_TYPE_H
