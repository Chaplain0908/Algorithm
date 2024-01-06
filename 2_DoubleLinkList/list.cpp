#define CATCH_CONFIG_MAIN   // 由catch提供一个main函数
#include <catch2/catch.hpp> //需要的头文件

#include <iostream>

using namespace std;

template <typename T> // 前置声明
class list;

template <typename T>
class list_iterator;

template <typename T> // 声明模板参数T
class node
{
    friend class list<T>;
    friend class list_iterator<T>;
    T value;
    node *next;
    node *prev;
    node(const T &value) : value(value), next(NULL), prev(NULL)
    {
    }
    node() : next(this), prev(this)
    {
    }
};

template <typename T>
class list_iterator
{
    friend class list<T>;
    node<T> *cur;
    list_iterator(node<T> *cur) : cur(cur) {}

public:
    T &operator*()
    {
        return cur->value;
    }
    list_iterator &operator++()
    {
        cur = cur->next;
        return *this;
    }
    list_iterator &operator--()
    {
        cur = cur->prev;
        return *this;
    }
    bool operator==(list_iterator with) const
    {
        return cur == with.cur;
    }
    bool operator!=(list_iterator with) const
    {
        return cur != with.cur;
    }
};

template <typename T>
class list
{
    node<T> sentinel; // 哨兵
    int n;

public:
    list() : n(0)
    {
    }

    // deconstructor
    ~list()
    {
        clear();
    }

    template <typename Iter>
    list(Iter begin, Iter end) : n(0)
    {
        while (begin != end)
        {
            push_back(*begin);
            ++begin;
        }
    }

    list_iterator<T> begin()
    {
        return list_iterator<T>(sentinel.next);
    }
    list_iterator<T> end()
    {
        return list_iterator<T>(&sentinel);
    }

    void push_back(const T &value)
    {
        node<T> *pnode = new node<T>(value);
        pnode->next = &sentinel;
        pnode->prev = sentinel.prev;
        sentinel.prev->next = pnode;
        sentinel.prev = pnode;
        ++n;
    }

    void pop_back()
    {
        if (n == 0)
        {
            return;
        }
        node<T> *pback = sentinel.prev;
        pback->prev->next = &sentinel;
        sentinel.prev = pback->prev;
        delete pback;
        --n;
    }

    void erase_one(const T &value)
    {
        node<T> *cur = sentinel.next;
        while (cur != &sentinel)
        {
            if (cur->value != value)
            {
                cur = cur->next;
                continue;
            }
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            delete cur;
            --n;
            return;
        }
    }

    void erase_all(const T &value)
    {
        node<T> *cur = sentinel.next;
        while (cur != &sentinel)
        {
            if (cur->value != value)
            {
                cur = cur->next;
                continue;
            }
            cur->prev->next = cur->next;
            cur->next->prev = cur->prev;
            node<T> *next = cur->next;
            delete cur;
            --n;
            cur = next;
        }
    }

    // erase(list_iterator)
    void erase_iterator(int site)
    {
        int size = 0;
        node<T> *p = sentinel.next;
        while (p != &sentinel)
        {
            p = p->next;
            ++size;
        }
        if ((site <= size))
        {
            node<T> *cur = this->sentinel.next;
            for (int i = 0; i < site; ++i)
            {
                cur = cur->next;
            }
            node<T> *prev = new node<T>();
            prev = cur->prev;
            prev->prev->next = cur;
            cur->prev = prev->prev;
            delete prev;
        }
    }

    void print() const
    {
        node<T> *cur = sentinel.next;
        cout << '{';
        while (cur != &sentinel)
        {
            cout << cur->value << ", ";
            cur = cur->next;
        }
        cout << '}' << endl;
    }

    string to_string() const
    {
        node<T> *cur = sentinel.next;
        string s = "{";
        while (cur != &sentinel)
        {
            s += std::to_string(cur->value);
            cur = cur->next;
            s += ", ";
        }
        s.push_back('}');
        return s;
    }

    string rto_string() const
    {
        node<T> *cur = sentinel.prev;
        string s = "{";
        while (cur != &sentinel)
        {
            s += std::to_string(cur->value);
            cur = cur->prev;
            s += ", ";
        }
        s += '}';
        return s;
    }

    int size() const
    {
        return n;
    }

    // clear
    void clear()
    {
        node<T> *cur = sentinel.next;
        while (cur != &sentinel)
        {
            cur = cur->next;
            delete cur->prev;
        }
        sentinel.next = &sentinel;
        sentinel.prev = &sentinel;
        n = 0;
    }

    bool empty() const
    {
        return sentinel.next == &sentinel && sentinel.prev == &sentinel;
    }

    void clone(const list<T> &src)
    {
        node<T> *itsrc = src.sentinel.next;
        node<T> *itpre = &this->sentinel;
        while (itsrc != &src.sentinel)
        {
            node<T> *pnew = new node<T>(*itsrc);
            itpre->next = pnew;
            pnew->prev = itpre;
            itpre = pnew;
            itsrc = itsrc->next;
        }
        itpre->next = &this->sentinel;
        this->sentinel.prev = itpre;
        this->n = src.n;
    }

    // copy constructor
    list(const list<T> &src)
    {
        this->clone(src);
    }

    // copu assignment
    list &operator=(const list<T> &src)
    {
        this->clear();
        this->clone(src);
        return *this;
    }

    // reverse
    void reverse()
    {
        node<T> *cur = sentinel.next;
        node<T> *temp = NULL;
        while (cur != &sentinel)
        {
            temp = cur->prev;
            cur->prev = cur->next;
            cur->next = temp;
            cur = cur->prev;
        }
        temp = sentinel.next;
        sentinel.next = sentinel.prev;
        sentinel.prev = temp;
    }
};

TEST_CASE("test list::clear")
{
    {
        list<int> l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        l.clear();
        REQUIRE(l.to_string() == "{}");
    }
}

TEST_CASE("test list::copy constructor")
{
    {
        list<int> l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        list<int> l2(l);
        REQUIRE(l2.to_string() == "{0, 1, 2, 3, 4, }");
    }
}

TEST_CASE("test list::copy assignment")
{
    {
        list<int> l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        list<int> l3;
        l3 = l;
        REQUIRE(l3.to_string() == "{0, 1, 2, 3, 4, }");
    }
}

TEST_CASE("test list::erase(list_iterator)")
{
    {
        list<int> l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        l.erase_iterator(3);
        REQUIRE(l.to_string() == "{0, 1, 3, 4, }");
    }
}

TEST_CASE("test list::reverse")
{
    {
        list<int> l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        l.reverse();
        REQUIRE(l.to_string() == "{4, 3, 2, 1, 0, }");
    }
}

TEST_CASE("test list::rprint")
{
    {
        list<int> l;
        for (int i = 0; i < 5; ++i)
        {
            l.push_back(i);
        }
        REQUIRE(l.to_string() == "{0, 1, 2, 3, 4, }");
        REQUIRE(l.rto_string() == "{4, 3, 2, 1, 0, }");
    }
}
// int main()
// {
//     // list<int> l;
//     // l.print();
//     // for (int i = 0; i < 5; i++)
//     // {
//     //     l.push_back(i);
//     //     l.print();
//     // }
//     // for (int i = 0; i < 5; i++)
//     // {
//     //     l.pop_back();
//     //     l.print();
//     // }

//     // int a[] = {1, 2, 1, 2, 1, 2, 1, 2, 3, 4};
//     // int n = sizeof(a) / sizeof(a[0]);
//     // list<int> l(a, a + n);
//     // l.print();
//     // l.erase_all(1);
//     // l.print();

//     int a[] = {1, 2, 1, 2, 1, 2, 1, 2, 3, 4};
//     int n = sizeof(a) / sizeof(a[0]);
//     list<int> l(a, a + n);
//     l.print();
//     list_iterator<int> it = l.begin();
//     list_iterator<int> end = l.end();
//     while (it != end)
//     {
//         *it *= 2;
//         ++it;
//     }
//     l.print();
//     // l.clear();
//     // l.print();

//     list<int> l2(l);
//     l2.print();
//     l2.rto_string();

//     list<int> l3;
//     l3 = l;
//     l3.print();

//     l3.erase_iterator(3);
//     l3.print();

//     l3.reverse();
//     l3.print();

//     system("pause");
//     return 0;
// }
/*
1.~list ok
2.copy constructor ok
3.copy assignment ok
4.clear ok
5.erase(list_iterator) ok
6.reverse ok
7.rprint() ok
*/