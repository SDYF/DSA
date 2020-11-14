#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int main() {
  srand((int)time(NULL));
  ofstream fs;
  fs.open("List.txt");
  char VIP, name;
  char *name_1;
  int arrival, service_time, n, i, p, j, total = 0, pre = 0, tol_time = 0;
  n = 65 + rand() % 31;
  fs << n << endl;

  for (i = 0; i < n; i++) {
    p = 3 + rand() % 4;
    name_1 = new char[p + 1];
    name_1[0] = (char)(65 + rand() % 26);
    for (j = 1; j <= p - 1; j++) {
      name = (char)(97 + rand() % 26);
      name_1[j] = name;
      // cout << name_1[j];
    }
    //    cin >> VIP;
    name_1[p] = '\0';

    do
      arrival = rand() % 480;
    while ((arrival < pre) || (arrival - pre > 15));
    pre = arrival;
    service_time = 10 + rand() % 26;

    if (rand() % 4 == 0)
      VIP = '1';
    else
      VIP = '0';

    tol_time = 5 + rand() % 31;

    fs << VIP << ' ' << name_1 << ' ' << arrival << ' ' << service_time << ' '
       << tol_time << endl;

    total += service_time;

    for (j = 0; j <= p; j++) name_1[j] = '\0';
  }
  fs.close();
  //   cout << total << endl;
}