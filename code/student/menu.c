int menu(void)
{
        char choice;
        printf("\n*************************************************\n");
        printf("\tS T U D E N T       M A N A N A G E\n\n");
        printf("\t\t1:create a list\n\n");
        printf("\t\t2:display the list\n\n");
        printf("\t\t3:preview the data\n\n");
        printf("\t\t4:add some student\n\n");
        printf("\t\t5:find a student\n\n");
        printf("\t\t6:sort the list by number\n\n");
        printf("\t\t7:delete some student\n\n");
        printf("\t\t8:save the data\n");
        printf("\n*************************************************\n");
        printf("your choice:");
        scanf(" %c", &choice); 
        return choice;  
}

