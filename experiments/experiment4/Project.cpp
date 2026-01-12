#include <graphics.h> 
#include <iostream>
#include <conio.h>
#include <time.h>
#include <math.h>
#include <vector>
using namespace std;

#define VerticesMax 1000
#define DigitCircleRadius 10
#define Correct 4
#define PI 3.141592653
#define UnitLength 10
#define OriginX 200
#define OriginY 200

class Edge {
    int to, value;
public:
    Edge(const int to, const int value) : to(to), value(value) {}
    int To() { return to; }
    int Value() { return value; }
};

class Graph {
    int vertices;
    vector<vector<Edge> > adj;
public:
    void initial(const int vertices) {
        this->vertices = vertices;
        adj.resize(VerticesMax);
        for (int i = 1; i <= this->vertices; i++)
            adj[i].clear();
    }
    void addEdge(const int from, const int to, const int value) {
        adj[from].push_back(Edge(to, value));
    }
    void Dijkstra(const int begin, const int end);
    void Draw(const int begin, const int end, const int pre[]);
    void Path(const int *x, const int *y, const int src, const int cur, const int pre[]);
};

void Graph::Dijkstra(const int begin, const int end) {
    int dis[VerticesMax];
    int pre[VerticesMax];
    bool vis[VerticesMax];
    fill(dis, dis + VerticesMax, INT_MAX);
    fill(pre, pre + VerticesMax, 0);
    fill(vis, vis + VerticesMax, false);
    dis[begin] = 0;
    for (int i = 1; i <= vertices; i++) {
        int minVex = 0;
        for (int j = 1; j <= vertices; j++)
            if (!vis[j] && dis[minVex] > dis[j])
                minVex = j;
        for (vector<Edge>::iterator it = adj[minVex].begin(); it != adj[minVex].end(); it++) {
            if (dis[(*it).To()] > dis[minVex] + (*it).Value()) {
                dis[(*it).To()] = dis[minVex] + (*it).Value();
                pre[(*it).To()] = minVex;       //记录路径
            }
        }
        vis[minVex] = true;
    }

    Draw(begin, end, pre);
}

void Graph::Draw(const int begin, const int end, const int pre[]) {
    
    int x[VerticesMax];
    int y[VerticesMax];
    for (int i = 1; i <= vertices; i++) {
        x[i] = rand() % 300 + 200;
        y[i] = rand() % 300 + 200;
    }

    initgraph(700, 700);
    const int DigitXY = DigitCircleRadius / sqrt(2);
    for (int i = 1; i <= vertices; i++) {
        circle(x[i], y[i], DigitCircleRadius);
        char digit = i + 48;
        outtextxy(x[i] - DigitXY + Correct, y[i] - DigitXY, digit);
        for (vector<Edge>::iterator it = adj[i].begin(); it != adj[i].end(); it++) {
            
            char len = it->Value() + 48;
            outtextxy((x[i] + x[it->To()]) / 2, (y[i] + y[it->To()]) / 2, len);

            double angle = fabs(asin((y[it->To()] - y[i]) / sqrt((x[i] - x[it->To()]) * (x[i] - x[it->To()]) + (y[i] - y[it->To()]) * (y[i] - y[it->To()]))));
            if (x[i] < x[it->To()]) {
                if (y[i] < y[it->To()])
                    line(x[i] + DigitCircleRadius * cos(angle), y[i] + DigitCircleRadius * sin(angle), x[it->To()] - DigitCircleRadius * cos(angle), y[it->To()] - DigitCircleRadius * sin(angle));
                else
                    line(x[i] + DigitCircleRadius * cos(angle), y[i] - DigitCircleRadius * sin(angle), x[it->To()] - DigitCircleRadius * cos(angle), y[it->To()] + DigitCircleRadius * sin(angle));
            }
            else {
                if (y[i] < y[it->To()])
                    line(x[i] - DigitCircleRadius * cos(angle), y[i] + DigitCircleRadius * sin(angle), x[it->To()] + DigitCircleRadius * cos(angle), y[it->To()] - DigitCircleRadius * sin(angle));
                else
                    line(x[i] - DigitCircleRadius * cos(angle), y[i] - DigitCircleRadius * sin(angle), x[it->To()] + DigitCircleRadius * cos(angle), y[it->To()] + DigitCircleRadius * sin(angle));
            }
        }
    }
    setlinecolor(LIGHTCYAN);
    Path(x, y, begin, end, pre);          //画出最短路
    _getch();
    closegraph();
}

void Graph::Path(const int *x, const int *y, const int src, const int cur, const int pre[]) {
    if (pre[cur] == src) {
        double angle = fabs(asin((y[pre[cur]] - y[cur]) / sqrt((x[cur] - x[pre[cur]]) * (x[cur] - x[pre[cur]]) + (y[cur] - y[pre[cur]]) * (y[cur] - y[pre[cur]]))));
        if (x[cur] < x[pre[cur]]) {
            if (y[cur] < y[pre[cur]])
                line(x[cur] + DigitCircleRadius * cos(angle), y[cur] + DigitCircleRadius * sin(angle), x[pre[cur]] - DigitCircleRadius * cos(angle), y[pre[cur]] - DigitCircleRadius * sin(angle));
            else
                line(x[cur] + DigitCircleRadius * cos(angle), y[cur] - DigitCircleRadius * sin(angle), x[pre[cur]] - DigitCircleRadius * cos(angle), y[pre[cur]] + DigitCircleRadius * sin(angle));
        }
        else {
            if (y[cur] < y[pre[cur]])
                line(x[cur] - DigitCircleRadius * cos(angle), y[cur] + DigitCircleRadius * sin(angle), x[pre[cur]] + DigitCircleRadius * cos(angle), y[pre[cur]] - DigitCircleRadius * sin(angle));
            else
                line(x[cur] - DigitCircleRadius * cos(angle), y[cur] - DigitCircleRadius * sin(angle), x[pre[cur]] + DigitCircleRadius * cos(angle), y[pre[cur]] + DigitCircleRadius * sin(angle));
        }
        return;
    }
    else {
        Path(x, y, src, pre[cur], pre);
        double angle = fabs(asin((y[pre[cur]] - y[cur]) / sqrt((x[cur] - x[pre[cur]]) * (x[cur] - x[pre[cur]]) + (y[cur] - y[pre[cur]]) * (y[cur] - y[pre[cur]]))));
        if (x[cur] < x[pre[cur]]) {
            if (y[cur] < y[pre[cur]])
                line(x[cur] + DigitCircleRadius * cos(angle), y[cur] + DigitCircleRadius * sin(angle), x[pre[cur]] - DigitCircleRadius * cos(angle), y[pre[cur]] - DigitCircleRadius * sin(angle));
            else
                line(x[cur] + DigitCircleRadius * cos(angle), y[cur] - DigitCircleRadius * sin(angle), x[pre[cur]] - DigitCircleRadius * cos(angle), y[pre[cur]] + DigitCircleRadius * sin(angle));
        }
        else {
            if (y[cur] < y[pre[cur]])
                line(x[cur] - DigitCircleRadius * cos(angle), y[cur] + DigitCircleRadius * sin(angle), x[pre[cur]] + DigitCircleRadius * cos(angle), y[pre[cur]] - DigitCircleRadius * sin(angle));
            else
                line(x[cur] - DigitCircleRadius * cos(angle), y[cur] - DigitCircleRadius * sin(angle), x[pre[cur]] + DigitCircleRadius * cos(angle), y[pre[cur]] + DigitCircleRadius * sin(angle));
        }
    }
}

int main() {
    srand((unsigned)time(NULL));        //设置随机种子

    int vertices, edges;
    cout << "Please input the number of vertices and edges :";  //输入顶点数和边数
    cin >> vertices >> edges;

    Graph graph;
    graph.initial(vertices);            //图的初始化
    cout << "Please input all the edges :" << endl; //输入边
    for (int i = 1; i <= edges; i++) {
        int from, to, value;
        cin >> from >> to >> value;
        graph.addEdge(from, to, value);
    }

    int begin, end;
    cout << "Please input starting vertex and end vertex :";    //输入起止点
    cin >> begin >> end;
    graph.Dijkstra(begin, end);         //求最短路径

    return 0;
}
