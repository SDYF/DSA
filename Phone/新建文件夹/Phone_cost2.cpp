#pragma GCC optimize(3)
#include <time.h>
#include <windows.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Fee {
  string number;  //记录号码
  long cost;      //话费
};

void quickSort(int left, int right, string*& arr);
long Phone_cost(string call_type, string time);

int main() {
  clock_t startTime, endTime;
  ifstream fs;
  startTime = clock();  //计算程序运行时间
  fs.open("records.txt", ios::in);
  ofstream out;
  out.open("cost.txt", ios::out);

  string* s;
  s = new string[1000000];
  long i = 0;
  while (!fs.eof()) {
    fs >> s[i];
    i++;
    fs.get();
    if (fs.peek() == EOF) break;
  }

  quickSort(0, 999999, s);

  // for (i = 999980; i < 1000000; i++) cout << s[i] << endl;

  Fee* fee;
  fee = new Fee[1000000];

  string temp;
  long j = 0;

  temp.assign(s[0], 0, 11);
  fee[j].number = temp;
  fee[j].cost = 0;
  for (i = 0; i < 1000000; i++) {
    if (temp != s[i].substr(0, 11)) {
      j++;
      temp = s[i].substr(0, 11);
      fee[j].number = temp;
      fee[j].cost = 0;
    }
    fee[j].cost += Phone_cost(s[i].substr(11, 2), s[i].substr(13, 4));

    //  if (i > 999980) cout << 1 << endl;
  }
  // cout << 1;

  for (i = 0; i <= j; i++) {
    out << fee[i].number;
    out << setw(8) << setfill('0') << fee[i].cost << endl;
  }

  endTime = clock();
  cout << "The run time is " << (double)(endTime - startTime) / CLOCKS_PER_SEC
       << 's' << endl;  //输出运行时间
  fs.close();
  out.close();
  cin.ignore();
  return 0;
}

void quickSort(int left, int right, string*& arr) {
  if (left >= right) return;
  int i, j;
  string temp, base;
  i = left, j = right;
  base = arr[left];  //取最左边的数为基准数
  while (i < j) {
    while (arr[j].substr(3, 8) >= base.substr(3, 8) && i < j) j--;
    while (arr[i].substr(3, 8) <= base.substr(3, 8) && i < j) i++;
    if (i < j) {
      temp = arr[i];
      arr[i] = arr[j];
      arr[j] = temp;
    }
  }
  //基准数归位
  arr[left] = arr[i];
  arr[i] = base;
  quickSort(left, i - 1, arr);   //递归左边
  quickSort(i + 1, right, arr);  //递归右边
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