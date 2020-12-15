#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

struct ElemType {
  double coe;
  int exp;
};

struct LNode {
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
struct LNode *PolySub(struct LNode **L, struct LNode *L1, struct LNode *L2);
struct LNode *PolyMul(struct LNode **L, struct LNode *L1, struct LNode *L2);
int n_in();
struct LNode *PolyPower(struct LNode **L, struct LNode *L1, int n);
double double_in();
void PolyCalculate(struct LNode *L, double a);

int main() {
  char lab = '\0';
  int count = 0, lab_1 = 0, i = 0, n = 0, n1 = 0, n2 = 0;
  struct LNode *L[10], *s;
  int a[10];
  double a_;

  for (i = 0; i < 10; i++) a[i] = 0;
  a[0] = 1;

  L[0] = (struct LNode *)malloc(sizeof(struct LNode));
  L[0]->next = NULL;

  while (1) {
    Catalog();

    lab_1 = 0;
    lab = getchar();
    if (getchar() != '\n') {
      lab_1 = 1;
      while (getchar() != '\n') continue;
    }
    if (lab_1) {
      printf("错误输入！\n");
      continue;
    }

    switch (lab) {
      case '1':  //创建多项式
        CreatPoly(L, &count, a);
        break;

      case '2':  //打印多项式
        printf("请输入想打印的多项式(0~9)\n");
        n = Poly_in(a);
        PrintPoly(*(L + n));
        break;

      case '3':  //销毁多项式
        printf("请输入想销毁的多项式(0~9)\n");
        n = Poly_in(a);
        PolyDelete(*(L + n));
        count--;
        a[n] = 0;
        printf("第%d号多项式销毁成功\n\n", n);
        break;

      case '4':  //复制多项式
        printf("请输入被复制的多项式\n");
        n1 = Poly_in(a);
        printf("请输入目标多项式\n");
        n2 = PolyCopy_in(a);
        PolyCopy(L, n1, n2, a);
        if (!(a[n2])) {
          a[n2] = 1;
          count++;
        }

        printf("成功将第%d号多项式复制到第%d号多项式\n\n", n1, n2);
        break;

      case '5':  //多项式求和
        printf("请输入要求和的两个多项式:\n\n");
        // Sleep(1);
        printf("请输入第一个多项式\n");
        n1 = Poly_in(a);
        printf("请输入第二个多项式\n");
        n2 = Poly_in(a);
        PolyDelete(L[0]);
        L[0] = PolyAdd(L, *(L + n1), *(L + n2));
        PrintPoly(L[0]);
        break;
      case '6':
        printf("请输入要求差的两个多项式：\n\n");
        // Sleep(1);
        printf("请输入被减式式\n");
        n1 = Poly_in(a);
        printf("请输入减式\n");
        n2 = Poly_in(a);
        L[0] = PolySub(L, *(L + n1), *(L + n2));
        PrintPoly(L[0]);
        break;
      case '7':
        printf("请输入要求积的两个多项式：\n\n");
        // sleep(1);
        printf("请输入第一个多项式\n");
        n1 = Poly_in(a);
        printf("请输入第二个多项式\n");
        n2 = Poly_in(a);
        PolyDelete(*(L + 0));
        *(L + 0) = PolyMul(L, *(L + n1), *(L + n2));
        PrintPoly(*(L + 0));
        break;
      case '8':
        printf("请输入要求n次幂的多项式：\n\n");
        n1 = Poly_in(a);
        printf("请输入整数n (0<=n<=9):\n");
        n = n_in();
        *(L + 0) = PolyPower(L, *(L + n1), n);
        PrintPoly(*(L + 0));
        break;

      case '9':
        printf("请输入要计算的多项式：\n\n");
        n1 = Poly_in(a);
        printf("请输入实数a\n");
        a_ = double_in();
        PolyCalculate(*(L + n1), a_);
        break;
      case '0':
        printf("感谢使用本程序！\n");
        return 0;
        break;
      default:
        printf("错误输入！\n\n");
        break;
    }

    //    printf("\ncount=%d\n\n", count);
  }
}

void Catalog() {
  printf("请输入需要执行的项目(0~9)：\n");
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

void CreatPoly(struct LNode **L, int *count, int *a) {
  if ((*count) > 10) {
    printf("多项式储存空间已满！\n");
    return;
  }
  (*count)++;

  int i = 0;
  int j = 0;
  char n = '\0';

  for (i = 1; i < 10; i++)
    if (a[i] == 0) {
      a[i] = 1;
      break;
    }

  printf("请输入多项式的次数n，n大于0小于10\n");
  while (1) {
    n = getchar();
    if (n < '0' || n > '9') {
      printf("请重新输入！\n");
      while (getchar() != '\n') continue;
      continue;
    } else
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

  while (!c) {
    p = *(L + i);
    lab = 0;
    while ((p->next) != NULL) {
      q = p->next;
      p = p->next->next;
      free(q);
    }
    p = *(L + i);
    for (j = ((int)n - 48); j >= 0; j--) {
      c = scanf("%lf", &coep);
      if (!c) {
        printf("%d次项系数输入错误，请重新输入所有系数！\n", j);
        break;
      }
      if (!coep)
        continue;
      else {
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

  if (!lab) {
    p->next = (struct LNode *)malloc(sizeof(struct LNode));
    p = p->next;
    p->data.coe = 0;
    p->data.exp = 0;
    p->next = NULL;
  }

  printf("成功创建%d号多项式！\n\n", i);
  setbuf(stdin, NULL);
  return;
}

int Poly_in(int *a) {
  char lab = '\0';
  int lab_1;

  while (1) {
    lab_1 = 0;
    lab = getchar();
    if (getchar() != '\n') {
      lab_1 = 1;
      while (getchar() != '\n') continue;
    }
    if (lab_1 || lab < '0' || lab > '9') {
      printf("错误输入！\n");
      continue;
    }
    if (a[(int)lab - 48] == 0) {
      printf("该多项式未被创建，请重新输入\n");
      continue;
    }
    break;
  }

  setbuf(stdin, NULL);
  return ((int)lab - 48);
}

int PolyCopy_in(int *a) {
  char lab = '\0', lab_2 = '\0';
  int lab_1 = 0, lab_3 = 0, lab_4 = 1;

  while (1) {
    lab_1 = 0;
    lab_4 = 1;
    lab = getchar();
    if (getchar() != '\n') {
      lab_1 = 1;
      while (getchar() != '\n') continue;
    }
    if (lab_1 || lab < '0' || lab > '9') {
      printf("错误输入！\n");
      continue;
    }
    if (a[(int)lab - 48] == 1) {
      printf("该多项式已被创建，是否覆盖？(Y/N)\n");

      while (1) {
        lab_3 = 0;
        lab_2 = getchar();

        if (getchar() != '\n') {
          lab_3 = 1;
          while (getchar() != '\n') continue;
        }

        if (lab_3) {
          printf("错误输入！请输入Y/N\n");
          continue;
        } else if (lab_2 == 'Y' || lab_2 == 'y')
          break;
        else if (lab_2 == 'N' || lab_2 == 'n') {
          printf("请重新输入目标字符串\n");
          lab_4 = 0;
          break;
        } else {
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

int PrintPoly(struct LNode *L0) {
  struct LNode *p;
  p = L0;
  p = p->next;

  if ((p->data.exp) == 0) {
    printf("%lf\n\n", (p->data.coe));
    return (0);
  }
  while (p != NULL) {
    if (fabs(p->data.coe) > 1.0e-7) printf("%lf", (p->data.coe));

    //   printf("x^%d",p->data.exp);
    if ((p->data.exp) != 1)
      if ((p->data.exp) != 0)
        printf("x^%d", (p->data.exp));
      else
        printf("\n");
    else
      printf("x");

    if (((p->next) != NULL) && (p->next->data.coe > 1.0e-7)) printf("+");

    p = p->next;
  }
  printf("\n\n");
  return (0);
}

void PolyDelete(struct LNode *L0) {
  struct LNode *p, *q;
  p = L0;

  while ((p->next) != NULL) {
    q = p->next;
    p->next = p->next->next;
    free(q);
  }

  return;
}

void PolyCopy(struct LNode **L, int n1, int n2, int *a) {
  if (a[n2]) PolyDelete(*(L + n2));

  struct LNode *p, *q, *t;

  q = (struct LNode *)malloc(sizeof(struct LNode));
  *(L + n2) = q;
  p = *(L + n1);

  q->data.coe = p->data.coe;

  while ((p->next) != NULL) {
    q->next = (struct LNode *)malloc(sizeof(struct LNode));
    q->next->data.coe = p->next->data.coe;
    q->next->data.exp = p->next->data.exp;
    //   printf("%lf %d\n", q->next->data.coe, q->next->data.exp);
    q = q->next;
    p = p->next;
  }
  q->next = NULL;

  //  PrintPoly(*(L + n2));
  return;
}

struct LNode *PolyAdd(struct LNode **L, struct LNode *L1, struct LNode *L2) {
  struct LNode *p, *q, *s, *t;
  int lab = 0;

  //    PolyDelete(*(L + 0));
  s = (struct LNode *)malloc(sizeof(struct LNode));
  t = s;
  s->next = NULL;
  p = L1;
  q = L2;

  while ((p->next) != NULL && (q->next) != NULL) {
    if ((p->next->data.exp) > (q->next->data.exp)) {
      s->next = (struct LNode *)malloc(sizeof(struct LNode));
      s->next->data.exp = p->next->data.exp;
      s->next->data.coe = p->next->data.coe;
      s = s->next;
      p = p->next;
      lab = 1;
    } else if ((p->next->data.exp) < (q->next->data.exp)) {
      s->next = (struct LNode *)malloc(sizeof(struct LNode));
      s->next->data.exp = q->next->data.exp;
      s->next->data.coe = q->next->data.coe;
      s = s->next;
      q = q->next;
      lab = 1;
    } else if (fabs(q->next->data.coe + p->next->data.coe) > 1.0e-7) {
      s->next = (struct LNode *)malloc(sizeof(struct LNode));
      s->next->data.exp = q->next->data.exp;
      s->next->data.coe = q->next->data.coe + p->next->data.coe;
      s = s->next;
      q = q->next;
      p = p->next;
      lab = 1;
    } else {
      q = q->next;
      p = p->next;
    }
  }

  if (!lab) {
    s->next = (struct LNode *)malloc(sizeof(struct LNode));
    s->next->data.exp = 0;
    s->next->data.coe = 0;
    s = s->next;
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

struct LNode *PolySub(struct LNode **L, struct LNode *L1, struct LNode *L2) {
  struct LNode *p, *q, *t;
  p = (struct LNode *)malloc(sizeof(struct LNode));
  t = p;
  q = L2;
  p->data.coe = L2->data.coe;
  //  PrintPoly(L1);
  //  PrintPoly(L2);

  while ((q->next) != NULL) {
    p->next = (struct LNode *)malloc(sizeof(struct LNode));
    p->next->data.coe = -q->next->data.coe;
    //  printf("%f\n", p->next->data.coe);
    p->next->data.exp = q->next->data.exp;
    p = p->next;
    q = q->next;
  }
  p->next = NULL;

  // PrintPoly(t->next);
  printf("\n");
  t = PolyAdd(L, L1, t);

  return t;
}

struct LNode *PolyMul(struct LNode **L, struct LNode *L1, struct LNode *L2) {
  struct LNode *p, *q, *s, *t, *m;

  q = L2;
  t = (struct LNode *)malloc(sizeof(struct LNode));
  t->next = (struct LNode *)malloc(sizeof(struct LNode));
  t->next->data.coe = 0;
  t->next->data.exp = 0;
  t->next->next = NULL;

  s = (struct LNode *)malloc(sizeof(struct LNode));
  s->next = NULL;

  while ((q->next) != NULL) {
    PolyDelete(s);
    s = (struct LNode *)malloc(sizeof(struct LNode));
    m = s;
    s->next = NULL;
    p = L1;
    while ((p->next) != NULL) {
      s->next = (struct LNode *)malloc(sizeof(struct LNode));
      s->next->data.coe = (q->next->data.coe) * (p->next->data.coe);
      s->next->data.exp = (q->next->data.exp) + (p->next->data.exp);
      //     printf("%lf %d\n", s->next->data.coe, s->next->data.exp);
      s = s->next;
      p = p->next;
    }
    s->next = NULL;
    t = PolyAdd(L, m, t);
    q = q->next;
  }

  return (t);
}

int n_in() {
  char lab = '\0';
  int lab_1;

  while (1) {
    lab_1 = 0;
    lab = getchar();
    if (getchar() != '\n') {
      lab_1 = 1;
      while (getchar() != '\n') continue;
    }
    if (lab_1 || lab < '0' || lab > '9') {
      printf("错误输入！\n");
      continue;
    }
    break;
  }

  setbuf(stdin, NULL);
  return ((int)lab - 48);
}

struct LNode *PolyPower(struct LNode **L, struct LNode *L1, int n) {
  int i = 0;
  struct LNode *p;
  p = L1;

  for (i = 1; i < n; i++) {
    p = PolyMul(L, L1, p);
  }
  return (p);
}

double double_in() {
  double a;
  int b = 0;

  while (b == 0) {
    b = scanf("%lf", &a);
    if (!b) printf("错误输入，请重新输入实数a\n");
    setbuf(stdin, NULL);
  }
  return (a);
}

void PolyCalculate(struct LNode *L, double a) {
  struct LNode *p;
  p = L;
  double sum = 0;

  while ((p->next) != NULL) {
    sum += p->next->data.coe * pow(a, p->next->data.exp);
    p = p->next;
  }
  printf("在a=%lf处多项式的值为%lf\n", a, sum);
  return;
}