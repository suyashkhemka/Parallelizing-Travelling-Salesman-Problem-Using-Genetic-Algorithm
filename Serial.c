
#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<time.h>
void main()
{
    int i,j,n,a[20][20],city[10000][20],c,t;
    printf("Enter the number of cities");
    //scanf("%d",&n);
n=10;
    printf("Enter the cost matrix");

    for(i=0;i<n;i++)
    {
        for(j=0;j<n;j++)
        {
            if(j==i+1)
            {
                a[i][j]=1;

            }
            else if(i==j)
            {
                a[i][j]=0;

            }
            else
                a[i][j]=4;
           // scanf("%d",&a[i][j]);

        }
    }
    int b[10000]={0};
    int f[10000]={0};

    printf("Enter the count");
    //scanf("%d",&c);
    c=100;
    printf("Enter the number of threads");
    //scanf("%d",&t);
    t=800;

j=0;

int r,flag=0,flag1,flag2,count=0,l,k1=0,flag3,k,dist=0,min,max,minid,criteria=0;
for(i=0;i<t;i++)
{

j=0;k1=0;
//srand(time(NULL));
r=rand()%n;
while(j!=n)
{

flag=0;
for(k=0;k<k1;k++)
{
if(city[i][k]==r)
    {
    flag=1;
    break;
    }
}
    if(flag==0)
    {
        city[i][j]=r;
        j++;
		k1++;
    }
	r=rand()%n;
}
}
printf("\n");
for(i=0;i<t;i++)
{
    for(j=0;j<n;j++)
    {
        printf("(%d)%d  ",i,city[i][j]);
    }
    printf("\n");
}
flag=0;
while(count<c)
{


for(i=0;i<t;i++)
{
dist=0;
for(j=0;j<n-1;j++)
{
    dist+=a[city[i][j]][city[i][j+1]];
}
//printf("%d",dist);
b[i]=dist;

if(f[i]==1)
{
b[i]=999;
}
}
min=999;max=0;//????

for(k=0;k<t;k++)
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
for(i=0;i<t;i++)//goood one
{


if(b[i]>criteria)
{
    flag=1;
    f[i]=1;
    b[i]=999;

}
}
flag2=0;

for(i=0;i<t;i++)
{
if(i!=minid && f[i]!=1)
{

flag2=0;
while(flag2==0)
{

    r=rand()%t;
    if(f[r]==0 && r!=i)
    {
          //printf("%d,%d\n",i,r);


        flag2=1;
        k=(n/2);

            for(j=0;k<n;j++)
            {


                flag1=0;
                for(l=0;l<k;l++)
                {   //printf("%d, %d i= %d r= %d j= %d l= %d\n",city[r][j],city[i][l],i,r,j,l);
                    if(city[r][j]==city[i][l])
                    {

                        flag1=1;
                        break;
                    }
                }
                //printf("flag=%d \n",flag1);
                if(flag1==0)
                {
                    city[i][k]=city[r][j];
                    k++;

                }
               // printf("{%d}\n",k);
                if(k==n)
                    break;

            }
           /* for(k=0;k<n;k++)
            {

              printf("%d->",city[i][k]);
            }*/

        }
}
}
}

count++;
printf("\n");
}


     printf("/n Min distance using genetic algorithm is %d",min);
     printf("/n Path is \n\n");
     for(i=0;i<n;i++)
     {
         printf("%d->",city[minid][i]);
     }

}

