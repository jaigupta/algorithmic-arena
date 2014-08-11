/* Jai Gupta */
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <cstdlib>
#include <algorithm>
#include <list>
#include <deque>
#include <bitset>
#include <cmath>
#include <set>
#include <sstream>

using namespace std;

#define oo 0x7F7F7F7F
#define LET(x,a)     __typeof(a) x(a)
#define EACH(it,v)   for(LET(it,v.begin());it!=v.end();++it)
#define REP(i,n)     for(__typeof(n) i(0); i<n; i++)
#define ALL(x)       (x).begin(), (x).end()
#define gint(t)      scanf("%d", &t);
#define pint(t)      printf("%d\n", t);
#define pb           push_back
#define mp           make_pair
#ifdef JAI_ARENA
#define debug(args...) {cerr<<"> "; dbg,args;cerr<<endl;}
#define debugv(v)      {cerr<<"> "; EACH(it, v) dbg,(*it); cerr<<endl;}
#else
#define debug(args...) {}
#define debugv(x) {}
#endif
typedef long long int   ll;
typedef unsigned long long int ull;
typedef unsigned int    uint;
typedef pair<int, int>  pii;
typedef vector<int>     vi;
typedef vector<vi>      vii;
typedef vector<pii>     vpii;

struct debugger
{
    template<typename T> debugger& operator , (const T& v)
    {
        cerr<<v<<" ";
        return *this;
    }
} dbg;


#define BUF 4096
char ibuf[BUF];
int ipt = BUF;

int readUInt() {
    while (ipt < BUF && ibuf[ipt] < '0') ipt++;
    if (ipt == BUF) {
    fread(ibuf, 1, BUF, stdin);
    ipt = 0;
    while (ipt < BUF && ibuf[ipt] < '0') ipt++;
    }
    int n = 0; char neg = 0;
    if(ipt !=0 && ibuf[ipt-1] == '-') neg = 1;
    while (ipt < BUF && ibuf[ipt] >= '0') n = (n*10)+(ibuf[ipt++]-'0');
    if (ipt == BUF) {
    fread(ibuf, 1, BUF, stdin);
    ipt = 0;
    while (ipt < BUF && ibuf[ipt] >= '0') n = (n*10)+(ibuf[ipt++]-'0');
    }
    return neg?-n:n;
}
int testcase;
void solve() {
    int res = 0;
    for(int i = 1; i<1111; i++) {
        char done[10];
        memset(done, 0, sizeof done);
        int n = i;
        while(n) {
            int r   = n%10;
            if(done[r]) break;
            done[r] = 1;
            n/=10;
        }
        if(!n) res++;
        printf("%d %d\n", i, res);
    }
}
bool input() {
    return true;
}
void preprocess() {

}
int main()
{
    solve();
    return 0;
}
