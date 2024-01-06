#include<iostream>
#include<queue>
using namespace std;

char graph[550][550];
int startx, starty, endx, endy;
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};
bool visited[550][550];
int n, m;

bool BFS(){
    queue<pair<int, int>> q;
    q.push(make_pair(startx, starty));
    visited[startx][starty] = true;
    while(!q.empty()){
        pair<int, int> front = q.front();
        q.pop();
        for(int i = 0; i < 4; ++i){
            int nextx = front.first + dir[i][0];
            int nexty = front.second + dir[i][1];
            if(nextx < 0|| nexty < 0||nextx >= n||nexty >= m){
                continue;
            }
            if(graph[nextx][nexty] == 'E'){
                return true;
            }
            if(graph[nextx][nexty] == '#'){
                continue;
            }
            if(visited[nextx][nexty]){
                continue;
            }
            q.push(make_pair(nextx, nexty));
            visited[nextx][nexty] = true;
        }
    }
    return false;
}

int main()
{
    while(cin >> n >> m)
    {
        for(int i = 0; i < n; ++i)
        {
            for(int j = 0; j < m; ++j)
            {
                visited[i][j] = false;
                char ch;
                cin >> ch;
                graph[i][j] = ch;
                if(ch == 'S'){
                    startx = i;
                    starty = j;
                }else if(ch == 'E'){
                    endx = i;
                    endy = j;
                }
            }
        }
        if(BFS()){
            cout << "Yes" << endl;
        }else{
            cout << "No" << endl;
        }
    }
    
}