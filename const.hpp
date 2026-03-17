#if !defined(CONST_H)
#define CONST_H

#include "header.hpp"

namespace pm
{
enum class const_type
{
  INT,
  FLOAT,
  STRING,
  CHAR,
  BOOL,
  NULL_TYPE,
};

class const_t
{
public:
  const_type type;

  const_t () : type{ const_type::NULL_TYPE } {}
  const_t (const_type _Type) : type{ _Type } {}
  ~const_t () {}
};

class const_int : public const_t
{
public:
  uint8_t *val; /* store in leb128 format */
  size_t vl;

  const_int () : const_t (const_type::INT), val{ nullptr }, vl{ 0 } {}

  const_int (int v) : const_t (const_type::INT), vl{ 0 }
  {
    std::vector<uint8_t> leb;
    int vv = v;
    do
      {
        uint8_t byte = vv & 0x7F;
        vv >>= 7;
        if ((vv != 0 && vv != -1) || ((byte & 0x40) != (vv & 0x40)))
          {
            byte |= 0x80;
          }
        leb.push_back (byte);
      }
    while ((vv != 0 && vv != -1) || ((leb.back () & 0x40) != (vv & 0x40)));
    val = new uint8_t[vl = leb.size ()];
    std::copy (leb.begin (), leb.end (), val);
  }

  const_int (char *d, size_t dl) : const_t (const_type::INT), vl{ 0 }
  {
    std::string num_str (d, dl);
    std::vector<uint8_t> leb;
    bool is_neg = false;
    size_t idx = 0;

    if (!num_str.empty () && (num_str[0] == '-' || num_str[0] == '+'))
      {
        is_neg = (num_str[0] == '-');
        idx = 1;
      }

    std::vector<uint8_t> digits;
    for (; idx < num_str.size (); ++idx)
      {
        if (num_str[idx] < '0' || num_str[idx] > '9')
          break;
        digits.push_back (num_str[idx] - '0');
      }

    std::vector<uint8_t> num;
    if (!digits.empty ())
      {
        num.push_back (0);
        for (auto j : digits)
          {
            int carry = j;
            for (size_t i = 0; i < num.size (); ++i)
              {
                int val = num[i] * 10 + carry;
                num[i] = val & 0xFF;
                carry = val >> 8;
              }
            while (carry)
              {
                num.push_back (carry & 0xFF);
                carry >>= 8;
              }
          }
      }
    else
      {
        num.push_back (0);
      }

    bool is_more = true;
    while (is_more)
      {
        uint8_t byte = num[0] & 0x7F;
        bool sign_bit = is_neg && ((byte & 0x40) != 0);

        int carry = 0;
        for (size_t i = num.size (); i-- > 0;)
          {
            int val = (carry << 8) | num[i];
            num[i] = (val >> 7) & 0xFF;
            carry = val & 0x7F;
          }

        while (num.size () > 1 && num.back () == 0)
          num.pop_back ();

        if ((num.size () == 1
             && ((num[0] == 0 && !sign_bit) || (num[0] == 0x7F && sign_bit))))
          is_more = false;
        else
          byte |= 0x80;

        leb.push_back (byte);
      }

    val = new uint8_t[vl = leb.size ()];
    std::copy (leb.begin (), leb.end (), val);
  }

  ~const_int () {}
};

class const_float : public const_t
{
public:
  float val;

  const_float () : const_t (const_type::FLOAT), val (0.0f) {}
  const_float (float _Val) : const_t (const_type::FLOAT), val{ _Val } {}

  ~const_float () {}
};

class const_string : public const_t
{
public:
  std::string val;

  const_string () : const_t (const_type::STRING), val ("") {}
  const_string (std::string _Val) : const_t (const_type::STRING), val{ _Val }
  {
  }

  ~const_string () {}
};

class const_char : public const_t
{
public:
  char val;

  const_char () : const_t (const_type::CHAR), val (0) {}
  const_char (char _Val) : const_t (const_type::CHAR), val{ _Val } {}

  ~const_char () {}
};

class const_bool : public const_t
{
public:
  bool val;

  const_bool () : const_t (const_type::BOOL), val (false) {}
  const_bool (bool _Val) : const_t (const_type::BOOL), val{ _Val } {}

  ~const_bool () {}
};

class const_nulltype : public const_t
{
public:
  const_nulltype () : const_t (const_type::NULL_TYPE) {}
  ~const_nulltype () {}
};

void print_constt (const const_t *);
} // namespace pm

#endif // CONST_H
