/*
 *replace blank to %20
 请实现一个函数，将一个字符串中的每个空格替换成“%20”。
 例如，当字符串为We Are Happy.则经过替换之后的字符串为We%20Are%20Happy
 * */

#include <stdio.h>
#include <string.h>

void replace_blank(char *a, int length)
{
    int blanklen = 0, origlen = 0, newlen;
    int indexorig, indexnew;
    int i = 0;
    
    if (a == NULL || length <= 0)
        return;
    while (a[i] != '\0') {
        origlen++;
        if (a[i] == ' ')
            blanklen++;
        i++;
    }
    //printf("bl:%d\n", blanklen);
    newlen = origlen + blanklen*2;
    if (newlen > length)
        return;
    indexorig = origlen;
    indexnew = newlen;

    while (indexorig >= 0 && indexnew > indexorig) {
        if (a[indexorig] == ' ') {
            a[indexnew--] = '0';
            a[indexnew--] = '2';
            a[indexnew--] = '%';
        } else {
            a[indexnew--] = a[indexorig];
        }
        indexorig--;
    }
    
}

int main(int argc, char **argv)
{
    char *b = "we are happy";
    char a[100];

    strcpy(a, b);
    printf("orig: %s\n", a);
    replace_blank(a, sizeof(a));
    printf("new: %s\n", a);
    return 0;
}
