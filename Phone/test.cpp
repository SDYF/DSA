#include <time.h>
#include <windows.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

long a[100000000];

int main() {
  clock_t startTime, endTime;
  ifstream fs;
  startTime = clock();
  fs.open("records_2.txt", ios::in);

  string s, number, call_type, time;
  long i, n;

  for (i = 0; i < 100000000; i++) a[i] = 0;

  i = 0;

  while (!fs.eof()) {
    fs >> s;
    number.assign(s, 3, 4);
    // cout << number << endl;
    n = stol(number);
    n = pow(n, 2);
    n = n % 97;
    a[n]++;
    fs.get();

    if (fs.peek() == EOF) break;
    i++;
  }
  cout << i << endl;
  cout << s << endl;
  for (i = 0; i < 100000000; i++)
    if (a[i]) cout << i << ' ' << a[n] << endl;
  endTime = clock();
  cout << "The run time is " << (double)(endTime - startTime) / CLOCKS_PER_SEC
       << 's' << endl;
  fs.close();
}