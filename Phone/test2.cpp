#include <iostream>
#include <string>

using namespace std;

int main() {
  string s1, s2;
  s1 = "201714999";
  s2 = "20171512";
  if (s1.substr(5, 6) > s2.substr(5, 6))
    cout << 1;
  else
    cout << 0;
}