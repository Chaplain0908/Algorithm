#include<iostream>
#include<queue>

using namespace std;

struct visitor
{
    int priority;
    int No;
    visitor(int p, int n){
        priority = p;
        No = n;
    }
};

bool operator< (visitor a, visitor b){
    if(a.priority != b.priority){
        return a.priority < b.priority;
    }
    return a.No > b.No;
}

int main(){
    // priority_queue<int, vector<int>, greater<int>> pq;
    // int a[] = {3, 21, 53, 20, 39, 49, 25};
    // for(int e : a){
    //     pq.push(e);
    // }
    // while(!pq.empty()){
    //     cout << pq.top() << endl;
    //     pq.pop();
    // }

    priority_queue<visitor> pq;
    pq.emplace(0, 1);
    pq.emplace(1, 2);
    pq.emplace(2, 3);
    pq.emplace(0, 4);
    pq.emplace(1, 5);
    pq.emplace(2, 6);
    pq.emplace(0, 7);
    pq.emplace(1, 8);
    pq.emplace(2, 9);
    pq.emplace(0, 10);
    pq.emplace(1, 11);
    pq.emplace(2, 12);

    while (!pq.empty())
    {
        cout << pq.top().priority << " " << pq.top().No << endl;
        pq.pop();
    }
    


    system("pause");
    return 0;
}