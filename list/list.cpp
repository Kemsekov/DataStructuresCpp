#pragma once
#include "list.hpp"
#include <stdexcept>

inline void throw_if_empty(list* l){
    if(l->empty()) 
        std::__throw_length_error("there is no elements in list");
}

inline void throw_if_invalid_pos(list* l, int pos){
    throw_if_empty(l);
    if(pos>=l->size())
        std::__throw_range_error("pos must be less than size of the list!");
    if(pos<0)
        std::__throw_range_error("pos cannot be less than zero!");   
}

list::~list(){
    auto buf = _front;
    while (buf!=nullptr)
    {
        auto to_delete = buf;
        buf = buf->next;
        delete to_delete;
    }
}


inline bool list::empty(){
    return _size==0;
}
inline int list::size(){
    return _size;
}
double& list::front(){
    throw_if_empty(this);
    return _front->value;
}

double& list::back(){
    throw_if_empty(this);
    return _back->value;
}

void list::push_back(double n){
    if(empty()){
        _back = new element{n};
        _front = _back;
    }
    else{
        _back->next = new element{n};
        _back->next->previous = _back;
        _back = _back->next;
    }
    _size++;
}

void list::push_front(double n){
    if(empty()){
        _front = new element{n};
        _back = _front;
    }
    else{
        _front->previous = new element{n};
        _front->previous->next = _front;
        _front = _front->previous;
    }
    _size++;
}

void list::pop_back(){
    throw_if_empty(this);
    auto to_delete = _back;
    _back = _back->previous;
    delete to_delete;
    if(_back != nullptr)
        _back->next = nullptr;
    _size--;
    if(empty()){
        _back = nullptr;
        _front = nullptr;
    }
}

void list::pop_front(){
    throw_if_empty(this);
    auto to_delete = _front;
    _front = _front->next;
    delete to_delete;
    if(_front != nullptr)
        _front->previous = nullptr;
    _size--;
    if(empty()){
        _front = nullptr;
        _back = nullptr;
    }
}

element* list::get_element(int pos){
    throw_if_invalid_pos(this,pos);
    element* result;
    if(pos>_size/2){
        result = _back;
        for(int i = pos+1;i<_size;i++)
            result = result->previous;
    }
    else{
        result = _front;
        for(int i = 0;i<pos;i++)
            result = result->next;
    }
    return result;
}

void list::insert(int pos,double n){
    if(pos==0){
        push_front(n);
        return;
    }
    if(pos==_size){
        push_back(n);
        return;
    }
    auto insert_point = get_element(pos);
    auto previous = insert_point->previous;
    auto new_element = new element{n,insert_point,previous};
    previous->next = new_element;
    insert_point->previous = new_element;
    _size++;
}

void list::pop(int pos){
    if(pos==0){
        pop_front();
        return;
    }
    if(pos==_size || pos==_size-1){
        pop_back();
        return;
    }
    auto to_pop = get_element(pos);
    if(to_pop->previous != nullptr)
        to_pop->previous->next = to_pop->next;
    if(to_pop->next != nullptr)
        to_pop->next->previous = to_pop->previous;
    
    delete to_pop;
    _size--;
    

}
