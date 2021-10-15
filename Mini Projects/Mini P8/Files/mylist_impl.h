//
// Created by cyx on 20-5-29.
//

#ifndef INTLIST_IMPL_H
#define INTLIST_IMPL_H

#include <iostream>
#include "mylist.h"

template <class T>
void List<T>::print()
{
    Node_t<T>* itr = first;
    while(itr){
        std::cout << itr->val;
        itr = itr->next;
    }
    std::cout << "\n";
}

template <class T>
bool List<T>::isEmpty() const{
    return first == nullptr;
}

template <class T>
T List<T>::removeFront(){
    if(isEmpty()) throw EmptyList();
    Node_t<T> *item = first;
    first = item->next;
    if(isEmpty()){
        last = nullptr;
    }
    T value = item->val;
    delete item;
    return value;
}

template <class T>
void List<T>::removeAll(){
    while(!isEmpty()) removeFront();
}

template <class T>
const Node_t<T>* List<T>::returnFront() const{
    return first;
}

template <class T>
void List<T>::insertBack(T val){
    if(isEmpty()) first = last = new Node_t<T>;
    else last = last->next = new Node_t<T>;
    last->val = val;
    last->next = nullptr;
}

/*template <class T>
List<T> reverse(const List<T>& target){
    List<T> result;
    const Node_t<T>* t_first = target.returnFront();
    while(t_first){
        result.insertBack(t_first->val);
        t_first = t_first->next;
    }
    return result;
}*/

template <class T>
void List<T>::copyFrom(const List<T> &l){
    this->removeAll();
    //List x = reverse(l);
    const Node_t<T>* front = l.returnFront();
    while (front != nullptr){ insertBack(front->val);
        front = front->next;}
}

template <class T>
List<T>::List(): first(nullptr), last(nullptr){}
template <class T>
List<T>::List(const List &l): first(nullptr), last(nullptr){
    copyFrom(l);
}
template <class T>
List<T>& List<T>::operator=(const List<T> &l){
    if(this != &l) copyFrom(l);
    return *this;
}
template <class T>
List<T>::~List(){
    removeAll();
}

bool isLarger(const List<int> &a, const List<int> &b){
    if(a.isEmpty() && b.isEmpty())
        return false;
    bool flag = false;
    const Node_t<int>* a_first = a.returnFront();
    const Node_t<int>* b_first = b.returnFront();
    while( a_first && b_first ){
        if(a_first->val > b_first->val){
            flag = true;}
        else if(a_first->val < b_first->val){
            flag = false;}
        a_first= a_first->next;
        b_first= b_first->next;
    }
    if( a_first || b_first ){
        if(a_first) flag = true;
        else flag =  false;
    } 
    return flag;
}

/*List<int> reversed(const List<int>& target){
    List<int> result;
    const Node_t<int>* t_first = target.returnFront();
    while(t_first){
        result.insertBack(t_first->val);
        t_first = t_first?t_first->next:nullptr;
    }
    return result;
}*/

List<int> add_digit_by_digit(const Node_t<int>* a_first, const Node_t<int>* b_first){
    List<int> result;
    int next_itr = 0;
    while( a_first|| b_first|| next_itr){
        int add = (a_first ? a_first->val : 0) + (b_first ? b_first->val : 0) + next_itr;
        next_itr = add/10;
        add = add%10;
        result.insertBack(add);
        a_first = a_first?a_first->next:nullptr;
        b_first = b_first?b_first->next:nullptr;
    }
    return result;
}

List<int> add(const List<int> &a, const List<int> &b){
    const Node_t<int>* a_first = a.returnFront();
    const Node_t<int>* b_first = b.returnFront();
    return add_digit_by_digit(a_first, b_first);
}


#endif //INTLIST_IMPL_H
