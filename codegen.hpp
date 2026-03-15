#if !defined(CODEGEN_H)
#define CODEGEN_H

#include "header.hpp"

namespace wl
{
WL_API std::vector<uint8_t> compile_to_wasm (const std::string &);
} // namespace wl

#endif // CODEGEN_H
