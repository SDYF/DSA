#include <stdio.h>
#include <stdlib.h>

struct ElemType
{
    double coe;
    int exp;
};

struct LNode
{
    struct ElemType data;
    struct LNode *next;
};

void Catalog();
void CreatPoly(struct LNode **L, int *count, int *a);
int Poly_in(int *a);
int PrintPoly(struct LNode **L, int i);
int PolyAdd(struct LNode **L);
void PolyDelete(struct LNode **L, int i, int *a, int *count);
void PolyCopy(struct LNode **L, int n1, int n2, int *a, int *count);
int PolyCopy_in(int *a);

int main()
{

    char lab = '\0';
    int count = 0, lab_1 = 0, i = 0, n = 0, n1 = 0, n2 = 0;
    struct LNode *L[10];
    int a[10];

    for (i = 0; i < 10; i++)
        a[i] = 0;

    while (1)
    {
        Catalog();

        lab_1 = 0;
        lab = getchar();
        if (getchar() != '\n')
        {
            lab_1 = 1;
            while (getchar() != '\n')
                continue;
        }
        if (lab_1)
        {
            printf("错误输入！\n");
            continue;
        }

        switch (lab)
        {
        case '1': //创建多项式
            CreatPoly(L, &count, a);
            break;

        case '2': //打印多项式
            printf("请输入想打印的多项式(0~9)\n");
            n = Poly_in(a);
            PrintPoly(L, n);
            break;

        case '3': //销毁多项式
            printf("请输入想销毁的多项式(0~9)\n");
            n = Poly_in(a);
            PolyDelete(L, n, a, &count);
            break;

        case '4': //复制多项式
            printf("请输入被复制的多项式\n");
            n1 = Poly_in(a);
            printf("请输入目标多项式\n");
            n2 = PolyCopy_in(a);
            PolyCopy(L, n1, n2, a, &count);

        default:
            printf("错误输入！\n\n");
            break;
        }

        printf("\ncount=%d\n\n", count);
    }
}

void Catalog()
{
    printf("请输入需要执行的项目(1~)：\n");
    printf("1.创建多项式        2.打印显示多项式\n");
    printf("3.销毁多项式        4.复制多项式\n");
    printf("5.求两个多项式的和        6.求两个多项式的差\n");
    printf("7.求两个多项式的积        8.求一个多项式的n次幂\n");
    printf("9.计算一个多项式在x=a处的值\n");
    printf("0.退出程序\n");
    printf("注：0号多项式为上次计算结果\n\n");

    //等待后续添加；
    return;
}

void CreatPoly(struct LNode **L, int *count, int *a)
{
    if ((*count) > 10)
    {
        printf("多项式储存空间已满！\n");
        return;
    }
    (*count)++;

    int i = 0;
    int j = 0;
    char n = '\0';

    for (i = 1; i < 10; i++)
        if (a[i] == 0)
        {
            a[i] = 1;
            break;
        }

    printf("请输入多项式的次数n，n大于0小于10\n");
    while (1)
    {
        n = getchar();
        if (n < '0' || n > '9')
        {
            printf("请重新输入！\n");
            while (getchar() != '\n')
                continue;
            continue;
        }
        else
            break;
    }

    *(L + i) = (struct LNode *)malloc(sizeof(struct LNode));

    (*(L + i))->data.coe = (int)n - 48;
    struct LNode *p, *q;
    int c = 0;
    double coep = 0.0;
    int lab = 0;
    q = (struct LNode *)malloc(sizeof(struct LNode));
    printf("请从高次到低次依次输入多项式的系数，以空格分开，回车结束\n");

    p = *(L + i);
    p->next = NULL;

    while (!c)
    {
        p = *(L + i);
        lab = 0;
        while ((p->next) != NULL)
        {
            q = p->next;
            p = p->next->next;
            free(q);
        }
        p = *(L + i);
        for (j = ((int)n - 48); j >= 0; j--)
        {
            c = scanf("%lf", &coep);
            if (!c)
            {
                printf("%d次项系数输入错误，请重新输入所有系数！\n", j);
                break;
            }
            if (!coep)
                continue;
            else
            {
                p->next = (struct LNode *)malloc(sizeof(struct LNode));
                p = p->next;
                p->data.coe = coep;
                p->data.exp = j;
                p->next = NULL;
                lab = 1;
            }
        }

        //    if ((c=scanf("%d"))) { printf("输入系数过多，请重新输入！"); c=0;}

        setbuf(stdin, NULL);
    }

    if (!lab)
    {
        p->next = (struct LNode *)malloc(sizeof(struct LNode));
        p = p->next;
        p->data.coe = 0;
        p->data.exp = 0;
        p->next = NULL;
    }

    printf("成功创建%d号多项式！\n\n", i);
    //    setbuf(stdin,NULL);
    return;
}

int Poly_in(int *a)
{

    char lab = '\0';
    int lab_1;

    while (1)
    {

        lab_1 = 0;
        lab = getchar();
        if (getchar() != '\n')
        {
            lab_1 = 1;
            while (getchar() != '\n')
                continue;
        }
        if (lab_1 || lab < '0' || lab > '9')
        {
            printf("错误输入！\n");
            continue;
        }
        if (a[(int)lab - 48] == 0)
        {
            printf("该多项式未被创建，请重新输入");
            continue;
        }
        break;
    }

    setbuf(stdin, NULL);
    return ((int)lab - 48);
}

int PolyCopy_in(int *a)
{

    char lab = '\0', lab_2 = '\0';
    int lab_1 = 0, lab_3 = 0, lab_4 = 1;

    while (1)
    {

        lab_1 = 0;
        lab_4 = 1;
        lab = getchar();
        if (getchar() != '\n')
        {
            lab_1 = 1;
            while (getchar() != '\n')
                continue;
        }
        if (lab_1 || lab < '0' || lab > '9')
        {
            printf("错误输入！\n");
            continue;
        }
        if (a[(int)lab - 48] == 1)
        {
            printf("该多项式已被创建，是否覆盖？(Y/N)\n");

            while (1)
            {
                lab_3 = 0;
                lab_2 = getchar();

                if (getchar() != '\n')
                {
                    lab_3 = 1;
                    while (getchar() != '\n')
                        continue;
                }

                if (lab_3)
                {
                    printf("错误输入！请输入Y/N\n");
                    continue;
                }
                else if (lab_2 == 'Y' || lab_2 == 'y')
                    break;
                else if (lab_2 == 'N' || lab_2 == 'n')
                {
                    printf("请重新输入目标字符串\n");
                    lab_4 = 0;
                    break;
                }
                else
                {
                    printf("错误输入！请输入Y/N\n");
                    continue;
                }
            }
        }
        if (lab_4)
            break;
        else
            continue;
    }

    setbuf(stdin, NULL);
    return ((int)lab - 48);
}

int PrintPoly(struct LNode **L, int i)
{
    struct LNode *p;
    p = *(L + i);
    p = p->next;

    if ((p->data.exp) == 0)
    {
        printf("%lf\n\n", (p->data.coe));
        return (0);
    }
    while (p != NULL)
    {
        printf("%lf", (p->data.coe));

        //   printf("x^%d",p->data.exp);
        if ((p->data.exp) != 1)
            if ((p->data.exp) != 0)
                printf("x^%d", (p->data.exp));
            else
                printf("\n");
        else
            printf("x");

        if ((p->next) != NULL)
            printf("+");

        p = p->next;
    }
    printf("\n");
    return (0);
}

void PolyDelete(struct LNode **L, int i, int *a, int *count)
{
    struct LNode *p, *q;
    p = *(L + i);

    *count--;
    a[i] = 0;

    while ((p->next) != NULL)
    {
        q = p->next;
        p->next = p->next->next;
        free(q);
    }

    printf("第%d号多项式销毁成功\n\n", i);
    return;
}

void PolyCopy(struct LNode **L, int n1, int n2, int *a, int *count)
{
}