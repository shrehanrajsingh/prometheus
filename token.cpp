#include "token.hpp"

namespace pm
{
bool
is_keyword (std::string_view s)
{
  std::vector<std::string_view> a = { "fun", "return" };

  for (auto &&i : a)
    if (i == s)
      return true;

  return false;
}

bool
is_operator (char d)
{
  static std::string ops = "!~%^&*()-+=[]{}\\|:;'\",.<>/?";
  return ops.find (d) != std::string::npos;
}

bool
is_dtype (std::string_view d)
{
  std::vector<std::string_view> a
      = { "i32", "i64", "u32", "u64", "f32", "f64", "bool", "char" };

  for (auto &&i : a)
    if (i == d)
      return true;

  return false;
}

bool
is_operator_full (char *d, size_t dl)
{
  static const char *ops[]
      = { "!",  "~",   "%",   "^",  "&",  "*",  "(",  ")",  "-",  "+",  "=",
          "[",  "]",   "{",   "}",  "\\", "|",  ":",  ";",  "'",  "\"", ",",
          ".",  "<",   ">",   "/",  "?",  "==", "!=", "<=", ">=", "&&", "||",
          "++", "--",  "+=",  "-=", "*=", "/=", "%=", "&=", "|=", "^=", "<<",
          ">>", "<<=", ">>=", "->", "::", "=>", "//", "/*", "*/" };
  static const size_t ops_count = sizeof (ops) / sizeof (ops[0]);

  for (size_t i = 0; i < ops_count; ++i)
    {
      size_t len = strlen (ops[i]);
      if (dl == len && strncmp (d, ops[i], len) == 0)
        return true;
    }

  return false;
}

token *
tok_sm::gen_one ()
{
  char d = tsm.peek ();

  bool saw_var = false;
  bool saw_op = false;
  bool saw_num = false;
  bool saw_dot = false;

  char var[128] = { 0 };
  char op[32] = { 0 };
  char num[128] = { 0 };

  size_t oc = 0;
  size_t vc = 0;
  segsz_t nc = 0;

  while (d != '\0')
    {
      if (saw_num || (!saw_var && isnumber (d)))
        {
          if (!saw_num)
            saw_num = true;

          if (!isnumber (d) && d != '.')
            {
              num[nc] = '\0';

              return new tok_const (new const_int (num, nc));
            }

          num[nc++] = d;
        }

      if (d == '.' && saw_num)
        {
          if (saw_dot)
            {
              num[nc] = '\0';

              return new tok_const (new const_float (atof (num)));
            }
          else
            {
              saw_dot = true;
              num[nc++] = d;
            }
        }

      if (isalpha (d) || (saw_var && isnumber (d)))
        {
          if (!saw_var)
            saw_var = true;

          var[vc++] = d;
        }
      else
        {
          if (saw_var)
            {
              var[vc] = '\0';

              if (!strcmp (var, "then") || !strcmp (var, "end"))
                {
                  return new tok_blockscope (var[0] == 't');
                }
              else
                {
                  if (is_dtype (var))
                    return new tok_dtype (var);
                  if (is_keyword (var))
                    return new tok_keyword (var);
                  return new tok_identifier (var);
                }
            }
        }

      if (is_operator (d))
        {
          if (!saw_op)
            saw_op = true;

          op[oc++] = d;
        }
      else
        {
          if (saw_op)
            {
              op[oc] = '\0';

              //   std::cout << op << '\t' << oc << '\t' << int (tsm.peek ())
              //             << '\n';

              if (op[0] == '-' && oc == 1)
                {
                  if (tsm.peek () == '\n')
                    {
                      return new tok_blockscope ();
                    }
                }

              if (is_operator_full (op, oc))
                {
                  tsm.next ();
                  return new tok_operator (op);
                }

              eprintf ("invalid operator '%s'", op);
              exit (EXIT_FAILURE);

              oc = 0;
              saw_op = false;
            }
        }

      if (d == '\n')
        {
          tsm.next ();
          return new tok_nl ();
        }

      d = tsm.next ();
    }

  if (saw_var)
    {
      var[vc] = '\0';

      if (!strcmp (var, "then") || !strcmp (var, "end"))
        {
          return new tok_blockscope (var[0] == 't');
        }
      else
        {
          if (is_dtype (var))
            return new tok_dtype (var);
          if (is_keyword (var))
            return new tok_keyword (var);
          return new tok_identifier (var);
        }
    }

  if (saw_op)
    {
      op[oc] = '\0';

      //   std::cout << op << '\t' << oc << '\t' << int (tsm.peek ())
      //             << '\n';

      if (op[0] == '-' && oc == 1)
        {
          return new tok_blockscope ();
        }

      if (is_operator_full (op, oc))
        {
          tsm.next ();
          return new tok_operator (op);
        }

      eprintf ("invalid operator '%s'", op);
      exit (EXIT_FAILURE);

      oc = 0;
      saw_op = false;
    }

  return new tok_eof ();
}

void
tok_sm::gen ()
{
  token *t = gen_one ();

  while (t->type != tok_type::TOK_EOF)
    {
      result.push_back (t);
      t = gen_one ();
    }

  result.push_back (t);
}

void
print_tok_type (const tok_type t)
{
  switch (t)
    {
    case tok_type::KEYWORD:
      printf ("KEYWORD");
      break;
    case tok_type::IDENTIFIER:
      printf ("IDENTIFIER");
      break;
    case tok_type::DTYPE:
      printf ("DTYPE");
      break;
    case tok_type::OPERATOR:
      printf ("OPERATOR");
      break;
    case tok_type::BLOCK_SCOPE:
      printf ("BLOCK_SCOPE");
      break;
    case tok_type::TOK_NL:
      printf ("TOK_NL");
      break;
    case tok_type::TOK_EOF:
      printf ("TOK_EOF");
      break;
    case tok_type::TOK_CONST:
      printf ("TOK_CONST");
      break;
    default:
      printf ("UNKNOWN");
      break;
    }
}

void
print_token (const token *t)
{
  if (!t)
    {
      printf ("null token\n");
      return;
    }
  print_tok_type (t->type);
  switch (t->type)
    {
    case tok_type::KEYWORD:
      printf ("('%s')", static_cast<const tok_keyword *> (t)->val.c_str ());
      break;
    case tok_type::IDENTIFIER:
      printf ("('%s')", static_cast<const tok_identifier *> (t)->val.c_str ());
      break;
    case tok_type::DTYPE:
      printf ("('%s')", static_cast<const tok_dtype *> (t)->val.c_str ());
      break;
    case tok_type::OPERATOR:
      printf ("('%s')", static_cast<const tok_operator *> (t)->val.c_str ());
      break;
    case tok_type::BLOCK_SCOPE:
    case tok_type::TOK_NL:
    case tok_type::TOK_EOF:
      // No extra info
      break;
    case tok_type::TOK_CONST:
      {
        printf (": ");
        print_constt (static_cast<const tok_const *> (t)->c);
      }
      break;
    default:
      printf (" (unknown)");
      break;
    }
  printf ("\n");
}
} // namespace pm
