#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

typedef int state;
typedef uint8_t priority;

namespace DecFSM{

struct base_action {
    protected:
        state on_state;
    public:
        state get_on_state(){
            return this->on_state;
        };
        void set_on_state(state _on_state){
            this->on_state = _on_state;
        };
        virtual void enter(){};
        virtual void exit(){};
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


typedef base_action action;

template<class Event>
class dec_fsm {
    typedef base_transition<Event> transition;
protected:
    bool is_engine_started = false;
    state current_state;
    unordered_map<state, list<transition*>> cylinder;
    unordered_map<state, action*> actions;
    void do_enter_and_exit_job(state old_state, state new_state);
    void do_enter_job(state enter_state);
    void do_exit_job(state exit_state);
    bool check_transit(transition* trans, Event _event);
public:
    dec_fsm(state _entry_state) : current_state(_entry_state){};
    ~dec_fsm(){};
    void register_transition(transition* _transition);
    void register_action(action* _action);
    void process(Event _event);
    void start_engine();
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
void dec_fsm<Event>::register_action(action* _action){
    state _on_state = _action->get_on_state();
    if(!actions.contains(_on_state)){
        actions.insert_or_assign(_on_state, _action);
    }
} 
 

template<class Event>
void dec_fsm<Event>::do_enter_and_exit_job(state old_state, state new_state){
    // exit
    this->do_exit_job(old_state);
    // enter
    this->do_enter_job(new_state);
}

template<class Event>
void dec_fsm<Event>::do_enter_job(state enter_state){
    if(actions.contains(enter_state)){
        actions[enter_state]->enter();
    }
}

template<class Event>
void dec_fsm<Event>::do_exit_job(state exit_state){
    if(actions.contains(exit_state)){
        actions[exit_state]->exit();
    }
}

template<class Event>
bool dec_fsm<Event>::check_transit(transition* trans, Event _event){
    if(trans->condition(_event)){
        state new_state = trans->get_target_state();
        state old_state = current_state;
        do_enter_and_exit_job(old_state,new_state);

        current_state = new_state;
        return true;
    }else{
        return false;
    }
}

template<class Event>
void dec_fsm<Event>::process(Event _event){
    if(!this->is_engine_started){
        this->start_engine();
    }
    if(this->cylinder.contains(current_state)){
        //std::cout << "State Exists" << std::endl;
        list<transition*> _ls = cylinder[current_state];
        for (auto it = _ls.begin(); it != _ls.end(); it++){
            transition* trans = *(it);
            if(this->check_transit(trans, _event)){
                break;
            }
        }
    }
}

template<class Event>
void dec_fsm<Event>::start_engine(){
    this->is_engine_started = true;
    do_enter_job(this->current_state);
}

template<class Event>
state dec_fsm<Event>::get_current_state(){
    return this->current_state;
}

}
