#define CATCH_CONFIG_MAIN   // 由catch提供一个main函数
#include <catch2/catch.hpp> //需要的头文件

#include <iostream>
using namespace std;

class node
{
    node() = default;
    friend class list;
    int value;  // 节点存放值
    node *next; // 指向下个节点的指针
    node(int value) : value(value), next(NULL) {}
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
    ~list()
    {
        clear();
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
            head = NULL;
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

    void erase_even()
    {
        node *p = head;
        node *prev = NULL;
        while (p != NULL)
        {
            if (p->value % 2 == 1)
            {
                if (prev == NULL)
                {
                    head = p->next;
                }
                else
                {
                    prev->next = p->next;
                }
                delete p;
                n--;
                return;
            }
            prev = p;
            p = p->next;
        }
    }

    int erase_even_all()
    {
        int cnt = 0;
        node *p = head;
        node *prev = NULL;
        while (p != NULL)
        {
            if (p->value % 2 == 1)
            {
                if (prev == NULL)
                {
                    head = p->next;
                }
                else
                {
                    prev->next = p->next;
                }
                node *next = p->next;
                delete p;
                n--;
                p = next;
                cnt++;
            }
            else
            {
                prev = p;
                p = p->next;
            }
        }
        return cnt;
    }

    void reverse()
    {
        node *p = head;
        node *prev = NULL;
        while (p != NULL)
        {
            node *next = p->next;
            p->next = prev;
            prev = p;
            p = next;
        }
        head = prev;
    }

    void clone(const list& src)
    {
        this->head = NULL;
        node* prev = NULL;
        node *itsrc = src.head;
        while(itsrc != NULL){
            node*pnew = new node(*itsrc);
            pnew->next = NULL;
            if(prev == NULL){
                this->head = pnew;
            }else{
                prev->next = pnew;
            }
            prev = pnew;
            itsrc = itsrc->next;
        }
        this->n = src.n;
    }
};
TEST_CASE("test list::erase_even")
{
    {
        list l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        l.erase_even();
        REQUIRE(l.to_string() == "{0, 2, 3, 4, }");
    }
    {
        list l;
        for (int i = 1; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{1, 2, 3, 4, }");
        l.erase_even();
        REQUIRE(l.to_string() == "{2, 3, 4, }");
    }
}
TEST_CASE("test list::erase_even_all")
{
    {
        list l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        REQUIRE(l.erase_even_all() == 2);
        REQUIRE(l.to_string() == "{0, 2, 4, }");
    }
    {
        list l;
        l.push_back(1);
        l.push_back(3);
        l.push_back(5);
        l.push_back(7);
        l.push_back(4);
        l.push_back(6);
        REQUIRE(l.to_string() == "{1, 3, 5, 7, 4, 6, }");
        REQUIRE(l.erase_even_all() == 4);
        REQUIRE(l.to_string() == "{4, 6, }");
    }
}
TEST_CASE("reverse")
{
    {
        list l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        l.reverse();
        REQUIRE(l.to_string() == "{4, 3, 2, 1, 0, }");
    }
    {
        list l;
        REQUIRE(l.to_string() == "{}");
        l.reverse();
        REQUIRE(l.to_string() == "{}");
    }
    {
        list l;
        l.push_back(1);
        REQUIRE(l.to_string() == "{1, }");
        l.reverse();
        REQUIRE(l.to_string() == "{1, }");
    }
}
TEST_CASE("test list::copynode")
{
    {
        list l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        list listnew(l);
        REQUIRE(listnew.to_string() == "{0, 1, 2, 3, 4, }");
    }
    {
        list l;
        REQUIRE(l.to_string() == "{}");
        list listnew(l);
        REQUIRE(listnew.to_string() == "{}");
    }
}
TEST_CASE("test list::assign")
{
    {
        list l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        list listnew = l;
        REQUIRE(listnew.to_string() == "{0, 1, 2, 3, 4, }");
    }
    {
        list l;
        REQUIRE(l.to_string() == "{}");
        list listnew = l;
        REQUIRE(listnew.to_string() == "{}");
    }
}
