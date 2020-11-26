#include <stdio.h>

struct stack
{
    int dat[100];
    int p;
};

struct stack st0;
struct stack st1;
struct stack st2;

void tmppush(struct stack *st, int a)
{
    st->dat[st->p] = a;
    st->p++;
}

int tmppop(struct stack *st)
{
    (st->p)--;
    return st->dat[st->p];
}

void inqueue(int a)
{
    tmppush(&st1, a);
}

int dequeue(void)
{
    if (st2.p == 0) {
        while (st1.p > 0) {
            tmppush(&st2, tmppop(&st1));
        }
    }
    return tmppop(&st2);
}
int main(void)
{
    st0.p = 0;
    st1.p = 0;
    st2.p = 0;
    tmppush(&st0, 1);
    tmppush(&st0, 2);
    tmppush(&st0, 3);
    tmppush(&st0, 4);
    printf("%d\n", tmppop(&st0));
    printf("%d\n", tmppop(&st0));
    printf("%d\n", tmppop(&st0));
    printf("%d\n", tmppop(&st0));
    inqueue(1);
    inqueue(2);
    inqueue(3);
    inqueue(4);
    inqueue(5);
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
    printf("%d\n", dequeue());
}
