#include <iostream>
#include <string>

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

  bool operator<=(const tNode &P) { return this->weight <= P.weight; }
};

class queue {
 public:
  queue();
  void Initqueue(ch *, int);
  void Insert(tNode *);
  tNode *Pop();

 private:
  int length, front, rear;
  const int listsize = 128;
  tNode **elem;
};

queue::queue() { elem = new tNode *[listsize]; }

void queue::Initqueue(ch *char_count, int count) {
  for (int i = 0; i < count; i++) {
    tNode *NewNode = new tNode();
    NewNode->ch = (char)char_count->number;
    NewNode->Left = NewNode->Right = NULL;
    NewNode->weight = char_count->amount;
  }
}

int main() { return 0; }