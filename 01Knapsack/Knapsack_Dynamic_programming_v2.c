#include<stdio.h>
#include<math.h>
#define MAX 100
#define max(x,y) ((x)>(y))?(x):(y)
int f[MAX][MAX];
int p[MAX],w[MAX];
int infinity;
void traceBack(int n,int*x,int m)
{
	int val=f[n][m];
	int i,j;
	for(i=n;i>=1;i--)
	{
		int flag=0;
		for(j=0;j<=m;j++)
			if(val==f[i-1][j])
			{
				flag=1;
				break;
			}
		if(flag==1)
			x[i]=0;
		else
		{
			x[i]=1;
			val-=p[i];
		}
	}
}

void dknap(int n,int *x,int m)
{
	//base case we assume that f0(y)=0 for all y>=0
	int i,j;
	for(j=0;j<=m;j++)
		f[0][j]=0;
	for(i=1;i<=n;i++)
		for(j=0;j<=m;j++)
		{
			int x=j-w[i],val;
			if(x<0)
				val=-infinity;
			else
				val=f[i-1][x];
			f[i][j]= max(f[i-1][j],val+p[i]);
		}
	traceBack(n,x,m);
}

int main()
{
	infinity=pow(2,8*sizeof(int)-1)-1;
	printf("ENTER THE NUMBER OF OBJECTS : ");
	int n;
	scanf("%d",&n);
	int x[n+1];
	printf("ENTER THE CAPACITY OF THE KNAPSACK : ");
	int m;
	scanf("%d",&m);
	printf("ENTER THE WEIGHT AND PROFIT IN ASCENDING ORDER OF THE WEIGHTS \n");
	int i;
	for(i=1;i<=n;i++)
		scanf("%d %d",&w[i],&p[i]);
	dknap(n,x,m);
    for(int i=0;i<=n;i++)
    {
        for(int j=0;j<=m;j++)
            printf("%d ",f[i][j]);
        printf("\n");
    }
	for(i=1;i<=n;i++)
		printf("%d ",x[i]);
	printf("\n");
}
