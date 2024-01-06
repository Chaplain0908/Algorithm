#include<iostream>
#include<algorithm>
using namespace std;
//小

void makeHeap(int* a, int n){
    int* q = a-1;
    for(int i = 2; i <= n; ++i){
        int current = i;
        while(current != 1){
            int parent = current/2;
            if(q[current] < q[parent]){
                swap(q[current], q[parent]);
            }else{
                break;
            }
            current = parent;
        }
    }
}

void makeHeap2(int* a, int n){
    int* q = a-1;
    int start = n/2;
    while(start != 0){
        int parent = start;
        while(parent*2 <= n){
            int left = parent*2;
            int right = left+1;
            int mini;
            if(right <= n && q[left] > q[right]){
               mini = right;
            }else{
               mini = left;
            }
            if(q[mini] < q[parent]){
                swap(q[mini], q[parent]);
                parent = mini;
            }else{
                break;
            }
        }
        start--;
    }
}

void sortHeap(int* a, int n){
    int* q = a-1;
    while(n>1){
        swap(q[1], q[n]);
        n--;
        int current = 1;
        while(current*2 <= n){
            int left = current*2;
            int right = left+1;
            int mini;
            if(right <= n && q[right] < q[left]){
                mini = right;
            }else{
                mini = left;
            }
            if(q[current] > q[mini]){
                swap(q[current], q[mini]);
            }else{
                break;
            }
            current = mini;
        }
    }
}
void heapSort(int* a, int n){
    makeHeap2(a, n);
    sortHeap(a, n);
}

int main(){
    int a[] = {10, 239, 31, 46, 32, 21, 1, 9, 67};
    int n = sizeof(a)/sizeof(a[0]);
    sort(a, a+n);
    //heapSort(a, n);
    for(int i = 0; i < n; ++i){
        cout << a[i] << endl;
    }
    system("pause");
    return 0;
}