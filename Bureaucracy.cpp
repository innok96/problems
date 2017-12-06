#include<iostream>
#include<string>
#include<cstdio>
#include<cmath>
#include<sstream>
#include<iomanip>
#include<algorithm>
#include<set>
#include<map>
#include<queue>
#include<iterator>
#include<vector>
using namespace std;
typedef long long ll;
typedef double db;
int n, l, k;
vector<int>week, have, need, used, day;
vector<pair<int, int> >res;
vector<vector<int> >g;
void dfs1(int v){
	used[v]=1;
	for(int i=0; i<g[v].size(); i++){
		int to=g[v][i];
		if(!used[to]&&!have[to]) dfs1(to);
		else if(used[to]==1){
			printf("No Solution");
			exit(0);
		}
	}
	used[v]=2;
}
int dfs(int v){
	int mx=0;
	for(int i=0; i<g[v].size(); i++){
		int to=g[v][i];
		if(!have[to]) mx=max(dfs(to), mx);
		else mx=max(mx, day[to]);
	}
	have[v]=1;
	int d=k, m=mx%l;
	while(m--){
		d++;
		if(d>l) d=1;
	}
	if(week[v]>=d) day[v]=week[v]-d+mx;
	else day[v]=mx+week[v]+l-d;
	res.push_back(make_pair(day[v], v+1));
	return day[v];
}
int main(){
	scanf("%d%d", &n, &l);
	week.resize(n);
	for(int i=0; i<n; i++) scanf("%d", &week[i]);
	g.resize(n);
	used.resize(n);
	day.resize(n);
	have.resize(n);
	need.resize(n);
	for(int i=0; i<n; i++){
		int v;
		scanf("%d", &v);
		while(v){
			g[i].push_back(v-1);
			scanf("%d", &v);
		}
	}
	scanf("%d", &k);
	int v;
	scanf("%d", &v);
	while(v){
		have[v-1]=1;
		scanf("%d", &v);
	}
	scanf("%d", &v);
	while(v){
		need[v-1]=1;
		scanf("%d", &v);
	}
	for(int i=0; i<n; i++)
		if(!used[i]&&!have[i]&&need[i]) dfs1(i);
	for(int i=0; i<n; i++)
		if(!have[i]&&need[i]) dfs(i);
	printf("%d\n", *max_element(day.begin(), day.end()));
	sort(res.begin(), res.end());
	for(int i=0; i<res.size(); i++) printf("%d ", res[i].second);
}