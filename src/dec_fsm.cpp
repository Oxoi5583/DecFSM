#include "DecFSM.h"

namespace DecFSM{

//base_transition
bool base_transition::operator ==(const base_transition & other){
    return this->id == other.id;
}
bool base_transition::operator >(const base_transition & other){
    return this->id > other.id;
}

bool base_transition::operator <(const base_transition & other){
    return this->id < other.id;
}

bool base_transition::operator >=(const base_transition & other){
    return this->id >= other.id;
}

bool base_transition::operator <=(const base_transition & other){
    return this->id <= other.id;
}

state base_transition::get_from_state(){
    return this->__fm_state;
}
state base_transition::get_target_state(){
    return this->__to_state;
}

void base_transition::set_from_state(state _fm_state){
    this->__fm_state = _fm_state;
}
void base_transition::set_target_state(state _to_state){
    this->__to_state = _to_state;
}
void base_transition::set_priority(priority _p){
    this->id = _p;
}



void dec_fsm::add_row(transition* _transition){
    state __fm_state = _transition->get_from_state();
    if(!this->cylinder.contains(__fm_state)){
        //if from state not exists
        this->cylinder.insert_or_assign(__fm_state,list<transition*>());
    }

    list<transition*>* tr = &(this->cylinder[__fm_state]);
    tr->push_back(_transition);
    tr->sort([](transition* a, transition* b){ return a->id < b->id; });
}

void dec_fsm::process(){
    if(this->cylinder.contains(current_state)){
        //std::cout << "State Exists" << std::endl;
        list<transition*> _ls = cylinder[current_state];
        for (list<transition*>::iterator it = _ls.begin(); it != _ls.end(); it++){
            transition* trans = *(it);
            if(trans->condition()){
                //std::cout << "pri : " << (int)trans->id << std::endl;
                //std::cout << "From " << current_state << " Go to " << trans->get_target_state() << std::endl;
                current_state = trans->get_target_state();
                break;
            }
        }
    }
}

state dec_fsm::get_current_state(){
    return this->current_state;
}

} 