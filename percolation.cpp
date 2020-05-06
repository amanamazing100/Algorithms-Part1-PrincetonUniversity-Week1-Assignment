#include <iostream>
#include <string>
#include <cstdlib>
using namespace std;
int n=10;//n*n grid
int arr[102];// two extra for (i)arr[0]=-1 as tank;(ii) arr[101]=100 as sink. The grid is accessed as arr[x]=x-1. It has markings from 0 to n^2-1 to be usec as openings. 
int arrOpen[102];//to mainti state of the grids. Tank (arr[0]=-1) and sink(arr[101]=100) are open by default. 
int size[102];//To represent the sze of the group each node is part of. If root(tank)==root(sink), then the grid percolates.


//to find root
int root(int a)
{
	while(arr[a+1]!=a)//takes the content of the grid as input, hence the node is its own root if arr[x+1]==x.
	{
		a=arr[a+1];
	}
	return a;
}


//to connect two nodes
void connect(int a, int b)
{
	if(root(a)==root(b))//if their roots are equal, means they are already connected.
		{
			//cout<<a<<" "<<b<<" connected"<<endl;
			return;
		}
		if(size[root(a)+1]<size[root(b)+1])//weighted quick union
		{
			size[root(b)+1]+=size[root(a)+1];
			arr[root(a)+1]=arr[root(b)+1];
	
		}
		else 
		{
			size[root(a)+1]+=size[root(b)+1];
			arr[root(b)+1]=arr[root(a)+1];
		}
		while(a!=arr[a+1])//tree compression
		{
		arr[a+1]=arr[arr[a+1]+1];
		a=arr[a+1];
		}
		while(b!=arr[b+1])
		{
		arr[b+1]=arr[arr[b+1]+1];
		b=arr[b+1];
		}
		return;
}


//to check if a node is full		
int isFull(int a)
{
	if(arrOpen[a+1])
	{
		if(root(a)==root(-1))//the node should be connected to tank in order to flow
		{
			//cout<<"Full"<<endl;
			return 1;
		}
		else
			return 0;
	}
	else
		//cout<<"Empty"<<endl;
	return 0;
}



//to check if a node can hold the flowing matter
int isOpen(int a)
{
	
	return arrOpen[a+1];
}
	



//to open a node
void open()
{
	int x=rand()%100;//to generate random numbers [0,99]
	if(arrOpen[x+1])
		cout<<"\"already counted for\""<<endl;//may generate same numbers twice
	arrOpen[x+1]=1;//open the node
	cout<<x<<"to be opened"<<endl;
	
	//now to make connections if the neighbouring nodes are open
	if(x<10)
		connect(-1,x);//any top row open node will get the matter from the tank
	if(x/n>0)
		if(arrOpen[x-n+1])
		connect(x-n,x);
	if((x+1)/n==x/n)
		if(arrOpen[x+2])
		connect(x,x+1);
	if((x-1)/n==x/n)
		if(arrOpen[x])
		connect(x,x-1);
	if(x/n<n-1)
		if(arrOpen[x+n+1])
		connect(x,x+n);

	return;
}



//to find the number of open sites
int num_open()
{
	int count=0;
	for(int i=0;i<n*n;i++)
	{
		if (arrOpen[i+1])
		{	
		count++;
		cout<<" k"<<i;//to show which grids are opened
		}
	}
	
	return count;
}



//to check whether the grid percolates
int percolates()
{
	if(root(-1)!=root(n*n))
	{
		cout<<"doesn't percolate"<<endl;
		return 0;
	}
	else 
		cout<<"Percolates"<<endl;
	return 1;
}
	
	
//driver function	
int main(){
	arr[0]=-1;
	
	for(int i=0;i<=n*n;i++)
	{
		arr[i+1]=i;
	}
	
	for(int i=0;i<=n*n;i++)
	{
		arrOpen[i+1]=0;
	}
	
	for(int i=0;i<n*n+2;i++)
	{
		size[i]=1;
	}
	/*
	cout<<endl<<"size"<<endl;
	for(auto x:size)
		cout<<x<<" ";*/
	
	arrOpen[0]=1;
	arrOpen[101]=1;
	for(int i=n*n-n;i<n*n;i++)//all the bottom row grids are coinnected to the sink
	{
		connect(n*n,i);
	}
	
	for(int i=0;i<160;i++)//to open the desired number of grids change the final condition
	{
		open();
		cout<<i+1<<endl;
		if(percolates())
		{	
			int count=num_open();
			cout<<"number of open sites: "<<count<<endl;
		break;}
	}
			
	int count=num_open();
			cout<<"number of open sites: "<<count<<endl;
	
	/*
	for(int i=0;i<n*n;i++)
	{
		cout<<i<<" is ";isOpen(i);
	}*/
	/*
	for(int i=0;i<n*n;i++)
	{
		if(isFull(i))
		cout<<i<<" is ";isFull(i);
	}
	*/
	
	
	percolates();
	/*
	cout<<"arr"<<endl;
	for(int i=-1;i<=100;i++)
		cout<<root(i)<<" ";*/
	
	
	return 0;
}