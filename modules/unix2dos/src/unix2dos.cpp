#include <iostream>
using namespace std;

int main() {
  char c = 0;

  cin.get(c);

  while (cin.gcount()) {
    if (c == '\n')
      cout.write("\r\n", 2);
    else
      cout.put(c);
    cin.get(c);
  }
}
