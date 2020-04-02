/*
	Here let us assume that we represent the graph as cost matrix
	Let there are n vertices in the graph numbered as 1,2,3,..n.
	For minimum cost between any to pair of vertices let us use the
	recursive definition
	A(k)[i,j]=min(A(k-1)[i,j],A(k-1)[i,k]+A(k-1)[k,j]);
		for k=1,2,3,..n for all i and j
	The above recursive definition considers all possible paths between 
	vertices i and j along the path
	[i,j]=[i,k] U [k,i]// where U is union operator
	 k=1,2,3,...,n
			[k]
			/ \	
	               /   \
                      /     \
		    [i]     [j]
	Now we assume that the graph is a simple graph i.e. it neither has any
	parallel edges or self loops so we set A[i,i] to 0 for all i
	We also assume that the graph as no negative cycles in the graph
	
	Now there are few more important things to be considered before we proceed.
	
		when i<j
			->(k<i<j) or (i<k<j)
				A[i,k]+A[k,j]
					no changes have been made to the terms in the above expression
					in the kth pass in the matrix A so Ak can used in place of A(k-1) 
					so the corresponding entry in the A matrix is still the value 
					of A(k-1). This is so because in the kth pass 
					A(k)[i,k]=min(A[i,k],(A[i,k]+A[k,k]))
						=min(A[i,k],(A[i,k]+0))
						=min(A[i,k],A[i,k])
						=A[i,k]
			->k=<i<j
				A[i,i]+A[i,j] as k=i
					As we know that A[i,i] is 0 there is no change in the value 
					to which it is assigned
			->i<j=k
				A[i,j]+A[j,j] as k=j
					As we know that A[j,j] is 0 there is no change in the value
					to which it is assigned
			->i<j<k
				A[i,k]+A[k,j]
					the values of each of the above terms are yet to be changed
					in the kth pass in matrix A,so the corresponding entry in 
					the A matrix is still the value	of A(k-1).
		
		when i=j
			->k<i=j
				A[i,k]+A[k,i]
					no changes have been made to the terms in the above expression
					in the kth pass in the matrix A so Ak can used in place of A(k-1) 
					so the corresponding entry in the A matrix is still the value 
					of A(k-1)
		
			->i=j<k
				A[i,k]+A[k,i]
					the values of each of the above terms are yet to be changed
					in the kth pass in matrix A,so the corresponding entry in 
					the A matrix is still the value	of A(k-1).
			
			Now as there are no negative cycles in the graph so the above expression
			for A[i,i] i.e. A[i,k]+A[k,i] is>=0 now as
			A(k)[i,j]=min(A(k)[i,j],recursive def) as as A[i,i] is set to zero the value 
			for the diagonal elements of the matrix remains unaltered(i.e. 0)
		
		when j<i
			->(k<=j<i) or (j<k<i)
				A[i,k]+A[k,j]
					no changes have been made to the terms in the above expression
					in the kth pass in the matrix A so Ak can used in place of A(k-1) 
					so the corresponding entry in the A matrix is still the value 
					of A(k-1)
			
			->j<i<=k
				A[i,k]+A[k,j]
					the values of each of the above terms are yet to be changed
					in the kth pass in matrix A,so the corresponding entry in 
					the A matrix is still the value	of A(k-1).

	HOW IS IT SO THAT THE ALGORITHM GIVES THE SHORTEST PATH?
		
		although we get all possible paths using i-k-j but it is not sure that at that instant
		whether the path [i,k] or [k,j] are optimal or not...
					
		Suppose k1 is certain constant
		And previously we had calculated 
		A(k1)[i,j] using A(k1-1)[i,k1]+A(k1-1)[k1,j] i.e i-k1-j
		
		now suppose A(k1-1)[i,k1] and A(k1-1)[k1,j] were not optimal and say for some higher k2
		and k3 we get optimal paths i,k1 and k1,j as
			A(k2)[i,k1] => i-k2-k1
			A(k3)[k1,j] => k1-k2-j
		so optimal path i-j should be along i-k2-k1-k3-j (alteast)
		but this path shall be included ultimately for higher k2 and k3 as
			i-k2-j or i-k3-j		

										
	 		
*/

#include<stdio.h>
#include<math.h>
#define MAX 100
#define min(x,y) ((x)<(y))?(x):(y);
long int cost[MAX][MAX];//as addition to two infinite(max limit in int) can cause overflow
int lim=pow(2,(8*sizeof(int))-1)-1;

void input(int n)
{
	int i,j;
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			cost[i][j]=lim;
	printf("ENTER THE VERTICES AND COST AS X Y COST , AS IF X->Y is the direction of edge\n");
	printf("TO STOP ENTERING EDGES PRESS CTRL+Z IN WINDOWS OR CTRL+D IN LINUX\n");
	while(1)
	{
		int x,y,z;
		if(scanf("%d %d %d",&x,&y,&z)==-1)
			break;
		cost[x][y]=z;
	}
}

void floyd(int n)
{
	int i,j,k;
	long int A[n+1][n+1];
	//copy the cost matrix to A i.e form A0 and set diagonal elements to 0
	for(i=1;i<=n;i++)
		for(j=1;j<=n;j++)
			if(i==j)
				A[i][j]=0;
			else
				A[i][j]=cost[i][j];
	for(k=1;k<=n;k++)
		for(i=1;i<=n;i++)
			for(j=1;j<=n;j++)
				A[i][j]=min(A[i][j],A[i][k]+A[k][j]);
	
	printf("\n\nTHE ALL PAIRS SHORTEST PATH IS SHOWN AS A MATRIX\n\t");
	for(i=1;i<=n;i++)
		printf("%d\t",i);
	printf("\n");
	for(i=1;i<=n;i++)
		printf("------------");
	printf("\n");
	for(i=1;i<=n;i++)
	{
		printf("%d |\t",i);
		for(j=1;j<=n;j++)
			printf("%ld\t",A[i][j]);
		printf("\n");
	}
}

int main()
{
	printf("ENTER THE NUMBER OF VERTICES : ");
	int n;
	scanf("%d",&n);
	input(n);
	floyd(n);
	printf("\n");
	return 0;
}
	
