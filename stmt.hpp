#if !defined(STMT_H)
#define STMT_H

#include "expr.hpp"
#include "header.hpp"
#include "type.hpp"

namespace pm
{
enum class stmt_type
{
  FUN_DECL,
  VAR_DECL,
  RETURN,
  STMT_EOF,
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
  using ap_container = std::vector<std::pair<std::string, pm_type_container>>;
  // expr_t *name;

  std::string name;
  ap_container aps;
  std::vector<stmt_t *> body;

  stmt_fundecl () : stmt_t (stmt_type::FUN_DECL) {}
  stmt_fundecl (std::string _Name, ap_container _Aps,
                std::vector<stmt_t *> _Body)
      : stmt_t (stmt_type::FUN_DECL), name{ _Name }, aps{ _Aps }, body{ _Body }
  {
  }

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

class stmt_eof : public stmt_t
{
public:
  stmt_eof () : stmt_t (stmt_type::STMT_EOF) {}
  ~stmt_eof () {}
};
} // namespace pm

#endif // STMT_H
