#include <bits/stdc++.h>
#include <vector>
using namespace std;

#define VerticesMax 1000

class edge {
    public:
        int from, to, value;
        void in() {
            cin >> from >> to >> value;
        };
};

vector<vector<class edge> > graph(VerticesMax);
void path(const int src, const int cur, const int pre[]) {
    if (cur == src) {
        cout << cur << endl;
        return ;
    }
    else {
        path(src, pre[cur], pre);
        cout << cur << endl;
    }
}

int main() {

    int vertices , edges;   //顶点个数，边的个数
    cout << "Please input the number of vertices and edges :";
    cin >> vertices >> edges;

    edge e;
    cout << "Please input all the edges :" << endl;
    for (int i = 1;i <= edges;i++) {
        e.in();
        graph[e.from].push_back(e);
    }

    int begin, end;
    cout << "Please input starting vertex and end vertex :";
    cin >> begin >> end;
    
    int dis[VerticesMax];
    int pre[VerticesMax];
    bool vis[VerticesMax];
    fill(dis, dis + VerticesMax, INT_MAX);
    fill(pre, pre + VerticesMax, 0);
    fill(vis, vis + VerticesMax, false);
    dis[begin] = 0;
    for (int i = 1;i <= vertices;i++) {
        int minVex = 0;
        for (int j = 1;j <= vertices;j++)
            if (! vis[j] && dis[minVex] > dis[j])
                minVex = j;
        for (vector<class edge>::iterator it = graph[minVex].begin();it != graph[minVex].end();it++) {
            if (dis[(*it).to] > dis[minVex] + (*it).value) {
                dis[(*it).to] = dis[minVex] + (*it).value;
                pre[(*it).to] = minVex;
            }
        }
        //path.push_back(minVex);
        vis[minVex] = true;
    }
    path(begin, end, pre);
    return 0;
}
