#include<cstdio>
/*useful Functions*/

inline int hcf(int m,int n)
{
  int temp,remainder;
  remainder=n;
  while(remainder)
  {
    remainder=m%n;
    m=n;
    n=remainder;
  }
  return m;
}

inline int lcm(int a,int b)
{
  return (a*b)/hcf(a,b);
}

//Frac class Definition

class Frac
{
public:
  int n;
  int d;
  Frac(int n_,int d_):n(n_),d(d_)
  {}
  inline void correct()
  {
    int h=hcf(n,d);
    n/=h;
    d/=h;
    if(d<0)
    {
      d*=-1;
      n*=-1;
    }
  }
  inline void mul(int m)
  {
    n*=m;
    d*=m;
  }
};

Frac operator+(Frac x, Frac y)
{
  Frac sum(x.n*y.d+y.n*x.d,x.d*y.d);
  sum.correct();
  return sum;
}
Frac operator-(Frac x,Frac y)
{
  int h=hcf(x.d,y.d);
  x.mul(h);
  y.mul(h);
  Frac sum(x.n*y.d-y.n*x.d,x.d*y.d);
  sum.correct();
  return sum;
}
Frac operator*(Frac x,Frac y)
{
  Frac ans(x.n*y.n,x.d*y.d);
  ans.correct();
  return ans;
}
Frac operator/(Frac x,Frac y)
{
  Frac ans(x.n*y.d,x.d*y.n);
  ans.correct();
  return ans;
}
int main()
{
  Frac a(2,3);
  Frac b(3,4);
  Frac c=a-b;
  printf("%d/%d",c.n,c.d);
  return 0;
}
