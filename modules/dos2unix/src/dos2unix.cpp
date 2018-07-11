#include <iostream>
using namespace std;

int main() {
  char c = 0;

  cin.get(c);

  while (cin.gcount()) {
    if (c != '\r')
      cout.put(c);
    cin.get(c);
  }
}
