#pragma once
#include <iostream>
#include <unordered_map>
#include <list>
#include <algorithm>

using namespace std;

typedef int state;
typedef uint8_t priority;

namespace DecFSM{


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
        
        virtual bool condition(){ return false; };
};


typedef base_transition transition;

class dec_fsm {
    
protected:
    state current_state;
    unordered_map<state, list<transition*>> cylinder;
public:
    dec_fsm(state _entry_state) : current_state(_entry_state){};
    ~dec_fsm(){};
    void add_row(transition* _transition);
    void process();
    state get_current_state();
};


}
