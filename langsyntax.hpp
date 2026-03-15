#if !defined(LANGSYNTAX_H)
#define LANGSYNTAX_H

#include "header.hpp"

namespace pm
{
class ls_sm
{
public:
  char *code;

  ls_sm (char *_Code) : code{ _Code } {}
  ~ls_sm () {}

  char
  next ()
  {
    return *++code;
  }

  char
  peek ()
  {
    return *code;
  }

  char
  peek_next ()
  {
    return *(code + 1);
  }

  char
  peek_prev ()
  {
    return *(code - 1);
  }

  /* next non-space character  */
  char
  next_sns ()
  {
    char d = next ();

    while (d == ' ' || d == '\t' || d == '\n')
      d = next ();

    return d;
  }

  char
  prev ()
  {
    return *--code;
  }
};
} // namespace pm

#endif // LANGSYNTAX_H
