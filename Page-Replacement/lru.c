#include<stdio.h>
#include<conio.h>

int RefString[20],PT[10],nof,nor;

void Accept()
{
	int i;
	printf("Enter Reference String: \n");
	for(i=0;i<nor;i++)
	{
		printf("[%d]=",i);
		scanf("%d",&RefString[i]);
	}
}

int Search(int s)
{
	int i;
	for(i=0;i<nof; i++)
		if(PT[i]==s)
			return(i);
	return(-1);
}

int GetLRU(int e)
{
	int i,j,Pos=99,Posi,k;
	for(i=0;i<nof;i++)
	{
		for(j=e-1;j>=0;j--)
		{
			if(PT[i]==RefString[j])
			{
				if(j<Pos)
				{
					Pos=j;
					Posi=i;
				}
				break;
			}
		}
	}
	return(Posi);
}

void LRU()
{
	int i,j,k,Faults=0;

	for(k=0,i=0; k<nof && i<nor; i++)
	{
		gotoxy(3*i+1,2);
		printf("%2d",RefString[i]);
		if(Search(RefString[i])==-1)
		{
			PT[k]=RefString[i];
			for(j=0;j<3;j++)
			{
				gotoxy(3*i+1,j+3);
				if(PT[j])
					printf("%2d",PT[j]);
			}
			Faults++;
			k++;
		}
	}
	while(i<nor)
	{
		gotoxy(3*i+1,2);
		printf("%2d",RefString[i]);
		if(Search(RefString[i])==-1)
		{
			k = GetLRU(i);
			PT[k]=RefString[i];
			for(j=0;j<nof;j++)
			{
				gotoxy(3*i+1,j+3);
				printf("%2d",PT[j]);
			}
			Faults++;
		}
		i++;
	}
	gotoxy(10,24);
	printf("Total Page Faults: %d",Faults);
	getch();
}

void main()
{
	clrscr();
	printf("Enter Length of reference string: ");
	scanf("%d",&nor);
	printf("Enter No.of Frames: ");
	scanf("%d",&nof);
	clrscr();
	Accept();
	clrscr();
	LRU();
}

