#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

typedef int state;
typedef uint8_t priority;

namespace DecFSM{

struct base_event{

};

template<class Event>
struct base_transition {
    private:
        virtual void _v(){};
    protected:

        state __fm_state = 0;
        state __to_state = 0;
    public:
        priority id = 0;
        bool operator ==(const base_transition & other);
        bool operator >(const base_transition & other);
        bool operator <(const base_transition & other);
        bool operator >=(const base_transition & other);
        bool operator <=(const base_transition & other);

        base_transition(){};
        ~base_transition(){};
        state get_from_state();
        state get_target_state();
        void set_from_state(state _fm_state);
        void set_target_state(state _to_state);
        void set_priority(priority _p);
        
        virtual bool condition(Event _event){ return false; };
};



template<class Event>
class dec_fsm {
    typedef base_transition<Event> transition;
protected:
    state current_state;
    unordered_map<state, list<transition*>> cylinder;
public:
    dec_fsm(state _entry_state) : current_state(_entry_state){};
    ~dec_fsm(){};
    void register_transition(transition* _transition);
    void process(Event _event);
    state get_current_state();
}; 

//base_transition
template<class Event>
bool base_transition<Event>::operator ==(const base_transition & other){
    return this->id == other.id;
}
template<class Event>
bool base_transition<Event>::operator >(const base_transition & other){
    return this->id > other.id;
}
template<class Event>
bool base_transition<Event>::operator <(const base_transition & other){
    return this->id < other.id;
}
template<class Event>
bool base_transition<Event>::operator >=(const base_transition & other){
    return this->id >= other.id;
}
template<class Event>
bool base_transition<Event>::operator <=(const base_transition & other){
    return this->id <= other.id;
}
template<class Event>
state base_transition<Event>::get_from_state(){
    return this->__fm_state;
}
template<class Event>
state base_transition<Event>::get_target_state(){
    return this->__to_state; 
}
template<class Event>
void base_transition<Event>::set_from_state(state _fm_state){
    this->__fm_state = _fm_state;
}
template<class Event>
void base_transition<Event>::set_target_state(state _to_state){
    this->__to_state = _to_state;
}
template<class Event>
void base_transition<Event>::set_priority(priority _p){
    this->id = _p;
}


template<class Event>
void dec_fsm<Event>::register_transition(transition* _transition){
    state __fm_state = _transition->get_from_state();
    if(!this->cylinder.contains(__fm_state)){
        //if from state not exists
        this->cylinder.insert_or_assign(__fm_state,list<transition*>());
    }

    list<transition*>* tr = &(this->cylinder[__fm_state]);
    tr->push_back(_transition);
    tr->sort([](transition* a, transition* b){ return (a->id) < (b->id); });
} 
 
template<class Event>
void dec_fsm<Event>::process(Event _event){
    if(this->cylinder.contains(current_state)){
        //std::cout << "State Exists" << std::endl;
        list<transition*> _ls = cylinder[current_state];
        for (auto it = _ls.begin(); it != _ls.end(); it++){
            transition* trans = *(it);
            if(trans->condition(_event)){
                current_state = trans->get_target_state();
                break;
            }
        }
    }
}

template<class Event>
state dec_fsm<Event>::get_current_state(){
    return this->current_state;
}
}
