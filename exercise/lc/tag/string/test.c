#include <stdio.h>
#include <string.h>

int main(void)
{
    char s[] = "abcd";

    printf("%s, %d\n", s, strlen(s));
    s[3] = '\0';
    printf("%s, %d\n", s, strlen(s));
}
