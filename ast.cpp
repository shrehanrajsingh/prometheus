#include "ast.hpp"

namespace pm
{
token **
get_block (token **&t, size_t &size)
{
  int c = 0;

  token **u = t;
  token *d = nullptr;

  while (1)
    {
      d = *t++;

      if (d->type == tok_type::TOK_EOF)
        break;

      if (d->type == tok_type::BLOCK_SCOPE)
        {
          tok_blockscope *tb = static_cast<tok_blockscope *> (d);

          if (tb->is_open)
            {
              c++;
            }
          else
            {
              if (!c)
                {
                  break;
                }

              c--;
            }
        }
    }

  --t;
  //   print_token (*t);
  size = t - u;
  token **res = new token *[t - u];
  std::copy (u, t, res);
  return res;
}

expr_t *
ast_sm::gen_expr (token *start, token *end)
{
  token *t;
  while (start < end)
    {
      t = start++;

      switch (t->type)
        {
        case tok_type::BLOCK_SCOPE:
          {
          }
          break;

        case tok_type::DTYPE:
          {
          }
          break;

        case tok_type::IDENTIFIER:
          {
          }
          break;

        case tok_type::KEYWORD:
          {
            tok_keyword *tkw = static_cast<tok_keyword *> (t);
          }
          break;

        case tok_type::OPERATOR:
          {
          }
          break;

        case tok_type::TOK_EOF:
          {
            goto end;
          }
          break;

        case tok_type::TOK_NL:
          {
          }
          break;
        default:
          break;
        }
    }

end:;
  return nullptr;
}

stmt_t *
ast_sm::gen_one ()
{
  token *d = nullptr;

  while (1)
    {
      d = *t++;
      //   print_token (d);
      switch (d->type)
        {
        case tok_type::BLOCK_SCOPE:
          {
          }
          break;

        case tok_type::DTYPE:
          {
          }
          break;

        case tok_type::IDENTIFIER:
          {
          }
          break;

        case tok_type::KEYWORD:
          {
            tok_keyword *tkw = static_cast<tok_keyword *> (d);

            if (tkw->val == "fun")
              {
                token *t_name = *t++;
                token *ret_type = nullptr;

                if (t_name->type != tok_type::IDENTIFIER)
                  {
                    throw std::invalid_argument ("syntax error");
                  }

                if (!((*t)->type == tok_type::OPERATOR
                      && static_cast<tok_operator *> (*t++)->val == "->"))
                  {
                    throw std::invalid_argument ("syntax error");
                  }

                ret_type = *t++;

                std::string arg_name;
                pm_type_container arg_type;
                bool saw_colon = false;

                std::vector<std::pair<std::string, pm_type_container>> ap;

                while (1)
                  {
                    d = *++t;

                    if (d->type == tok_type::IDENTIFIER && !saw_colon)
                      {
                        arg_name = static_cast<tok_identifier *> (d)->val;
                      }

                    if (d->type == tok_type::OPERATOR
                        && static_cast<tok_operator *> (d)->val == ":")
                      {
                        saw_colon = 1;
                      }

                    if (d->type == tok_type::DTYPE && saw_colon)
                      {
                        arg_type = type_container_from_string (
                            static_cast<tok_dtype *> (d)->val);
                      }

                    if (d->type == tok_type::TOK_NL && saw_colon)
                      {
                        ap.push_back (std::make_pair (arg_name, arg_type));
                        saw_colon = false;
                      }

                    if (d->type == tok_type::BLOCK_SCOPE)
                      {
                        break;
                      }
                  }

                // for (auto &&i : ap)
                //   {
                //     std::cout << i.first << '\t' << int (i.second.type)
                //               << '\n';
                //   }

                size_t sblk = 0;
                t++;
                token **blk = get_block (t, sblk);

                token *k = blk[sblk - 1];
                blk[sblk - 1] = new tok_eof ();

                ast_sm bsm (blk);
                bsm.gen ();

                blk[sblk - 1] = k;

                return new stmt_fundecl (
                    static_cast<tok_identifier *> (t_name)->val, ap,
                    bsm.result);
              }
          }
          break;

        case tok_type::OPERATOR:
          {
          }
          break;

        case tok_type::TOK_EOF:
          {
            goto end;
          }
          break;

        case tok_type::TOK_NL:
          {
          }
          break;

        default:
          break;
        }
    }

end:;
  return nullptr;
}

void
ast_sm::gen ()
{
  stmt_t *r = gen_one ();

  while (r != nullptr && r->type != stmt_type::STMT_EOF)
    {
      result.push_back (r);
      r = gen_one ();
    }
}
} // namespace pm
