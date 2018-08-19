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
  double a=((point *)p)->y;
  double b=((point *)p)->y;
/*  if((int)(l-r)==0)
  {
     return (int)((((struct point *)p)->y) - (((struct point *)q)->y));
  }*/
  if(l>r)
  {
    return 1;
  }
  else if(l<r)
  {
    return -1;
  }
  else
  {
    return 0;
  }	
  //return (int)(l-r);
}

int comparatory(const void *p,const void *q)
{
  double l=((point *)p)->y;
  double r=((point *)q)->y;
  
  /*if((int)(l-r)==0){
      return (int)((((struct point *)p)->x)-(((struct point *)q)->x));
  }
  return (int)(l-r);*/
  if(l>r)
  {
    return 1;
  }
  else if(l<r)
  {
    return -1;
  }
  else
  {
    return 0;
  }
}

//bottomleftoperation
void bottomLeftOperation(point *sortedAccToX,point *sortedAccToY,int size,point BL_Xmin,point BL_Ymin)
{ 
 int i;
 point BL_Xmin2= {0}, BL_Ymin2 = {0};
 for(i=0;i<size;i++)
 {
   if(sortedAccToX[i].x>BL_Xmin.x && sortedAccToX[i].x< BL_Ymin.x && 
     sortedAccToX[i].y>BL_Ymin.y && sortedAccToX[i].y< BL_Xmin.y)
   {
     BL_Xmin2=sortedAccToX[i];
     break;
   }
 }
 for(i=0;i<size;i++)
 {
   if(sortedAccToY[i].x>BL_Xmin.x && sortedAccToY[i].x< BL_Ymin.x && 
     sortedAccToY[i].y>BL_Ymin.y && sortedAccToY[i].y< BL_Xmin.y)
   {
     BL_Ymin2=sortedAccToY[i];
     break;
   }
 }
  if(BL_Xmin2.x==EmptyStruct.x && BL_Ymin2.x==EmptyStruct.x && BL_Xmin2.y==EmptyStruct.y &&  BL_Ymin2.y==EmptyStruct.y)
     return;
  else if(BL_Xmin2.x == BL_Ymin2.x && BL_Xmin2.y == BL_Ymin2.y)
   {
      int D=findRotation(BL_Xmin2,BL_Xmin,BL_Ymin);
      if(D<=0)
      {
        push(BL_Xmin2);
        return;
      }
   }
 else if(BL_Xmin2.x != BL_Ymin2.x || BL_Xmin2.y != BL_Ymin2.y)
   {
      int xmin2rotvalue=findRotation(BL_Xmin2,BL_Xmin,BL_Ymin);
      int ymin2rotvalue=findRotation(BL_Ymin2,BL_Xmin,BL_Ymin);
      if(xmin2rotvalue ==1 && ymin2rotvalue ==1)
         {
            return;
         }
      else if((xmin2rotvalue<=0 && ymin2rotvalue==1)||(xmin2rotvalue==1 && ymin2rotvalue<=0))
         {
            if(xmin2rotvalue<=0) push(BL_Xmin2);
            else if(ymin2rotvalue<=0) push(BL_Ymin2);
            else{}
            return;
         }
      else if(xmin2rotvalue <=0 && ymin2rotvalue <=0)
         {
           bottomLeftOperation(sortedAccToX,sortedAccToY,size,BL_Xmin2,BL_Ymin2);
         }
      else{}
   }
  else{}   
}

//bottomright  
void bottomRightOperation(point *sortedAccToX,point *sortedAccToY,int size,point BR_Xmax,point BR_Ymin)
{ 
 int i;
 point BR_Ymin2={0},BR_Xmax2={0};
 for(i=0;i<size;i++)
 {
   if(sortedAccToY[i].x>BR_Ymin.x && sortedAccToY[i].x<BR_Xmax.x && BR_Ymin.y<sortedAccToY[i].y &&
    sortedAccToY[i].y<BR_Xmax.y)
   {  BR_Ymin2=sortedAccToY[i];
      break;
   }
 }
 for(i=size-1;i>=0;i--)
 {
   if(sortedAccToX[i].x>BR_Ymin.x && sortedAccToX[i].x<BR_Xmax.x && BR_Ymin.y<sortedAccToX[i].y &&
    sortedAccToX[i].y<BR_Xmax.y)
   {
     BR_Xmax2=sortedAccToX[i];
     break;
    }
  }
  if(BR_Ymin2.x==EmptyStruct.x && BR_Xmax2.x==EmptyStruct.x && BR_Ymin2.y==EmptyStruct.y && BR_Xmax2.y==EmptyStruct.y)
      return;
  else if(BR_Ymin2.x==BR_Xmax2.x && BR_Ymin2.y==BR_Xmax2.y )
   {
      int D=findRotation(BR_Xmax2,BR_Ymin,BR_Xmax);
      if(D<=0)
      {
        push(BR_Xmax2);
        return;
      }
   }
 else if(BR_Ymin2.x!=BR_Xmax2.x || BR_Ymin2.y!=BR_Xmax2.y)
   {
      int xmax2rotvalue=findRotation(BR_Xmax2,BR_Ymin,BR_Xmax);
      int ymin2rotvalue=findRotation(BR_Ymin2,BR_Ymin,BR_Xmax);
      if(xmax2rotvalue ==1 && ymin2rotvalue ==1)
         return;
      else if((xmax2rotvalue ==1 && ymin2rotvalue<=0)|| (ymin2rotvalue ==1 && xmax2rotvalue<=0))
         {
            //add to convex hull set
            if(xmax2rotvalue<=0)
                  push(BR_Xmax2);
            else if(ymin2rotvalue<=0)
                  push(BR_Ymin2);
            else{}
            return;
         }
      else if(xmax2rotvalue <=0 && ymin2rotvalue <=0)
         {
           bottomRightOperation(sortedAccToX,sortedAccToY,size,BR_Xmax2,BR_Ymin2);
         }
      else{}
   }
  else{}   
}

//topright
void topRightOperation(point *sortedAccToX,point *sortedAccToY,int size,point TR_Xmax,point TR_Ymax)
{
  int i;
  point TR_Xmax2={0},TR_Ymax2={0};
  for(int i=size-1;i>=0;i--)
  {
     if(sortedAccToX[i].x>TR_Ymax.x && sortedAccToX[i].x<TR_Xmax.x && TR_Xmax.y<sortedAccToX[i].y  && sortedAccToX[i].y<TR_Ymax.y)
    { TR_Xmax2=sortedAccToX[i];
       break;
    }
  }
  for(int i=size-1;i>=0;i--)
  {
     if(sortedAccToY[i].x>TR_Ymax.x && sortedAccToY[i].x<TR_Xmax.x && TR_Xmax.y<sortedAccToY[i].y  && sortedAccToY[i].y<TR_Ymax.y)
    { TR_Ymax2=sortedAccToY[i];
       break;
    }
  }
  if(TR_Ymax2.x==EmptyStruct.x && TR_Xmax2.x==EmptyStruct.x && TR_Ymax2.y==EmptyStruct.y && TR_Xmax2.y==EmptyStruct.y)
     return;
  else if(TR_Ymax2.x==TR_Xmax2.x && TR_Xmax2.y==TR_Xmax2.y)
   {
      int D=findRotation(TR_Xmax2,TR_Xmax,TR_Ymax);
      if(D<=0)
      {
        //add to convex hull set
        push(TR_Xmax2);
        return;
      }
   }
 else if(TR_Ymax2.x!=TR_Xmax2.x || TR_Xmax2.y!=TR_Xmax2.y)
   {
      int xmax2rotvalue=findRotation(TR_Xmax2,TR_Xmax,TR_Ymax);
      int ymax2rotvalue=findRotation(TR_Ymax2,TR_Xmax,TR_Ymax);
      if(xmax2rotvalue ==1 && ymax2rotvalue ==1)
         return;
      else if((xmax2rotvalue<=0 && ymax2rotvalue==1) || (xmax2rotvalue ==1 && ymax2rotvalue<=0))
         {
            //add to convex hull set
            if(xmax2rotvalue<=0) push(TR_Xmax2);
            else if(ymax2rotvalue<=0) push(TR_Ymax2);
            else{}
            return;
         }
      else if(xmax2rotvalue <=0 && ymax2rotvalue <=0)
         {
           bottomRightOperation(sortedAccToX,sortedAccToY,size,TR_Xmax2,TR_Ymax2);
         }
      else{}  
   }
 else{} 
}

//topleft
void topLeftOperation(point *sortedAccToX,point *sortedAccToY,int size,point TL_Xmin,point TL_Ymax)
{
  int i;
  point TL_Xmin2={0},TL_Ymax2={0};
  for(int i=0;i<size;i++)
  {
    if(sortedAccToX[i].x>TL_Xmin.x && sortedAccToX[i].x<TL_Ymax.x && TL_Xmin.y<sortedAccToX[i].y && sortedAccToX[i].y<TL_Ymax.y)
    {
       TL_Xmin2=sortedAccToX[i];
       break;
    }
  }
  for(int i=size-1;i>=0;i--)
  {
   if(sortedAccToY[i].x>TL_Xmin.x && sortedAccToY[i].x<TL_Ymax.x && TL_Xmin.y<sortedAccToY[i].y && sortedAccToY[i].y<TL_Ymax.y)
   {
      TL_Ymax2=sortedAccToY[i];
      break;
   }
  }
if(TL_Ymax2.x==EmptyStruct.x && TL_Xmin2.x==EmptyStruct.x && TL_Ymax2.y==EmptyStruct.y && TL_Xmin2.y==EmptyStruct.y)
     return;
  else if(TL_Ymax2.x==TL_Xmin.x && TL_Ymax2.y==TL_Xmin.y )
   {
      int D=findRotation(TL_Xmin2,TL_Ymax,TL_Xmin);
      if(D<=0)
      {
        //add to convex hull set
        push(TL_Xmin2);
        return;
      }
   }
 else if(TL_Ymax2.x!=TL_Xmin.x || TL_Ymax2.y!=TL_Xmin.y )
   {
      int xmin2rotvalue=findRotation(TL_Xmin2,TL_Ymax,TL_Xmin);
      int ymax2rotvalue=findRotation(TL_Ymax2,TL_Ymax,TL_Xmin);
      if(xmin2rotvalue ==1 && ymax2rotvalue ==1)
         return;
      else if((xmin2rotvalue==1 && ymax2rotvalue<=0)||(xmin2rotvalue<=0 && ymax2rotvalue ==1))
         {
            //add to convex hull set
            if(xmin2rotvalue<=0) push(TL_Xmin2);
            else if(ymax2rotvalue<=0) push(TL_Ymax2);
            else{}
            return;
         }
      else if(xmin2rotvalue <=0 && ymax2rotvalue <=0)
         {
           topLeftOperation(sortedAccToX,sortedAccToY,size,TL_Xmin2,TL_Ymax2);
         }
      else{}
   }
  else{}   
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
initStack(size);
if(BL_Xmin.x!=TL_Xmin.x || BL_Xmin.y!=TL_Xmin.y)
   {
      push(BL_Xmin);
   }
    push(TL_Xmin);
if(BL_Ymin.x!=BR_Ymin.x || BL_Ymin.y!=BR_Ymin.y)
   {
    push(BL_Ymin);
   }
    push(BR_Ymin);
if(BR_Xmax.x!=TR_Xmax.x || BR_Xmax.y!=TR_Xmax.y)
   {
    push(BR_Xmax);
   }
    push(TR_Xmax);
if(TL_Ymax.x!=TR_Ymax.x || TL_Ymax.y!=TR_Ymax.y)
   {
    push(TL_Ymax);
   }
    push(TR_Ymax);
printf("\n\n");
printf("BL_Xmin:\t%lf\t%lf\n",BL_Xmin.x,BL_Xmin.y);
printf("BL_Ymin:\t%lf\t%lf\n",BL_Ymin.x,BL_Ymin.y);
printf("BR_Xmax:\t%lf\t%lf\n",BR_Xmax.x,BR_Xmax.y);
printf("BR_Ymin:\t%lf\t%lf\n",BR_Ymin.x,BR_Ymin.y);
printf("TL_Xmin:\t%lf\t%lf\n",TL_Xmin.x,TL_Xmin.y);
printf("TL_Ymax:\t%lf\t%lf\n",TL_Ymax.x,TL_Ymax.y);
printf("TR_Xmax:\t%lf\t%lf\n",TR_Xmax.x,TR_Xmax.y);
printf("TR_Ymax:\t%lf\t%lf\n",TR_Ymax.x,TR_Ymax.y);
bottomLeftOperation(sortedAccToX,sortedAccToY,size,BL_Xmin,BL_Ymin);
bottomRightOperation(sortedAccToX,sortedAccToY,size,BR_Xmax,BR_Ymin);
topRightOperation(sortedAccToX,sortedAccToY,size,TR_Xmax,TR_Ymax);
topLeftOperation(sortedAccToX,sortedAccToY,size,TL_Xmin,TL_Ymax);
printf("\n\nStack:\n");
printStack();
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
 }
printPoints(points,numberOfPoints);
findConvexHull(points,numberOfPoints);
return 0;
}

 
