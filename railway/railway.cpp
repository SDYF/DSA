#include <climits>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <string>

#define Infinity 100000

using namespace std;

struct City {
  int num;
  string name;
};

#pragma region Garph

class Graph {
 public:
  Graph(int);
  //~Graph();
  void Print_arces();
  void Dijkstra(int, int, City *);

 private:
  int vexnum, arcnum;  //顶点数和边数
  int *vexs;           //顶点数组
  int **arces;         //邻接矩阵
  // City *city;          //城市信息
};

Graph::Graph(int vex_num) {
  vexnum = vex_num;
  arcnum = 0;
  vexs = new int[vexnum];
  arces = new int *[vexnum];
  int i, j;
  for (i = 0; i < vexnum; i++) arces[i] = new int[vexnum];
  for (i = 0; i < vexnum; i++)
    for (j = 0; j < vexnum; j++) arces[i][j] = Infinity;

  ifstream in;
  in.open("dist.txt", ios::in);
  int a, b, length;
  while (!in.eof()) {
    in >> a >> b >> length;
    arces[a][b] = length;
    arces[b][a] = length;
    arcnum++;
    in.get();
    if (in.peek() == EOF) break;
  }
  in.close();
}

void Graph::Print_arces() {
  int i, j;
  for (i = 0; i < vexnum; i++) {
    for (j = 0; j < vexnum; j++) {
      cout << arces[i][j] << ' ';
    }
    cout << endl;
  }
}

void Graph::Dijkstra(int begin, int end, City *city) {
  int *S, *D, **P, i, j, min, k, w;
  S = new int[vexnum];
  D = new int[vexnum];
  P = new int *[vexnum];
  for (i = 0; i < vexnum; i++) P[i] = new int[vexnum];
  for (i = 0; i < vexnum; i++) {
    S[i] = 0;
    D[i] = arces[begin][i];
    if (D[i] != Infinity) {
      P[i][0] = begin;
      P[i][1] = i;
      P[i][2] = -1;
    }
  }  //初始化 S,D,P

  S[begin] = 1;
  D[begin] = 0;

  for (i = 1; i < vexnum; i++) {
    min = Infinity;
    for (j = 0; j < vexnum; j++)
      if (!S[j] && D[j] < min) {
        min = D[j];
        k = j;
      }
    S[k] = 1;

    for (j = 0; j < vexnum; j++) {
      if (!S[j] && D[k] + arces[k][j] < D[j]) {
        D[j] = D[k] + arces[k][j];
        for (w = 0; P[k][w] != -1; w++) P[j][w] = P[k][w];
        P[j][w] = j;
        P[j][w + 1] = -1;
      }
    }
  }

  cout << D[end] << ' ';
  cout << city[P[end][0]].name;
  for (i = 1; P[end][i] != -1; i++) cout << " -> " << city[P[end][i]].name;
  cout << endl;
}

#pragma endregion

void city_in(City *&, int &);

int main() {
  int num_city = 0;  //城市个数
  City *city;        //城市编号及名称
  city = new City[50];
  city_in(city, num_city);  //读取城市信息

  Graph G(num_city);
  G.Print_arces();

  int begin[3] = {2, 6, 13}, end[3] = {9, 15, 12};
  for (int i = 0; i < 3; i++) G.Dijkstra(begin[i], end[i], city);
}

void city_in(City *&city, int &num_city) {
  ifstream in;
  in.open("city.txt", ios::in);

  while (!in.eof()) {
    num_city++;
    in >> city[num_city - 1].num;
    in.get();
    in >> city[num_city - 1].name;
    in.get();
    if (in.peek() == EOF) break;
  }
  in.close();
}