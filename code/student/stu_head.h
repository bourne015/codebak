#include <stdio.h>
#include <stdlib.h>
        
//int n = 0;
typedef struct student {
        int num;
        char name[10];
        int score;      
        struct student *next;
} STU; 

STU *mycreate(void);
STU *display(void);
void preview(STU *);
STU *add_stu(STU *);
void find_stu(STU *);
STU *sor_stu(STU *);
STU *delete_stu(STU *);
int save(STU *);
