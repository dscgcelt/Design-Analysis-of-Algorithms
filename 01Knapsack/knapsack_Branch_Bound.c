#include<stdio.h>
#define MAX 100
struct node{
	int cw;	//current weight
	int cp;	//current profit
	double c;	//c^(x) for the node x
	int u;	//u(x)for the node x
	int j;	//indicates the jth object
	int val;//indicated whether the jth object is included or not using 0/1
	int parent;//store the parent of the node(x)
	};
struct node a[MAX];
int k;
struct node del[MAX];
int delnode=1;
int n,m;
int upper;
int p[MAX],w[MAX];

void insertMinHeap(struct node);
struct node deleteMinHeap();
int minSon(int);
void heapify(int);
void display(struct node* x);
int Ubound(int cw,int cp,int k);
float bound(int cw,int cp,int k);
void LCsearch();

void insertMinHeap(struct node x)
{
	if(k==0)
		a[k]=x;
	else{
		a[k]=x;
		int s = k;
		int p = (k-1)/2;
		while(p>=0 && a[p].c>a[s].c)
		{
			a[s]=a[p];
			a[p]=x;
			s=p;
			p=(p-1)/2;
		}
	}
	k++;
}
struct node deleteMinHeap()
{
	struct node temp=a[0];
	a[0]=a[k-1];
	k--;
	heapify(0);
	return temp;
}
int minSon(int p)
{
	int s=2*p+1;
	if(s>=k)
		return -1;
	if(s+1<k && a[s+1].c<a[s].c)
		s++;
	return s;
}
void heapify(int p)
{
	int s=minSon(p);
	if(s>=0 && a[p].c>a[s].c)
	{
		struct node temp=a[p];
		a[p]=a[s];
		a[s]=temp;
		heapify(s);
	}
}

int Ubound(int cw,int cp,int k)
{
	int b=cp,c=cw;
	int i;
	for(i=k+1;i<=n;i++)
		if(c+w[i]<=m)
		{
			c=c+w[i];
			b-=p[i];
		}
	return b;
}

float bound(int cw,int cp,int k)
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

void LCsearch()
{
	struct node E={0,0,0.0,0,0,0,0};
	upper=E.u=Ubound(E.cw,E.cp,E.j);
	E.c=-bound(E.cw,-E.cp,E.j);
	k=0;
	while(1)
	{
		if(E.j==n)
		{
			display(&E);
			printf("\n");
		}
		else{
			int i;
			for(i=1;i>=0;i--)			
			{
				struct node child=E;
				child.j++;
				child.val=i;			
				if(child.cw+i*w[child.j]>m)
					continue;
				child.cw+=i*w[child.j];		
				child.cp-=i*p[child.j];
				child.c=-bound(child.cw,-child.cp,child.j);
				child.u=Ubound(child.cw,child.cp,child.j);
				if(child.u<upper)
					upper=child.u;
				child.parent=delnode;
				insertMinHeap(child);
			}
			del[delnode++]=E;
		}
		if(k==0)
			return;
		E=deleteMinHeap();
		if(E.c>upper)
			return;
	}
}

void display(struct node* x)
{
	if(x->parent == 0)
		return;
	display(del+x->parent);
	printf("x[%d] = %d \t",x->j ,x->val);	
}

int main()
{
	printf("\n\n~~~~~~~~~~~THIS CODE IS DEVELOPED BY HITECH GA~~~~~~~~~~~~~\n\n");
	printf("PRESS ENTER TO CONTINUE...\n");
	getchar();
	printf("ENTER THE NUMBER OF OBJECT : ");
	scanf("%d",&n);
	printf("ENTER THE CAPACITY OF THE KNAPSACK : ");
	scanf("%d",&m);
	printf("ENTER THE WEIGHT AND PROFIT OF THE OBJECTS\n");
	int i;
	for(i=1;i<=n;i++)
		scanf("%d %d",w+i,p+i);
	getchar();
	LCsearch();
	return 0;
}
		
