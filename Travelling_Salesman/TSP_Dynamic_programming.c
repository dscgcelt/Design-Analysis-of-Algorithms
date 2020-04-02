#include<stdio.h>
#include<math.h>
#define MAX 100
int cost[MAX][MAX];
int infinity=pow(2,8*sizeof(int)-1)-1;
void input(int n)
{
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cost[i][j]=infinity;
	printf("ENTER THE EDGEs AS i j cost SUCH THAT THE COST BETWEEN EDGES i->j IS COST\n");
	while(1)
	{
		int x,y,z;
		if(scanf("%d %d %d",&x,&y,&z)==-1)
			break;
		cost[x][y]=z;
	}
}

int g(int i,int* S,int nS)
{
	if(nS==0)
		return cost[i][1];
	int temp[nS-1];
	int min=infinity;
	int k,l;
	for(k=1;k<=nS;k++)
	{
		int j=S[k];
		int index=1;
		for(l=1;l<=nS;l++)
			if(k!=l)
				temp[index++]=S[l];
		int val=cost[i][j]+g(j,temp,nS-1);
		if(val<min)
			min=val;
	}
	return min;
}
	
int main()
{
	printf("ENTER THE NUMBER OF VERTICES : ");
	int n;
	scanf("%d",&n);
	input(n);
	int temp[n];
	int i;
	for(i=2;i<=n;i++)
		temp[i-1]=i;
	printf("THE COST OF THE TOUR = %d\n", g(1,temp,n-1));
}	
