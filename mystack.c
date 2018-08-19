point* stack=NULL;
int top,size;

void initStack(int ssize)
{
  stack=(point *)malloc(ssize* sizeof(point));
  top=-1;
  size=ssize;
}

void push(point p)
{
  top++;
  stack[top]=p;
}

point pop()
{
  point q=stack[top];
  top--;
  return q;
}

void printStack()
{
  for(int i=0;i<=top;i++)
  {
     printf("%lf\t%lf\n",stack[i].x,stack[i].y);
  }
} 
