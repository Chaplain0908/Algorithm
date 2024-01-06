#include<iostream>

using namespace std;

struct btnode
{
    int value;
    btnode*left;
    btnode*right;
    btnode(int value){
        this->value = value;
        left = NULL;
        right = NULL;
    }
};

struct bst
{
private:
    btnode*root;
    int cnt;
public:
    bst(){
        root = NULL;
        cnt = 0;
    }
private:
    static void freeTree(btnode*r){
        if(r == NULL){
            return;
        }
        freeTree(r->left);
        freeTree(r->right);
        delete r;
    }
public:
    ~bst(){
        freeTree(root);
    }
    void addUnique(int val){
        if(root == NULL){
            root = new btnode(val);
            cnt++;
            return;
        }
        btnode* parent = root;
        while(true){
            if(val < parent->value){
                if(parent->left == NULL){
                    parent->left = new btnode(val);
                    cnt++;
                    return;
                }
                parent = parent->left;
            }else if(val > parent->value){
                if(parent->right == NULL){
                    parent->right = new btnode(val);
                    cnt++;
                    return;
                }
                parent = parent->right;
            }else{
                return;
            }
        }
    }
    btnode* addUnique2Helper(btnode*r, int val){
        if(r == NULL){
            cnt++;
            return new btnode(val);
        }
        if(val < r->value){
            r->left = addUnique2Helper(r->left, val);
        }else if(val > r->value){
            r->right = addUnique2Helper(r->right, val);
        }
        return r;
    }
    void addUnique2(int val){
        root = addUnique2Helper(root, val);
    }
    bool find(int val)const{
        btnode* parent = root;
        while(parent != NULL){
            if(val < parent->value){
                parent = parent->left;
            }else if(val > parent->value){
                parent = parent->right;
            }else{
                return true;
            }
        }
        return false;
    }
    static bool find2Helper(const btnode*r, int val){
        if(r == NULL){
            return false;
        }
        if(val < r->value){
            return find2Helper(r->left, val);
        }else if(val > r->value){
            return find2Helper(r->right, val);
        }else{
            return true;
        }
    }
    bool find2(int val)const{
        return find2Helper(root, val);
    }

    void EraseLeftMostofRight(btnode* it){
        btnode* descendant = it->right;
        btnode* dparent = it;
        while(descendant->left != NULL){
            dparent = descendant;
            descendant = descendant->left;
        }
        it->value = descendant->value;
        if(descendant == dparent->left){
            dparent->left = descendant->right;
        }else{
            dparent->right = descendant->right;
        }
        delete descendant;
        cnt--;
    }
    void erase(int val){
        btnode* parent = NULL;
        btnode* it = root;
        while(it != NULL){
            if(val < it->value){
                parent = it;
                it = it->left;
            }else if(val > it->value){
                parent = it;
                it = it->right;
            }else{
                if(it->left != NULL && it->right != NULL){
                    EraseLeftMostofRight(it);
                    return;
                }
                btnode* descendant;
                if(it->left == NULL && it->right == NULL){ //it points to leaf node
                    descendant = NULL;
                }else if(it->left != NULL && it->right == NULL){
                    descendant = it->left;
                }else if(it->left == NULL && it->right != NULL){
                    descendant = it->right;
                }
                if(parent == NULL){
                    root = descendant;
                }else if(it == parent->left){
                    parent->left = descendant;
                }else{
                    parent->right = descendant;
                }
                delete it;
                cnt--;
                return;
            }
        }
    }
    btnode* EraseLeftMostofRightHelper(btnode*r, btnode*replacee){
        if(r->left != NULL){
            r->left = EraseLeftMostofRightHelper(r->left, replacee);
            return r;
        }else{
            replacee->value = r->value;
            btnode* descendant = r->right;
            delete r;
            cnt--;
            return descendant;
        }
    }
    btnode* erase2Helper(btnode* r, int val){
        if(r == NULL){
            return NULL;
        }
        if(val < r->value){
            r->left = erase2Helper(r->left, val);
            return r;
        }else if(val > r->value){
            r->right = erase2Helper(r->right, val);
            return r;
        }else{
            if(r->left != NULL && r->right != NULL){
                r->right = EraseLeftMostofRightHelper(r->right, r);
                return r;
            }
            btnode* descendant;
            if(r->left != NULL){
                descendant = r->left;
            }else{
                descendant = r->right;
            }
            delete r;
            cnt--;
            return descendant;
        }
    }
    void erase2(int val){
        root = erase2Helper(root, val);
    }
private:
    static void printHelper(const btnode* r){
        if(r == NULL){
            return;
        }
        printHelper(r->left);
        cout << r->value << " ";
        printHelper(r->right);
    }
public:
    void print()const{
        printHelper(root);
        cout << endl;
    }
};

int main(){
    bst tree;
    int a[] = {5, 2, 7, 9, 1, 3, 10, 6, 4, 8};
    for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i){
        tree.addUnique2(a[i]);
        tree.print();
    }
    tree.erase2(11);
    tree.print();
    system("pause");
    return 0;
}


