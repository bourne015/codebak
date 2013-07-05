# include <stdio.h>

struct student
{
int age;
float score;
char sex;

};
int main(void)
{
struct student st = {80,66.6,'F'};
struct student *pst = &st;

pst->age = 90;
//st.age = 66.6;
printf("%d %f\n",st.age,pst->score);

return 0;
} 
