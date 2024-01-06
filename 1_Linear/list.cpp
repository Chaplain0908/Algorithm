#define CATCH_CONFIG_MAIN   // 由catch提供一个main函数
#include <catch2/catch.hpp> //需要的头文件

#include <iostream>
using namespace std;

class node
{
    friend class list;
    friend class list_iterator;
    int value;  // 节点存放值
    node *next; // 指向下个节点的指针
    node(int value) : value(value), next(NULL) {}
};

class list_iterator{
    friend class list;
private:
    node* current;
    list_iterator(node* current){
        this->current = current;
    }
public:
    list_iterator& operator++(){
        current = current->next;
        return *this;
    }
    bool operator!=(const list_iterator& another) const{
        return this->current != another.current;
    }
    int operator*(){
        return current->value;
    }
};

class list
{
    node *head; // 指向第一个节点
    int n;      // list长度
public:
    list()
    {
        head = NULL;
        n = 0;
    }

    list_iterator begin(){
        return list_iterator(head);
    }

    list_iterator end(){
        list_iterator it(NULL);
        return it;
    }

    void push_front(int num)
    {
        node *pnode = new node(num);
        pnode->next = head;
        head = pnode;
        n++;
    }
    void push_back(int num)
    {
        if (head == NULL)
        { // list empty
            head = new node(num);
        }
        else
        {
            node *cur = head;
            while (cur->next != NULL)
            {
                cur = cur->next;
            }
            cur->next = new node(num);
        }
        n++;
    }
    int size() const
    {
        return n;
    }
    void print() const
    {
        node *cur = head;
        cout << "{";
        while (cur != NULL)
        {
            cout << cur->value << ", ";
            cur = cur->next;
        }
        cout << "}" << endl;
    }

    string to_string() const
    {
        node *cur = head;
        string s = "{";
        while (cur != NULL)
        {
            s += std::to_string(cur->value);
            cur = cur->next;
            s += ", ";
        }
        s.push_back('}');
        return s;
    }

    void pop_back()
    {
        // node* pnode = new node(num);
        if (head == NULL)
        {
            return;
        }
        if (head->next == NULL)
        {
            free(head);
            head == NULL;
            return;
        }
        node *cur = head;
        node *prev = NULL;
        while (cur->next)
        {
            prev = cur;
            cur = cur->next;
        }
        delete (cur); // free-malloc / delete-new
        prev->next = NULL;
        n = n - 1;
    }

    void pop_front()
    {
        // node* pnode = new node(num);
        if (head == NULL)
        {
            return;
        }
        node *cur = head;
        head = cur->next;
        delete (cur); // free-malloc / delete-new
        cur = NULL;
        n = n - 1;
    };

    void clear()
    {
        node *p;
        while (head != NULL)
        {
            p = head;
            head = head->next;
            delete p;
        }
    };
};

TEST_CASE("default constructor")
{
    list l;
    REQUIRE(l.size() == 0);
    REQUIRE(l.to_string() == "{}");
}
// void test_list()
TEST_CASE("test list::push_back")
{
    list l;
    for (int i = 0; i < 5; ++i)
    {
        l.push_back(i);
        REQUIRE(l.size() == i + 1);
    }

    REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
}

TEST_CASE("test list::pop_back")
{
    list l;
    for (int i = 0; i < 5; ++i)
    {
        l.push_back(i);
    }
    REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
    l.pop_back();
    REQUIRE(l.size() == 4);

    REQUIRE(l.to_string() == "{0, 1, 2, 3, }");
}
TEST_CASE("test list::pop_front")
{
    list l;
    for (int i = 0; i < 5; ++i)
    {
        l.push_back(i);
    }
    REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
    l.pop_front();
    REQUIRE(l.size() == 4);
    REQUIRE(l.to_string() == "{1, 2, 3, 4, }");
}
TEST_CASE("test list::clear")
{
    list l;
    for (int i = 0; i < 5; ++i)
    {
        l.push_back(i);
    }
    REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
    l.clear();
    REQUIRE(l.size() == 5);
    REQUIRE(l.to_string() == "{}");
}

TEST_CASE("test list_iterator"){
    list l;
    for (int i = 0; i < 5; ++i)
    {
        l.push_back(i);
    }
    for(list_iterator it = l.begin(); it != l.end(); ++it){
        cerr << *it << " ";
    }
    cerr << endl;
}

TEST_CASE("test range_for"){
    list l;
    for (int i = 0; i < 5; ++i)
    {
        l.push_back(i);
    }
    for(int e : l){
        cerr << e << " ";
    }
    cerr << endl;
}
