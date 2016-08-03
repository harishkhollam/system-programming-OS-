#include<stdio.h>
int No_Of_States;
int States[100];
int No_Of_Inp_Sym;
char InputSymbol[10];
int No_Of_Final_States;
int FinalStates[10];
int TransitionTable[10][10];
char InputString[80];
void DFA();
void DisplayTable()
{
	int i,j;
	printf("\nTransition table");
	printf("\n*********************************\n");
	printf("\nInputSymbol");
	for(i = 0; i < No_Of_Inp_Sym; i++)
	{
		printf("\t%c",InputSymbol[i]);
	}
	printf("\n*********************************\n");
	for(i  = 0; i < No_Of_States;i++)
	{
		printf("\tq%d",i);
		for(j = 0; j < No_Of_Inp_Sym; j++)
		printf("\t%d",TransitionTable[i][j]);
		printf("\n");
	}
	printf("\n*********************************\n");
}

void AcceptInput()
{
	char ch[5];	int i;	int j;
	//1. No of states
	printf("\nEnter number of states:");
	scanf("%d",&No_Of_States);
	//2. State numbers
	for(i = 0; i < No_Of_States; i++)
	{
		States[i] = i;
	}
	//3. no of input symbol
	printf("\nEnter number of input Symbol");
	scanf("%d",&No_Of_Inp_Sym);
	//4. Accept input symbol
	for(i = 0; i < No_Of_Inp_Sym; i++)
	{
		printf("\nEnter input symbol %d:",i);
		fflush(stdin);
		scanf("%s",ch);
		InputSymbol[i] =ch[0];
	}
	//5. No of final states
	printf("\nEnter number of final states:");
	scanf("%d",&No_Of_Final_States);
	//6. Name of all final states
	for(i = 0; i < No_Of_Final_States; i++)
	{
		printf("\nEnter Final state %d:",i);
		scanf("%d",&FinalStates[i]);
	}
	//7. transition Table
	printf("\nEnter information in transition table");
	for(i= 0; i < No_Of_States; i++)
	{
		for(j = 0; j < No_Of_Inp_Sym; j++)
		{
printf("\nEnter for state q%d Input Symbol %c:",i,InputSymbol[j]);
			scanf("%d",&TransitionTable[i][j]);
		}
	}
	DisplayTable();
	//8. Input String to be validated
	printf("\nEnter input string to validate");
	scanf("%s",InputString);
}
void DFA()
{
	int i=0;int k;char ch;int curr = 0;int flag = 0;
	while(InputString[i]!='\0')
	{
		ch= InputString[i];
		for(k=0; k < No_Of_Inp_Sym; k++)
		{
			if(ch==InputSymbol[k])
	        {
printf("\ncurrent state=%d  next character=%c",curr,InputSymbol[k]);
				curr= TransitionTable[curr][k];
			}       
		}
		i++;
	}
	//check if current state is one of final state
	for(i = 0; i < No_Of_Final_States; i++)
	{
		if(curr == FinalStates[i])
			flag  =1;
	}
	if(flag == 1)
		printf("\n%s is a Valid String",InputString);
	else
		printf("\n%s is not a valid string",InputString);
}
int main()
{
	AcceptInput();
	DFA();
	getch();
	return 0;
}

































///*
//	------------------------------------------------------------------
//	(b) L = { set of all strings over {x, y, z} which start with xy, end with zz and
//	   does not contain substring zxx }
//	-----------------------------------------------------------------*/
//
//#include<stdio.h>
//#include<string.h>
//#include<stdlib.h>
//int main()
//{
//int i,j,k,no_of_states,no_of_input_symb,no_of_final_states,cur;
//char input_symb[100];
//int final_states[50];
//char ch,c;
//int transition[10][10],flag;
//char test_string[100];
//printf("\nEnter Number of states\n");
//scanf("\n%d",&no_of_states);
//for(i=0;i<no_of_states;i++)
//   {
//      printf("\nEnter state no\n");
//      scanf("\n%d",&transition[i]);
//   }
//printf("\nEnter Number of input symbol\n");
//scanf("\n%d",&no_of_input_symb);
//for(i=0;i<no_of_input_symb;i++)
//   {
//      printf("\nEnter symbol \n");
//      scanf("\n%c",&input_symb[i]);
//   }
//printf("\nEnter Number of final states\n");
//scanf("\n%d",&no_of_final_states);
//for(i=0;i<no_of_final_states;i++)
//   {
//      printf("\nEnter final state \n");
//      scanf("\n%d",&final_states[i]);
//   }
// for(i=0;i<no_of_states;i++)
//   {
//       for(j=0;j<no_of_input_symb;j++)
//            {
//            printf("\nEnter transition to flag q%d for symbol %c\n",i,input_symb[j]);
//             scanf("%d",&transition[i][j]);
//            }
//   }
//  printf("\nTransition Table\n");
//  printf("\n------------------------\nAlpbabet ");
//  
//for(i=0;i<no_of_input_symb;i++)
//   {
//      printf(" %c  ",input_symb[i]);
//   } 
//printf("\nstates");
//  printf("\n------------------------\n");
//for(i=0;i<no_of_states;i++)
//   {    printf("      q%d",i);         
//       for(j=0;j<no_of_input_symb;j++)
//            {
//              printf("  q%d",transition[i][j]);
//            }
//        printf("\n");
//   }
//  printf("\n------------------------\n");
//while(1)
//{
//cur=0;
//flag=0;
//printf("\nEnter string to check valid or invalid\n");
//scanf("%s",test_string);
//i=0;
//while(test_string[i]!='\0')
//{
//ch=test_string[i];
////printf("%c",ch);
//for(k=0;k<no_of_input_symb;k++)
//   {   if(ch==input_symb[k])
//        {
//          printf("\ncurrent state=%d  next character=%c",cur,input_symb[k]);
//       cur=transition[cur][k];
//        }       
//   }
//i++;
//}
//printf("\ncurrent state=%d",cur);
//for(i=0;i<no_of_final_states;i++)
//   {
//     // printf("\nfinal state=%d",final_states[i]);
//      if(cur==final_states[i])
//       flag=1; 
//   }
//if(flag==1)
//printf("\nvalid string\n");
//else if(flag==0)
//printf("\nInvalid string\n");
//printf("\nDo you want 2 checking another string if yes then press y  otherwise press n\n");
//scanf("\n%c",&c);
//if(c=='n')
//break;
//else if(c=='y')
//continue;
//}
//return(0);
//}
//
///*---------------------Output-----------------
//Enter Number of states
//7
//
//Enter state no
//0
//
//Enter state no
//1
//
//Enter state no
//2
//
//Enter state no
//3
//
//Enter state no
//4
//
//Enter state no
//5
//
//Enter state no
//6
//
//Enter Number of input symbol
//3
//
//Enter symbol 
//x
//
//Enter symbol 
//y
//
//Enter symbol 
//z
//
//Enter Number of final states
//1
//
//Enter final state 
//4
//
//Enter transition to flag q0 for symbol x
//1
//
//Enter transition to flag q0 for symbol y
//6
//
//Enter transition to flag q0 for symbol z
//6
//
//Enter transition to flag q1 for symbol x
//6
//
//Enter transition to flag q1 for symbol y
//2
//
//Enter transition to flag q1 for symbol z
//6
//
//Enter transition to flag q2 for symbol x
//2
//
//Enter transition to flag q2 for symbol y
//2
//
//Enter transition to flag q2 for symbol z
//3
//
//Enter transition to flag q3 for symbol x
//5
//
//Enter transition to flag q3 for symbol y
//2
//
//Enter transition to flag q3 for symbol z
//4
//
//Enter transition to flag q4 for symbol x
//5
//
//Enter transition to flag q4 for symbol y
//2
//
//Enter transition to flag q4 for symbol z
//4
//
//Enter transition to flag q5 for symbol x
//6
//
//Enter transition to flag q5 for symbol y
//2
//
//Enter transition to flag q5 for symbol z
//4
//
//Enter transition to flag q6 for symbol x
//6
//
//Enter transition to flag q6 for symbol y
//6
//
//Enter transition to flag q6 for symbol z
//6
//
//Transition Table
//
//------------------------
//Alpbabet  x   y   z  
//states
//------------------------
//      q0  q1  q6  q6
//      q1  q6  q2  q6
//      q2  q2  q2  q3
//      q3  q5  q2  q4
//      q4  q5  q2  q4
//      q5  q6  q2  q4
//      q6  q6  q6  q6
//
//------------------------
//
//Enter string to check valid or invalid
//xyzz
//
//current state=0  next character=x
//current state=1  next character=y
//current state=2  next character=z
//current state=3  next character=z
//current state=4
//valid string
//
//Do you want 2 checking another string if yes then press y  otherwise press n
//y
//
//Enter string to check valid or invalid
//xyzxxzz
//
//current state=0  next character=x
//current state=1  next character=y
//current state=2  next character=z
//current state=3  next character=x
//current state=5  next character=x
//current state=6  next character=z
//current state=6  next character=z
//current state=6
//Invalid string
//
//Do you want 2 checking another string if yes then press y  otherwise press n
//n
//
//
//--------------------------------------------*/
