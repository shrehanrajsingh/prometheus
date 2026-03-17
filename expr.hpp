#if !defined(EXPR_H)
#define EXPR_H

#include "const.hpp"
#include "header.hpp"

namespace pm
{
enum class expr_type
{
  VAR_DECL,
  VAR,
  CONST,
};

class expr_t
{
public:
  expr_type type;

  expr_t (expr_type _Type) : type{ _Type } {}
  ~expr_t () {}
};

class expr_vardecl : public expr_t
{
public:
  expr_t *name;
  expr_t *val;

  expr_vardecl ()
      : expr_t (expr_type::VAR_DECL), name{ nullptr }, val{ nullptr }
  {
  }

  ~expr_vardecl () {}
};

class expr_var : public expr_t
{
public:
  std::string val;

  expr_var () : expr_t (expr_type::VAR) {}
  expr_var (std::string _Val) : expr_t (expr_type::VAR), val{ _Val } {}

  ~expr_var () {}
};

class expr_const : public expr_t
{
public:
  const_t *val;

  expr_const () : expr_t (expr_type::CONST), val{ nullptr } {}
  expr_const (const_t *_Val) : expr_t (expr_type::CONST), val{ _Val } {}
  ~expr_const () {}
};
} // namespace pm

#endif // EXPR_H
