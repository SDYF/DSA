#include <fstream>
#include <iostream>
#include <string>

using namespace std;

struct ch {
  int number;  //字符ASCLL码
  int amount;  //字符总数
};

struct tNode {
  char ch;
  int weight;
  tNode *Left, *Right;

  tNode() {
    Left = NULL;
    Right = NULL;
  }

  tNode(const tNode &P) {
    ch = P.ch;
    weight = P.weight;
    if (P.Left == NULL)
      Left = NULL;
    else {
      Left = new tNode();
      *Left = *(P.Left);
    }

    if (P.Right == NULL)
      Right = NULL;
    else {
      Right = new tNode();
      *Right = *(P.Right);
    }
  }

  bool operator<=(const tNode &P) { return this->weight <= P.weight; }
};

#pragma region queue
//储存结点的队列
class queue {
 public:
  queue();
  void Init(ch *, int);
  void Insert(tNode *);
  int getsize();
  void queue_print();
  tNode *Pop();

 private:
  int front, rear, size;
  const int listsize = 128;
  tNode **elem;
};

queue::queue() { cout << "Succeed!" << endl; }

void queue::Init(ch *char_count, int count) {
  elem = new tNode *[listsize];
  front = 0;
  rear = count - 1;
  size = count;
  tNode *NewNode;
  for (int i = 0; i < count; i++) {
    NewNode = new tNode();
    NewNode->ch = (char)char_count[i].number;
    NewNode->Left = NewNode->Right = NULL;
    NewNode->weight = char_count[i].amount;
    elem[i] = NewNode;
  }
}

void queue::Insert(tNode *Node) {
  int lab = 0;
  for (int i = front; i <= rear; i++) {
    if (elem[i]->weight <= Node->weight)
      elem[i - 1] = elem[i];
    else {
      elem[i - 1] = Node;
      front -= 1;
      size += 1;
      lab = 1;
      break;
    }
  }
  if (!lab) {
    front -= 1;
    size += 1;
    elem[rear] = Node;
  }
  // this->queue_print();
}

tNode *queue::Pop() {
  front += 1;
  size -= 1;
  return (elem[front - 1]);
}

int queue::getsize() { return size; }

void queue::queue_print() {
  cout << front << ' ' << rear << ' ' << size << endl;
  for (int i = front; i <= rear; i++) {
    cout << elem[i]->ch << ' ' << elem[i]->weight << endl;
  }
  cout << endl << endl;
}

#pragma endregion

#pragma region Huffman
// Huffman树实现
class Huffman {
 public:
  Huffman();
  //~Huffman();

  //接口函数

  void BulidTree(queue);  //构建Huffman树
  void BuildList();       //构建编码表
  void DisList();         //输出编码表
  void PrintTree();
  bool IsLeaf(tNode *);       //判断是否为叶子结点
  string Compress(string);    //文件压缩
  string Decompress(string);  //文件解压

 private:
  void BuildList(tNode *, string);
  string *List;  //编码表；
  tNode *Root;   //根节点
};

Huffman::Huffman() {
  List = new string[128];
  cout << "Huffman Succeed!" << endl;
}

void Huffman::BulidTree(queue Q) {
  tNode *x, *y, *Parent;
  while (Q.getsize() > 1) {
    x = Q.Pop();
    y = Q.Pop();
    Parent = new tNode();
    Parent->ch = '\0';
    Parent->Left = x;
    Parent->Right = y;
    Parent->weight = x->weight + y->weight;
    Q.Insert(Parent);
    Q.getsize();
  }
  Root = new tNode();
  Root = Q.Pop();
}

void Huffman::BuildList() {
  if (Root != NULL) BuildList(Root, "");
}

void Huffman::BuildList(tNode *Node, string s) {
  if (IsLeaf(Node)) {
    List[(int)(Node->ch)] = s;
    return;
  }
  BuildList(Node->Left, s + '0');
  BuildList(Node->Right, s + '1');
}

string Huffman::Compress(string txt) {
  string Comp;
  for (int i = 0; i < txt.length(); i++) {
    Comp += List[txt[i]];
  }
  return Comp;
}

string Huffman::Decompress(string txt) {
  string Deco;
  tNode *Node;
  for (int i = 0; i < txt.length();) {
    Node = Root;

    while (!IsLeaf(Node)) {
      if (txt[i] == '0')
        Node = Node->Left;
      else
        Node = Node->Right;
      i++;
    }

    Deco += Node->ch;
  }
  return Deco;
}

void Huffman::DisList() {
  for (int i = 0; i < 128; i++)
    if (List[i] != "") cout << (char)i << ' ' << List[i] << endl;
  cout << endl;
}

bool Huffman::IsLeaf(tNode *Node) {
  if ((Node->Left == NULL) && (Node->Right == NULL))
    return true;
  else
    return false;
}

void Huffman::PrintTree() {}

#pragma endregion

/*函数声明*/
void read(ch *&, int &, string &);
void sort(ch *&, int);
void print(string);

/*主函数*/
int main() {
  ch *char_count;
  char_count = new ch[128];
  int count = 0, i;
  string txt;                    // stdio.h文件
  read(char_count, count, txt);  //读取stdio.h
  sort(char_count, count);       //对字符进行排序

  queue Q;
  Q.Init(char_count, count);
  Q.queue_print();

  Huffman H;
  string Comp, Deco;
  H.BulidTree(Q);
  H.BuildList();
  H.DisList();
  Comp = H.Compress(txt);
  Deco = H.Decompress(Comp);

  print(Deco);

  // cout << count;
  /*for (i = 0; i < count; i++)
    cout << (char)char_count[i].number << ' ' << char_count[i].amount << endl;
   cout << txt;*/
}

void read(ch *&char_count, int &count, string &txt) {
  //文件读取
  ifstream in;
  in.open("stdio.h", ios::in);

  long a[128];
  char c;
  int i;

  for (i = 0; i < 128; i++) a[i] = 0;
  while ((c = in.get()) != EOF) {
    a[(int)c]++;
    txt += c;
  }

  for (i = 0; i < 128; i++)
    if (a[i] != 0) {
      char_count[count].amount = a[i];
      char_count[count].number = i;
      count++;
    }
  in.close();
  //读取结束
}

void sort(ch *&char_count, int count) {
  ch t;
  int i = 0, j = 0;
  for (i = 0; i < count + 1; i++)
    for (j = i + 1; j < count; j++)
      if (char_count[i].amount > char_count[j].amount) {
        t = char_count[i];
        char_count[i] = char_count[j];
        char_count[j] = t;
      }
  return;
}

void print(string txt) {
  ofstream out;
  out.open("stdio1.txt", ios::out);
  out << txt;
}
