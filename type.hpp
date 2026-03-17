#if !defined(PM_TYPE_H)
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

template <> class pm_type<pm_type_kind::CHAR>
{
public:
  using storage_type = char;
  static constexpr pm_type_kind kind = pm_type_kind::CHAR;

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

using pm_i32_t = pm_type<pm_type_kind::I32>;
using pm_i64_t = pm_type<pm_type_kind::I64>;
using pm_u32_t = pm_type<pm_type_kind::U32>;
using pm_u64_t = pm_type<pm_type_kind::U64>;
using pm_char_t = pm_type<pm_type_kind::CHAR>;
using pm_bool_t = pm_type<pm_type_kind::BOOL>;

typedef struct
{
  pm_type_kind type;

  union
  {
    pm_i32_t u_i32;
    pm_i64_t u_i64;
    pm_u32_t u_u32;
    pm_u64_t u_u64;
    pm_char_t u_chr;
    pm_bool_t u_bool;
  };

} pm_type_container;

pm_type_container type_container_from_string (std::string_view);

} // namespace pm

#endif // PM_TYPE_H
