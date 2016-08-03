#include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 20

char OPTAB[][6] = {"STOP","ADD","SUB","MULT","MOVER","MOVEM",
				   "COMP","BC","DIV","READ","PRINT"};
char REGTAB[][5] = {"AREG","BREG","CREG","DREG"};
char CONDTAB[][4] = {"LT","LE","EQ","GT","GE","ANY"};
char ADTAB[][7] = {"START","END","ORIGIN"};
int TokCnt,PC,i,j,k;
char SrcFile[MAX],Tok1[MAX],Tok2[MAX],Tok3[MAX],Buffer[80];
FILE *fp;

int SearchOp(char *s)
{
	int i;
	for(i=0;i<11;i++)
		if(strcmpi(OPTAB[i],s)==0)
			return(i);
	return(-1);
}

int SearchReg(char *s)
{
	int i;
	for(i=0;i<4;i++)
		if(strcmpi(REGTAB[i],s)==0)
			return(i);
	return(-1);
}

int SearchCond(char *s)
{
	int i;
	for(i=0;i<6;i++)
		if(strcmpi(CONDTAB[i],s)==0)
			return(i);
	return(-1);
}

int SearchDirective(char *s)
{
	int i;
	for(i=0;i<4;i++)
		if(strcmpi(ADTAB[i],s)==0)
			return(i);
	return(-1);
}

int IsDigits(char *s)
{
	while(*s)
	{
		if(*s<'0' || *s>'9')
			return 0;
		s++;
	}
	return 1;
}

void PassOne()
{
	fp=fopen(SrcFile,"r");
	while(fgets(Buffer,80,fp))
	{
		TokCnt = sscanf(Buffer,"%s %s %s",Tok1,Tok2,Tok3);
		switch(TokCnt)
		{
			case 1:
				i = SearchOp(Tok1);
				if(i==0)					// STOP
					break;
				i = SearchDirective(Tok1);
				if(i!=1)
					printf("\n%d: %s\nInvalid Mnemonic/Statement",Buffer,PC);
				break;
			case 2:
				i = SearchOp(Tok1);
				if(i==9 || i==10)			// READ or PRINT
					break;
				i = SearchDirective(Tok1);
				if(i==0 || i==2)			// START or ORIGIN
				{
					if(IsDigits(Tok2))
						PC = atoi(Tok2)-1;
					else
						printf("\n%d: %sInvalid Statement",PC,Buffer);
				}
				else
					printf("\n%d: %sInvalid Mnemonic/Statement",PC,Buffer);
				break;
			case 3:
				i = SearchOp(Tok1);
				if(i>=1 && i<=8)			// ADD - DIV
				{
					if(i==7)				// First operand is reg or cond
						k = SearchCond(Tok2);
					else
						k = SearchReg(Tok2);
					if(k==-1)
						printf("\n%d: %s\nInvalid Statement",PC,Buffer);
				}
				else if(strcmp(Tok2,"DC")==0)	// DC
				{
					if(!IsDigits(Tok3))
						printf("\n%d: %sInvalid Statement",PC,Buffer);
				}
				else if(strcmpi(Tok2,"DS")==0)		// DS
				{
					if(!IsDigits(Tok3))
						printf("\n%d: %sInvalid Statement",PC,Buffer);
					else
						PC = atoi(Tok3)-1;
				}
				else
					printf("\n%d: %sInvalid Menmonic/Statement",PC,Buffer);
		}
		PC++;
	}
	fcloseall();
}

void main()
{
	clrscr();
	printf("\nEnter Source File Name: ");
	scanf("%s",SrcFile);
	PassOne();
}