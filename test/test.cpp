#include <iomanip>
#include <iostream>
#include <string>
using namespace std;
int main() {
  string a = "01234";
  string b = "01234567";
  long n = stoi(a);
  cout << setw(8) << setfill('0') << n << endl;
}