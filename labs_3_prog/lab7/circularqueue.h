#ifndef CIRCULARQUEUE_H
#define CIRCULARQUEUE_H

#include <iostream>
using namespace std;

template <class T>
class CircularQueue
{
public:
    template <class DataT>
    class Element
    {
    public:
        DataT &data;
        Element<DataT> *next;
        Element<DataT> *perv;
        Element() : next(nullptr), perv(nullptr), data(0) { }
        Element(DataT &data) : data(data), next(nullptr), perv(nullptr) { }
        Element(DataT &data, Element *next, Element *perv) : data(data), next(next), perv(perv) { }
        ~Element() { }
    };

    unsigned len = 0;
    unsigned size;

    Element<T> *first;
    Element<T> *last;
    Element<T> *current;

    CircularQueue() : size(0), first(nullptr), last(nullptr), current(nullptr) { }
    CircularQueue(unsigned size);
    ~CircularQueue() { }

    void pushBack(T &data);
    void popForward();
    void next();
    T getCurrent() const;
    unsigned length() const;
};

template<class T>
inline CircularQueue<T>::CircularQueue(unsigned size) : first(nullptr), last(nullptr), current(nullptr), size(size)
{
    if(size < 1) {
        throw runtime_error("Wrong elements count");
    }
}

template<class T>
inline void CircularQueue<T>::pushBack(T &data)
{
    if(len >= size) {
        throw runtime_error("Queue size not enough for add new element");
    }

    Element<T> *el = new Element<T>(data);
    len++; // Увеличиваем счетчик элементов
    if(!first){
        first = el;
        last = el;
        current = el;
        return;
    }

    last->next = el;
    el->perv = last;
    last = el;
}

template<class T>
inline void CircularQueue<T>::popForward()
{
    if(!first) {
        return;
    }

    if(current == first) {
        current = current->next;
    }

    len--; // Уменьшаем счетчик элементов
    if(len){
        first = first->next;
        delete first->perv;
        first->perv = nullptr;
    } else {
        delete first;
    }
}

template<class T>
inline void CircularQueue<T>::next()
{
    if(current == last){
        current = first;
        return;
    }

    current = current->next;
}

template<class T>
inline T CircularQueue<T>::getCurrent() const
{
    return current->data;
}

template<class T>
inline unsigned CircularQueue<T>::length() const
{
    return len;
}

#endif // CIRCULARQUEUE_H
