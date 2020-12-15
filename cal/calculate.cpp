#include <cmath>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

using namespace std;

bool isoperator(char);
double operate(char, double, double);
int op_index(char);

int main() {
  stack<double> SVAL;
  stack<char> SOP;

  string exp;
  double a, b;
  char c, ch;
  bool end_lab = false;
  bool nega_lab = false;  //标记是否为负数
  size_t index, i;

  while (true) {
    cout << "请输入以\'#\'结尾的表达式，输入回车结束程序" << endl;
    getline(cin, exp);
    if (exp.empty()) break;
    index = 0;
    SOP.push('#');
    while (!SOP.empty()) {
      ch = exp[index];

      if (!isoperator(ch))
        if (nega_lab) {
          SVAL.push(-stod(exp.substr(index), &i));
          index += i;
          nega_lab = false;
          continue;
        } else {
          SVAL.push(stod(exp.substr(index), &i));
          index += i;

          continue;
        }

      switch (ch) {
        case '(':
          SOP.push('(');
          break;
        case ')':
          while (SOP.top() != '(') {
            a = SVAL.top();
            SVAL.pop();
            b = SVAL.top();
            SVAL.pop();
            SVAL.push(operate(SOP.top(), a, b));
            SOP.pop();
          }
          SOP.pop();
          break;
        case '-':
          c = exp[index - 1];
          if (isoperator(c)) {
            nega_lab = true;
            break;
            cout << "- true" << endl;
          }

          goto part1;
        default:
        part1:

          while (op_index(ch) <= op_index(SOP.top())) {
            if (SOP.top() == '#') {
              SOP.pop();
              break;
            }
            a = SVAL.top();
            SVAL.pop();
            b = SVAL.top();
            SVAL.pop();
            SVAL.push(operate(SOP.top(), b, a));
            SOP.pop();
          }

          if (ch != '#') SOP.push(ch);
          break;
      }

      index++;
    }

    cout << "restult = " << SVAL.top() << endl;

    SVAL.pop();
  }

  cout << "Calculator ending..." << endl;
  return 0;
}

bool isoperator(char ch) {
  if (ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '(' ||
      ch == ')' || ch == '^' || ch == '#')
    return true;
  else
    return false;
}

double operate(char ch, double a, double b) {
  switch (ch) {
    case '+':
      return (a + b);

    case '-':
      return (a - b);

    case '*':
      return (a * b);
    case '/':
      return (a / b);
    case '^':
      return (pow(a, b));
    default:
      cout << "Error" << endl;
      break;
  }
  return 0;
}

int op_index(char ch) {
  if (ch == '#') return -1;
  if (ch == '(') return 0;
  if (ch == '+' || ch == '-') return 1;
  if (ch == '*' || ch == '/') return 2;

  if (ch == '^') return 3;
  return 0;
}

//  cout << 3 << ' ' << SVAL.top() << "  " << SOP.top() << endl;