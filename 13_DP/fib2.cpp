#include<iostream>

using namespace std;

int main(){
    int fib[30] = {1, 1};
    for(int i = 2; i < 30; ++i){
        fib[i] = fib[i-1]+fib[i-2];
    }

    for(int j = 0; j < 30; ++j){
        cout << fib[j] << endl;
    }

    system("pause");
    return 0;
}