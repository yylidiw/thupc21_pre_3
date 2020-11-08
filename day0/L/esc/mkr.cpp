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

int deck[150];

int main()
{
    freopen("mahjong.in","w",stdout);
    int N=148,p=0;
    for(int i=1;i<=37;++i)
        for(int j=1;j<=4;++j)
            deck[++p]=i;
    srand(time(0));
    std::random_shuffle(deck+1,deck+N+1);
    for(int i=1;i<=N;++i)
        printf("%s\n",crd(deck[i]));
    return 0;
}