#include<iostream>
#include<string>
#include<cstring>
#include<set>
#include<cstdio>
#include<map>
#include<ctime>
#include<cmath>
#include<queue>
#include<vector>
#include<bitset>	
#include<stack>
#include<algorithm>
using namespace std;
typedef long long ll;
typedef double db;
typedef pair<ll, ll> P;
struct vert{
	int num, l, h, numroad;
	vert(){}
	vert(int num1, int l1, int h1, int numroad1){num=num1, l=l1, h=h1, numroad=numroad1;}
};
vector<vector<vert> >g;
const int INF=1e9;
int main(){
	int n, m, start, target;
	scanf("%d%d%d%d", &n, &m, &start, &target);
	start--, target--;
	int money, maxtime;
	scanf("%d%d", &money, &maxtime);
	g.resize(100*n);
	for(int i=0; i<m; i++){
		int u, v, type, len, high;
		scanf("%d%d%d%d%d", &u, &v, &type, &len, &high);
		u--, v--;
		if(u==v) continue;
		if(type==0){
			for(int j=0; j<min(n, money+1); j++){
				g[u+j*100].push_back(vert(v+j*100, len, high, i+1));
			}
		}
		else{
			for(int j=0; j<min(n, money+1)-1; j++){
				g[u+j*100].push_back(vert(v+(j+1)*100, len, high, i+1));
			}
		}
	}	
	if (start == target) { printf("0\n0\n"); return 0; };
	//for(int i=0; i<100*n; i++) random_shuffle(g[i].begin(), g[i].end());
	int l=0, r=1e6+20;
	int ans[10111], it1=0, megaflag=0;
	P resp[10000];
	while(l<r-1){
		int mid=(l+r)/2;
		int d[10011];
		for(int i=0; i<10010; i++) d[i]=INT_MAX;
		set<P>q;
		P p[10000];
		d[start]=0;
		q.insert(P(d[start], start));
		p[start].first=-1;
		int flag=-1;
		while(!q.empty()){
			int v=(*q.begin()).second;
			q.erase(q.begin());
			for(int i=0; i<g[v].size(); i++){
				int to=g[v][i].num, len=g[v][i].l;
				if(g[v][i].h>mid) continue;
				if(d[v]+len<d[to]){
					q.erase(P(d[to], to));
					d[to]=d[v]+len;
					p[to]=P(v, g[v][i].numroad);
					if(to/100<=money&&(to%100)==target&&d[to]<=maxtime){
						flag=to;
						break;
					}
					q.insert(P(d[to], to));
				}
			}
			if(flag!=-1) break;
		}
		int f=0;
		if(flag!=-1){
			megaflag=flag;
			f=1;
			for(int i=0; i<10000; i++) resp[i]=p[i];
		}
		if(f){
			r=mid;
		}
		else l=mid;
	}
	if(megaflag!=-1){
		int i=megaflag;
		it1=0;
		while(resp[i].first!=-1){
			if(i==resp[i].first) break;
			if(resp[i].first==-1) break;
			ans[it1]=resp[i].second;
			it1++;
			i=resp[i].first;
		}
	}
	if(l>1e6) printf("-1");
	else{
		printf("%d\n%d\n", r, it1);
		for(int i=it1-1; i>=0; i--) printf("%d ", ans[i]);
	}
}