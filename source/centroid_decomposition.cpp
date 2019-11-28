
// manually set n = number of vertices 
// vertex index from 1 to n
// first call tree_init();
// ae(u,v) only one direction
// call work(1);

const int TREE_MAXV=300000+5;
struct edge{int v,next;}e[TREE_MAXV*2];int g[TREE_MAXV],etot;
int qu[TREE_MAXV],pre[TREE_MAXV],off[TREE_MAXV];
int n;
void ae(int u,int v){
	e[etot].v=v;
	e[etot].next=g[u];g[u]=etot++;
}
int getcen(int rt){
	static int sz[TREE_MAXV];
	static bool bo[TREE_MAXV];
	int p=0,q=0;
	pre[rt]=0;
	qu[q++]=rt;
	while(p!=q){
		int u=qu[p++];
		sz[u]=bo[u]=1;
		for (int i=g[u];~i;i=e[i].next)if(!off[e[i].v] && e[i].v!=pre[u]){
			pre[e[i].v]=u;
			qu[q++]=e[i].v;
		}
	}
	for (int i=q-1;i>=0;i--){
		int u=qu[i];
		if(bo[u] && sz[u]*2>=q)return u;
		sz[pre[u]]+=sz[u];
		if(sz[u]*2>q)bo[pre[u]]=0;
	}
}
void bfs(int rt,int preroot=0){
	int p=0,q=0;
	pre[rt]=preroot;
	qu[q++]=rt;
	while(p!=q){
		int u=qu[p++];
		for (int i=g[u];~i;i=e[i].next)if(!off[e[i].v] && e[i].v!=pre[u]){
			pre[e[i].v]=u;
			qu[q++]=e[i].v;
		}
	}
}
void work(int rt){
	int cen=getcen(rt);
	off[cen]=1;

	for (int i=g[cen];~i;i=e[i].next)if(!off[e[i].v]){
		bfs(e[i].v,cen);


	}
	for (int i=g[cen];~i;i=e[i].next)if(!off[e[i].v]){
		work(e[i].v);
	}
}
void tree_init(){
	static bool ini=0;
	if(!ini){
		ini=1;
		memset(g,-1,sizeof(g));
	}else{
		for (int i=0;i<=n;i++)off[i]=0,g[i]=-1;
	}
	etot=0;
}
void readedge(){
	for (int i=1;i<n;i++){
		int x,y;gn(x);gn(y);
		ae(x,y);ae(y,x);
	}
}

