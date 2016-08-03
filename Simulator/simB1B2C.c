#include<stdio.h>
#include<stdlib.h>
main()
{
FILE *fp;
char *fn;
long int mem[100],reg[4],con[6]={0,0,0,0,0,1},inst,op1,op2,lc=0,i=0;
printf("\n enter source file name");
scanf("%s",fn);
fp=fopen(fn,"r");
if(fp==NULL)
{
printf("\n can not open");
exit(0);
}
while(!feof(fp))
{
fscanf(fp,"%ld",&mem[i]);
i++;
}
fclose(fp);
while(1)
{
inst=mem[lc]/10000;
op1=((mem[lc]%10000)/1000)-1;
op2=((mem[lc]%10000)%1000);
switch(inst)
{
case 11:exit(0);
case 9:reg[op1]=reg[op1]+mem[op2];
break;
case 10:reg[op1]=reg[op1]-mem[op2];
break;
case 7:reg[op1]=reg[op1]*mem[op2];
break;
case 1:reg[op1]=mem[op2];
break;
case 2:mem[op2]=reg[op1];
break;
case 5:if(reg[op1]<mem[op2])
con[0]=1;
if(reg[op1]<=mem[op2])
con[1]=1;
if(reg[op1]==mem[op2])
con[2]=1;
if(reg[op1]>mem[op2])
con[3]=1;
if(reg[op1]>=mem[op2])
con[4]=1;
break;
case 6:if(con[op1]==1)
lc=op2-1;
for(i=0;i<5;i++)
con[i]=0;
break;
case 8:reg[op1]=reg[op1]/mem[op2];
break;
case 3:printf("enter value");
scanf("%ld",&mem[op2]);
break;
case 4:printf("the answer is %ld",mem[op2]);
break;
}
lc++;
}
}


