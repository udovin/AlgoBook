#include <bits/stdc++.h>
#define ll long long
const int MAXN = 5005;
struct stick
{
    ll fr, wh, cap, flow;
};
using namespace std;
ll n, m, u, v, ans, c, level[MAXN + 100], taken[MAXN + 100];
vector<stick> allEdges;
vector< vector<ll> > g(MAXN + 100);
bool bfs(ll st, ll f)
{
    for(int i = 0; i <= MAXN; i++)
    {
        level[i] = -1;
    }
    level[st] = 0;
    queue<ll> q;
    q.push(st);
    while(!q.empty())
    {
        ll cur = q.front();
        q.pop();
        for(int i = 0; i < g[cur].size(); i++)
        {
            stick e = allEdges[g[cur][i]];
            if(e.flow < e.cap && level[e.wh] == -1)
            {
                level[e.wh] = level[cur] + 1;
                q.push(e.wh);
            }
        }
    }
    return (!(level[f] == -1));
}
ll dfs(ll x, ll f, ll fl)
{
    if(x == f) return fl;
    if(fl == 0) return 0;
    for(; taken[x] < g[x].size(); taken[x]++)
    {
        stick e = allEdges[g[x][taken[x]]];
        if(level[e.wh] == level[x] + 1)
        {
            ll newFlow = dfs(e.wh, f, min(fl, e.cap - e.flow));
            if(newFlow)
            {
                allEdges[g[x][taken[x]]].flow += newFlow;
                allEdges[g[x][taken[x]] ^ 1].flow -= newFlow;
                return newFlow;
            }
        }
    }
    return 0;
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin >> n >> m;
    for(int i = 0; i < 2 * m; i += 2)
    {
        cin >> u >> v >> c;
        allEdges.push_back({u, v, c, 0});
        allEdges.push_back({v, u, c, 0});
        g[u].push_back(i);
        g[v].push_back(i ^ 1);
    }
    while(bfs(1, n))
    {
        for(int i = 0; i <= MAXN; i++)
        {
            taken[i] = 0;
        }
        while(ll newFlow = dfs(1, n, 1e18))
            ans += newFlow;
    }
    cout << ans << "\n";
    return 0;
}
