#include <prometheus.hpp>

void
test1 ()
{
  std::string d = "";
  auto o = pm::compile_to_wasm (d);

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

  pm::tok_sm tksm (const_cast<char *> (s.c_str ()));
  tksm.gen ();

  std::vector<pm::token *> &toks = tksm.result;

  for (auto &&i : toks)
    {
      pm::print_token (i);
    }

  pm::ast_sm am (toks.data ());
  am.gen ();
}

int
main (int argc, char const *argv[])
{
  test2 ();
  return 0;
}