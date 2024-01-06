#include<iostream>
using namespace std;

int garph[1010][100010];
bool visited[1010][100010];
int startx, starty, endx, endy;
int dir[4][2] = {{1,0},{-1,0},{0,1},{0,-1}};

bool bfs(){
    
}





int main(){
    int n, m;
    cin >> n >> m;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cin >> garph[i][j];
            visited[i][j] = false;
        }
    }
    cin >> startx >> starty;
    cin >> endx >> endy;
    return 0;
}