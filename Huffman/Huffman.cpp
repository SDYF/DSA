#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  ifstream in;
  in.open("stdio.h", ios::in);

  long a[128];
  char c;
  int i;

  for (i = 0; i < 128; i++) a[i] = 0;
  while ((c = in.get()) != EOF) {
    a[(int)c]++;
  }

  for (i = 0; i < 127; i++)
    if (a[i]) cout << (char)i << ' ' << a[i] << endl;
  in.close();
}