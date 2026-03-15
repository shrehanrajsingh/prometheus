#if !defined(HEADER_H)
#define HEADER_H

#include <filesystem>
#include <fstream>
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <ostream>
#include <sstream>
#include <string>
#include <typeinfo>
#include <vector>

#include <cassert>
#include <cctype>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#include <binaryen-c.h>

#define WL_API

#define here printf ("%s: %d (%s)\n", __FILE__, __LINE__, __FUNCTION__);
#define eprintf(...) fprintf (stderr, __VA_ARGS__)

#endif // HEADER_H
