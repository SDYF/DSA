#include <iostream>
using namespace std;
namespace A
{
    int a = 100;
    namespace B //Ƕ��һ�������ռ�B
    {
        int a = 20;
    }
} // namespace A

int a = 200; //����һ��ȫ�ֱ���

int main(int argc, char *argv[])
{
    cout << "A::a =" << A::a << endl;
    cout << "A::B::a =" << A::B::a << endl;
    cout << "a =" << a << endl;
    cout << "::a =" << ::a << endl;

    int a = 30;
    cout << "a =" << a << endl;
    cout << "::a =" << ::a << endl;

    return 0;
}