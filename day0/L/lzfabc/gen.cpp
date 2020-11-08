#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define li long long
using namespace std;
inline li read(){
	li x = 0;
	int y = 0,c = gc;
	while(c < '0' || c > '9') y = c,c = gc;
	while(c >= '0' && c <= '9') x = x * 10 + c - '0',c = gc;
	return y == '-' ? -x : x;
}
inline void prt(li x){
	if(x >= 10) prt(x / 10);
	pc(x % 10 + '0');
}
inline void print(li x){
	if(x < 0) pc('-'),x = -x;
	prt(x);
}
inline void file(char *s){
	char c[50];
	int d = read();
	//int d = 0;
	sprintf(c,"%s%d.in",s,d);
	//freopen(c,"r",stdin);
	//sprintf(c,"%s.out",s);
	freopen(c,"w",stdout);
}
li s1 = 19260817,s2 = 23333333,s3 = 998244853,srd;
inline li rd(){
	return srd = (srd * s1 + s2 + rand()) % s3;
}
inline void outpai(int paii){
	if(paii <= 27) cout<<(paii - 1) % 9 + 1<<("MPS"[(paii - 1) / 9]);
	else if(paii <= 34) cout<<("ESWNBFZ"[paii - 28]);
	else if(paii == 35) cout<<"DOUBLE";
	else if(paii == 36) cout<<"REVERSE";
	else cout<<"PASS";
	pc('\n');
}
int a[150];
int main(){
	srand(time(0));rd();
	//file("mahjong");
	freopen("mahjong.in","w",stdout);
	int i,j = 0;
	for(i = 1;i <= 37;++i){
		a[++j] = i;a[++j] = i;a[++j] = i;a[++j] = i;
	}
	for(i = 1;i <= 148;++i) swap(a[i],a[rd() % i + 1]);
	for(i = 1;i <= 148;++i) outpai(a[i]);
	return 0;
}
