#pragma once

struct element{
    double value      = 0;
    element* next     = nullptr;
    element* previous = nullptr;
};

class list{ 
    public:
    bool empty();
    double& front();
    double& back();
    void push_back(double n);
    void push_front(double n);
    int size();
    element* get_element(int pos);
    void pop_back();
    void pop_front();
    void insert(int pos,double n);
    void pop(int pos);  
    ~list();
    private:
    element* _front = nullptr;
    element* _back = nullptr;
    int _size = 0;
};