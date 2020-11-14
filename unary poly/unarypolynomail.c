#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>

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
int PrintPoly(struct LNode *L0);
struct LNode *PolyAdd(struct LNode **L, struct LNode *L1, struct LNode *L2);
void PolyDelete(struct LNode *L0);
void PolyCopy(struct LNode **L, int n1, int n2, int *a);
int PolyCopy_in(int *a);
void PolySub(struct LNode **L, struct LNode *L1, struct LNode *L2);
struct LNode *PolyMul(struct LNode **L, struct LNode *L1, struct LNode *L2);
int n_in();
struct LNode *PolyPower(struct LNode **L, struct LNode *L1, int n);
double double_in();
void PolyCalculate(struct LNode *L, double a);

int main()
{

    char lab = '\0';
    int count = 0, lab_1 = 0, i = 0, n = 0, n1 = 0, n2 = 0;
    struct LNode *L[10], *s;
    int a[10];
    double a_;

    for (i = 0; i < 10; i++)
        a[i] = 0;
    a[0] = 1;

    L[0] = (struct LNode *)malloc(sizeof(struct LNode));
    L[0]->next = NULL;

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
            printf("�������룡\n");
            continue;
        }

        switch (lab)
        {
        case '1': //��������ʽ
            CreatPoly(L, &count, a);
            break;

        case '2': //��ӡ����ʽ
            printf("���������ӡ�Ķ���ʽ(0~9)\n");
            n = Poly_in(a);
            PrintPoly(*(L + n));
            break;

        case '3': //���ٶ���ʽ
            printf("�����������ٵĶ���ʽ(0~9)\n");
            n = Poly_in(a);
            PolyDelete(*(L + n));
            count--;
            a[n] = 0;
            printf("��%d�Ŷ���ʽ���ٳɹ�\n\n", n);
            break;

        case '4': //���ƶ���ʽ
            printf("�����뱻���ƵĶ���ʽ\n");
            n1 = Poly_in(a);
            printf("������Ŀ�����ʽ\n");
            n2 = PolyCopy_in(a);
            PolyCopy(L, n1, n2, a);
            if (!(a[n2]))
            {
                a[n2] = 1;
                count++;
            }

            printf("�ɹ�����%d�Ŷ���ʽ���Ƶ���%d�Ŷ���ʽ\n\n", n1, n2);
            break;

        case '5': //����ʽ���
            printf("������Ҫ��͵���������ʽ:\n\n");
            // Sleep(1);
            printf("�������һ������ʽ\n");
            n1 = Poly_in(a);
            printf("������ڶ�������ʽ\n");
            n2 = Poly_in(a);
            PolyDelete(L[0]);
            L[0] = PolyAdd(L, *(L + n1), *(L + n2));
            PrintPoly(L[0]);
            break;
        case '6':
            printf("������Ҫ������������ʽ��\n\n");
            //Sleep(1);
            printf("�����뱻��ʽʽ\n");
            n1 = Poly_in(a);
            printf("�������ʽ\n");
            n2 = Poly_in(a);
            PolySub(L, *(L + n1), *(L + n2));
            break;
        case '7':
            printf("������Ҫ�������������ʽ��\n\n");
            // sleep(1);
            printf("�������һ������ʽ\n");
            n1 = Poly_in(a);
            printf("������ڶ�������ʽ\n");
            n2 = Poly_in(a);
            PolyDelete(*(L + 0));
            *(L + 0) = PolyMul(L, *(L + n1), *(L + n2));
            PrintPoly(*(L + 0));
            break;
        case '8':
            printf("������Ҫ��n���ݵĶ���ʽ��\n\n");
            n1 = Poly_in(a);
            printf("����������n (0<=n<=9):\n");
            n = n_in();
            *(L + 0) = PolyPower(L, *(L + n1), n);
            PrintPoly(*(L + 0));
            break;

        case '9':
            printf("������Ҫ����Ķ���ʽ��\n\n");
            n1 = Poly_in(a);
            printf("������ʵ��a");
            a_ = double_in();
            PolyCalculate(*(L + n1), a_);
            break;
        case '0':
            printf("��лʹ�ñ�����\n");
            return 0;
            break;
        default:
            printf("�������룡\n\n");
            break;
        }

        //    printf("\ncount=%d\n\n", count);
    }
}

void Catalog()
{
    printf("��������Ҫִ�е���Ŀ(1~)��\n");
    printf("1.��������ʽ        2.��ӡ��ʾ����ʽ\n");
    printf("3.���ٶ���ʽ        4.���ƶ���ʽ\n");
    printf("5.����������ʽ�ĺ�        6.����������ʽ�Ĳ�\n");
    printf("7.����������ʽ�Ļ�        8.��һ������ʽ��n����\n");
    printf("9.����һ������ʽ��x=a����ֵ\n");
    printf("0.�˳�����\n");
    printf("ע��0�Ŷ���ʽΪ�ϴμ�����\n\n");

    //�ȴ�������ӣ�
    return;
}

void CreatPoly(struct LNode **L, int *count, int *a)
{
    if ((*count) > 10)
    {
        printf("����ʽ����ռ�������\n");
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

    printf("���������ʽ�Ĵ���n��n����0С��10\n");
    while (1)
    {
        n = getchar();
        if (n < '0' || n > '9')
        {
            printf("���������룡\n");
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
    printf("��Ӹߴε��ʹ������������ʽ��ϵ�����Կո�ֿ����س�����\n");

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
                printf("%d����ϵ�����������������������ϵ����\n", j);
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

        //    if ((c=scanf("%d"))) { printf("����ϵ�����࣬���������룡"); c=0;}

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

    printf("�ɹ�����%d�Ŷ���ʽ��\n\n", i);
    setbuf(stdin, NULL);
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
            printf("�������룡\n");
            continue;
        }
        if (a[(int)lab - 48] == 0)
        {
            printf("�ö���ʽδ������������������\n");
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
            printf("�������룡\n");
            continue;
        }
        if (a[(int)lab - 48] == 1)
        {
            printf("�ö���ʽ�ѱ��������Ƿ񸲸ǣ�(Y/N)\n");

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
                    printf("�������룡������Y/N\n");
                    continue;
                }
                else if (lab_2 == 'Y' || lab_2 == 'y')
                    break;
                else if (lab_2 == 'N' || lab_2 == 'n')
                {
                    printf("����������Ŀ���ַ���\n");
                    lab_4 = 0;
                    break;
                }
                else
                {
                    printf("�������룡������Y/N\n");
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

int PrintPoly(struct LNode *L0)
{
    struct LNode *p;
    p = L0;
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

void PolyDelete(struct LNode *L0)
{
    struct LNode *p, *q;
    p = L0;

    while ((p->next) != NULL)
    {
        q = p->next;
        p->next = p->next->next;
        free(q);
    }

    return;
}

void PolyCopy(struct LNode **L, int n1, int n2, int *a)
{
    if (a[n2])
        PolyDelete(*(L + n2));

    struct LNode *p, *q;
    p = *(L + n1);
    q = *(L + n2);

    while ((p->next) != NULL)
    {
        q->next = (struct LNode *)malloc(sizeof(struct LNode));
        q->next->data = p->next->data;
        q = q->next;
        p = p->next;
    }
    q->next = NULL;
    return;
}

struct LNode *PolyAdd(struct LNode **L, struct LNode *L1, struct LNode *L2)
{
    struct LNode *p, *q, *s, *t;

    //    PolyDelete(*(L + 0));
    s = (struct LNode *)malloc(sizeof(struct LNode));
    t = s;
    s->next = NULL;
    p = L1;
    q = L2;

    while ((p->next) != NULL && (q->next) != NULL)
    {
        if ((p->next->data.exp) > (q->next->data.exp))
        {
            s->next = (struct LNode *)malloc(sizeof(struct LNode));
            s->next->data.exp = p->next->data.exp;
            s->next->data.coe = p->next->data.coe;
            s = s->next;
            p = p->next;
        }
        else if ((p->next->data.exp) < (q->next->data.exp))
        {
            s->next = (struct LNode *)malloc(sizeof(struct LNode));
            s->next->data.exp = q->next->data.exp;
            s->next->data.coe = q->next->data.coe;
            s = s->next;
            q = q->next;
        }
        else
        {
            s->next = (struct LNode *)malloc(sizeof(struct LNode));
            s->next->data.exp = q->next->data.exp;
            s->next->data.coe = q->next->data.coe + p->next->data.coe;
            s = s->next;
            q = q->next;
            p = p->next;
        }
    }

    if ((p->next) == NULL)
        if ((q->next) == NULL)
            s->next = NULL;
        else
            s->next = q->next;
    else
        s->next = p->next;

    return (t);
}

void PolySub(struct LNode **L, struct LNode *L1, struct LNode *L2)
{
    struct LNode *p, *q;
    q = L2;
    p->data.coe = L2->data.coe;

    while ((q->next) != NULL)
    {
        p->next = (struct LNode *)malloc(sizeof(struct LNode));
        p->next->data.coe = -q->next->data.coe;
        p->next->data.exp = q->next->data.exp;
        p = p->next;
        q = q->next;
    }
    p->next = NULL;
    PolyAdd(L, L1, p);

    return;
}

struct LNode *PolyMul(struct LNode **L, struct LNode *L1, struct LNode *L2)
{
    struct LNode *p, *q, *s, *t;

    p = L1;
    q = L2;
    s->next = NULL;
    t->next = NULL;
    while ((q->next) != NULL)
    {
        PolyDelete(s);
        while ((p->next) != NULL)
        {
            s->next = (struct LNode *)malloc(sizeof(struct LNode));
            s->next->data.coe = (q->next->data.coe) * (p->next->data.coe);
            s->next->data.exp = (q->next->data.exp) + (p->next->data.exp);
            s = s->next;
            p = p->next;
        }
        s->next = NULL;
        t = PolyAdd(L, s, t);
        q = q->next;
    }

    return (t);
}

int n_in()
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
            printf("�������룡\n");
            continue;
        }
        break;
    }

    setbuf(stdin, NULL);
    return ((int)lab - 48);
}

struct LNode *PolyPower(struct LNode **L, struct LNode *L1, int n)
{
    int i = 0;
    struct LNode *p;
    p = L1;

    for (i = 1; i < n; i++)
    {
        p = PolyMul(L, L1, p);
    }
    return (p);
}

double double_in()
{
    double a;
    int b = 0;

    while (b == 0)
    {
        b = scanf("%lf", &a);
        if (!b)
            printf("�������룬����������ʵ��a\n");
        setbuf(stdin, NULL);
    }
    return (a);
}
void PolyCalculate(struct LNode *L, double a)
{
    struct LNode *p;
    p = L;
    double sum = 0;

    while ((p->next) != NULL)
    {
        sum += p->next->data.coe * pow(a, p->next->data.exp);
        p = p->next;
    }
    printf("��a=%d������ʽ��ֵΪ%lf\n", a, sum);
    return;
}