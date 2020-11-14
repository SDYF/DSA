#pragma GCC optimize(2)
#include <time.h>
#include <windows.h>

#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

using namespace std;

struct Fee {
  int status;
  string number;
  long cost;
  struct Fee *next;
};

long Hash_index(string);
long Phone_cost(string, string);

int main() {
  clock_t startTime, endTime;
  ifstream fs;
  startTime = clock();
  fs.open("records.txt", ios::in);
  ofstream out;
  out.open("cost.txt", ios::out);

  string s, number, call_type, time;
  long i = 0, index, j = 0;
  long *a;
  a = new long[300000];
  Fee *fee, *p;
  fee = new Fee[1000000];

  while (!fs.eof()) {
    fs >> s;
    number.assign(s, 0, 11);
    call_type.assign(s, 11, 2);
    time.assign(s, 13, 4);

    index = Hash_index(number);
    p = &fee[index];

    if ((p->status == 1) && (number.compare(p->number))) {
      while (p->next != NULL) p = p->next;
      p->next = new Fee;
      p = p->next;

      p->next = NULL;
      p->number = number;
      p->status = 1;
      p->cost = Phone_cost(call_type, time);
      a[i] = index;
      i++;
    } else if ((p->status == 1) && !(number.compare(p->number))) {
      p->cost += Phone_cost(call_type, time);
    } else if (p->status != 1) {
      p->number = number;
      p->status = 1;
      p->cost = Phone_cost(call_type, time);
      p->next = NULL;
      a[i] = index;
      i++;
    }

    fs.get();
    if (fs.peek() == EOF) break;
  }

  for (j = 0; j < i; j++) {
    p = &fee[a[j]];
    while (p != NULL) {
      out << p->number;
      out << setw(8) << setfill('0') << p->cost << endl;
      p = p->next;
    }
  }
  endTime = clock();
  cout << "The run time is " << (double)(endTime - startTime) / CLOCKS_PER_SEC
       << 's' << endl;
  fs.close();
  out.close();
  cin.ignore();
  delete[] fee;
  delete[] a;
  return 0;
}

long Hash_index(string num) {
  string num_1, num_2;
  long n;
  int num1;
  num_1.assign(num, 3, 4);
  num_2.assign(num, 7, 4);
  num1 = stoi(num_1);
  n = (long)pow(num1, 2) % 97;
  n = n * 10000 + stol(num_2);
  return n;
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
