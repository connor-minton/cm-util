#ifndef BASE64_MAP_H
#define BASE64_MAP_H

namespace base64 {
  const char PADDING = '=';
  void binary_to_ascii(const char bytes[3], char chars[4]);
  void ascii_to_binary(const char chars[4], char bytes[3]);
}

#endif
