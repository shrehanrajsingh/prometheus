#include "codegen.hpp"

namespace wl
{
WL_API std::vector<uint8_t>
compile_to_wasm (const std::string &a)
{
  BinaryenModuleRef mod = BinaryenModuleCreate ();

  BinaryenType params[] = {
    BinaryenTypeInt32 (),
    BinaryenTypeInt32 (),
  };

  BinaryenType param_type = BinaryenTypeCreate (params, 2);

  BinaryenType result_type = BinaryenTypeInt32 ();

  BinaryenExpressionRef p_a = BinaryenLocalGet (mod, 0, BinaryenTypeInt32 ());
  BinaryenExpressionRef p_b = BinaryenLocalGet (mod, 1, BinaryenTypeInt32 ());
  BinaryenExpressionRef sum
      = BinaryenBinary (mod, BinaryenAddInt32 (), p_a, p_b);

  BinaryenAddFunction (mod, "add", param_type, result_type, NULL, 0, sum);

  BinaryenAddFunctionExport (mod, "add", "add");
  BinaryenModuleValidate (mod);

  size_t size;
  BinaryenModuleAllocateAndWriteResult wasm
      = BinaryenModuleAllocateAndWrite (mod, NULL);

  uint8_t *data = (uint8_t *)wasm.binary;
  std::vector<uint8_t> wasm_bytes (data, data + wasm.binaryBytes);

  return wasm_bytes;
}
} // namespace wl
