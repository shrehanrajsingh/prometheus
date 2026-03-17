#include "const.hpp"

namespace pm
{
void
print_constt (const const_t *c)
{
  if (!c)
    return;

  switch (c->type)
    {
    case const_type::INT:
      {
        auto *ci = static_cast<const const_int *> (c);
        std::cout << "INT (hex): ";
        for (size_t i = 0; i < ci->vl; ++i)
          std::cout << std::hex << (int)ci->val[i] << " ";
        std::cout << std::dec << std::endl;
        break;
      }
    case const_type::FLOAT:
      {
        auto *cf = static_cast<const const_float *> (c);
        std::cout << "FLOAT: " << cf->val << std::endl;
        break;
      }
    case const_type::STRING:
      {
        auto *cs = static_cast<const const_string *> (c);
        std::cout << "STRING: " << cs->val << std::endl;
        break;
      }
    case const_type::CHAR:
      {
        auto *cc = static_cast<const const_char *> (c);
        std::cout << "CHAR: " << cc->val << std::endl;
        break;
      }
    case const_type::BOOL:
      {
        auto *cb = static_cast<const const_bool *> (c);
        std::cout << "BOOL: " << (cb->val ? "true" : "false") << std::endl;
        break;
      }
    case const_type::NULL_TYPE:
      std::cout << "NULL_TYPE" << std::endl;
      break;
    }
}
} // namespace pm
