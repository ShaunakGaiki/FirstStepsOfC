#include <stdio.h>
#include<stdlib.h>
#include<math.h>
void swap(float *xp, float *yp)
{
    float temp = *xp;
    *xp = *yp;
    *yp = temp;
}
void bubbleSort(float arr[], int n)
{
   int i, j;
   for (i = 0; i < n-1; i++)      
       for (j = 0; j < n-i-1; j++) 
           if (arr[j] > arr[j+1])
              swap(&arr[j], &arr[j+1]);
}
int main()
{
  float *data,sum=0,sigma=0,mode,mean,median,LQ,UQ;
  int i,len;
  printf("Enter the number of data points available: ");
  scanf("%d",&len);
  data=(float*)malloc(len*sizeof(data[0]));
  printf("\nEnter the data: ");
  for(i=0;i<len;i++)
  {
    scanf("%f",&data[i]);
    sum+=data[i];
  }
  bubbleSort(data,len);
  mean=sum/len;
  if(len%2==1)
  {
	median=data[len/2];
	if(((len/2)%2)==1)
	{
		LQ=data[len/4];
		UQ=data[((len/2-1)/2)+(len-1)];
	}
	else
	{
		LQ=(data[len/4]+data[len/4-1])/2;
		UQ=(data[len-1-(len/4)]+data[len-(len/4)])/2;
	}
  }
  else
  {
	median=((data[len/2-1])+(data[(len/2)]))/2;
	if(((len/2-1)%2)==1)
	{
		LQ=data[len/4];
		UQ=(data[len-1-(len/4)]+data[len-(len/4)])/2;
	}
	else
	{
		LQ=(data[len/4]+data[len/4-1])/2;
		UQ=(data[len-1-(len/4)]+data[len-(len/4)])/2;
	}
  }
  for(i=0;i<len;i++)
  {
    sigma+=((data[i]-mean)*(data[i]-mean));
  }
  printf("Mean: %f\nMode: (not in the program yet)\nStandard Deviation(whole population): %f\nStandard Deviation(with sampling): %f\nRange: %f\nLowest Point: %f\nLQ: %f\nMedian: %f\nUQ: %f\nHighest Point: %f\nInterquartile Range: %f\n",mean,sqrt(sigma/len),sqrt(sigma/(len-1)),data[len-1]-data[0],data[0],LQ,median,UQ,data[len-1],UQ-LQ);
}
