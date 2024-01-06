#include<iostream>
using namespace std;
//小顶堆
class heap{
private:
    int* p;
    int size;
    int capacity;
public:
    heap(){
        p = NULL;
        size = 0;
        capacity = 0;
    }
    ~heap(){
        delete[] p;
    }
    void adjustAfterPush(){
        int* q = p-1;
        int current = size;
        while(current!=1){
            int parent = current/2;
            if(q[current] < q[parent]){
                swap(q[current], q[parent]);
            }else{
                return;
            }
            current = parent;
        }
    }
    void push(int val){
        if(size+1 > capacity){
            int new_capacity;
            if(capacity == 0){
                new_capacity = 1;
            }else{
                new_capacity = capacity*2;
            }
            int* new_p = new int[new_capacity];
            for(int i = 0; i < capacity; ++i){
                new_p[i] = p[i];
            }
            delete[] p;
            p = new_p;
            capacity = new_capacity;
        }
        p[size] = val;
        size++;
        adjustAfterPush();
    }
    void adjustAfterPop(){
        int* q = p-1;
        swap(q[1], q[size+1]);
        int start = 1;
        while(start*2 <= size){
            int left = start*2;
            int right = left+1;
            int mini;
            if(right <= size && q[left] > q[right]){
                mini = right;
            }else{
                mini = left;
            }
            if(q[start] > q[mini]){
                swap(q[start], q[mini]);
            }else{
                return;
            }
            start = mini;
        }
    }
    int getSize()const{
        return size;
    }
    void pop(){
        size--;
        adjustAfterPop();
    }
    int top()const{
        return p[0];
    }
};

int main(){
    heap h;
    int a[] = {12, 3, 56, 2, 5, 24, 89, 32};
    for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i){
        h.push(a[i]);
    }
    while(h.getSize() != 0){
        cout << h.top() << endl;
        h.pop();
    }
    system("pause");
    return 0;
}