#include <time.h>
#include <windows.h>

#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  clock_t startTime, endTime;
  ifstream fs;
  startTime = clock();
  fs.open("records.txt", ios::in);

  string s, number, call_type, time;
  long i;

  while (!fs.eof()) {
    fs >> s;
    number.assign(s, 0, 11);
    call_type.assign(s, 11, 2);
    time.assign(s, 13, 4);
    cout << number << ' ' << call_type << ' ' << time << endl;
    fs.get();
    if (fs.peek() == EOF) break;
  }

  endTime = clock();
  cout << "The run time is " << (double)(endTime - startTime) / CLOCKS_PER_SEC
       << 's' << endl;
  fs.close();
}