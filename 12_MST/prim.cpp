#include <iostream>
#include <queue>

using namespace std;

struct edge
{
    int from;
    int to;
    int dis;

    edge(int from, int to, int dis)
    {
        this->from = from;
        this->to = to;
        this->dis = dis;
    }

    bool operator>(edge with)const{
        if(this->dis != with.dis){
            return this->dis>with.dis;
        }
        if(this->to != with.to){
            return this->to>with.to;
        }
        return this->from>with.from;
    }
};

class disjoint{
private:
    vector<int> v;
public:
    disjoint(int n):v(n){
        for(int i = 0; i < n; ++i){
            v[i] = i;
        }
    }

    int find(int a){
        while(a != v[a]){
            a = v[a];
        }
        return a;
    }

    void setUnion(int a, int b){
        a = find(a);
        b = find(b);
        if(a > b){
            v[a] = v[b];
        }else{
            v[b] = v[a];
        }
    }
};

// bool operator>(edge a, edge b){
//     if(a.dis != b.dis){
//         return a.dis>b.dis;
//     }
//     if(a.to != b.to){
//         return a.to>b.to;
//     }
//     return a.from>b.from;
// }

class graph
{
private:
    int *data;
    int n;

public:
    graph(int n)
    {
        data = new int[n * n]{};
        this->n = n;
    }
    ~graph()
    {
        delete[] data;
    }

    void addEdge(int from, int to, int len)
    {
        data[from * n + to] = len;
        data[to * n + from] = len;
    }
    int getn() const
    {
        return n;
    }

    void prim(int begin)
    {
        vector<bool> visited(n, false);
        visited[begin] = true;
        priority_queue<edge, vector<edge>, greater<edge>> q;
        for (int i = 0; i < n; ++i)
        {
            if (data[begin * n + i] != 0)
            {
                edge e(begin, i, data[begin * n + i]);
                q.push(e);
            }
        }
        while (!q.empty())
        {
            edge mini = q.top();
            q.pop();
            if (visited[mini.to])
            {
                continue;
            }
            cout << mini.from << " " << mini.to << " " << mini.dis << endl;
            visited[mini.to] = true;
            for (int i = 0; i < n; ++i)
            {
                if (data[mini.to * n + i] != 0 && !visited[i])
                {
                    edge e(mini.to, i, data[mini.to * n + i]);
                    q.push(e);
                }
            }
        }
    }

    void Kruskal(){
        priority_queue<edge, vector<edge>, greater<edge>> q;
        for(int i = 0; i < n; ++i){
            for(int j = i+1; j < n; ++j){
                if(data[i*n + j] != 0){
                    edge e(i, j, data[i*n + j]);
                    q.push(e);
                }
            }
        }
        disjoint d(n);
        while(!q.empty()){
            edge e = q.top();
            //cout << "pop: " << e.from << " " << e.to << " " << e.dis << endl;
            q.pop();
            //cout << d.find(e.from) << " " << d.find(e.to) << endl;
            if(d.find(e.from) != d.find(e.to)){
                d.setUnion(e.from, e.to);
                cout << e.from << " " << e.to << " " << e.dis << endl;
            }
        }
    }
};

int main()
{
    // graph g(6);
    // g.addEdge(1, 2, 1);
    // g.addEdge(2, 3, 4);
    // g.addEdge(3, 4, 6);
    // g.addEdge(4, 5, 3);
    // g.addEdge(5, 1, 4);
    // g.addEdge(0, 1, 1);
    // g.addEdge(0, 2, 2);
    // g.addEdge(0, 3, 5);
    // g.addEdge(0, 4, 2);
    // g.addEdge(0, 5, 3);

    // graph g(4);
    // g.addEdge(0, 3, 4);
    // g.addEdge(3, 2, 2);
    // g.addEdge(2, 1, 3);
    // g.addEdge(1, 0, 1);

    graph g(7);
    g.addEdge(0, 1, 12);
    g.addEdge(0, 5, 16);
    g.addEdge(0, 6, 14);
    g.addEdge(1, 2, 10);
    g.addEdge(1, 5, 7);
    g.addEdge(6, 5, 9);
    g.addEdge(6, 4, 8);
    g.addEdge(5, 2, 6);
    g.addEdge(5, 4, 2);
    g.addEdge(2, 4, 5);
    g.addEdge(2, 3, 3);
    g.addEdge(4, 3, 4);
    
    cout << "prim1" << endl;
    g.prim(1);
    cout << "Kruskal" << endl;
    g.Kruskal();
    cout << "prim0" << endl;
    g.prim(0);
    

    

    system("pause");
    return 0;
}