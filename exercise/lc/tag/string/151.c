#include <stdio.h>
#include <string.h>


void reverse_sub(char *s, int start, int end)
{
    char t;

    while (start < end)  {
        t = s[start];
        s[start] = s[end];
        s[end] = t;
        start++;
        end--;
    }
}

void str_strip(char *s, int len)
{
    int i = 0, start = 0, end = len-1;

    while (s[start] == ' ')
        start++;
    while (s[end] == ' ')
        end--;
    end = end-start;
    while (i <= end)
        s[i++] = s[start++];
    s[end+1] = '\0';
}

void word_strip(char *s, int len)
{
    int start  = 0, end  = 0, i = 0;
    
    while (end < len) {
        while (s[start] && s[start] != ' ')
            start++;
        start++;
        if (s[start] == ' ') {
            end  = start+1;
            while (s[end] && s[end] == ' ')
                end++;
            while (s[end] && s[end] != ' ') 
                s[start++] = s[end++];
            i = start;
            while(i < end)
                s[i++] = ' ';
        }
    }
    s[start] = '\0';
}

char *reverseWords(char *s)
{
    int start, end, len;

    len = strlen(s);
    if (len <=1)
        return s;

    //reverse the while string
    reverse_sub(s, 0, len-1);
    
    //reverse each word
    for (start = 0; start < len; start = end+1) {
        while (s[start] && s[start] == ' ') start++;
        
        end = start;
        while (s[end] && s[end] != ' ') end++;
        
        reverse_sub(s, start, end-1);
    }
    //drop space in head and tail
    str_strip(s, len);
    //drop space beside words
    word_strip(s, len);
    return s;
}

int main(void)
{
    //char s[] = "  hello    world!     dda    ";
    char s[] = "  hello    w b";

    printf("%s\n", s);
    reverseWords(s);
    printf("%s\n", s);
}
