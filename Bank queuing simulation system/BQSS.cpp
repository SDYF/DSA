#include <stdlib.h>
#include <windows.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <queue>
#include <string>

#define TIME 480

using namespace std;

typedef struct {
  int VIP;
  string name;
  int arr_time;
  int ser_time;
  int tol_time;
  int cur_tol_time;
} customer;

enum status { idle, busy };
typedef struct {
  status cur_status;
  int cur_start_time;
  int cur_customer;
  int cur_cust_type;
} window;

void Window_init(window *&, int);
void Time_update(int &, int &);
void End_Serve(window *&, int, int);
void Serve(queue<int> &, window *&, int, customer *, int);
void Wait_tolerance(queue<int> &, customer *&, int &, int &);
void Print_win(window *, customer *, queue<int>, queue<int>, int num);
void Percent_print(double a);

int main() {
  int n = 0, i = 0;
  ifstream fs;
  fs.open("List.txt", ios::in);
  fs >> n;
  customer *cust;
  cust = new customer[n];

  //读取文件
  for (i = 0; i < n; i++) {
    fs >> cust[i].VIP >> cust[i].name >> cust[i].arr_time >> cust[i].ser_time >>
        cust[i].tol_time;
    cust[i].cur_tol_time = 0;
  }

  /*输出测试
  for (i = 0; i < n; i++) {
      cout << cust[i].VIP << ' ' << cust[i].name << ' ' << cust[i].arr_time
           << ' ' << cust[i].ser_time << ' ' << cust[i].tol_time << endl;
  }*/

  //窗口初始化
  int num = 0, hour = 9, minute = -1, is_print;
  cout << "请输入窗口个数\n";
  cin >> num;
  window *win;
  cout << "是否输出窗口信息（1 输出/0 不输出）" << endl;
  cin >> is_print;

  win = new window[num];
  Window_init(win, num);

  int cur_cust = 0, total_wait_time = 0, V_wait_time = 0, N_wait_time = 0,
      leave_cust = 0, time = 0, busy_win = 0, total_busy_win = 0, VIP_num = 0,
      Nor_num = 0;
  double busy_rate = 0.0, leave_rate = 0.0, T_wait_AVG = 0.0, V_wait_AVG = 0.0,
         N_wait_AVG = 0.0;
  queue<int> VQ, NQ;  // VIP队列与普通队列

  for (time = 0; time <= TIME; time++) {
    if (is_print) Time_update(hour, minute);

    //入队
    for (; cur_cust < n; cur_cust++) {
      if (cust[cur_cust].arr_time == time)
        if (cust[cur_cust].VIP) {
          VQ.push(cur_cust);
          VIP_num++;
        } else {
          NQ.push(cur_cust);
          Nor_num++;
        }

      else
        break;
    }

    //顾客办理业务
    busy_win = 0;

    for (i = 0; i < num; i++) {
      //办完业务的顾客离开窗口
      if ((win[i].cur_status == busy) &&
          (win[i].cur_start_time + cust[win[i].cur_customer].ser_time == time))
        End_Serve(win, i, time);

      //空闲窗口接待顾客
      if (win[i].cur_status == idle) {
        if (!VQ.empty())
          Serve(VQ, win, i, cust, time);
        else if (!NQ.empty())
          Serve(NQ, win, i, cust, time);
      }
      if (win[i].cur_status == busy) busy_win++;
    }

    total_busy_win += busy_win;
    busy_rate = (double)busy_win / num;
    if (is_print) {
      cout << "Busy Window Rate:";
      printf("%.2lf", busy_rate * 100);
      cout << '%' << endl;
    }

    //顾客等待及容忍时间
    Wait_tolerance(VQ, cust, V_wait_time, leave_cust);
    Wait_tolerance(NQ, cust, N_wait_time, leave_cust);

    //输出窗口状态
    if (is_print) Print_win(win, cust, VQ, NQ, num);

    // Sleep(500);
    if (is_print) system("cls");
  }
  //银行营业结束,计算时间
  cout << "Bank Close Now!" << endl;
  busy_rate = (double)total_busy_win / (num * TIME);
  total_wait_time = N_wait_time + V_wait_time;
  leave_rate = (double)leave_cust / n;
  T_wait_AVG = (double)total_wait_time / n;
  V_wait_AVG = (double)V_wait_time / VIP_num;
  N_wait_AVG = (double)N_wait_time / Nor_num;

  //窗口平均占用率
  cout << "Total Busy Window Rate:";
  Percent_print(busy_rate);

  //等待时间
  cout << "Total Wait Time:" << total_wait_time << endl;
  cout << "Average:";
  printf("%.2lf", T_wait_AVG);
  cout << endl;

  cout << "VIP Wait Time:" << V_wait_time << endl;
  cout << "Average:";
  printf("%.2lf", V_wait_AVG);
  cout << endl;

  cout << "Ordinary customer Wait Time:" << N_wait_time << endl;
  cout << "Average:";
  printf("%.2lf", N_wait_AVG);
  cout << endl;

  cout << "Number of customers having left:" << leave_cust << endl;
  cout << "Rate:";
  Percent_print(leave_rate);
}

void Window_init(window *&win, int num) {
  int i = 0;
  for (i = 0; i < num; i++) {
    win[i].cur_status = idle;
    win[i].cur_customer = -1;
    win[i].cur_start_time = 0;
    win[i].cur_cust_type = -1;
  }
}

void Time_update(int &h, int &m) {
  m++;
  if (m == 60) {
    m = 0;
    h++;
  }
  cout << "Time:" << h << ':';
  if (m < 10) cout << "0";
  cout << m << endl << endl;
}

void End_Serve(window *&win, int i, int time) {
  win[i].cur_status = idle;
  win[i].cur_cust_type = -1;
  win[i].cur_customer = -1;
  win[i].cur_start_time = time;
}

void Serve(queue<int> &Q, window *&win, int i, customer *cust, int time) {
  win[i].cur_customer = Q.front();
  win[i].cur_status = busy;
  win[i].cur_start_time = time;
  win[i].cur_cust_type = cust[Q.front()].VIP;
  Q.pop();
}

void Wait_tolerance(queue<int> &Q, customer *&cust, int &wait_time,
                    int &leave_cust) {
  if (Q.empty()) return;
  int c;
  for (int i = 0; i < Q.size(); i++) {
    c = Q.front();
    cust[c].cur_tol_time++;
    wait_time++;
    Q.pop();
    if (cust[c].cur_tol_time == cust[c].tol_time)
      leave_cust++;
    else
      Q.push(c);
  }
}

void Print_win(window *win, customer *cust, queue<int> VQ, queue<int> NQ,
               int num) {
  cout << "---------------------------" << endl;
  int i;
  for (i = 0; i < num; i++) {
    cout << "Window No." << (i + 1) << endl;
    if (win[i].cur_status == idle)
      cout << "Idle" << endl;
    else {
      cout << "Busy" << endl;
      cout << "customer:" << cust[win[i].cur_customer].name << endl;
    }
    cout << "---------------------------" << endl;
  }

  cout << endl << endl << endl;
  cout << "WAITING" << endl;
  cout << "---------------------------" << endl;
  for (i = 0; i < VQ.size(); i++) {
    cout << cust[VQ.front()].name << "(VIP)" << ' ';
    if ((i % 5 == 0) && (i != (VQ.size() - 1))) cout << endl;
    VQ.pop();
  }

  for (i = 0; i < NQ.size(); i++) {
    cout << cust[NQ.front()].name << ' ';
    if (((i + 1 + VQ.size()) % 5 == 0) && (i != (NQ.size() - 1))) cout << endl;
    NQ.pop();
  }
  cout << endl << "---------------------------" << endl;
}

void Percent_print(double a) {
  printf("%.2lf", a * 100);
  cout << '%' << endl << endl;
}