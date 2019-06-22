//
// Created by daniil on 22.06.19.
//

#ifndef LIST_MY_LIST_H
#define LIST_MY_LIST_H

template<typename T>
struct my_list {


    struct base_node {
        friend struct my_list;

        base_node() : next(nullptr), prev(nullptr) {};

        base_node(base_node *left, base_node *right) : next(right), prev(left) {}

        base_node *next;
        base_node *prev;

        friend struct my_list;
    };

    struct node : base_node {
        explicit node(T const &_val) : val(_val) {}

        node(T const &_val, base_node *left, base_node *right) : base_node(left, right), val(_val) {};
        T val;


        friend void swap(node &a, node &b) {
            std::swap(a.val, b.val);
            std::swap(a.next, b.next);
            std::swap(a.prev, b.prev);
        }

        friend struct my_list;
    };

    template<typename V>
    struct Iterator : std::iterator<std::bidirectional_iterator_tag, V> {
        friend my_list;
        friend base_node;

        Iterator() : ptr(nullptr) {}

        ~Iterator() = default;

        template<class Another>
        Iterator(Another *p) : ptr(p) {}

        template<class Another>
        Iterator(Iterator<Another> const &other) : ptr(other.ptr) {}

        template<class Another>
        Iterator &operator=(Iterator<Another> const &other) {
            ptr = other.ptr;
            return *this;
        }

        template<class Another>
        bool operator==(Iterator<Another> const &b) const {
            return ptr == b.ptr;
        }

        template<class Another>
        bool operator!=(Iterator<Another> const &b) const {
            return ptr != b.ptr;
        }

        V &operator*() const {
            return (static_cast<node *>(const_cast<base_node *>(ptr))->val);
        }

        V &operator*() {
            return (static_cast<node *>(const_cast<base_node *>(ptr))->val);
        }

        V *operator->() const {
            return &(static_cast<node *>(const_cast<base_node *>(ptr))->val);
        }

        Iterator &operator++() {
            ptr = ptr->next;
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp(*this);
            ptr = ptr->next;
            return tmp;
        }

        Iterator &operator--() {
            ptr = ptr->prev;
            return *this;
        }

        Iterator operator--(int) {
            Iterator tmp(*this);
            ptr = ptr->prev;
            return tmp;
        }

    private:
        base_node *ptr;
    };

    typedef T value_type;

    typedef Iterator<T> iterator;
    typedef Iterator<T const> const_iterator;
    typedef std::reverse_iterator<iterator>
            reverse_iterator;
    typedef std::reverse_iterator<const_iterator>
            const_reverse_iterator;

    my_list() noexcept;

    my_list(my_list<T> const &other);

    my_list &operator=(my_list const &other);

    ~my_list();


    bool empty() const noexcept;

    void clear() noexcept;

    void push_back(const T &val);


    void push_front(const T &val);


    void pop_back();

    void pop_front();


    T &back();

    T const &back() const;

    T &front();

    T const &front() const;

    iterator begin();

    iterator end();

    const_iterator begin() const;

    const_iterator end() const;

    reverse_iterator rbegin();

    reverse_iterator rend();


    const_reverse_iterator rend() const;

    const_reverse_iterator rbegin() const;

    iterator insert(const_iterator pos, T const &val);

    iterator erase(const_iterator pos);


    void splice(const iterator pos, my_list &other, const_iterator first, const_iterator last);

    template<typename A, typename B>
    friend void swap(my_list<A> &a, my_list<B> &b) noexcept;

private:
    base_node __end;
    node *_end;
    node *_begin;
};

template<typename T>
my_list<T>::my_list() noexcept : __end(), _end(static_cast<node *>(&__end)), _begin(static_cast<node *>(_end)) {
}

template<typename T>
my_list<T>::my_list(const my_list &other)
        : __end(), _end(static_cast<node *>(&__end)), _begin(static_cast<node *>(_end)) {
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }
}

template<typename T>
my_list<T> &my_list<T>::operator=(my_list const &other) {
    if (this == &other)
        return *this;
    clear();
    for (auto it = other.begin(); it != other.end(); ++it) {
        push_back(*it);
    }
    return *this;
}

template<typename T>
bool my_list<T>::empty() const noexcept {
    return _begin == _end;
}

template<typename T>
my_list<T>::~my_list() {
    clear();
}

template<typename T>
T &my_list<T>::back() {
    return static_cast<node *>(_end->prev)->val;
}

template<typename T>
T const &my_list<T>::back() const {
    return static_cast<node *>(_end->prev)->val;
}

template<typename T>
T &my_list<T>::front() {
    return _begin->val;
}

template<typename T>
T const &my_list<T>::front() const {
    return _begin->val;
}

template<typename T>
void my_list<T>::push_back(const T &val) {
    const_iterator it = end();
    insert(it, val);
}

template<typename T>
void my_list<T>::push_front(const T &val) {
    auto tmp = new node(val, nullptr, _begin);
    _begin->prev = tmp;
    _begin = tmp;
}

template<typename T>
void my_list<T>::clear() noexcept {
    while (!empty()) {
        pop_back();
    }
}

template<typename T>
void my_list<T>::pop_back() {
    auto it = end();
    --it;
    erase(it);
}

template<typename T>
void my_list<T>::pop_front() {
    auto tmp = _begin;
    _begin = static_cast<node *>(_begin->next);
    delete (tmp);
    _begin->prev = nullptr;
}

template<typename T>
typename my_list<T>::iterator my_list<T>::begin() {
    return iterator(_begin);
}

template<typename T>
typename my_list<T>::iterator my_list<T>::end() {
    return iterator(_end);
}

template<typename T>
typename my_list<T>::const_iterator my_list<T>::begin() const {
    return const_iterator(_begin);
}

template<typename T>
typename my_list<T>::const_iterator my_list<T>::end() const {
    return const_iterator(_end);
}

template<typename T>
typename my_list<T>::reverse_iterator my_list<T>::rbegin() {
    return reverse_iterator(end());
}

template<typename T>
typename my_list<T>::reverse_iterator my_list<T>::rend() {
    return reverse_iterator(begin());
}

template<typename T>
typename my_list<T>::const_reverse_iterator my_list<T>::rbegin() const {
    return const_reverse_iterator(end());
}


template<typename T>
typename my_list<T>::const_reverse_iterator my_list<T>::rend() const {
    return const_reverse_iterator(begin());
}

template<typename T>
typename my_list<T>::iterator my_list<T>::insert(my_list<T>::const_iterator pos, const T &val) {
    node *tmp = new node(val, pos.ptr->prev, pos.ptr);
    if (empty()) {
        _begin = tmp;
        _end->prev = _begin;
        return _begin;
    }

    if (pos.ptr == _begin) {
        _begin->prev = tmp;
        _begin = tmp;
        return tmp;
    }
    if (pos.ptr->prev->next != nullptr) pos.ptr->prev->next = tmp;
    pos.ptr->prev = tmp;
    return tmp;
}

template<typename T>
typename my_list<T>::iterator my_list<T>::erase(my_list::const_iterator pos) {
    base_node *tmp = pos.ptr;
    base_node *ans = pos.ptr->next;
    if (tmp == _begin) {
        _begin = static_cast<node *>(_begin->next);
    } else {
        pos.ptr->prev->next = pos.ptr->next;
        if (pos.ptr->next != nullptr) pos.ptr->next->prev = pos.ptr->prev;
    }
    delete (static_cast<node *>(tmp));
    return ans;
}

template<typename A, typename B>
void swap(my_list<A> &a, my_list<B> &b) noexcept {
    struct node;
    if (&a == &b) return;
    if (a.empty() && b.empty()) {
        return;
    } else if (a.empty()) {
        auto tmp = a._begin;
        auto t1 = b._begin->next;
        auto t2 = b._end->prev;

        a._begin = b._begin;
        a._end = b._end;

        b._begin = tmp;
        b._end = tmp;

        t1->prev = a._begin;
        t2->next = a._end;
    } else if (b.empty()) {
        auto tmp = b._begin;
        auto t1 = a._begin->next;
        auto t2 = a._end->prev;

        b._begin = a._begin;
        b._end = a._end;

        a._begin = tmp;
        a._end = tmp;

        t1->prev = b._begin;
        t2->next = b._end;
    } else {
        auto tmp1 = a._end->prev;
        auto tmp2 = b._end->prev;
        b._end->prev->next = a._end;
        a._end->prev->next = b._end;
        b._end->prev = tmp1;
        a._end->prev = tmp2;
        tmp1 = a._begin->next;
        tmp2 = b._begin->next;
        b._begin->next->prev = a._begin;
        a._begin->next->prev = b._begin;
        b._begin->next = tmp1;
        a._begin->next = tmp2;

        std::swap(a._begin->val, b._begin->val);
    }
}

template<typename T>
void my_list<T>::splice(const my_list::iterator pos, my_list &other, my_list::const_iterator first,
                        my_list::const_iterator last) {
    if (first == last) return;
    if (pos == begin() && first == other.begin()) {
        pos.ptr->prev = last.ptr->prev;
        last.ptr->prev->next = pos.ptr;
        _begin = static_cast<node *>(first.ptr);
        other._begin = static_cast<node *>(last.ptr);
        last.ptr->prev = nullptr;
    } else if (pos == begin() && first != other.begin()) {
        pos.ptr->prev = last.ptr->prev;
        last.ptr->prev->next = pos.ptr;
        _begin = static_cast<node *>(first.ptr);
        first.ptr->prev->next = last.ptr;
        last.ptr->prev = first.ptr->prev;
        _begin->prev = nullptr;
    } else if (pos != begin() && first == other.begin()) {
        pos.ptr->prev->next = first.ptr;
        first.ptr->prev = pos.ptr->prev;
        pos.ptr->prev = last.ptr->prev;
        last.ptr->prev->next = pos.ptr;
        other._begin = static_cast<node *>(last.ptr);
        other._begin->prev = nullptr;
    } else {
        base_node *pNode = pos.ptr->prev;
        base_node *pBaseNode = pos.ptr;
        base_node *pNode1 = first.ptr;
        base_node *pNode2 = last.ptr->prev;
        base_node *other_p1 = pNode1->prev;
        base_node *other_p2 = last.ptr;
        pNode->next = pNode1;
        pNode1->prev = pNode;
        pNode2->next = pBaseNode;
        pBaseNode->prev = pNode2;
        other_p1->next = other_p2;
        other_p2->prev = other_p1;
    }
}


#endif //LIST_MY_LIST_H
