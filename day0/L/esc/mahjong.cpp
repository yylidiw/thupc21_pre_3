#include<bits/stdc++.h>
#define dmax(a,b) ((a)>(b)?(a):(b))
std::map<std::string,int> dec;
const int T=37;
typedef std::vector<int> arr;
std::string name[40];
#define crd(x) name[x].c_str()
int cmin(int &a,int b)
{
	return a>b?a=b,1:0;
}

struct Decinit
{
	Decinit()
	{
		int no=0;
		for(int i=1;i<=9;++i)
			dec[std::to_string(i)+"M"]=++no;
		for(int i=1;i<=9;++i)
			dec[std::to_string(i)+"P"]=++no;
		for(int i=1;i<=9;++i)
			dec[std::to_string(i)+"S"]=++no;
		const std::string card[10]={"E","S","W","N","B","F","Z","DOUBLE","REVERSE","PASS"};
		for(std::string s:card)
			dec[s]=++no;
		for(auto i=dec.begin();i!=dec.end();++i)
			name[i->second]=i->first;
	}
}DECINIT;

struct hand
{
	arr cnt;
	hand(){cnt.resize(40);}
	void print()
	{
		for(int i=1;i<=T;++i)
			for(int j=1;j<=cnt[i];++j)
				printf("%s ",crd(i));
		puts("");
	}
	int dis(const arr &d,int add=0)
	{
		arr c=cnt;
		int tot=0;
		if(add)
			for(int i:d)++c[i];
		else
			for(int i:d)--c[i];
		for(int i:c)tot+=i;
		tot/=3;
		int f[3][3][5][2];
		memset(f,63,sizeof(f));
		f[0][0][0][0]=0;
		for(int i=0;i<3;++i)
			for(int j=i*9+1;j<=i*9+9;++j)
			{
				int g[3][3][5][2];
				memset(g,63,sizeof(g));
				for(int x=0;x<=2;++x)
					for(int y=0;y<=2;++y)
						for(int z=0;z<=4;++z)
							for(int w=0;w<=1;++w)
								if(f[x][y][z][w]<100)
								{
									int F=f[x][y][z][w];
									for(int k=x+y;k<=4;++k)
									{
										int d=k-x-y;
										int cs=dmax(0,k-c[j]);
										if(d>=2&&!w&&d-2+z<=tot)
											cmin(g[y][d-2][z+d-2][1],F+cs);
										if(d>=3&&z+d-3<tot)
											cmin(g[y][d-3][z+d-3+1][w],F+cs);
										if(d<3&&z+d<=tot)
											cmin(g[y][d][z+d][w],F+cs);
									}
								}
				if(j==i*9+9)
				{
					memset(f,63,sizeof(f));
					for(int z=0;z<=tot;++z)
						for(int w=0;w<=1;++w)
							f[0][0][z][w]=g[0][0][z][w];
				}
				else memcpy(f,g,sizeof(g));
			}
		int (*F)[2]=f[0][0];
		for(int i=28;i<=T-3;++i)
			for(int z=tot;z>=0;--z)
				for(int w=1;w>=0;--w)
					if(F[z][w]<100)
					{
						int c2=dmax(0,2-c[i]);
						int c3=dmax(0,3-c[i]);
						if(!w)cmin(F[z][1],F[z][w]+c2);
						if(z<tot)cmin(F[z+1][w],F[z][w]+c3);
					}
		return F[tot][1];
	}
}pl[4];

int dir=1;
int cur=0;
int deck[150];
int now=1;
const int N=148;

int main()
{
	char s[12];
	for(int i=1;i<=N;++i)
	{
		scanf("%s",s);
		deck[i]=dec[s];
	}
	for(int i=1;i<=13;++i)
		for(int j=0;j<=3;++j)
			pl[j].cnt[deck[now++]]++;

	while(1)
	{
		if(now>N)
		{
			puts("DRAW");
			break;
		}
		printf("%c IN %s\n",'A'+cur,crd(deck[now]));
		pl[cur].cnt[deck[now++]]++;
		if(pl[cur].dis({})==0)
		{
			printf("%c SELFDRAWN\n",'A'+cur);
			printf("%c WIN\n",'A'+cur);
			return 0;
		}
		int min,play,next;
		skip:;
		min=333,play;
		for(int i=T;i;--i)
			if(pl[cur].cnt[i])
				if(cmin(min,pl[cur].dis({i})))play=i;
		pl[cur].cnt[play]--;
		next=cur+dir&3;
		if(play==T)
		{
			printf("%c OUT PASS %c\n",'A'+cur,'A'+next);
			cur^=2;
		}
		else if(play==T-1)
		{
			printf("%c OUT %s\n",'A'+cur,crd(play));
			dir=-dir;
			cur=cur+dir&3;;
		}
		else if(play==T-2)
		{
			printf("%c OUT %s\n",'A'+cur,crd(play));
		}
		else
		{
			printf("%c OUT %s\n",'A'+cur,crd(play));
			for(int i=1;i<4;++i)
				if(pl[cur+i&3].dis({play},1)==0)
				{
					printf("%c RON\n",'A'+(cur+i&3));
					printf("%c WIN\n",'A'+(cur+i&3));
					return 0;
				}

			for(int i=0;i<4;++i)
				if(i!=cur&&pl[i].cnt[play]>=2&&pl[i].dis({play,play})<pl[i].dis({}))//PONG
				{
					printf("%c PONG %s %s %s\n",'A'+i,crd(play),crd(play),crd(play));
					cur=i;
					pl[cur].cnt[play]-=2;
					goto skip;
				}
			
			if(play<=27)
			{
				int num=(play-1)%9+1;
				pl[next].cnt[play]++;
				for(int i=2;i>=0;--i)
					if(num+i<=9&&num+i>=3&&pl[next].cnt[play+i]&&pl[next].cnt[play+i-1]&&pl[next].cnt[play+i-2]&&pl[next].dis({play+i,play+i-1,play+i-2})<pl[next].dis({play}))
					{
						printf("%c CHOW %s %s %s\n",'A'+next,crd(play+i-2),crd(play+i-1),crd(play+i));
						cur=next;
						for(int j=0;j<=2;++j)pl[cur].cnt[play+i-j]--;
						goto skip;	
					}
				pl[next].cnt[play]--;
			}

			cur=next;
		}
	}
}