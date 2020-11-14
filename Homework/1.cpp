#include <iostream>
#include <vector>
#include <cstdlib>
#include <string>
#include <stdexcept>

using namespace std;

template <class T>
class Stack
{
private:
    vector<T> elems; // 元素

public:
    void push(T const &); // 入栈
    void pop();           // 出栈
    T top() const;        // 返回栈顶元素
    bool empty() const
    { // 如果为空则返回真。
        return elems.empty();
    }
};

template <class T>
void Stack<T>::push(T const &elem)
{
    // 追加传入元素的副本
    elems.push_back(elem);
}

template <class T>
void Stack<T>::pop()
{
    if (elems.empty())
    {
        throw out_of_range("Stack<>::pop(): empty stack");
    }
    // 删除最后一个元素
    elems.pop_back();
}

template <class T>
T Stack<T>::top() const
{
    if (elems.empty())
    {
        throw out_of_range("Stack<>::top(): empty stack");
    }
    // 返回最后一个元素的副本
    return elems.back();
}

//typedef int ElemType;

typedef struct LNode
{
    /* data */
    int data;
    struct LNode *next;
} LNode, *LinkList;

int Change(Stack<int> &S, LNode *&L, LNode *&p);

int main()
{
    LNode *p, *q;
    LNode *L;

    p = new LNode;
    L = p;
    int i = 0;
    for (i = 0; i <= 10; i++)
    {
        p->data = i;

        if (i == 10)
            p->next = NULL;
        else
        {
            p->next = new LNode;
            //   cout << p->data << endl;
            p = p->next;
        }
    }

    Stack<int> S;

    //  cout << L->data << endl;
    p = L;
    q = new LNode;
    p = q;
    Change(S, L, q);

    while (p != NULL)
    {
        cout << (p->data) << endl;
        p = p->next;
    }
}

int Change(Stack<int> &S, LNode *&L, LNode *&p)
{
    if (L->next != NULL)
    {
        S.push(L->data);

        Change(S, L->next, p);
    }
    else
        S.push(L->data);

    //   L->data = S.top();

    p->data = S.top();
    S.pop();
    //    cout << p->data << endl;
    if (S.empty() == true)
        p->next = NULL;
    else
    {

        p->next = new LNode;
        p = p->next;
    }

    return 0;
}