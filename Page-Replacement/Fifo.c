#include<stdio.h>
#include<conio.h>
int RefString[20];
int Frames[5];
int N;
int No_Of_Frames;
int Pg_Fault;
void AcceptInput()
{
	int i;
	printf("\nEnter number of values in ref string");
	scanf("%d",&N);
	for(i = 0 ; i < N; i++)
	{
		printf("\nEnter RefString[%d]:",i);
		scanf("%d",&RefString[i]);
	}
	printf("\nEnter No of Frames:");
	scanf("%d",&No_Of_Frames);

	for(i = 0; i < No_Of_Frames; i++)
		Frames[i] = -1;
}
 void DisplayOutput()
 {
	 printf("\nPage Fault Count :%d\n",Pg_Fault);
 }
 //RefString[1,2,3,1,2,5,4,3,2,1,4,6,7]
//No_Of_Frames[3]={-1,-1,-1}
 int IsPageFault(int k)
 {
	int i;
	for(i = 0;i < No_Of_Frames; i++)
		if(Frames[i] == k)
			return 0;

	return 1;
 }
 void DisplayFrames()
 {
	int i;
	for(i = 0 ; i < No_Of_Frames; i++)
		printf("%5d",Frames[i]);
	printf("\n");
 }
 //1,2,3,1,4,5,4,6,7,8
 //No of Frames = 3
void FIFO()
{
	int k = 0;
	int i = 0;	
	while(i < N)
	{
		printf("\nRef Value[%d]",RefString[i]);

		if(IsPageFault(RefString[i]))
		{
			Pg_Fault++;
			Frames[k] = RefString[i];
			k = (k+ 1) % No_Of_Frames;
		}
		i++;
		
		DisplayFrames();
	}
}

int main()
{
	AcceptInput();
	FIFO();
	DisplayOutput();
	getch();
	return 0;
}

