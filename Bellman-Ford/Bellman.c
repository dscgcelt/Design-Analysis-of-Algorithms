/*
	In this algorithm we find single source shortest paths. i.e. we assign a vertex as the source
	then we find the shortest path from that source to all other vertices...
	In this algorithm let there be n vertices numbered as 1,2,3...n and  we consider the source 
	vertex as v.
	we use an array dist[1:n] where each entry stores the length of the shortest from v to each 
	vertex u after the end of the algorithm. u=1,2,3,4,...n
	we set dist[v]=0 initially
	There are (n-1) passes in the above algorithm. We assume a variable k which manages the passes.
	k=1,2,3...,(n-1).
	In each pass say for a given vertex u we do,
	dist(k)[u]=min(dist(k-1)[u],min(dist(k-1)[i]+cost[i,u]));
	Here i is the possible incoming edges to vertex u.
	
	Now let us check the correctness of the algorithm.
	CLAIM:
		In the kth pass (k=1,2,3,..(n-1)) the vertex from the source gets that optimal path where the
		number for edges from source to that vertex is atmost k.
	
		[Now why the number of passes are atmost (n-1) .... This is so because we assume that there are no 
		negative cycle in the graph, so the maximum possible path length from source to any vertex is (n-1).
		Had it not been so, let us assume that the path length was more than (n-1)... In that case the path 
		would include a cycle. Now as we no negative cycle(i.e. total length on the closed path is >=0) then
		for the path corresponding to the one containing the cycle we have another path with the cycle 
		eliminated and yet having smaller path cost. So our assumption of max path length in the optimal path
		being >(n-1) is wrong.]
	
	Now let us prove our claim by induction...
			
		Basis: 
			Initially we copy the values from cost[v][u] to dist[u], where v is the source and u=1,2,3,..n
			So in pass 1 all vertices get the cost corresponding to path length of 1 from source to that 
			particular vertex.
		
		Induction:
			Let us assume that in the (k-1)th pass all the vertices have the optimal path having path length 
			from source to the concerned vertex of atmost (k-1). i.e. the optimal path length <=(k-1).
			
			Now we consider the incoming edges to a vetex u, and we get an optimal cost from vertex which has 
			an optimal cost corresponding to path length <=(k-1).[from the induction hypothesis].[Even note 
			that it does not matter in the order in which we process the egdes in the graph in a particular pass]
			So on including the concerned edge we get optimal cost for vertex u corresponding to 
			path length <=(k-1)+1 
						=(k)
	
	NOW WE SHALL IMPLEMENT USING ADJACENCY COST MATRIX AND EDGE LIST
	
*/

/*#include<stdio.h>
#include<math.h>
#define MAX 100
#define min(x,y) ((x)<(y))?(x):(y);
long int cost[MAX][MAX];//as addition to two infinite(max limit in int) can cause overflow
int lim=pow(2,(8*sizeof(int))-1)-1;
long int dist[MAX];

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

void bellmanFord(int v,int n)
{
	int i,j,k;
	//PASS 1
	for(i=1;i<=n;i++)							//O(n)
		dist[i]=cost[v][i];
	dist[v]=0;
	//PASSES 2 to n-1
	for(k=2;k<=n-1;k++)							//O(n)
		for(i=1;i<=n;i++)						//O(n)
		{
			if(i!=v)
			{
				long int minimum=lim;
				for(j=1;j<=n;j++)				//O(n)
					if(cost[j][i]!=lim && dist[j]+cost[j][i]<minimum)
						minimum=dist[j]+cost[j][i];
				dist[i]=min(dist[i],minimum);
			}
		}
	printf("THE SINGLE SOURCE SHORTEST PATH COSTS ARE AS FOLLOWS \n");
	for(i=1;i<=n;i++)							//O(n)
		printf("[ %d -> %d ] => %ld\n",v,i,dist[i]);
	printf("\n");
}//complexity is O(n+n*n*n+n)=O(n^3)

int main()
{
	printf("ENTER THE NUMBER OF VERTICES : ");
	int n;
	scanf("%d",&n);
	printf("ENTER THE SOURCE VERTEX : ");
	int v;
	scanf("%d",&v);
	input(n);
	bellmanFord(v,n);
	return 0;
} 
*/

#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#define MAX 100
int lim=pow(2,(8*sizeof(int))-1)-1;
struct EdgeList{
	int vertex1;
	int vertex2;
	int cost;
	};
struct EdgeList * edges;
int dist[MAX];

void input(int e)
{
	int i;
	printf("ENTER THE VERTICES AND COST AS X Y COST , AS IF X->Y is the direction of edge\n");
	for(i=1;i<=e;i++)
		scanf("%d %d %d",&edges[i].vertex1,&edges[i].vertex2,&edges[i].cost);
}	
void bellmanFord(int v,int n,int e)// v is the source vertex, n is the number of vertices, e is the
				//number of edges
{
	int i,k;
	for(i=1;i<=n;i++)				//O(n)
		dist[i]=lim;
	//pass 1
	for(i=1;i<=e;i++)				//O(e)
		if(edges[i].vertex1==v)
			dist[edges[i].vertex2]=edges[i].cost;
	dist[v]=0;						//O(1)
	//Initialializing the dist array by inifinity is important as we scan edges whose start is 
	//source and store the cost in the dist[vertex2] but all those edges whose start is not 
	//source might result in garbage being retained in the dist array...
 
	//pass 2
	for(k=2;k<=n-1;k++)					//O(n)
		for(i=1;i<=e;i++)				//O(e)
			if(edges[i].vertex2!=v && dist[edges[i].vertex2]>dist[edges[i].vertex1]+edges[i].cost)
				dist[edges[i].vertex2]=dist[edges[i].vertex1]+edges[i].cost;
	printf("THE SINGLE SOURCE SHORTEST PATH COSTS ARE AS FOLLOWS \n");
	for(i=1;i<=n;i++)					//O(n)
		printf("[ %d -> %d ] => %d\n",v,i,dist[i]);
	printf("\n");
}//complexity is O(n+e+ne+n)=O(ne)

int main()
{
	printf("ENTER THE NUMBER OF VERTICES : ");
	int n;
	scanf("%d",&n);
	printf("ENTER THE NUMBER OF EDGES : ");
	int e;
	scanf("%d",&e);
	printf("ENTER THE SOURCE VERTEX : ");
	int v;
	scanf("%d",&v);	
	edges=(struct EdgeList*)malloc((e+1)*sizeof(struct EdgeList));
	input(e);
	bellmanFord(v,n,e);
	free(edges);
}
