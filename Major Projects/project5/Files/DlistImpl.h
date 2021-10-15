#ifndef DLISTIMPL_H
#define DLISTIMPL_H

#include "Dlist.h"

template <class T>
bool Dlist<T>::isEmpty() const{
    return this->first == nullptr;
}

template <class T>
void Dlist<T>::insertFront(T *op){
    node* newN = new node;
    newN->op = op;
    if(this->isEmpty()){
        newN->next = nullptr;
        newN->prev = nullptr;
        this->first = newN;
        this->last = newN;
    }
    else{
        newN->prev = nullptr;
        newN->next = first;
        first->prev = newN;
        first = newN;
    }
}

template <class T>
void Dlist<T>::insertBack(T *op){
    node* newN = new node;
    newN->op = op;
    if(this->isEmpty()){
        newN->prev = nullptr;
        newN->next= nullptr;
        this->first = newN;
        this->last = newN;
    }
    else{
        newN->prev = last;
        newN->next = nullptr;
        last->next = newN;
        last = newN;
    }
}

template <class T>
T *Dlist<T>::removeFront(){
    if(this->isEmpty()) throw EmptyList();
    node* keep = first;
    T* kVal = keep->op;
    if(keep == last){
        this->first = nullptr;
        this->last = nullptr;
    }
    else{
        this->first = keep->next;
        first->prev = nullptr;
    }
    delete keep;
    return kVal;
}

template <class T>
T *Dlist<T>::removeBack(){
    if(this->isEmpty()) throw EmptyList();
    node* keep = last;
    T* kVal = keep->op;
    if(keep == first){
        this->first = nullptr;
        this->last = nullptr;
    }
    else{
        this->last = keep->prev;
        last->next = nullptr;
    }
    delete keep;
    return kVal;
}

template <class T>
void Dlist<T>::removeAll(){
    if(!this->isEmpty()){
        node* item = this->first;
        while(item!= this->last){
            item= item->next;
            delete item->prev->op;
            delete item->prev;
        }
        //removing the last item
        delete item->op;
        delete item;
    }
    this->first = this->last = nullptr;
}

template <class T>
void Dlist<T>::copyAll(const Dlist &l){
    if(!l.isEmpty()){
        node* item = l.last;
        while(item!= l.first){
            T* copyItem = new T(*item->op);
            this->insertFront(copyItem);
            item = item->prev;
        }
        this->insertFront(new T(*item->op));
    }
}

template <class T>
Dlist<T>::Dlist():first(nullptr), last(nullptr){}

template <class T>
Dlist<T>::Dlist(const Dlist &l):first(nullptr), last(nullptr){
    copyAll(l);
}

template <class T>
Dlist<T> &Dlist<T>::operator=(const Dlist &l){
    if(this!= &l){
        removeAll();
        copyAll(l);
    }
    return *this;
}

template <class T>
Dlist<T>::~Dlist(){
    removeAll();
}

#endif