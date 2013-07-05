#include <stdio.h> 
#include <stdlib.h> 
#include <time.h> 
//#include <conio.h> 
int r,p,q=0,score=0;
int speed; 
int  b[20][10]; 
int  block[7][3][2] 
={{-1,0,0,-1,1,-1}, 
{-1,-1,0,-1,1,0}, 
{-1,0,-1,1,1,0}, 
{-1,-1,-1,0,1,0}, 
{0,-1,1,0,1,-1}, 
{-2,0,-1,0,1,0}, 
{0,-1,0,1,-1,0}}; 
void Display(void); 
void BlockRandom(void); 
void GotoXY(int x, int y); 
void FillBlock(void); 
void CleanBlock(void); 
void MoveLeft(void); 
void MoveRight(void); 
void MoveDown(void); 
void FastDown(void); 
void End(void); 
void CheckBlock(void); 
void CheckLine(void); 
void CleanLine(int); 
void ChangeBlock(void); 
void Swap(int &, int &); 
void Welcome(void); 
void Pause(void); 
int main(void)
{ 
	int i,j,k; 
	char c; 
	p=1; 
	for(i=0;i<20;i++) 
	for(j=0;j<10;j++) 
	b[i][j]=0; 
	BlockRandom(); 
	Welcome(); 
	Display(); 
	while(1) 
	{ 
		for(k=0;k<20;k++) 
		{ 
			if(kbhit()) 
			{
				c=getch(); 
				switch(c) 
				{
				case 'a':case '4':MoveLeft();break; 
				case 'd':case '6':MoveRight();break; 
				case 'w':case '8':CleanBlock();ChangeBlock();Display();break; 
				case 's':case '5':FastDown();break; 
				case 'x':case '2':MoveDown();break; 
				case 'p':Pause();break; 
				case 'q':{
						GotoXY(1,24);
						printf("Sorry,Game Over!"); 
						GotoXY(1,25);
						printf("Press any key to ESC..."); 
						getch(); 
						exit(1);
						 };break; 
				}
			} 

			_sleep(25);
		} 
	MoveDown(); 
	} 


return 0;
} 
void Display() 
{
	int i,j; 
	FillBlock(); 
	GotoXY(1,1); 
	for(i=0;i<20;i++) 
	{
		printf("■"); 
		for(j=0;j<10;j++) 
		{
			switch(b[i][j]) 
			{
			case 0:printf("  ");break; 
			case 1:printf("□");break; 
			case 2:printf("■");break;
		}
	} 
			printf("■\n");} 
			for(i=0;i<12;i++) 
			printf("■"); 
			GotoXY(1,22);
			printf("SCORE:%d",score); 
			GotoXY(1,23);
			printf("LEVEL=%d",score/100); 
} 
typedef struct
{
	int X;
	int Y;
}COORD;
void GotoXY(int x, int y)
 {  
	COORD c;  
	c.X = x-1;  
	c.Y = y-1;  
}  
void BlockRandom() 
{ 
	srand((unsigned)time(NULL));  
	int k,rr,i; 
	k=rand()%7;
	rr=rand()%4; 
	r=k; 
	for (i=0;i<=rr;i++) 
	ChangeBlock(); 
} 
void FillBlock() 
{
	int i,x,y; 
	for(i=0;i<3;i++) 
	{
		x=block[r][i][0]; 
		y=block[r][i][1]; 
		if(b[x+p][5+y+q]!=2) 
			b[x+p][5+y+q]=1; 
		else End(); 
		if(5+y+q>9) 
			MoveLeft(); 
		if(5+y+q<0) 
			MoveRight(); 
	} 
	if(b[p][5+q]!=2) 
	b[p][5+q]=1;
	else End(); 
} 
void CleanBlock(void) 
{
	int i,x,y; 
	for(i=0;i<3;i++) 
	{
		x=block[r][i][0]; 
		y=block[r][i][1]; 
		b[x+p][5+y+q]=0; 
	} 
b[p][5+q]=0; 
} 
void MoveLeft(void) //左移
{
	if(p==0) return; 
	int i,x,y; 
	for(i=0;i<20;i++) 
	if(b[i][0]==1) return; 
	for(i=0;i<3;i++) 
	{
		x=block[r][i][0]; 
		y=block[r][i][1]; 
		if(b[x+p][4+y+q]==2) 
			return;
	} 
		CleanBlock(); 
		q--; 
		FillBlock(); 


		Display(); 
} 

void MoveRight(void) //右移
{
	if(p==0) return; 
	int i,x,y; 
	for(i=0;i<20;i++) 
	if(b[i][9]==1) return; 
	for(i=0;i<3;i++) 
	{
		x=block[r][i][0]; 
		y=block[r][i][1]; 
		if(b[x+p][6+y+q]==2) 
			return;
	}
		CleanBlock(); 
		q++; 
		FillBlock(); 
		Display(); 
} 
void MoveDown(void) //下移
{ 
	CleanBlock(); 
	p++; 
	Display(); 
	CheckBlock(); 
} 
void End() 
{
	char c=0; 
	int i,j,x,y; 
	for(i=0;i<3;i++) 
	{
		x=block[r][i][0]; 
		y=block[r][i][1]; 
		b[x+p][5+y+q]=2; 
	} 
	b[p][5+q]=2; 
	GotoXY(1,1); 
	for(i=0;i<20;i++) 
	{
		printf("■"); 
		for(j=0;j<10;j++) 
		{
			switch(b[i][j]) 
			{
			case 0:printf("  ");break; 
			case 1:printf("□");break; 
			case 2:printf("■");break;
		}
		
	} 
			printf("■\n");} 
			for(i=0;i<12;i++) 
			printf("■"); 
			GotoXY(1,22);
			printf("SCORE:%d",score); 
			GotoXY(1,23);
			printf("LEVEL:%d",score/100); 
 
			GotoXY(1,24);
			printf("Sorry,Game Over!"); 
			GotoXY(1,25);
			printf("Press Q to ESC..."); 
			do 
			{
				c=getch();
			} 
			while(c!='q'); 
			exit(1); 
}  
void CheckBlock() 
{
	int i,x,y,k; 
	char c; 
	Display(); 
	for(i=0;i<10;i++) 
	if(b[0][i]==1&&b[1][i]==2) End(); 

	for(i=0;i<3;i++) 
	{
		x=block[r][i][0]; 
		y=block[r][i][1]; 
		if(b[x+p+1][5+y+q]==2||b[p+1][5+q]==2||x+p==19) 

		{  
			for(k=0;k<10;k++) 
			{ 
				if(kbhit()) 
				{
					c=getch(); 
					switch(c) 
					{
					case 'a':case '4':MoveLeft();break; 
					case 'd':case '6':MoveRight();break; 
					case 'w':case '8':CleanBlock();ChangeBlock();Display();break; 
					case 'p':Pause();break; 
					case 'q':
						{
							GotoXY(1,24);
							printf("Sorry,Game Over!"); 
							GotoXY(1,25);
							printf("Press any key to ESC..."); 
							c=getch(); 
							exit(1);
						};
						break; 
					}
				} 

			_sleep(5);
			}  
			if(!(b[x+p+1][5+y+q]==2||b[p+1][5+q]==2||x+p==19)) 
				CheckBlock(); 
			for(i=0;i<3;i++) 
			{
				x=block[r][i][0]; 
				y=block[r][i][1]; 
				b[x+p][5+y+q]=2; 
			} 
			b[p][5+q]=2;
			CheckLine();
			BlockRandom();
			p=0;q=0;
			FillBlock();
			CheckBlock();
			Display();
		} 
	} 
} 
void CheckLine() 
{
	int i,j,s=0,t=0; 
	for(i=0;i<20;i++) 
	{
		s=0; 
		for(j=0;j<10;j++) 

		s+=b[i][j]; 

		if (s==20) 
		{s=0;CleanLine(i);t++;} 
	} 
	switch (t) 
	{
	case 1:score++;break; 
	case 2:score+=3;break; 
	case 3:score+=5;break; 
	case 4:score+=8;break; 
	} 
	switch(score/100) 
	{
	case 0:speed=25;break; 
	case 1:speed=20;break; 
	case 2:speed=17;break; 
	case 3:speed=15;break; 
	case 4:speed=12;break; 
	case 5:speed=10;break; 
	case 6:speed=7;break; 
	case 7:speed=5;break; 
	case 8:speed=2;break; 
	case 9:{speed=0;break;} 
	} 
} 

 
void CleanLine(int l) 
{
	int i,j; 
	for(i=l-1;i>=0;i--) 
	for(j=0;j<10;j++) 
	b[i+1][j]=b[i][j]; 
	for(i=0;i<10;i++) 
	b[0][j]=0; 
} 
void ChangeBlock(void) 
{	
	int i,yy; 
	if (r==4) return; 
	for(i=0;i<3;i++) 
	{ 
		if(block[r][i][0]*block[r][i][1]>0) 
		block[r][i][1]=(-1)*block[r][i][1];
		else if(block[r][i][0]*block[r][i][1]<0)
		block[r][i][0]=(-1)*block[r][i][0];
		else if(block[r][i][0]==0) 
		Swap(block[r][i][0],block[r][i][1]);
		else if(block[r][i][1]==0)
		{
			Swap(block[r][i][0],block[r][i][1]);
			block[r][i][1]*=-1;
		} 
	} 
	for(i=0;i<3;i++) 
	{ 
		yy=block[r][i][1]; 
		if(5+yy+q>9) q--; 
		if(5+yy+q<0) q++; 
		if(5+yy+q>9) q--; 
		if(5+yy+q<0) q++;} 
} 

void Swap(int &x,int *y) 
{ 
	int temp; 
	temp=x; 
	x=y; 
	y=temp; 
} 

void Welcome(void)//进入游戏界面 
{ 
	int i;
    printf("旋转：W/8 下落：X/2 左移：A/4 右移：D/6 瞬间下落：S/5 暂停：P 退出：Q\n"); 
	printf("平均每提高100分 速度会加快一个级别\n"); 
	printf("S 为快速下落 按下后直接落到底部\n");
	for(i=0;i<25;i++)
	{
		printf("*");
		_sleep(100);
	}
	printf("\n\n");
	printf("Now ");_sleep(200);
	printf("let ");_sleep(200);
	printf("us ");_sleep(200);
	printf("play ");_sleep(200);
	printf("the ");_sleep(200);
	printf("game ");_sleep(200);
	printf("!\n\n");_sleep(200);
	for(i=0;i<25;i++)
	{
		printf("*");
		_sleep(100);
	}
	printf("\n\n");
	system("pause"); 
	system("cls"); 
} 

void FastDown(void) 
{
	while(p) 
	MoveDown(); 
	 
} 

void Pause(void) 
{
	char c; 
	GotoXY(1,23);
	printf("Pause! "); 
	do 
	{
		c=getch();
	} 
	while(c!='p'); 
} 
