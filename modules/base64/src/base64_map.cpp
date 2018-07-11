#include <stdexcept>
#include <sstream>
#include "base64_map.h"

namespace base64 {
  /**
   * `index` is a number 0-63
   */
  char index_to_b64digit(char index) {
    /**
     * Important boundaries:
     * index 00-25 -> base64 A-Z
     * index 26-51 -> base64 a-z
     * index 52-61 -> base64 0-9
     * index 62    -> base64 +
     * index 63    -> base64 /
     */
    if (index < 26) return index + 'A';
    if (index < 52) return index - 26 + 'a';
    if (index < 62) return index - 52 + '0';
    if (index == 62) return '+';
    if (index == 63) return '/';

    // unexpected input. throw an error
    std::stringstream ss;
    ss << "index_to_b64digit(char): expected index to be"
        << " between 0 and 63. Actual value: " << (int)index;
    throw std::invalid_argument(ss.str());
  }

  /**
   * `b64digit` is in the character class [A-Za-z0-9+/=]
   * If input is '=', returns 0.
   */
  char b64digit_to_index(char b64digit) {
    /**
     * Important boundaries:
     * index 00-25 -> base64 A-Z
     * index 26-51 -> base64 a-z
     * index 52-61 -> base64 0-9
     * index 62    -> base64 +
     * index 63    -> base64 /
     */
    if (b64digit >= 'A' && b64digit <= 'Z')
      return b64digit - 'A';
    if (b64digit >= 'a' && b64digit <= 'z')
      return b64digit - 'a' + 26;
    if (b64digit >= '0' && b64digit <= '9')
      return b64digit - '0' + 52;
    if (b64digit == '+')
      return 62;
    if (b64digit == '/')
      return 63;
    if (b64digit == '=')
      return 0;

    // unexpected input. throw an error
    std::stringstream ss;
    ss << "b64digit_to_index(char): expected input to be"
        << " a valid base64 digit. Actual value: (char)" << (int)b64digit;
    throw std::invalid_argument(ss.str());
  }

  void binary_to_ascii(const char bytes[3], char chars[4]) {
    chars[0] = index_to_b64digit((bytes[0] & 0xfc) >> 2);
    chars[1] = index_to_b64digit(((bytes[0] & 0x3) << 4) | ((bytes[1] & 0xf0) >> 4));
    chars[2] = index_to_b64digit(((bytes[1] & 0xf) << 2) | ((bytes[2] & 0xc0) >> 6));
    chars[3] = index_to_b64digit(bytes[2] & 0x3f);
  }

  void ascii_to_binary(const char chars[4], char bytes[3]) {
    char indices[4];
    indices[0] = b64digit_to_index(chars[0]);
    indices[1] = b64digit_to_index(chars[1]);
    indices[2] = b64digit_to_index(chars[2]);
    indices[3] = b64digit_to_index(chars[3]);

    bytes[0] = (indices[0] << 2) | ((indices[1] & 0x30) >> 4);
    bytes[1] = ((indices[1] & 0xf) << 4) | ((indices[2] & 0x3c) >> 2);
    bytes[2] = ((indices[2] & 0x3) << 6) | indices[3];
  }
}
