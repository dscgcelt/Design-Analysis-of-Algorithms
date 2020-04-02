#include<stdio.h>
#define MAX 100
int p[MAX];
int w[MAX];
int x[MAX];
int y[MAX];
int fp=-1,fw,n,m;
float Bound(int k,int cp,int cw)
{
	float b=cp;
	int c=cw;
	int i;
	for(i=k+1;i<=n;i++)
	{
		c+=w[i];
		if(c<=m)
			b+=p[i];
		else
			return b+(1-1.0*(c-m)/w[i])*p[i];
	}
	return b;
}
void BKnap(int k,int cp,int cw)
{
	if(cw+w[k]<=m)
	{
		y[k]=1;
		if(k<n)
			BKnap(k+1,cp+p[k],cw+w[k]);
		else if(cp+p[k]>fp)
		{
			fp=cp+p[k];
			fw=cw+w[k];
			int j;
			for(j=1;j<=n;j++)
				x[j]=y[j];
		}
	}
	if(Bound(k,cp,cw)>=fp)
	{
		y[k]=0;
		if(k<n)
			BKnap(k+1,cp,cw);
		else if(cp>fp)
		{
			fp=cp;
			fw=cw;
			int j;
			for(j=1;j<=n;j++)
				x[j]=y[j];
		}
	}
}
int main()
{
	printf("ENTER THE NUMBER OF OBJECTS : ");
	scanf("%d",&n);
	printf("ENTER THE CAPACITY OF THE KNAPSACK : ");
	scanf("%d",&m);
	printf("ENTER THE PROFIT AND WEIGHTS OF THE OBJECTS \n");
	int i;
	for(i=1;i<=n;i++)
		scanf("%d %d",p+i,w+i);
	BKnap(1,0,0);
	printf("THE OPTIMAL FINAL PROFIT = %d\n",fp);
	printf("THE OPTIMAL FINAL WEIGHT = %d\n",fw);
	printf("THE OPTIMAL SOLUTION VECTOR = < ");
	for(i=1;i<=n;i++)
		printf("%d ",x[i]);
	printf(">\n");
	return 0;
}
