#include<iostream>
#include<string>
#include<cstring>
#include<set>
#include<cstdio>
#include<map>
#include<unordered_map>
#include<ctime>
#include<deque>
#include<cmath>
#include<queue>
#include<vector>
#include<bitset>
#include<stack>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<int, int>P;
struct state{
    int len, link;
    map<char, int>next;
};
const int NMAX=100111;
state st[2*NMAX];
vector<int>g[2*NMAX];
int sz=1, last=0;
void build(char c){
    int cur=sz++;
    st[cur].len=st[last].len+1;
    int p=last;
    for(p; p!=-1&&!st[p].next.count(c); p=st[p].link)
        st[p].next[c]=cur;
    if(p==-1)
        st[cur].link=0;
    else{
        int q=st[p].next[c];
        if(st[p].len+1==st[q].len)
            st[cur].link=q;
        else{
            int clone=sz++;
            st[clone].next=st[q].next;
            st[clone].len=st[p].len+1;
            st[clone].link=st[q].link;
            st[q].link=st[cur].link=clone;
            for(p; p!=-1&&st[p].next[c]==q; p=st[p].link)
                st[p].next[c]=clone;
        }
    }
    last=cur;
}

struct V {
    int in, out, v;
    V(){}
    V(int in, int out, int v) : in(in), out(out), v(v) {}
};

char used[2*NMAX];
int timer=0, tin[2*NMAX], tout[2*NMAX], high=0, HMAX=0;
vector <V> h[2*NMAX];

void dfs (int v) {
    used[v]=1;
    high++;
    HMAX=max(HMAX, high);
    tin[v]=timer++;
    for (int i=0; i<g[v].size(); i++)
        if (!used[g[v][i]]) 
            dfs(g[v][i]);
    tout[v]=timer++;
    h[--high].push_back(V(tin[v], tout[v], v));
}

bool check (int a, int b, int H, int & ans) {
    if (tin[a]>tin[b]) swap(a, b);
    int l=0, r=h[H].size()-1;
    while (l<r) {
        int m=(l+r)/2;
        if (h[H][m].out<tin[a]) l=m+1;
        else r=m;           
    }
    if (h[H][l].in<=tin[a] && tout[b]<=h[H][l].out) {ans=h[H][l].v; return 1;}
    else return 0;
}

int lca (int a, int b) {
    if (a==b) return a;
    int ans=0;
    int l=0, r=HMAX-1;
    while (l<r) {
        int m=(l+r)/2;
        if (check(a, b, m, ans)) l=m+1; 
        else r=m;
    }
    return ans;
}

int main(){
    freopen("substrcmp.in", "r", stdin); freopen("substrcmp.out", "w", stdout);
    st[0].link=-1;
    st[0].len=0;
    char s[NMAX];
    int pos[NMAX];
    scanf("%s", &s);
    int n=strlen(s);
    for(int i=0; i<n; i++){
        build(s[i]);
        pos[i]=last;
    }
    for(int i=1; i<sz; i++){
        int u=st[i].link;
        g[u].push_back(i);
        g[i].push_back(u);
    }
    dfs(0);
    int m;
    scanf("%d", &m);
    while(m--){
        int l1, r1, l2, r2;
        scanf("%d%d%d%d", &l1, &r1, &l2, &r2);
        l1--, r1--, l2--, r2--;
        if(r1-l1!=r2-l2){
            puts("No");
            continue;
        }
        int len1=r1-l1+1;
        int t1=pos[r1], t2=pos[r2];
        printf("%s\n", st[lca(t1, t2)].len>=len1?"Yes":"No");
    }
}