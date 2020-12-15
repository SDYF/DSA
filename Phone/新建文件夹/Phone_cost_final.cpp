#pragma GCC optimize(2)
#include <time.h>
#include <windows.h>

#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

using namespace std;

int Phone_cost(int, int);

int main() {
  clock_t startTime, endTime;
  startTime = clock();

  FILE *in, *out;
  in = fopen("record.txt", "r");
  out = fopen("cost_1.txt", "w");

  long *fee, *a, index;
  fee = (long *)malloc(100000000 * sizeof(long));
  a = (long *)malloc(200000 * sizeof(long));
  long i = 0, j = 0, k = 0;
  long phone_cost;
  int call_type, time;
  char record[23];

  while ((fgets(record, 23, in)) != NULL) {
    index = record[10] + record[9] * 10 + record[8] * 100 + record[7] * 1000 +
            record[6] * 10000 + record[5] * 100000 + record[4] * 1000000 +
            record[3] * 10000000 - 533333328;

    time = record[16] + record[15] * 10 + record[14] * 100 + record[13] * 1000 -
           53328;

    if (record[12] == '0')
      phone_cost = time * 40;
    else
      phone_cost = time * 20;

    if (fee[index] != 0) {
      fee[index] += phone_cost;  //相同号码话费累加
    } else {                     //第一次出现的号码
      fee[index] = phone_cost;
      a[i] = index;
      i++;
    }
  }

  for (j = 0; j < i; j++) {
    fprintf(out, "139%08d ", a[j]);

    fprintf(out, "%08ld\n", fee[a[j]]);
  }
  endTime = clock();
  cout << "The run time is " << (double)(endTime - startTime) / CLOCKS_PER_SEC
       << 's' << endl;  //输出运行时间
  fclose(in);
  fclose(out);
}