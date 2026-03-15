#include <wlang.hpp>

void
test1 ()
{
  std::string d = "";
  auto o = wl::compile_to_wasm (d);

  FILE *fptr = fopen ("../../tests/out.wasm", "wb");
  fwrite (o.data (), 1, o.size (), fptr);

  fclose (fptr);
}

void
test2 ()
{
  std::ifstream fl ("../../ground/test.wll");

  if (!fl.is_open ())
    {
      std::cerr << "Error opening file\n";
      return;
    }

  std::ostringstream ss;
  ss << fl.rdbuf ();
  fl.close ();

  std::string s = ss.str ();

  wl::tok_sm tksm (const_cast<char *> (s.c_str ()));
  tksm.gen ();

  std::vector<wl::token *> &toks = tksm.result;

  for (auto &&i : toks)
    {
      wl::print_token (i);
    }
}

int
main (int argc, char const *argv[])
{
  test2 ();
  return 0;
}