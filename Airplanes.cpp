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
struct pt{
	db x, y, z;
	pt(){}
	pt(db x1, db y1, db z1){x=x1, y=y1, z=z1;}
	pt operator^ (pt p){return pt(y*p.z-p.y*z, -(x*p.z-p.x*z), x*p.y-p.x*y);}
	db operator* (pt p) {return x*p.x+y*p.y+z*p.z;}
	db mod(){return sqrt(x*x+y*y+z*z);}
	void in(){scanf("%lf%lf%lf", &x, &y, &z);}
	void out(){printf("%lf %lf %lf", x, y, z);}
};
int main(){
	int n, res=0;
	scanf("%d", &n);
	vector<pt>a(n), used;
	for(int i=0; i<n; i++) a[i].in();
	for(int i=0; i<n-1; i++){
		for(int j=i+1; j<n; j++){
			pt v=a[i]^a[j];
			int f=1;
			for(int k=0; k<used.size(); k++){
				if((used[k]^v).mod()==0){
					f=0;
					break;
				}
			}
			if(f){
				if(v.mod()) used.push_back(v);
				int kol1=0, kol2=0;
				vector<pt>kol;
				for(int k=0; k<n; k++){
					if(a[k]*v<0) kol1++;
					else if(a[k]*v>0) kol2++;
					else kol.push_back(a[k]);
				}
				int mx=0;
				for(int k=0; k<kol.size(); k++){
					int c1=0, c2=0, flag=0;
					pt hp=v^kol[k];
					for(int q=0; q<kol.size(); q++){
						if(hp*kol[q]>0) c1++;
						else if(hp*kol[q]<0) c2++;
						else flag=1;
					}
					mx=max(mx, max(c1, c2)+flag);
				}
				res=max(res, max(kol1, kol2)+mx);
			}
		}
	}
	printf("%d", max(1, res));
}