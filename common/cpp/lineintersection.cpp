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
#include <functional>
#include <set>
#include <sstream>

using namespace std;

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define MAX(a,b)   (((a)>(b))?(a):(b))
#define MIN(a,b)   (((a)<(b))?(a):(b))
#define CMAX(a,b)  if((a)<(b)) a=b
#define CMIN(a,b)  if((a)>(b)) a=b
#define FOR(i,a,b)   for(i=a; i<b; i++)
#define REVI(i,a,b)  for(int i= a ; i >= b ; --i)
#define LET(x,a)     __typeof(a) x(a)
#define IFOR(i,a,b)  for(LET(i,a);i!=(b);++i)
#define DFOR(i,a,b)  for(LET(i,a);i<(b);++i)
#define EACH(it,v)   IFOR(it,v.begin(),v.end())
#define SWAP(a,b,t)  t=a,a=b,b=t
#define REP(i,n)     for(__typeof(n) i(0); i<n; i++)
#define gint(t)      scanf("%d", &t);
#define pint(t)      printf("%d\n", t);
#define pb           push_back
#define ALL(x)       (x).begin(), (x).end()

#ifdef JAI_ARENA
#define debug(args...) {dbg,args; cerr<<endl;}
#define dline cerr<<endl
#else
#define debug(args...) {};
#endif

typedef long long int   ll;
typedef unsigned long long int ull;
typedef unsigned int    uint;
typedef pair<int, int>  pii;
typedef vector<int>     vi;
typedef vector<vi>      vii;
typedef vector<pii>     vpii;
#define PI 3.14159265359
#define HPI 1.57079632679
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

const double EPS = 1E-9;
double l,r;
struct pt {
    double x, y;
    pt(double _x, double _y):x(_x),y(_y) {}
};
typedef pair<double, double> pdd;
struct seg {
    pt p, q;
    double theta;
    int id;
    seg(double x1, double y1, double x2, double y2, double theta, int _id) :
	p(pt(x1, y1)), q(pt(x2, y2)), theta(theta), id(_id) {}
    double get_y (double x) const {
	if (abs (p.x - q.x) < EPS)  return p.y;
	return p.y + theta*(x - p.x);
    }
};

inline bool intersect1d (double l1, double r1, double l2, double r2) {
    if (l1 > r1)  swap (l1, r1);
    if (l2 > r2)  swap (l2, r2);
    return max (l1, l2) <= min (r1, r2) + EPS;
}
/** check if the triangle formed by the three points is positive or negative
  * 0  = Zero
  * 1  = Positive
  * -1 = Negative
  */
inline int vec (const pt & a, const pt & b, const pt & c) {
    double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return abs(s)<EPS ? 0 : s>0 ? +1 : -1;
}
/** Check if two given segments intersect
  */
bool intersect (const seg & a, const seg & b) {
    return intersect1d (a.p.x, a.q.x, b.p.x, b.q.x)
	&& intersect1d (a.p.y, a.q.y, b.p.y, b.q.y)
	&& vec (a.p, a.q, b.p) * vec (a.p, a.q, b.q) <= 0
	&& vec (b.p, b.q, a.p) * vec (b.p, b.q, a.q) <= 0;
}
bool inrange(const seg &a, const seg &b, double x) {
    if(x<=a.p.x+EPS || x>=a.q.x-EPS) return false;
    if(x<=b.p.x+EPS || x>=b.q.x-EPS) return false;
    return true;
}
/** Get intersection point of two segments
  */
pair<double, double> inspoint(const seg &a, const seg &b) {
    double xa = (a.p.y - b.p.y - a.theta * a.p.x + b.theta * b.p.x)/(b.theta - a.theta);
    double ya = a.p.y + a.theta*(xa-a.p.x);
    return pair<double, double>(xa, ya);
}
/** get vertical cut of a segment a given x
 */
double getverticalcut(const seg &a, double x) {
    return a.p.y + a.theta*(x-a.p.x);
}
double cur_x = 0;
/** Get the ordering of the segments after the cur_x value
  * choose the extra x needed for arrangement accordingly.
  */
bool operator< (const seg & a, const seg & b) {
    return a.get_y(cur_x+1e-8) < b.get_y(cur_x+1e-8);
}
struct event {
    double x, y;
    int tp, id, id2; /* type of event, id of first and second event +1=start, -1=end, 0=intersect*/
    
    event() { }
    event (double x, double y, int tp, int id, int id2 = 0)
	: x(x), y(y), tp(tp), id(id), id2(id2)
	{ }
 
    bool operator< (const event & e) const {
	if (abs (x - e.x) > EPS)  return x > e.x; // lower x first
	return tp > e.tp;                         // lower tp value first
    }
};
 
multiset<seg> s;
vector < set<seg>::iterator > where;
priority_queue<event> e;
inline set<seg>::iterator prev (set<seg>::iterator it) {
    return it == s.begin() ? s.end() : --it;
}
 
inline set<seg>::iterator next (set<seg>::iterator it) {
    return ++it;
}

void putsegment(const int id, const vector<seg> &a)
{
    pdd tmpp;
    set<seg>::iterator
	nxt = s.lower_bound (a[id]),
	prv = prev (nxt);
    if (nxt != s.end() && abs(nxt->theta-a[id].theta) > EPS)
    {
    	tmpp = inspoint(*nxt, a[id]);
    	//debug("pushing3", nxt->id, id, tmpp.first, nxt->p.x, nxt->q.x);
    	if(inrange(*nxt, a[id], tmpp.first) && tmpp.first > cur_x+EPS) 
    	    e.push(event(tmpp.first, tmpp.second, 0, nxt->id, id));
    }
    if (prv != s.end() && abs(prv->theta-a[id].theta) > EPS)
    {
    	tmpp = inspoint(*prv, a[id]);
    	//debug("pushing2", id, prv->id, tmpp.first, prv->p.x, prv->q.x);
    	if(inrange(*prv, a[id], tmpp.first) && tmpp.first > cur_x+EPS) 
    	    e.push(event(tmpp.first, tmpp.second, 0, prv->id, id));
    }
    //debug("pushin", id);
    where[id] = s.insert (nxt, a[id]);
}
void delsegment(const int id, const vector<seg> &a)
{
    pdd tmpp;
    set<seg>::iterator
	nxt = next (where[id]),
	prv = prev (where[id]);
    if (nxt != s.end() && prv != s.end() && abs(nxt->theta-prv->theta) > EPS)
    {
    	tmpp = inspoint(*prv, a[id]);
    	//debug("pushing1", nxt->id, prv->id, tmpp.first, nxt->p.x, nxt->q.x);
    	if(inrange(*nxt, *prv, tmpp.first) && tmpp.first > cur_x) e.push(event(tmpp.first, tmpp.second, 0, nxt->id, prv->id));
    }
    //debug("removing", id);
    s.erase (where[id]);
}
double hl, hr;
void checkh(const seg & sg) {
    if(sg.p.x<=l+EPS && sg.q.x>=l-EPS) {
    	double yl = getverticalcut(sg, l);
    	if(yl > hl) hl = yl;
    }
    if(sg.p.x<=r+EPS && sg.q.x>=r-EPS) {
    	double yr = getverticalcut(sg, r);
    	if(yr > hr) hr = yr;
    }
}
double solve (const vector<seg> & a) {
    double minh    = 10000;
    double lastx   = -10000;
    double lastmax = 1000;
    hr = hl = 0;
    s.clear();
    e=priority_queue<event>();
    int n = (int) a.size();
    for (int i=0; i<n; ++i) {
    	e.push(event (a[i].p.x, a[i].p.y, +1, i));
    	e.push(event (a[i].q.x, a[i].q.y, -1, i));
    	checkh(a[i]);
    	//debug("hl", hl, "hr", hr);
    }
    minh = min(hl, hr);
    where.resize (a.size());
   
    while (e.size()) {
	int id   = e.top().id;
	int id2  = e.top().id2;
	double x = e.top().x;
	double y = e.top().y;
	cur_x = x;
	if(cur_x > r) break;
	int tp   = e.top().tp;
	e.pop();
	debug(x, y, id, id2, tp);
	if(tp == 0 && cur_x >= l-EPS && cur_x<=r+EPS) {
	    //debug(x, y, "minh");
	    if(abs(lastx-cur_x)<EPS){
            if(lastmax < y) { lastmax = y;}
	    }else if(tp == 0){
    		if(minh > lastmax) minh = lastmax;
    		set<seg>::iterator it = s.end(); it--;
    		double my = getverticalcut(*it, cur_x);
    		//debug("new ", it->id, my);
    		lastx = cur_x; lastmax = max(y, my);
	    }
	    debug(minh, lastmax);
	}
	if (tp == +1) {
	    putsegment(id, a);
	}
	else if(tp == -1){
	    delsegment(id, a);
	}else {
	    delsegment(id, a);
	    delsegment(id2, a);
	    putsegment(id, a);
	    putsegment(id2, a);
	}
	
    }
    if(minh > lastmax) minh = lastmax;
    return minh;
}
#define gd(x) scanf("%lf", &x);
int main()
{
    int n; gint(n);
    n = min(n, 10);
    gd(l); gd(r);
    vector<seg> a;
    REP(ni, n) {
	double x, y, th; gd(x); gd(y); gd(th); th = (th*PI)/180.0;
	double dx = y*tan(th);
	debug("line", x-dx, x, x+dx);
	a.push_back(seg(x-dx, 0, x, y, tan(HPI-th), 2*ni));
	a.push_back(seg(x, y, x+dx, 0, -tan(HPI-th), 2*ni+1));
    }
    double minh = solve(a);
    printf("%.9lf\n", minh);
}
