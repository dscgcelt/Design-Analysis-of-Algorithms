#include<stdio.h>
#define MAX 100
struct pw{
	float p;
	float w;
	};
struct pw pairs[MAX];
float p[MAX],w[MAX];
int Largest(int i,int m,int t,int h)
{
	int j;
	for(j=t;j<=h;j++)
		if(w[i]+pairs[j].w>m)
			break;
	return j-1;
}
void traceBack(int *b,int n,int*x)
{
	struct pw val=pairs[b[n+1]-1];
	int i,j;
	for(i=n;i>=1;i--)
	{
		int flag=0;
		for(j=b[i-1];j<=b[i]-1;j++)
			if(val.p==pairs[j].p && val.w==pairs[j].w)
			{
				flag=1;
				break;
			}
		if(flag==1)
			x[i]=0;
		else
		{	
			x[i]=1;
			val.p-=p[i];
			val.w-=w[i];
		}	
	}
}								
	
void dknap(int n,int *x,int m)
{
	int b[n+2];
	b[0]=1;
	pairs[1].p=pairs[1].w=0.0;
	int next;
	int t=1,h=1;
	b[1]=next=2;
	int i,j;
	for(i=1;i<=n;i++)
	{
		int k=t;
		int u=Largest(i,m,t,h);	
		for(j=t;j<=u;j++)
		{
			float pp=pairs[j].p+p[i];
			float ww=pairs[j].w+w[i];
			while(k<=h && pairs[k].w<ww)
			{
				pairs[next]=pairs[k];
				next++;
				k++;
			}
			if(k<=h && pairs[k].w==ww)
			{
				if(pp<pairs[k].p)
					pp=pairs[k].p;
				k++;
			}
			if(pp>pairs[next-1].p)
			{
				pairs[next].p=pp;
				pairs[next].w=ww;
				next++;
			}
			while(k<=h && pairs[k].p<pairs[next-1].p)
				k++;
		}
		while(k<=h)
			pairs[next++]=pairs[k++];
		b[i+1]=next;
		t=b[i];h=next-1;
	}
	traceBack(b,n,x);
}

int main()
{
	printf("ENTER THE NUMBER OF OBJECTS : ");
	int n;
	scanf("%d",&n);
	int x[n+1];
	printf("ENTER THE CAPACITY OF THE KNAPSACK : ");
	int m;
	scanf("%d",&m);
	printf("ENTER THE PROFIT AND WEIGHT IN ASCENDING ORDER OF THE WEIGHTS \n");
	int i;
	for(i=1;i<=n;i++)
		scanf("%f %f",&p[i],&w[i]);
	dknap(n,x,m);
	for(i=1;i<=n;i++)
		printf("%d ",x[i]);
	printf("\n");
}

