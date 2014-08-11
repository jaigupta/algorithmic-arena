#define LET(x,a)     __typeof(a) x(a)
#define EACH(it,v)   for(LET(it,v.begin());it!=v.end();++it)
#define debug(args...) {cerr<<"> "; D,args;cerr<<endl;}
#define debugv(v) EACH(it, v) debug(*it);
#include <iostream>
using namespace std;
class Debugger {
public:
	void init() {
		*this,"Initializing debugger...\n";
	}
	void end() {
		*this,"Exiting debugger...\n";
	}
	template<typename T> Debugger& operator , (const T& v)
	{
	    cerr<<v<<" ";
	    return *this;
	}
} D;
