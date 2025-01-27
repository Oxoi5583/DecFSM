#pragma once
#include <iostream>
#include <map>
#include <vector>

template<typename T>
class State;
template<typename T>
class DecFSM;
template<typename T>
class Transition;

template<typename T>
class State{
protected:
    typedef void (T::*ActionFunc)();
    ActionFunc m_action_func = nullptr;
    ActionFunc m_enter_func = nullptr;
public:
    State(ActionFunc p_action_func, ActionFunc p_enter_func = nullptr)
    : m_action_func(p_action_func), m_enter_func(p_enter_func){};

    inline void _update(T* p_object){(p_object->*m_action_func)();};
    inline void _enter(T* p_object){(p_object->*m_enter_func)();};


    friend class State<T>;
    friend class Transition<T>;
    friend class DecFSM<T>;
};

template<typename T>
class Transition{
protected:
    typedef bool (T::*CheckerFunc)();
    State<T>* m_fm_state = nullptr;
    State<T>* m_to_state = nullptr;
    CheckerFunc m_checker = nullptr;
    bool m_is_checker_reversed = false;
public:
    Transition(State<T>* p_fm_state, State<T>* p_to_state, CheckerFunc p_checker, bool p_is_checker_reversed)
    : m_fm_state(p_fm_state), m_to_state(p_to_state), m_checker(p_checker), m_is_checker_reversed(p_is_checker_reversed){};

    inline State<T>* get_fm_state(){return m_fm_state;};
    inline State<T>* get_to_state(){return m_to_state;};

    inline State<T>* _check(T* p_object){
        bool check_ret = (m_is_checker_reversed) ? !(p_object->*m_checker)() : (p_object->*m_checker)();
        if(check_ret){
            return m_to_state;
        }else{
            return m_fm_state;
        }
    };


    friend class State<T>;
    friend class Transition<T>;
    friend class DecFSM<T>;
};

template<typename T>
class DecFSM{
protected:
    State<T>* m_current_state = nullptr;
    T* m_object = nullptr;

    std::map<State<T>*, std::vector<Transition<T>*>> m_transition_map;
public:
    DecFSM(T* p_object, State<T>* p_entry_state)
    : m_current_state(p_entry_state), m_object(p_object){};

    inline void add_transition(Transition<T>* p_transition){
        m_transition_map.try_emplace(p_transition->get_fm_state(), std::vector<Transition<T>*>());   
        m_transition_map[p_transition->get_fm_state()].push_back(p_transition);
    }

    inline void switch_state(State<T>* new_state){
        m_current_state = new_state;
        if(m_current_state->m_enter_func != nullptr){
            m_current_state->_enter(m_object);
        }
    }

    inline void _process(){
        if(m_transition_map.contains(m_current_state)){
            auto transitions = m_transition_map[m_current_state];
            State<T>* new_state = m_current_state;
            for(Transition<T>* transition : transitions){
                new_state = transition->_check(m_object);
                if(new_state != m_current_state){
                    switch_state(new_state);
                    break;
                }
            }
        }
        m_current_state->_update(m_object);
    }

    friend class State<T>;
    friend class Transition<T>;
    friend class DecFSM<T>;
};