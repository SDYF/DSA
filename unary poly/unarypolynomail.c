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
            PrintPoly(L, n);
            break;

        case '3': //���ٶ���ʽ
            printf("�����������ٵĶ���ʽ(0~9)\n");
            n = Poly_in(a);
            PolyDelete(L, n, a, &count);
            break;

        case '4': //���ƶ���ʽ
            printf("�����뱻���ƵĶ���ʽ\n");
            n1 = Poly_in(a);
            printf("������Ŀ�����ʽ\n");
            n2 = PolyCopy_in(a);
            PolyCopy(L, n1, n2, a, &count);

        default:
            printf("�������룡\n\n");
            break;
        }

        printf("\ncount=%d\n\n", count);
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
            printf("�������룡\n");
            continue;
        }
        if (a[(int)lab - 48] == 0)
        {
            printf("�ö���ʽδ������������������");
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

    printf("��%d�Ŷ���ʽ���ٳɹ�\n\n", i);
    return;
}

void PolyCopy(struct LNode **L, int n1, int n2, int *a, int *count)
{
}