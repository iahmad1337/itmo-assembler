#include <cstdint>

namespace lzw {
  using std::size_t;
  size_t lzw_encode(const uint8_t *in, size_t in_size, uint8_t * out, size_t out_size);
  size_t lzw_decode(const uint8_t *in, size_t in_size, uint8_t * out, size_t out_size);
}  // namespace lzw
