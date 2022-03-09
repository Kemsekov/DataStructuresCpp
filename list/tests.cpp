#pragma once
#include "list.hpp"
#include <assert.h>
#include <exception>
#include <stdexcept>
#include <iostream>

#define run_test(test_name) test_name(), cout<<#test_name<<" passed\n"

//returns true if function f throws exception when called
template<typename function,typename exception>
bool throws(function f,exception ex){
    try{
        f();
        return false;
    }
    catch(decltype(ex)){
        return true;
    }
}

namespace list_tests{
    void new_list__is_empty(){
        list l;
        assert(l.empty());
    }
    void push_front__works(){
        list l;
        l.push_front(0);
        l.push_front(1);
        l.push_front(2);
        assert(!l.empty());
        assert(l.size()==3);
        assert(l.get_element(0)->value==2);
        assert(l.get_element(1)->value==1);
        assert(l.get_element(2)->value==0);   
    }
    void push_back__works(){
        list l;
        l.push_back(0);
        l.push_back(1);
        l.push_back(2);
        assert(!l.empty());
        assert(l.size()==3);
        assert(l.get_element(0)->value==0);
        assert(l.get_element(1)->value==1);
        assert(l.get_element(2)->value==2);
    }

    void back__works(){
        list l;
        assert(
            throws([&](){l.back();},std::length_error(""))
        );
        l.push_back(0);
        assert(l.back()==0);
        l.push_back(1);
        assert(l.back()==1);
        l.push_back(2);
        assert(l.back()==2);
    }

    void front__works(){
        list l;
        assert(
            throws([&](){l.front();},std::length_error(""))
        );
        l.push_front(0);
        assert(l.front()==0);
        l.push_front(1);
        assert(l.front()==1);
        l.push_front(2);
        assert(l.front()==2);
    }

    void insert__works(){
        list l;
        l.insert(0,0);
        l.insert(1,1);
        l.insert(0,2);
        l.insert(1,10);
        l.insert(2,17);

        assert(!l.empty());
        assert(l.size()==5);
        assert(l.get_element(0)->value==2);
        assert(l.get_element(1)->value==10);
        assert(l.get_element(2)->value==17);
        assert(l.get_element(3)->value==0);
        assert(l.get_element(4)->value==1);
    }

    void get_element__throws_with_wrong_pos(){
        list l;
        assert(
            throws([&](){l.get_element(0);},std::length_error{""})
        );
        l.push_back(0);
        assert(
            throws([&](){l.get_element(2);},std::range_error{""})
        );
        assert(
            throws([&](){l.get_element(-1);},std::range_error{""})
        );
    }

    void pop_back__works(){
        list l;
        l.push_back(0);
        l.push_back(1);
        l.push_back(2);

        l.pop_back();
        assert(l.back()==1);
        l.pop_back();
        assert(l.back()==0);
        l.pop_back();
        assert(l.empty());
        assert(
            throws([&](){l.pop_back();},std::length_error{""})
        );
    }

    void pop_front__works(){
        list l;
        l.push_front(0);
        l.push_front(1);
        l.push_front(2);
        l.pop_front();
        assert(l.front()==1);
        l.pop_front();
        assert(l.front()==0);
        l.pop_front();
        assert(l.empty());
        assert(
            throws([&](){l.pop_front();},std::length_error{""})
        );
    }

    void pop__works(){
        list l;
        l.push_back(0);
        l.push_back(1);
        l.push_back(2);
        l.push_back(3);
        l.push_back(4);
        l.push_back(5);
        
        l.pop(1);
        assert(l.get_element(1)->value==2);
        l.pop(0);
        assert(l.front()==2);
        l.pop(l.size());
        assert(l.back()==4);
        l.pop(1);
        l.pop(1);
        assert(l.size()==1);
        assert(l.back()==l.front() && l.front()==2);
        l.pop(0);
        assert(l.empty());
    }

    void run(){
        using namespace std;
        run_test(new_list__is_empty);
        run_test(push_front__works);
        run_test(push_back__works);
        run_test(front__works);
        run_test(back__works);
        run_test(get_element__throws_with_wrong_pos);
        run_test(pop_back__works);
        run_test(pop_front__works);
        run_test(insert__works);
        run_test(pop__works);
    }
}
