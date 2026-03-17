#if !defined(TOKEN_H)
#define TOKEN_H

#include "const.hpp"
#include "header.hpp"
#include "langsyntax.hpp"

namespace pm
{
enum class tok_type
{
  KEYWORD = 0,
  IDENTIFIER = 1,
  DTYPE = 2,
  OPERATOR = 3,
  BLOCK_SCOPE = 4, /* block starter (- ... -) */
  TOK_NL = 5,
  TOK_CONST = 6,
  TOK_EOF,
};

class token
{
public:
  tok_type type;
  token (tok_type _Type = tok_type::TOK_EOF) : type{ _Type } {}
  ~token () {}
};

class tok_keyword : public token
{
public:
  std::string val;

  tok_keyword (std::string _Val) : token (tok_type::KEYWORD), val{ _Val } {}
  ~tok_keyword () {}
};

class tok_identifier : public token
{
public:
  std::string val;

  tok_identifier (std::string _Val) : token (tok_type::IDENTIFIER), val{ _Val }
  {
  }
  ~tok_identifier () {}
};

class tok_dtype : public token
{
public:
  std::string val;

  tok_dtype (std::string _Val) : token (tok_type::DTYPE), val{ _Val } {}
  ~tok_dtype () {}
};

class tok_operator : public token
{
public:
  std::string val;

  tok_operator (std::string _Val) : token (tok_type::OPERATOR), val{ _Val } {}
  ~tok_operator () {}
};

class tok_blockscope : public token
{
public:
  bool is_open;
  tok_blockscope () : token (tok_type::BLOCK_SCOPE), is_open{ false } {}
  tok_blockscope (bool _Is_Open)
      : token (tok_type::BLOCK_SCOPE), is_open{ _Is_Open }
  {
  }
  ~tok_blockscope () {}
};

class tok_nl : public token
{
public:
  tok_nl () : token (tok_type::TOK_NL) {}
  ~tok_nl () {}
};

class tok_eof : public token
{
public:
  tok_eof () : token (tok_type::TOK_EOF) {}
  ~tok_eof () {}
};

class tok_const : public token
{
public:
  const_t *c;

  tok_const () : token (tok_type::TOK_CONST) {}
  tok_const (const_t *_C) : token (tok_type::TOK_CONST), c{ _C } {}
  ~tok_const () {}
};

/* state machine */
class tok_sm
{
public:
  ls_sm tsm;
  std::vector<token *> result;

  tok_sm (char *code) : tsm{ ls_sm (code) } {}

  token *gen_one ();
  void gen ();
  ~tok_sm () {}
};

void print_tok_type (const tok_type);
void print_token (const token *);
} // namespace pm

#endif // TOKEN_H
