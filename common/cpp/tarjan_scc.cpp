#define MAX 100010
//vector < vector < int > > arr (MAX);
//vector < set < int  > >out (MAX);
vector < vector < int >>arr (MAX);
vector < set < int >>out (MAX);
int p[MAX], r[MAX], inv[MAX];
int num[MAX], low[MAX], visit[MAX], top = -1, st[MAX], ind[MAX], visit1[MAX];
int tme;
int N, E;

/* START OF UNION FIND */
inline void
makeset (int x)
{
    p[x] = x;
    r[x] = 0;
}

inline int
findp (int x)
{
    if (x == p[x])
	return x;
    return p[x] = findp (p[x]);
}


inline void
union_set (int a, int b)
{

    a = findp (a);
    b = findp (b);

    if (a == b)
	return;

    if (r[a] > r[b])
	p[b] = a;
    else
    {
	p[a] = b;
	if (r[a] == r[b])
	    r[b]++;
    }
}

/*END OF UNION _FIND */

/* FORM THE SCC FROM TARJAN ALGORITHM */
void
dfs (int x)
{
    //printf("Going into x=%d\n",x);
    visit[x] = 1;
    low[x] = num[x] = ++tme;
    st[++top] = x;
    int i, k;
    for (i = 0; i < arr[x].size (); i++)
    {
	k = arr[x][i];

	// THIS IS SO THAT IF WE VISITED SOME VERTEX Z prior to THIS VERTEX X  just becaue Z is number earlier , the num of it is not valid nor is the low

	if (inv[k])   continue;

	if (!visit[k])
	{
	    dfs (k);
	    low[x] = min (low[x], low[k]);
	}
	else
	    low[x] = min (low[x], num[k]);
    }
    if (low[x] == num[x])
    {
	makeset (x);

	//     printf ("connected\n");
      do
      {
//        printf ("%d,", st[top]);
	  makeset (st[top]);
	  union_set (st[top], x);
	  inv[st[top]] = 1;
//        scc[x].insert(st[top]);
      }
      while (st[top--] != x);
//      printf ("\n");
    }
}

/* GET THE ACYCLIC DAG AND FIND THE NUMBER OF DISJOINT COMPONENTS */
void
dfs1 (int x)
{

    if (visit1[x])
	return;
    visit1[x] = 1;
    set < int >::iterator it;
    for (it = out[x].begin (); it != out[x].end (); it++)
    {
	dfs1 (*it);
    }
}

int
main ()
{
    // POPULATE GRAPH 
    tme = 0;
    for (i = 0; i < E; i++)
    {
	scanf (" %d %d", &x, &y);
	arr[x].push_back (y);
	ind[y]++;
    }
    int total = 0;
    // CHECK FOR VERTICES WITH INDEGREE 0 and RUN DFS
    for (i = 1; i <= N; i++)
    {
	if (!visit[i] && (ind[i] == 0))
	{
	    top = -1;
	    dfs (i);
	}
    }

// IF ALL THE VERTICES ARE PART OF A SCC
    for (i = 1; i <= N; i++)
    {
	if (!visit[i])
	{
	    top = -1;
	    dfs (i);
	}
    }



    memset (ind, 0, sizeof (ind));
    int j, p = 0;
// GET THE SCC SET, TRY TO BUILD GRAPH FROM CONDENSED VERTEX TO OTHER CONDENSED VERTICES
    for (i = 1; i <= N; i++)
    {
	for (p = 0; p < arr[i].size (); p++)
	{
	    j = arr[i][p];
	    if (findp (i) != findp (j))
	    {
		if (out[findp (i)].count (findp (j)) == 0)
		{
//                   printf("edge from %d to %d\n",findp(i),findp(j));
		    out[findp (i)].insert (findp (j));
		    ind[findp (j)]++;
		}
	    }
	}
    }

/* CHECK IF THIS IS THE PARENT OF THE SCC AND ITS INDEGREE IS 0 , in a condensed DAG it is always possible 
i think  The call to visit1 is superfluous
*/
    for (i = 1; i <= N; i++)
    {
	if ((findp (i) == i) && (visit1[i] == 0) && (ind[i] == 0))
	{
//            printf("#%d,",i);
	    dfs1 (i);
	    total++;
	}
    }

    printf ("%d\n", total);
}

return 0;
}
