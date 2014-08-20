#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#ifndef ECLIPSE
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
#include "../../common/cpp/debugger.h"
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
void work()
{
	string s; cin>>s;
	int last =  s.length()-1;
	int pos = last/2;
	while(pos >=0 && s[pos] == s[last-pos] && s[pos] == '9') {
		pos--;
	}
	if (pos < 0) {
		cout<<'1';
		REP(i, s.length()-1) {cout<<'0';}
		cout<<'1'<<endl;
		return;
	}
	if (s[pos] <= s[last-pos]) {
		s[pos]++;
		pos++;
		while(pos <= last/2) {s[pos++] = '0';}
	}
	pos = last / 2;
	while(pos >=0) {
		s[last-pos] = s[pos];
		pos--;
	}
	cout<<s<<endl;
}
int main()
{
#ifdef JAI_ARENA
	D.init();
#endif
	int t=100;
	pint(t);
	while(t--) {
		pint((int)(rand()%1000000));
	}
#ifdef JAI_ARENA
	D.end();
#endif
    return 0;
}
#endif
