#if !defined(STMT_H)
#define STMT_H

#include "expr.hpp"
#include "header.hpp"

namespace pm
{
enum class stmt_type
{
  FUN_DECL,
  VAR_DECL,
  RETURN,
};

class stmt_t
{
public:
  stmt_type type;

  stmt_t (stmt_type _Type) : type{ _Type } {}
  ~stmt_t () {}
};

class stmt_fundecl : public stmt_t
{
public:
  expr_t *name;

  stmt_fundecl () : stmt_t (stmt_type::FUN_DECL) {}
  ~stmt_fundecl () {}
};

class stmt_vardecl : public stmt_t
{
public:
  expr_t *name;
  expr_t *val;

  stmt_vardecl ()
      : stmt_t (stmt_type::VAR_DECL), name{ nullptr }, val{ nullptr }
  {
  }
  ~stmt_vardecl () {}
};

class stmt_return : public stmt_t
{
public:
  stmt_return () : stmt_t (stmt_type::RETURN) {}
  ~stmt_return () {}
};
} // namespace pm

#endif // STMT_H
