 #include<stdio.h>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#define MAX 20

struct SYMBTAB
{
	char Symb[10];
	int Addr,Decl,Used,Val,Len;
}S[MAX];

char OPTAB[][6] = {"STOP","ADD","SUB","MULT","MOVER","MOVEM","COMP",
					"BC","DIV","READ","PRINT"};
char ADTAB[][7] = {"START","END","ORIGIN","EQU"};

int SymbCnt,TokCnt,PC,i,j,k,m;
char SrcFile[MAX],Tok1[MAX],Tok2[MAX],Tok3[MAX],Tok4[MAX],Buffer[80];
FILE *fp;

int SearchSymb(char *s)
{
	for(m=0;m<SymbCnt;m++)
		if(strcmpi(S[m].Symb,s)==0)
			return(m);
	return(-1);
}

int SearchOp(char *s)
{
	for(m=0;m<11;m++)
		if(strcmpi(OPTAB[m],s)==0)
			return(m);
	return(-1);
}

int SearchDirective(char *s)
{
	for(m=0;m<4;m++)
		if(strcmpi(ADTAB[m],s)==0)
			return(m);
	return(-1);
}

void DispSymbTab()
{
	for(m=0;m<SymbCnt;m++)
		if(S[m].Used == 1 && S[m].Decl == 0)
			printf("\nSymb %s used but not defined",S[m].Symb);
		else if(S[m].Used == 0 && S[m].Decl == 1)
			printf("\nSymb %s defined but not used",S[m].Symb);
	getch();
}

void PassOne()
{
	fp=fopen(SrcFile,"r");
	while(fgets(Buffer,80,fp))
	{
		TokCnt = sscanf(Buffer,"%s %s %s %s",Tok1,Tok2,Tok3,Tok4);
		switch(TokCnt)
		{
			case 2:
				i = SearchOp(Tok1);
				if(i==9 || i==10)			// READ or PRINT
				{
					j = SearchSymb(Tok2);
					if(j==-1)
					{
						strcpy(S[SymbCnt].Symb,Tok2);
						S[SymbCnt++].Used = 1;
					}
					else
						S[j].Used = 1;
					break;
				}
				i = SearchDirective(Tok1);
				if(i==0 || i==2)		  	// START or ORIGIN
				{
					PC = atoi(Tok2)-1;
				}
				else						// STOP with label
				{
					i = SearchOp(Tok2);
					if(i==0)
					{
						j = SearchSymb(Tok1);
						if(j==-1)
						{
							strcpy(S[SymbCnt].Symb,Tok1);
							S[SymbCnt].Addr = PC;
							S[SymbCnt].Decl = 1;
							S[SymbCnt].Val = 0;
							S[SymbCnt++].Len = 0;
						}
						else
						{
							if(S[j].Decl == 1)
								printf("\nMultiple declaration of symbol %s",Tok1);
							else
							{
								S[j].Addr = PC;
								S[j].Decl = 1;
								S[j].Val = S[j].Len = 0;
							}
						}
					}
				}
				break;
			case 3:
				i = SearchOp(Tok1);
				if(i>=1 && i<=8)				// ADD - DIV
				{
					Tok2[strlen(Tok2)-1]='\0';
					j = SearchSymb(Tok3);
					if(j==-1)
					{
						strcpy(S[SymbCnt].Symb,Tok3);
						S[SymbCnt++].Used = 1;
					}
					else
						S[j].Used = 1;
				}
				else if(strcmp(Tok2,"DC")==0)	// DC
				{
					j = SearchSymb(Tok1);
					if(j==-1)
					{
						strcpy(S[SymbCnt].Symb,Tok1);
						S[SymbCnt].Addr = PC;
						S[SymbCnt].Decl = 1;
						S[SymbCnt].Val = atoi(Tok3);
						S[SymbCnt++].Len = 1;
					}
					else
					{
						if(S[j].Decl == 1)
							printf("\nMultiple declaration of symbol %s",Tok1);
						else
						{
							S[j].Addr = PC;
							S[j].Decl = 1;
							S[j].Val = atoi(Tok3);
							S[j].Len = 1;
						}
					}
				}
				else if(strcmpi(Tok2,"DS")==0)	// DS
				{
					j = SearchSymb(Tok1);
					if(j==-1)
					{
						strcpy(S[SymbCnt].Symb,Tok1);
						S[SymbCnt].Addr = PC;
						S[SymbCnt].Decl = 1;
						S[SymbCnt].Val = 0;
						S[SymbCnt++].Len = atoi(Tok3);
					}
					else
					{
						if(S[j].Decl == 1)
							printf("\nMultiple declaration of symbol %s",Tok1);
						else
						{
							S[j].Addr = PC;
							S[j].Decl = 1;
							S[j].Val = 0;
							S[j].Len = atoi(Tok3);
						}
					}
					PC += atoi(Tok3)-1;
				}
				else								// Label
				{
					j = SearchSymb(Tok1);
					if(j==-1)
					{
						strcpy(S[SymbCnt].Symb,Tok1);
						S[SymbCnt].Addr = PC;
						S[SymbCnt].Decl = 1;
						S[SymbCnt].Val = 0;
						S[SymbCnt++].Len = 0;
					}
					else
					{
						if(S[j].Decl==1)
							printf("%d: Multiple declaration of symbol %s",Tok1);
						else
						{
							S[j].Addr = PC;
							S[j].Decl = 1;
							S[j].Val = S[j].Len = 0;
						}
					}
					i = SearchOp(Tok2);
					if(i==9 || i==10)			// READ or PRINT
					{
						j = SearchSymb(Tok3);
						if(j==-1)
						{
							strcpy(S[SymbCnt].Symb,Tok3);
							S[SymbCnt++].Used = 1;
						}
						else
							S[j].Used = 1;
					}
				}
				break;
			case 4:
				j = SearchSymb(Tok1);		// Label
				if(j==-1)
				{
					strcpy(S[SymbCnt].Symb,Tok1);
					S[SymbCnt].Addr = PC;
					S[SymbCnt].Decl = 1;
					S[SymbCnt].Val = 0;
					S[SymbCnt++].Len = 0;
				}
				else
				{
					if(S[j].Decl==1)
						printf("\nMultiple declaration of symbol %s",Tok1);
					else
					{
						S[j].Addr = PC;
						S[j].Decl = 1;
						S[j].Val = S[j].Len = 0;
					}
				}
				i = SearchOp(Tok2);
				if(i>=1 && i<=8)			// ADD - DIV
				{
					Tok3[strlen(Tok3)-1]='\0';
					j = SearchSymb(Tok4);
					if(j==-1)
					{
						strcpy(S[SymbCnt].Symb,Tok4);
						S[SymbCnt++].Used = 1;
					}
					else
						S[j].Used = 1;
				}
		}
		PC++;
	}
	fclose(fp);
}

void main()
{
	clrscr();
	printf("\nEnter Source File Name: ");
	scanf("%s",SrcFile);
	PassOne();
	DispSymbTab();
}