#include<iostream>

using namespace std;

enum slotStatus{
    EMPTY,
    OCCUPIED,
    TOMB,
};

class slot{
friend class hashTable;
    slotStatus status;
    int val;
    slot(){
        status = EMPTY;
    }
};

class hashTable{
    slot* slots;
    int slots_cnt;
public:
    hashTable(int slots_cnt){
        slots = new slot[slots_cnt];
        this->slots_cnt = slots_cnt;
    }
    ~hashTable(){
        delete[] slots;
    }

    int hash(int val) const{
        return val%slots_cnt;
    }

    void insert(int val){
        int s = hash(val);
        for(int i = 0; i < slots_cnt; ++i){
            if(slots[s].status != OCCUPIED){
                slots[s].val = val;
                slots[s].status = OCCUPIED;
                return;
            }
            if(slots[s].status == OCCUPIED && slots[s].val == val){
                return;
            }
            ++s;
            if(s == slots_cnt){
                s = 0;
            }
        }
        cout << "Wrong" << endl;
    }

    bool find(int val) const{
        int s = hash(val);
        for(int i = 0; i < slots_cnt; ++i){
            if(slots[s].status == OCCUPIED && slots[s].val == val){
                return true;
            } 
            if(slots[s].status == EMPTY){
                return false;
            }
            ++s;
            if(s == slots_cnt){
                s = 0;
            }
        }
        return false;
    }

    void erase(int val){
        int s = hash(val);
        for(int i = 0; i < slots_cnt; ++i){
            if(slots[s].status == EMPTY){
                return;
            }
            if(slots[s].status == OCCUPIED && slots[s].val == val){
                slots[s].status = TOMB;
                return;
            }
            ++s;
            if(s == slots_cnt){
                s = 0;
            }
        }
    }

    void print() const{
        for(int i = 0; i < slots_cnt; ++i){
            if(slots[i].status == OCCUPIED){
                cout << slots[i].val << " ";
            }
        }
        cout << endl;
    }
};

int main(){
    cout << boolalpha;

    hashTable h(10);
    h.insert(1);
    h.insert(10);
    h.insert(20);
    h.insert(10);
    h.insert(66);
    h.insert(32);
    h.print();

    h.insert(54);
    h.insert(3);
    h.insert(95);
    h.print();

    cout << h.find(22) << endl;
    cout << h.find(10) << endl;

    h.erase(10);
    h.erase(32);
    h.erase(3);
    h.print();

    h.insert(10);
    h.insert(32);
    h.insert(9);

    h.print();

    system("pause");
    return 0;

}


