#pragma GCC optimize(2)
#include <time.h>
#include <windows.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

long Hash_index(string);          //计算哈希表索引
long Phone_cost(string, string);  //计算话费

int main() {
  clock_t startTime, endTime;
  ifstream fs;
  startTime = clock();  //计算程序运行时间
  fs.open("record.txt", ios::in);
  ofstream out;
  out.open("cost.txt", ios::out);

  string s, number, call_type, time;
  long i = 0, index, j = 0;
  long *a;
  a = new long[300000];  //记录已被统计过的号码
  long *fee;
  fee = new long[100000000];

  while (!fs.eof()) {
    fs >> s;
    number.assign(s, 0, 11);
    call_type.assign(s, 11, 2);
    time.assign(s, 13, 4);

    index = stoi(number.substr(3, 8));

    if (fee[index] != 0) {
      fee[index] += Phone_cost(call_type, time);  //相同号码话费累加
    } else {                                      //第一次出现的号码
      fee[index] = Phone_cost(call_type, time);
      a[i] = index;
      i++;
    }

    fs.get();
    if (fs.peek() == EOF) break;
  }

  //输出号码和话费
  for (j = 0; j < i; j++) {
    out << "139";
    out << setw(8) << setfill('0') << a[j] << ' ';
    out << setw(8) << setfill('0') << fee[a[j]] << endl;
  }

  endTime = clock();
  std::cout << "The run time is "
            << (double)(endTime - startTime) / CLOCKS_PER_SEC << 's'
            << endl;  //输出运行时间
  fs.close();
  out.close();
  std::cin.ignore();
  delete[] fee;
  delete[] a;
  return 0;
}

long Phone_cost(string call_type, string time) {
  int call = stoi(call_type);
  int cost_per_s, time_int;
  long cost = 0;

  switch (call) {
    case 0:
      cost_per_s = 40;
      break;
    case 1:
      cost_per_s = 20;
      break;
    default:
      break;
  }
  time_int = stoi(time);
  cost = time_int * cost_per_s;
  return cost;
}
