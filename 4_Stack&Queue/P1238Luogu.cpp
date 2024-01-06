#include<iostream>
#include<queue>
#include<vector>

using namespace std;

bool graph[20][20];
int startx, starty, endx, endy;
int m, n;
int dir[4][2] = {{0,-1},{-1,0},{0,1},{1,0}};
pair<int, int> last[20][20];
bool found = false;
bool visited[20][20];

void visit(int x, int y){
    if(x == endx && y == endy){
        found = true;
        vector<pair<int, int>> path;
        while(x != startx || y != starty){
            pair<int, int> lastpoint = last[x][y];
            path.push_back(lastpoint);
            x = lastpoint.first;
            y = lastpoint.second;
        }
        for(int i = path.size()-1; i >= 0; i--){
            printf("(%d,%d)->", path[i].first+1, path[i].second+1);
        }
        printf("(%d,%d)\n", endx+1, endy+1);
        return;
    }
    for(int i = 0; i < 4; ++i){
        int nextx = x + dir[i][0];
        int nexty = y + dir[i][1];
        if(nextx < 0 || nexty < 0 || 
           nextx >= m || nexty >= n){
            continue;
        }
        if(graph[nextx][nexty] == 0){
            continue;
        }
        if(visited[nextx][nexty]){
            continue;
        }
        last[nextx][nexty] = make_pair(x, y);
        visited[nextx][nexty] = true;
        visit(nextx, nexty);
        visited[nextx][nexty] = false;
    }
}

int main(){
    cin >> m >> n;
    for(int i = 0; i < m; ++i){
        for(int j = 0; j < n; ++j){
            cin >> graph[i][j];
            visited[i][j] = false;
        }
    }
    cin >> startx >> starty;
    cin >> endx >> endy;
    startx--;
    starty--;
    endx--;
    endy--;
    visited[startx][starty] = true;
    visit(startx, starty);
    if(not found){
        cout << -1 << endl;
    }
    system("pause");
    return 0;
}