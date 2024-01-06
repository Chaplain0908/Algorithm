#include <iostream>
#include<vector>

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

    void rprint() const
    {
        node<T> *cur = sentinel.prev;
        cout << '{';
        while (cur != &sentinel)
        {
            cout << cur->value << ", ";
            cur = cur->prev;
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

    void merge(list<T> &other)
    {
        node<T> *i = this->sentinel.next;
        node<T> *j = other.sentinel.next;
        while (i != &this->sentinel && j != &other.sentinel)
        {
            if (i->value <= j->value)
            {
                i = i->next;
            }
            else
            {
                node<T> *k = j->next;
                i->prev->next = j;
                j->prev = i->prev;
                i->prev = j;
                j->next = i;
                j = k;
            }
        }
        if (j != &other.sentinel)
        {
            j->prev = this->sentinel.prev;
            this->sentinel.prev->next = j;
            other.sentinel.prev->next = &this->sentinel;
            this->sentinel.prev = other.sentinel.prev;
        }
        this->n += other.n;
        other.n = 0;
        other.sentinel.next = &other.sentinel;
        other.sentinel.prev = &other.sentinel;
    }

    void merge_sort()
    {
        if (n == 0 || n == 1)
        {
            return;
        }
        node<T> *mid = this->sentinel.next;
        for (int i = 0; i < n / 2; ++i)
        {
            mid = mid->next;
        }
        node<T> *midprev = mid->prev;
        list<T> other;
        other.sentinel.next = mid;
        mid->prev = &other.sentinel;
        other.sentinel.prev = this->sentinel.prev;
        this->sentinel.prev->next = &other.sentinel;
        this->sentinel.prev = midprev;
        midprev->next = &this->sentinel;
        other.n = n - n / 2;
        this->n = n / 2;
        this->merge_sort();
        other.merge_sort();
        this->merge(other);
    }
};

int main()
{
    // int a[] = {1, 3, 5};
    // int b[] = {2, 4, 6, 7, 8, 9};
    // list<int> la(a, a + (sizeof(a) / sizeof(a[0])));
    // list<int> lb(b, b + (sizeof(b) / sizeof(b[0])));
    // la.merge(lb);
    // la.print();
    // la.rprint();
    // lb.print();
    // lb.rprint();

    vector<int> v = {8, 3, 2, 1, -9, 10, 23, 9, -1, -8, 32, 56, 19};
    list<int> l(v.begin(), v.end());
    l.merge_sort();
    l.print();
    l.rprint();

    system("pause");
    return 0;
}
