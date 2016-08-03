/*
	Write the simulation program for demand paging and show the page
	scheduling and total number of page faults according to LRU page
	replacement algorithm. Assume memory of 'n' frames.
	Request Page Numbers:
	5,8,10,14,10,9,5,10,8,5,11,10,9,5,10
*/

#include<stdio.h>
#include<conio.h>

int RefString[20],PT[10],nof,nor;

void Accept()
{

	int i;

	printf("Enter Length of reference string: ");
	scanf("%d",&nor);
	printf("Enter No.of Frames: ");
	scanf("%d",&nof);

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

int GetMRU(int e)
{
	int i,j,Pos=-99,Posi,k;
	for(i=0;i<nof;i++)
	{
		for(j=e-1;j>=0;j--)
		{
			if(PT[i]==RefString[j])
			{
				if(j>Pos)
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

void MRU()
{
	int i,j,k,Faults=0;

	for(k=0,i=0; k<nof && i<nor; i++)
	{
		printf("\n%2d :\t",RefString[i]);
		if(Search(RefString[i])==-1)
		{
			PT[k]=RefString[i];
			for(j=0;j<3;j++)
			{
				if(PT[j])
					printf("%2d",PT[j]);
			}
			Faults++;
			k++;
		}
	}
	while(i<nor)
	{
		printf("\n%2d :\t",RefString[i]);
		if(Search(RefString[i])==-1)
		{
			k = GetMRU(i);
			PT[k]=RefString[i];
			for(j=0;j<nof;j++)
			{
				printf("%2d",PT[j]);
			}
			Faults++;
		}
		i++;
	}
	printf("\nTotal Page Faults: %d",Faults);
	getch();
}

void main()
{
	
	Accept();

	MRU();

	getch();
}

