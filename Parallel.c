
#ifndef __CUDACC__
#define __CUDACC__
#endif // __CUDACC__
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include "cuda_runtime.h"
#include "device_launch_parameters"
__constant__ int a[10][10];
__global__ void genetic( int n,int *city,int *b, int *f,int c   )
{

int  i=threadIdx.x,j=0;

int r,flag,flag1,flag2,count,l,flag3,k,dist=0,min,max,minid,criteria=0;
while(j!=n)
{
r=rand()%n;
flag=0;
for(k=0;k<n;k++)
{
if(city[i*n+k]==r)
    {
    flag=1;
    break;
    }
}
    if(flag==0)
    {
        city[i*n+j]=r;
        j++;
    }
}
flag=0;
while(count!=c)
{


for(j=0;j<n-1;j++)
{
    dist+=a[city[i*n+j]][city[(i*n)+j+1]];
}
b[i]=dist;
min=999;max=0;
if(f[i]==1)
{
b[i]=999;
}
__syncthreads();
for(k=0;k<n;k++)
{
    if(b[k]<min && f[k]==0)
    {
       min=b[k];
       minid=k;
    }
    if(b[k]>max && f[k]==0)
    {
       max=b[k];

    }
}

criteria=(min+max)/2;
if(b[i]>criteria)
{
    flag=1;
    f[i]=1;
    b[i]=999;

    break;
}
count++;
flag2=0;
if(i!=minid)
{


while(flag2==0)
{
    r=rand()%n;
    if(f[r]==0)
    {
        flag2=1;
        k=n/2;


            for(j=0;k<n;j++)
            {   flag1=0;
                for(l=0;l<k;l++)
                {
                    if(city[r*n+j]==city[i*n+l])
                    {
                        l=k;
                        flag1=1;
                        break;
                    }
                }
                if(flag==0)
                {
                    city[i*n+k]=city[r*n+j];
                    k++;

                }
            }



        }


}
}
count++;
}

}

void main()
{
    int i=0,j=0,n=0,cost[100][100],*city,*b,*f,c=0,t=0;
    printf("Enter the number of cities");
    scanf("%d",&n);
    printf("Enter the cost matrix");
    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            scanf("%d",&cost[i][j]);

        }
    }
    int bd[100]={0};
    int fd[100]={0};

     int city1[100][100]={300};
    printf("Enter the count");
    scanf("%d",&c);
    printf("Enter the number of threads");
    scanf("%d",&t);
    int size1=n*(sizeof(int));
    int size=t*n*(sizeof(int));
    cudaMemcpyToSymbol(a,cost,size);
    cudaMalloc((void**)&city,size);
    cudaMalloc((void**)&b,size1);
    cudaMalloc((void**)&f,size1);
 cudaMemcpy(city,city1,size,cudaMemcpyHostToDevice);
    cudaMemcpy(b,bd,size1,cudaMemcpyHostToDevice);
    cudaMemcpy(f,fd,size1,cudaMemcpyHostToDevice);
     genetic<<<1,t>>>(n,city,b,f,c);
     cudaMemcpy(bd,b,size1,cudaMemcpyDeviceToHost);
     int city1[100][100];
     cudaMemcpy(city1,city,size,cudaMemcpyDeviceToHost);
     int min=999;
     int minid;
     for(i=0;i<n;i++)
     {
         if(bd[i]<min)
         {
             minid=i;
             min=bd[i];
         }
     }

     printf("/n Min distance using genetic algorithm is %d",min);
     printf("/n Path is \n\n");
     for(i=0;i<n;i++)
     {
         printf("%d->",city1[minid][i]);
     }
}
