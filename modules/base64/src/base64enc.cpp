#include <iostream>
#include "base64_map.h"
using namespace std;

void apply_padding(char buf[4], int num_padding) {
  for (int i = 0; i < num_padding; i++)
    buf[3-i] = base64::PADDING;
}

int main() {
  char three_byte_buf[3] = {0,0,0};
  char four_byte_buf[4] = {0,0,0,0};

  cin.read(three_byte_buf, 3);

  while (cin.gcount() > 0) {
    int num_padding = 3 - cin.gcount();
    base64::binary_to_ascii(three_byte_buf, four_byte_buf);
    apply_padding(four_byte_buf, num_padding);
    cout.write(four_byte_buf, 4);
    cin.read(three_byte_buf, 3);
  }

  return 0;
}
