#include<iostream>
#include<map>

using namespace std;

map<int, int> mp;

int fib(int a){
    if(a == 0 || a == 1){
        return 1;
    }

    auto it = mp.find(a);

    if(it != mp.end()){
        return it->second;
    }

    int b = fib(a-1)+fib(a-2);
    mp[a] = b;

    return b;
}

int main(){
    for(int i = 0; i < 50; ++i){
        cout << fib(i) << endl;
    }
    
    system("pause");
    return 0;
}