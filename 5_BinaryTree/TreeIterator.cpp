#include<bits/stdc++.h>

using namespace std;

struct TreeNode
{
	int value;

	TreeNode * left;
	TreeNode * right;

	TreeNode(int value) :
		value(value), left(nullptr), right(nullptr)
	{
	}
};

class BSTIterator {
public:
    stack<TreeNode*> st;
    TreeNode* current;
    BSTIterator(TreeNode* root) {
        current = root;
        while(current != NULL){
            st.push(current);
            current = current->left;
        }
    }
    
    int next() {
        int ret;
        if(current == NULL){
            current = st.top();
            st.pop();
        }
        ret = current->value;
        current = current->right;
        while(current != NULL){
            st.push(current);
            current = current->left;
        }
        return ret;       
    }
    
    bool hasNext() {
        return current != NULL || !st.empty();
    }
};

int main()
{
	TreeNode nodes[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
	int N = 10;

	for (int i = 0; i < N; ++i) {
		int left = 2 * i + 1;
		int right = left + 1;
		if (left < N) {
			nodes[i].left = &nodes[left];
		}
		if (right < N) {
			nodes[i].right = &nodes[right];
		}
	}

    BSTIterator it(&nodes[0]);

    while(it.hasNext()){
        cout << it.next() << " ";
    }
    cout << endl;

	return 0;
}

