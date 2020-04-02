#include<stdio.h>
#include<math.h>
#define MAX 100
#define max 10
struct node{
	int c;
	int previ;
	int i;
	int depth;
	int mat[max][max];
	int included[max];
	int parent;
	};
struct node a[MAX];
struct node del[MAX];
int k;
int delnode=1;
int n;
int infinity;
int upper;

void insertMinHeap(struct node);
struct node deleteMinHeap();
int minSon(int);
void heapify(int);
int reduce(struct node* x);
void getcost(struct node* x);
void display(struct node* x);
void LCsearch(struct node E );

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

int reduce(struct node* x)
{	
	int cost=0;
	int i,j;
	int min;
	//row reduce	
	for(i=1;i<=n;i++)
	{
		min=infinity;
		for(j=1;j<=n;j++)
			if(x->mat[i][j]<min)
				min=x->mat[i][j];
		if(min!=infinity && min!=0)
		{
			for(j=1;j<=n;j++)
			 if(x->mat[i][j]!=infinity)
				x->mat[i][j]-=min;
			cost+=min;
		}
	}
	//column reduce
	for(j=1;j<=n;j++)
	{
		min=infinity;
		for(i=1;i<=n;i++)
			if(x->mat[i][j]<min)
				min=x->mat[i][j];
		if(min!=infinity && min!=0)
		{
			for(i=1;i<=n;i++)
			 if(x->mat[i][j]!=infinity)
				x->mat[i][j]-=min;
			cost+=min;
		}
	}
	return cost;
}

void getcost(struct node* x)
{
	int i;
	if(x->depth==1)
	{	x->c=reduce(x);return;}
	int val1=x->mat[x->previ][x->i];
	int val2=x->mat[x->i][1];
	for(i=1;i<=n;i++)
		x->mat[x->previ][i]=infinity;
	for(i=1;i<=n;i++)
		x->mat[i][x->i]=infinity;
	x->mat[x->i][1]=infinity;
	if(x->depth!=n)
		x->c+=val1+reduce(x);
	else
		x->c+=val1+val2+reduce(x);
}

void display(struct node* x)
{
	if(x->parent == 0)
		return;
	display(del+x->parent);
	printf(" - %d",x->i);	
}

int main()
{
	printf("\n\n~~~~~~~~~~~THIS CODE IS DEVELOPED BY HITECH GA~~~~~~~~~~~~~\n\n");
	printf("PRESS ENTER TO CONTINUE...\n");
	getchar();
	printf("ENTER THE NUMBER OF VERTICES : ");
	scanf("%d",&n);
	infinity=pow(2,8*sizeof(int)-1)-1;	
	upper=infinity;
	struct node E;
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			E.mat[i][j]=infinity;
	printf("ENTER THE EDGEs AS i j cost SUCH THAT THE COST BETWEEN EDGES i->j IS COST\n");
	while(1)
	{
		int x,y,z;
		if(scanf("%d %d %d",&x,&y,&z)==-1)
			break;
		E.mat[x][y]=z;
	}
	LCsearch(E);
	return 0;
}

void LCsearch(struct node E )
{
	E.i=1;E.depth=1;E.included[E.i]=1;E.parent=0;
	getcost(&E);
	k=0;
	while(1)
	{
		if(E.depth==n)
		{
			printf("1");
			display(&E);
			printf(" - 1\n");
			if(E.c<upper)
				upper=E.c;
		}
		else{
			int i,j;
			for(i=1;i<=n;i++)			
			{
				int flag=0;
				for(j=1;j<=n;j++)
					if(E.included[j]==i)
					{
						flag=1;
						break;
					}
				if(flag==1 || E.mat[E.i][i]==infinity)
					continue;
				struct node child=E;
				child.previ=child.i;
				child.i=i;
				child.depth++;			
				getcost(&child);
				child.parent=delnode;
				child.included[child.i]=1;
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
	
