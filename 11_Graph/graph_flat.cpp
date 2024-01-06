#include<iostream>
#include<queue>

using namespace std;

class graph{
private:
    int vcnt;
    int *data;
    
public:
    graph(int vcnt){
        this->vcnt = vcnt;
        data = new int[vcnt*vcnt];
        for(int i = 0; i < vcnt*vcnt; ++i){
            data[i] = 0;
        }
    }
    ~graph(){
        delete[] data;
    }

    void add_edge(int from, int to, int weight){
        data[from*vcnt + to] = weight;
        data[to*vcnt + from] = weight;
    }

    void print()const{
        for(int i = 0; i < vcnt; ++i){
            for(int j = 0; j < vcnt; ++j){
                if(data[i*vcnt + j] != 0){
                    cout << i << "->" << j << ":" << data[i*vcnt + j] << endl;
                }
            }
        }
    }

    void bfs(int start){
        queue<int> q;
        vector<bool> visited(vcnt, false); 
        q.push(start);
        visited[start] = true;
        while(!q.empty()){
            int from = q.front();
            cout << from << " ";
            q.pop();
            for(int to = 0; to < vcnt; ++to){
                if(data[from*vcnt + to] != 0 && not visited[to]){
                    q.push(to);
                    visited[to] = true; 
                }
            }
        }
        cout << endl;
    }

    void dfsHelper(int from, vector<bool> &visited){
        cout << from << " ";
        visited[from] = true;
        for(int to = 0; to < vcnt; ++to){
            if(data[from*vcnt + to] != 0 && visited[to] == false){
                dfsHelper(to, visited);
            }
        }
    }

    void dfs(int start){
        vector<bool> visited(vcnt, false);
        dfsHelper(start, visited);
        cout << endl;
    }

    

};

int main(){
    graph g(6);
    //g.add_edge(0, 1, 2);
    //g.add_edge(0, 4, 5);
    g.add_edge(0, 5, 1);
    g.add_edge(1, 5, 1);
    //g.add_edge(1, 2, 1);
    //g.add_edge(2, 5, 1);
    g.add_edge(2, 3, 6);
    g.add_edge(3, 5, 4);
    //g.add_edge(3, 4, 1);
    g.add_edge(4, 5, 1);
    
    g.dfs(5);
    system("pause");
    return 0;
}