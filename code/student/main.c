#include "stu_head.h"

int main()
{
	char choice;
	STU *head;
	while ((choice = menu()) != 'q') {
		switch(choice) {
			/*create the data, just for the first time*/
			case '1':
				head = mycreate();
				break;
			/*open the datafile and display it*/
			case '2':
				head = display();
				break;
			/*display the data in stack, need choose '2' first*/
			case '3':
				preview(head);
				break;
			/*add data to head*/
			case '4':
				head = add_stu(head);
				break;
			/*find a student by number*/
			case '5':
				find_stu(head);
				break;
			/*sort the data by number*/
			case '6':
				head = sort_stu(head);
				break;
			case '7':
				head = delete_stu(head);
				break;
			case '8':
				save(head);
				break;
			default:
				printf("wrong key\n");
				break;
		}
	}
	
	return 1;
}
