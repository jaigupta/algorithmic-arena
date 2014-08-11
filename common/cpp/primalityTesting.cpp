/* This file has Primality testing for large integers which are of the order of 10**18. This can be modified for better performance on smaller numbers of order 10**19. 

** ullMultipleMod(x,y,z) returns (x*y)%z for x and y of order 10**18
** ullMillerRabin(x) returns if x is prime.
*/
/* 64æ¡2é²æ°ã§ã®leading zeroã®æ¡æ° */
int ullNumberOfLeadingZerosTable[256]={8,7,6,6,5,5,5,5,4,4,4,4,4,4,4,4,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,3,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,2,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
int ullNumberOfLeadingZeros(ull x){
    int res=56; unsigned xl=x, xh=x>>32;
    if(xh)             res -= 32, xl = xh;
    if(xl&0xffff0000U) res -= 16, xl >>= 16;
    if(xl&0x0000ff00U) res -= 8,  xl >>= 8;
    return res + ullNumberOfLeadingZerosTable[xl];
}
 
/* (x*y)%m ãæ±ãã (å¶ç´ x,y < m) */
ull ullMultipleMod(ull x, ull y, ull m){
    int k,loop=2;
    ull xlo,xhi,ylo,yhi,rlo,rhi,d1,d2,a,q,r,mask=0xffffffffULL;
  
    if(m<=mask) return (x*y)%m;
  
    xlo=(x&mask); xhi=(x>>32);
    ylo=(y&mask); yhi=(y>>32);
    rhi=xhi*yhi; rlo=xlo*ylo;
    a=(rlo>>32)+xhi*ylo;
    rhi+=(a>>32); a&=mask; a+=xlo*yhi; rhi+=(a>>32);
    rlo = (rlo&mask) | ((a&mask)<<32);
  
    k = ullNumberOfLeadingZeros(m);
    rhi = (rhi<<k)|(rlo>>(64-k));
    rlo<<=k; m<<=k;
  
    d1=(m>>32); d2=(m&mask);
    while(loop--){
	r = rhi/d1*d2;
	rhi = ( (rhi%d1 << 32) | (rlo>>32) );
	rlo = ( (rlo&mask) << 32 );
	if(rhi<r) rhi+=m-r; else rhi-=r;
	if(rhi>m) rhi+=m;
    }
    return rhi>>k;
}

ull ullMultipleMod(ull a,ull b,ull m)
{
    if (a<b) swap(a,b);
    if (a<=2000000000) return a*b%m;
    ull t=0;
    a%=m;
    a%=m;
    for (;a>0;a=a>>3)
    {
	int c=(int)(a&7);
	if (c) t=(t+b*c)%m;
	b=(b<<3)%m;
    }
    return t;
}

// --- Testing Pseudo prime with primes till 50
bool pseudoprime(int64 a, int64 n)
{
    int c=0;
    int64 ans=1;
    int64 p=n-1;
    for (;!(p&1);p>>=1)c++;
    while (p)
    {
	if (p&1) ans=LMOD(ans,a,n);
	a=LMOD(a,a,n);
	p>>=1;
    }
    if (ans==1) return true;
    for (p=0;p<c;p++)
    {
	if (ans==n-1) return true;
	ans=LMOD(ans,ans,n);
    }
    return false;
}
 
bool is_prime(int64 n)
{
    if (n<=1) return false;
    if (n<SMALLN) return _is_prime[n];
    for (int p=2;p<50;p++) if (_is_prime[p] && !pseudoprime(p,n)) return false;
    return true;
}

// -- Done testing pseudo prime


/* (x^k)%m */
ull ullPowMod(ull x, ull k, ull m){
    ull res;
    if(k==0) return 1;
    res = ullPowMod(x,k/2,m);
    res = ullMultipleMod(res,res,m);
    if(k%2) res = ullMultipleMod(res,x,m);
    return res;
}
 
ull unsignedMillerRabinSuspectPow(int a, unsigned k, unsigned n){
    ull p=1; unsigned bit;
    for (bit=0x80000000U;bit;bit>>=1) {
	if(p>1)   p=(p*p)%n;
	if(k&bit) p=(p*a)%n;
    }
    return p;
}
 
int unsignedMillerRabinSuspect(int b, unsigned n){
    unsigned i,t=0,u=n-1; ull now, next;
 
    while(!(u&1)) t++, u>>=1;
    now = unsignedMillerRabinSuspectPow(b, u, n);
 
    for(i=1;i<=t;i++){
	next=(now*now)%n;
	if(next==1 && now!=1 && now!=n-1) return 0;
	now=next;
    }
    return next==1;
}
 
int unsignedMillerRabin(unsigned n){
    if(n<=1)return 0; if(n<=3)return 1; if(!(n&1))return 0;
    if(!unsignedMillerRabinSuspect(2,n)) return 0;
    if(n<=1000000){
	if(!unsignedMillerRabinSuspect(3,n)) return 0;
    } else {
	if(!unsignedMillerRabinSuspect(7,n)) return 0;
	if(!unsignedMillerRabinSuspect(61,n)) return 0;
    }
    return 1;
}
 
ull ullMillerRabinSuspectPow(ull a, ull k, ull n){
    ull p=1, bit;
    for (bit=0x8000000000000000ULL;bit;bit>>=1) {
	if(p>1)   p=ullMultipleMod(p,p,n);
	if(k&bit) p=ullMultipleMod(p,a,n);
    }
    return p;
}
 
int ullMillerRabinSuspect(ull b, ull n){
    ull i, t=0, u=n-1, now, next;
 
    while(!(u&1)) t++, u>>=1;
    now = ullMillerRabinSuspectPow(b, u, n);
 
    for(i=1;i<=t;i++){
	next=ullMultipleMod(now,now,n);
	if(next==1 && now!=1 && now!=n-1) return 0;
	now=next;
    }
    return now==1;
}
 
/* n < 341550071728321ULL */
int ullMillerRabin(ull n){
    int i,lim;
 
    if(n<(1ULL<<32)) return unsignedMillerRabin(n);
    if(!(n&1)) return 0;
  
    if(n < 341550071728321ULL) lim=17; else lim=29;
    if(!ullMillerRabinSuspect(2,n)) return 0;
    for(i=3;i<=lim;i+=2) if(!ullMillerRabinSuspect(i,n)) return 0;
 
    return 1;
}
 





// -- Primality testing till 10^18 simple

bool miller_rabin(uint64_t n)
{
    uint64_t m = n - 1;
    
    int s = 0;
    uint64_t d = m;

    while(d % 2 == 0)
    {
	d /= 2;
	s++;
    }

    for (int i = 0; i < 9; i++)
    {
	if (n < limit[i])
	    return true;

	uint64_t a = primes[i];
	uint64_t x = power(a, d, n);

	if (x == 1 || x == m)
	    continue;

	bool flag = false;
	for (int j = 0; j < (s - 1); j++)
	{
	    x = sqr(x, n);
	    if (x == 1)
		return false;

	    if (x == m)
	    {
		flag = true;
		break;
	    }
	}

	if (!flag)
	    return false;
    }

    return true;
}

bool is_prime(uint64_t n, bool *mark)
{
    if (n < M)
	return (!mark[n]);

    if (n % 2 == 0)
	return false;

    return miller_rabin(n);
}
