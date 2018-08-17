#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include"structdeclare.h"
#include"utilfunctions.c"
#include"mystack.c"
int comparatorx(const void *p,const void *q)
{
  double l=((point *)p)->x;
  double r=((point *)q)->x;
  if((int)(l-r)==0)
  {
     return (int)((((struct point *)p)->y) - (((struct point *)q)->y));
  }
  return (int)(l-r);
}

int comparatory(const void *p,const void *q)
{
  double l=((point *)p)->y;
  double r=((point *)q)->y;
  if((int)(l-r)==0){
      return (int)((((struct point *)p)->x)-(((struct point *)q)->x));
  }
  return (int)(l-r);
}

void findConvexHull(point *parr, int size)
{
  point BL_Xmin,BL_Ymin,BR_Ymin,BR_Xmax,TL_Xmin,TL_Ymax,TR_Xmax,TR_Ymax;
  point *sortedAccToX=(point *)malloc(size*sizeof(point));
  point *sortedAccToY=(point *)malloc(size*sizeof(point));
  for(int i=0;i<size;i++)
  {
     sortedAccToX[i]=parr[i];
     sortedAccToY[i]=parr[i];
  }
  qsort((void *)sortedAccToX,size,sizeof(point),comparatorx);
  qsort((void *)sortedAccToY,size,sizeof(point),comparatory);
  printPoints(sortedAccToX,size);
  printPoints(sortedAccToY,size);
  BL_Xmin=sortedAccToX[0];
  BL_Ymin=sortedAccToY[0];
  TR_Xmax=sortedAccToX[size-1];
  TR_Ymax=sortedAccToY[size-1];
  //BR_Ymin
  for(int i=0;i<size;i++)
  { 
     if(sortedAccToY[i].y==BL_Ymin.y)
     {
        BR_Ymin=sortedAccToY[i];
        continue;
     }
    break;
  }
 //BR_Xmax
 for(int i=size-1;i>=0;i--)
 {
    if(sortedAccToX[i].x==TR_Xmax.x)
    {
        BR_Xmax=sortedAccToX[i];
        continue;
    }
  break;
 }
 //TL_Xmin
 for(int i=0;i<size;i++)
 { 
   if(sortedAccToX[i].x==BL_Xmin.x)
   {
       TL_Xmin=sortedAccToX[i];
       continue;
   }
  break;
 }
 //TL_Ymax
 for(int i=size-1;i>=0;i--)
 {
   if(sortedAccToY[i].y==TR_Ymax.y)
   {
     TL_Ymax=sortedAccToY[i];
     continue;
   }
  break;
 }
printf("\n\n");
printf("BL_Xmin:\t%lf\t%lf\n",BL_Xmin.x,BL_Xmin.y);
printf("BL_Ymin:\t%lf\t%lf\n",BL_Ymin.x,BL_Ymin.y);
printf("BR_Xmax:\t%lf\t%lf\n",BR_Xmax.x,BR_Xmax.y);
printf("BR_Ymin:\t%lf\t%lf\n",BR_Ymin.x,BR_Ymin.y);
printf("TL_Xmin:\t%lf\t%lf\n",TL_Xmin.x,TL_Xmin.y);
printf("TL_Ymax:\t%lf\t%lf\n",TL_Ymax.x,TL_Ymax.y);
printf("TR_Xmax:\t%lf\t%lf\n",TR_Xmax.x,TR_Xmax.y);
printf("TR_Ymax:\t%lf\t%lf\n",TR_Ymax.x,TR_Ymax.y);
}
 
void bottomLeftOperation(point *sortedAccToX,point *sortedAccToY, point *parr,point BL_Xmin,point BL_Ymin)
{ 
 int i;
 point BL_Xmin'=NULL,BL_Ymin'=NULL;
 for(i=0;i<size;i++)
 {
   if(sortedAccToX[i].x>BL_Xmin.x && sortedAccToX[i].x< BL_Ymin.x && 
     sortedAccTOX[i].y>BL_Ymin.y && sortedAccToX[i].y< BL_Xmin.y)
   {
     BL_Xmin'=sortedAccToX[i];
     break;
   }
 }
 for(i=0;i<size;i++)
 {
   if(sortedAccToY[i].x>BL_Xmin.x && sortedAccToY[i].x< BL_Ymin.x && 
     sortedAccToY[i].y>BL_Ymin.y && sortedAccToY[i].y< BL_Xmin.y)
   {
     BL_Ymin'=sortedAccToY[i];
     break;
   }
 }
  if(BL_Xmin'==NULL && BL_Ymin'==NULL)
     return;
  else if(BL_Xmin'.x==BL_Ymin'.x && BL_Xmin'.y==BL_Ymin'.y)
   {
      int D=findRotation(BL_Xmin',BL_Xmin,BL_Ymin);
      if(D<=0)
      {
        //add to convex hull set
        return;
      }
   }
 else if(BL_Xmin' !=BL_Ymin')
   {
      int xmin'rotvalue=findRotation(BL_Xmin',BL_Xmin,BL_Ymin);
      int ymin'rotvalue=findRotation(BL_Ymin',BL_Xmin,BL_Ymin);
      if(xmin'rotavalue !=1 && ymin'rotvalue !=1)
         return;
      else if(xmin'rotvalue ==1 || ymin'rotvalue ==1)
         {
            //add to convex hull set
            return;
         }
      else if(xmin'rotvalue >=0 && ymin'rotvalue >=0)
         {
           bottomLeftOperation(sortedAccToX,sortedAccToY,parr,BL_Xmin',BL_Ymin');
         }
  else{}   
}
    

int main()
{
 point *points;
 int numberOfPoints;
 printf("Enter the number of points:");
 scanf("%d\n",&numberOfPoints);
 points=(point*)malloc(numberOfPoints*sizeof(point));
 for(int i=0;i<numberOfPoints;i++)
 {
   scanf("%lf%lf",&points[i].x,&points[i].y);
   points[i].isInConvexHull=false;
 }
printPoints(points,numberOfPoints);
findConvexHull(points,numberOfPoints);
return 0;
}

 
