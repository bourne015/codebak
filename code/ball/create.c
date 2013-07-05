static int create(void)
{
	int i = 0, j = 0,k = 0, l = 0;
	int total, same_da = 0, same_sol = 0;

//	printf("input the times to create:");
//	scanf("%d", &total);

	for (; j < solves; j++) {
		for (;k < num-1; k++) {
			data[j][k] = rand()%33+1;
		}
		data[j][num] = rand()%16+1;
	}
	
	for (; l < solves1; l++) 
	for (j = l+1; j < solves1; j++) {
		for (k = 0; k < num-1; k++)
		for (i = 0; i < num-1; i++) {
			if (data[j][k] = data[l][i])
				if(++same_da >= 4)
					same_sol++;
		}
	}
}
