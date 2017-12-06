#include<iostream>
#include<string>
#include<cstring>
#include<set>
#include<cstdio>
#include<map>
//#include<unordered_map>
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
typedef pair<int, int> P;
struct state{
	int link, len;
	map<char, int>next;
};
int sz=1, last=0;
const int NMAX=90999;
state st[2*NMAX];
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
int dp[2*NMAX];
int fun(int t){
	if(dp[t]) return dp[t];
	int kol=1;
	for(map<char, int>::iterator it=st[t].next.begin(); it!=st[t].next.end(); it++)
		kol+=fun(it->second);
	return dp[t]=kol;
}
int main(){
	st[0].link=-1;
	st[0].len=0;
	char s[NMAX];
	cin.getline(s, sizeof(s));
	int n=strlen(s);
	for(int i=0; i<n; i++)
		build(s[i]);
	fun(0);
	int q;
	scanf("%d", &q);
	dp[0]--;
	while(q--){
		int k;
		scanf("%d", &k);
		int t=0;
		while(k){
			for(map<char, int>::iterator it=st[t].next.begin(); it!=st[t].next.end(); it++){
				if(k<=dp[it->second]){
					t=it->second;
					printf("%c", it->first);
					k--;
					break;
				}
				k-=dp[it->second];
			}
		}
		puts("");
	}
}