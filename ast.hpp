#if !defined(AST_H)
#define AST_H

#include "expr.hpp"
#include "header.hpp"
#include "stmt.hpp"
#include "token.hpp"
#include "type.hpp"

namespace pm
{
class ast_sm
{
public:
  token **t;
  size_t ti;

  std::vector<stmt_t *> result;

  ast_sm () : ti{ 0 } {}
  ast_sm (token **_Toks) : t{ _Toks }, ti{ 0 } {}
  ~ast_sm () {}

  expr_t *gen_expr (token *, token *);

  stmt_t *gen_one ();
  void gen ();
};
} // namespace pm

#endif // AST_H
