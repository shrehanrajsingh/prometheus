#include "type.hpp"

namespace pm
{
pm_type_container
type_container_from_string (std::string_view s)
{
  pm_type_container c;

  if (s == "i32")
    c.type = pm_type_kind::I32;

  if (s == "i64")
    c.type = pm_type_kind::I64;

  if (s == "u32")
    c.type = pm_type_kind::U32;

  if (s == "u64")
    c.type = pm_type_kind::U64;

  if (s == "char")
    c.type = pm_type_kind::CHAR;

  if (s == "bool")
    c.type = pm_type_kind::BOOL;

  return c;
}
} // namespace pm
