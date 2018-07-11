#include <iostream>
#include <stdexcept>
#include "base64_map.h"
using namespace std;

void invalid_base64_block();
void assert_valid_base64_block(char chars[4]);
bool is_base64_digit(char c);
int get_num_padding(char chars[4]);

int main() {
  char three_byte_buf[3] = {0,0,0};
  char four_byte_buf[4] = {0,0,0,0};
  int num_padding = 0;

  cin.read(four_byte_buf, 4);

  while (cin.gcount() == 4 && num_padding == 0) {
    try {
      num_padding = get_num_padding(four_byte_buf);
      base64::ascii_to_binary(four_byte_buf, three_byte_buf);
    }
    catch (invalid_argument & e) {
      cerr << "Invalid character in input stream." << endl;
      return 1;
    }

    cout.write(three_byte_buf, 3 - num_padding);
    cin.read(four_byte_buf, 4);
  }

  return 0;
}

void invalid_base64_block() {
  throw invalid_argument("invalid base64 block");
}

void assert_valid_base64_block(char chars[4]) {
  if (!is_base64_digit(chars[0]))
    invalid_base64_block();
  if (!is_base64_digit(chars[1]))
    invalid_base64_block();
  if (!is_base64_digit(chars[2]) && chars[2] != base64::PADDING)
    invalid_base64_block();
  if (!is_base64_digit(chars[3]) && chars[3] != base64::PADDING)
    invalid_base64_block();
  if (chars[2] == base64::PADDING && chars[3] != base64::PADDING)
    invalid_base64_block();
}

/**
 * does not include padding character ('=')
 */
bool is_base64_digit(char c) {
  return (c >= 'A' && c <= 'Z')
    || (c >= 'a' && c <= 'z')
    || (c >= '0' && c <= '9')
    || (c == '+')
    || (c == '/');
}

int get_num_padding(char chars[4]) {
  assert_valid_base64_block(chars);
  if (chars[2] == base64::PADDING) return 2;
  if (chars[3] == base64::PADDING) return 1;
  return 0;
}
