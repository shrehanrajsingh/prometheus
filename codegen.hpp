#if !defined(CODEGEN_H)
#define CODEGEN_H

#include "header.hpp"

namespace pm
{
WL_API std::vector<uint8_t> compile_to_wasm (const std::string &);
} // namespace pm

#endif // CODEGEN_H
