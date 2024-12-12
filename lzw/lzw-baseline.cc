#include "lzw-baseline.hh"

namespace lzw {
  size_t lzw_encode(const uint8_t *in, size_t in_size, uint8_t * out, size_t out_size);
  size_t lzw_decode(const uint8_t *in, size_t in_size, uint8_t * out, size_t out_size);
}
