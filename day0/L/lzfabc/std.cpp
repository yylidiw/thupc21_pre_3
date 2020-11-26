#include<bits/stdc++.h>
#define gc getchar()
#define pc putchar
#define pii pair<int,int>
#define fi first
#define se second
#define mp make_pair
using namespace std;
int pai[200],head = 1,fx = 1;
struct player{
	int a[20],sum;
	bool pass;
}p[4]; 
inline void draw(){
	cout<<"DRAW"<<endl;
	exit(0);
}
inline void win(int x){
	pc(x + 'A');pc(' ');cout<<"WIN"<<endl;
	exit(0);
} 
inline void hupai(int x){
	pc(x + 'A');cout<<" RON"<<endl;
	win(x);
}
inline void zimo(int x){
	pc(x + 'A');cout<<" SELFDRAWN"<<endl;
	win(x);
}
#define nxt(x) (((x) + fx + 4) % 4)
inline void outpai(int paii){
	if(paii <= 27) cout<<(paii - 1) % 9 + 1<<("MPS"[(paii - 1) / 9]);
	else if(paii <= 34) cout<<("ESWNBFZ"[paii - 28]);
	else if(paii == 35) cout<<"DOUBLE";
	else if(paii == 36) cout<<"REVERSE";
	else cout<<"PASS";
}
inline void in(int x,int paii){
	pc(x + 'A');cout<<" IN ";
	outpai(paii);pc('\n');
}
inline void out(int x,int paii,int fg = -1){
	pc(x + 'A');cout<<" OUT ";
	outpai(paii);
	if(fg >= 0) pc(' '),pc(fg + 'A');
	pc('\n');
}
inline void outchi(int x,int paii){
	pc(x + 'A');cout<<" CHOW ";
	outpai(paii);pc(' ');outpai(paii + 1);pc(' ');outpai(paii + 2);pc('\n');
}
inline void outpeng(int x,int paii){
	pc(x + 'A');cout<<" PONG ";
	outpai(paii);pc(' ');outpai(paii);pc(' ');outpai(paii);pc('\n');
}
inline void mopai(int x){
	if(head > 148) draw();
	p[x].a[++p[x].sum] = pai[head++];
	in(x,p[x].a[p[x].sum]);
	sort(p[x].a + 1,p[x].a + p[x].sum + 1);
}
inline void chup(int x,int chu){
	int chid;
	for(chid = 1;chid <= p[x].sum;++chid) if(chu == p[x].a[chid]) break;
	swap(p[x].a[chid],p[x].a[p[x].sum]);
	--p[x].sum;
	sort(p[x].a + 1,p[x].a + p[x].sum + 1);
	out(x,chu);
}
int sl[40],dp[40][5][2][3][3],zy[40][5][2][3][3];
#define zhuanyi(a,b,x,y) if((x) < (a) || ((x) == (a) && (y) > (b))) (a) = (x),(b) = (y)
pii work(int x){
	memset(dp,0x3f,sizeof(dp));memset(zy,-1,sizeof(zy));
	dp[0][0][0][0][0] = 0;
	register int i,j,k,l,g,q,nx,ny,r;
	for(i = 0;i < 34;++i){
		for(j = 0;j <= x;++j){
			for(k = 0;k <= 1;++k){
				for(l = 0;l <= 2 && l + j <= x;++l){
					for(g = 0;g <= 2 && g + l + j <= x;++g) if(dp[i][j][k][l][g] < 15){
						for(q = l + g;q <= 4;++q){
							nx = dp[i][j][k][l][g] + max(0,q - sl[i + 1]);
							ny = (sl[i + 1] > q ? i + 1 : zy[i][j][k][l][g]);
							r = q - l - g;
							if(r >= 3 && j + l + 1 <= x) zhuanyi(dp[i + 1][j + l + 1][k][g][r - 3],zy[i + 1][j + l + 1][k][g][r - 3],nx,ny);
							if(r >= 2 && !k) zhuanyi(dp[i + 1][j + l][k + 1][g][r - 2],zy[i + 1][j + l][k + 1][g][r - 2],nx,ny);
							if(r <= 2) zhuanyi(dp[i + 1][j + l][k][g][r],zy[i + 1][j + l][k][g][r],nx,ny);
						}
						if(i % 9 == 0 || i >= 27) break; 
					}
					if(i % 9 == 0 || i >= 27) break; 
				}
			}
		}
	}
	return mp(dp[34][x][1][0][0],zy[34][x][1][0][0]);
}
int check(int x){
	memset(sl,0,sizeof(sl));
	for(int i = 1;i <= p[x].sum;++i) if(p[x].a[i] <= 34) ++sl[p[x].a[i]];
	pii as = work(4 - (14 - p[x].sum) / 3);
	return as.se;
}
inline bool ts(int x){
	for(int i = 1;i <= p[x].sum;++i) if(p[x].a[i] > 34) return 1;
	return 0;
}
void checkhu(int x,int chu){
	for(int i = nxt(x);i != x;i = nxt(i)) if(!ts(i)){
		p[i].a[++p[i].sum] = chu;
		if(check(i) == -1) hupai(i);
		--p[i].sum;
	}
}
bool chkpeng(int x,int chu){
	memset(sl,0,sizeof(sl));
	for(int i = 1;i <= p[x].sum;++i) ++sl[p[x].a[i]];
	int lst = work(4 - (14 - p[x].sum) / 3).fi;
	if(sl[chu] >= 2){
		sl[chu] -= 2;
		if(lst > work(3 - (14 - p[x].sum) / 3).fi){
			outpeng(x,chu);
			p[x].sum = 0;
			for(int i = 1;i <= 37;++i){
				while(sl[i]) p[x].a[++p[x].sum] = i,--sl[i];
			}
			return 1;
		}
	}
	return 0;
} 
int checkpeng(int chu){
	for(int x = 0;x < 4;++x) if(chkpeng(x,chu)) return x;
	return -1;
}
bool checkchi(int x,int chu){
	if(chu > 27) return 0;
	memset(sl,0,sizeof(sl));
	for(int i = 1;i <= p[x].sum;++i) ++sl[p[x].a[i]];
	int lst = work(4 - (14 - p[x].sum) / 3).fi;
	if(chu % 9 != 8 && chu % 9 != 0 && sl[chu + 1] && sl[chu + 2]){
		--sl[chu + 1];--sl[chu + 2];
		if(lst > work(3 - (14 - p[x].sum) / 3).fi){
			outchi(x,chu);
			p[x].sum = 0;
			for(int i = 1;i <= 37;++i){
				while(sl[i]) p[x].a[++p[x].sum] = i,--sl[i];
			}
			return 1;
		}
		++sl[chu + 1];++sl[chu + 2];
	}
	if(chu % 9 != 1 && chu % 9 != 0 && sl[chu - 1] && sl[chu + 1]){
		--sl[chu - 1];--sl[chu + 1];
		if(lst > work(3 - (14 - p[x].sum) / 3).fi){
			outchi(x,chu - 1);
			p[x].sum = 0;
			for(int i = 1;i <= 37;++i){
				while(sl[i]) p[x].a[++p[x].sum] = i,--sl[i];
			}
			return 1;
		}
		++sl[chu - 1];++sl[chu + 1];
	}
	if(chu % 9 != 1 && chu % 9 != 2 && sl[chu - 2] && sl[chu - 1]){
		--sl[chu - 2];--sl[chu - 1];
		if(lst > work(3 - (14 - p[x].sum) / 3).fi){
			outchi(x,chu - 2);
			p[x].sum = 0;
			for(int i = 1;i <= 37;++i){
				while(sl[i]) p[x].a[++p[x].sum] = i,--sl[i];
			}
			return 1;
		}
		++sl[chu - 2];++sl[chu - 1];
	}
	return 0;
}
int chupai(int x){
	if(p[x].a[p[x].sum] == 37){
		--p[x].sum;p[nxt(x)].pass = 1;
		out(x,37,nxt(x));
		return nxt(x);
	}
	if(p[x].a[p[x].sum] == 36){
		--p[x].sum;
		fx *= -1;
		out(x,36);
		return nxt(x);
	}
	if(p[x].a[p[x].sum] == 35){
		--p[x].sum;
		out(x,35);
		mopai(x);
		return chupai(x);
	}
	int chu = check(x);
	if(chu == -1) zimo(x);
	chup(x,chu);
	checkhu(x,chu);
	int px = checkpeng(chu);
	if(px >= 0) return chupai(px);
	if(checkchi(nxt(x),chu)) return chupai(nxt(x));
	return nxt(x);
}
int play(int x){
	if(p[x].pass){
		p[x].pass = 0;
		return nxt(x);
	}
	mopai(x);
	return chupai(x);
}
int main(){
	int i,j,l;
	string st;
	for(i = 1;i <= 148;++i){
		cin>>st;
		if(st[0] >= '1' && st[0] <= '9'){
			l = st[0] - '0';
			switch(st[1]){
				case 'M' : pai[i] = l;break;
				case 'P' : pai[i] = l + 9;break;
				case 'S' : pai[i] = l + 18;break;
			}
		}
		else{
			switch(st[0]){
				case 'E' : pai[i] = 28;break;
				case 'S' : pai[i] = 29;break;
				case 'W' : pai[i] = 30;break;
				case 'N' : pai[i] = 31;break;
				case 'B' : pai[i] = 32;break;
				case 'F' : pai[i] = 33;break;
				case 'Z' : pai[i] = 34;break;
				case 'D' : pai[i] = 35;break;
				case 'R' : pai[i] = 36;break;
				case 'P' : pai[i] = 37;break;
			}
		}
	}
	for(i = 1;i <= 13;++i){
		for(j = 0;j < 4;++j) mopai(j);
	}
	int nw = 0;
	while(1) nw = play(nw);
	return 0;
}
