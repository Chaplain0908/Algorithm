#include<iostream>
#include<vector>

using namespace std;

struct btnode
{
    int value;
    int height;
    btnode*left;
    btnode*right;
    btnode(int value): value(value), 
                       height(1), 
                       left(NULL),
                       right(NULL) 
    {}
    void setHeight();
};

int getHeight(btnode* p){
    if(p == NULL){
        return 0;
    }else{
        return p->height;
    }
}

void btnode::setHeight(){
    height = max(getHeight(left), getHeight(right))+1;
}

btnode* rightRotate(btnode* a, btnode* b){
    btnode* y = a->right;
    a->right = b;
    b->left = y;
    b->setHeight();
    a->setHeight();
    return a;
}

btnode* leftRotate(btnode* a, btnode* b){
    btnode* y = b->left;
    b->left = a;
    a->right = y;
    a->setHeight();
    b->setHeight();
    return b;
}

struct avl
{
private:
    btnode*root;
    int cnt;
public:
    avl(){
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
    ~avl(){
        freeTree(root);
    }

    static btnode* leftMayhigher(btnode* r){
        int factor = getHeight(r->left) - getHeight(r->right);
        if(factor <= 1){
            r->setHeight();
            return r;
        }
        if(getHeight(r->left->left) < getHeight(r->left->right)){
            r->left = leftRotate(r->left, r->left->right);
        }
        return rightRotate(r->left, r);
    }

    static btnode* rightMayhigher(btnode* r){
        int factor = getHeight(r->left) - getHeight(r->right);
        if(factor >= -1){
            r->setHeight();
            return r;
        }
        if(getHeight(r->right->left)>getHeight(r->right->right)){
            r->right = rightRotate(r->right->left, r->right);
        }
        return leftRotate(r, r->right);
    }

    btnode* addUnique2Helper(btnode*r, int val){
        if(r == NULL){
            cnt++;
            return new btnode(val);
        }
        if(val < r->value){
            r->left = addUnique2Helper(r->left, val);
            return leftMayhigher(r);
        }else if(val > r->value){  
            r->right = addUnique2Helper(r->right, val);
            return rightMayhigher(r);
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

    btnode* EraseLeftMostofRightHelper(btnode*r, btnode*replacee){
        if(r->left != NULL){
            r->left = EraseLeftMostofRightHelper(r->left, replacee);
            return rightMayhigher(r);
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
            return rightMayhigher(r);
        }else if(val > r->value){
            r->right = erase2Helper(r->right, val);
            return leftMayhigher(r);
        }else{
            if(r->left != NULL && r->right != NULL){
                r->right = EraseLeftMostofRightHelper(r->right, r);
                return leftMayhigher(r);
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

    bool isValidBSTHelper(btnode* r, btnode* &mini, btnode* &maxi){
        if(r == NULL){
            return true;
        }
        if(r->left != NULL){
            btnode* leftMini;
            btnode* leftMaxi;
            if(not isValidBSTHelper(r->left, leftMini, leftMaxi)){
                return false;
            }
            if(leftMaxi->value >= r->value){
                return false;
            }
            mini = leftMini;
        }else{
            mini = r;
        }
        if(r->right != NULL){
            btnode* rightMini;
            btnode* rightMaxi;
            if(not isValidBSTHelper(r->right, rightMini, rightMaxi)){
                return false;
            }
            if(rightMini->value <= r->value){
                return false;
            }
            maxi = rightMaxi;
        }else{
            maxi = r;
        }
        return true;
    }
    bool isValidBST() {
        btnode* mini;
        btnode* maxi;
        return isValidBSTHelper(root, mini, maxi);
    }

    int TreeDeep(btnode* root){//确认节点深度
        if(root == NULL){
            return 0;
        }
        return max(TreeDeep(root->left), TreeDeep(root->right)) + 1;
    }
    bool isBalancedHelper(btnode* root){ 
        if(root == NULL){
            return true;
        }
        if(not isBalancedHelper(root->left)){
            return false;
        }
        if(not isBalancedHelper(root->right)){
            return false;
        }
        int dif = abs(getHeight(root->left) - getHeight(root->right));
        return dif<=1;
    }
    bool isBalanced(){
        return isBalancedHelper(root);
    }

    bool checkHeighthelper(btnode* r){
        if(r == NULL){
            return true;
        }
        if(checkHeighthelper(r->left) == false){
            return false;
        }
        if(checkHeighthelper(r->right) == false){
            return false;
        }
        int height = max(getHeight(r->left), getHeight(r->right))+1;
        return r->height==height;
    }

    bool checkHeight(){
        return checkHeighthelper(root);
    }

    void checkIsAVL(){
        if(not isValidBST()){
            cout << "Not BST" << endl;
            return;
        }
        if(not isBalanced()){
            cout << "Not Balanced" << endl;
            return;
        }
        if(not checkHeight()){
            cout << "Wrong Height" << endl;
            return;
        }
        cout << "Pass" << endl;
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
    avl tree;
    //int a[] = {5, 2, 7, 9, 1, 3, 10, 6, 4, 8};
    // int a[] = {5};
    // for(int i = 0; i < sizeof(a)/sizeof(a[0]); ++i){
    //     tree.addUnique2(a[i]);
    //     tree.checkIsAVL();
    // }
    // tree.erase2(5);
    // tree.checkIsAVL();
    // tree.print();

    vector<int> v;
    for(int i = 0; i < 2000; ++i){
        int e = rand();
        v.push_back(e);
        tree.addUnique2(e);
    }
    tree.print();
    while(!v.empty()){
        int idx = rand()%v.size();
        int val = v[idx];
        tree.erase2(val);
        v.erase(v.begin()+idx);
        tree.checkIsAVL();
    }
    tree.print();



    system("pause");
    return 0;
}


