#include <stdio.h>
#include <string.h>

char char_repeat(char *s)
{
    int hash[256] = {0}, i, len;

    len = strlen(s);

    for (i = 0; i < len; i++)
            hash[s[i]]++;
    for (i = 0; i < len; i++)
        if (hash[s[i]] == 1)
            return s[i];
    return -1;
}

int main(void)
{
    char *s = "hhhabdbd", c;

    c = char_repeat(s);
    printf("%s \n %c\n", s, c);
}
