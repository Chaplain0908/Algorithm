#include<iostream>

using namespace std;

class graph{
private:
    int vcnt;
    int **data;
    
public:
    graph(int vcnt){
        this->vcnt = vcnt;
        data = new int*[vcnt];
        for(int i = 0; i < vcnt; ++i){
            data[i] = new int[vcnt];
            for(int j = 0; j < vcnt; ++j){
                data[i][j] = 0;
            }
        }
        // int *data0 = new int[vcnt];
        // data[0] = data0;
    }
    ~graph(){
        for(int i = 0; i < vcnt; ++i){
            delete[] data[i];
        }
        delete[] data;
    }

    void add_edge(int from, int to, int weight){
        data[from][to] = weight;
    }

    void print()const{
        for(int i = 0; i < vcnt; ++i){
            for(int j = 0; j < vcnt; ++j){
                if(data[i][j] != 0){
                    cout << i << "->" << j << ":" << data[i][j] << endl;
                }
            }
        }
    }

};