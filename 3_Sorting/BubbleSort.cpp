#include<iostream>
#include<vector>
#include<utility>
#include<math.h>
using namespace std;

int main(){
    vector<int> v = {4, 9, 8, 3, 6, 2, 1, 5, 0, 7};
    for(int i = 0; i < v.size()-1; ++i){
        for(int j = 0; j < v.size()-1-i; ++j){
            if(abs(v[j]) > abs(v[j+1])){
                swap(v[j], v[j+1]);
            }
        }
    }
    for(int i = 0; i < v.size(); ++i){
        cout << v[i] << " ";
    }

    system("pause");
    return 0;
}