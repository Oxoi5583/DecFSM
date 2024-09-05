#include <iostream>

#include "DecFSM.h"

enum my_state{
    A = 0,
    B = 1,
    C = 2,
};


struct A_to_B : public DecFSM::base_transition
{
    A_to_B() : base_transition(){
        this->set_from_state(my_state::A);
        this->set_target_state(my_state::B);
    }
    
    bool condition() override{
        return true;
    }
};

struct A_to_C : public DecFSM::base_transition
{
    A_to_C() : base_transition(){
        this->set_from_state(my_state::A);
        this->set_target_state(my_state::C);
        this->set_priority(254);
    }
    
    bool condition() override{
        return true;
    }
};

struct B_to_C : public DecFSM::base_transition
{
    B_to_C() : base_transition(){
        this->set_from_state(my_state::B);
        this->set_target_state(my_state::C);
    }
    
    bool condition() override{
        return true;
    }
};

struct C_to_A : public DecFSM::base_transition
{
    C_to_A() : base_transition(){
        this->set_from_state(my_state::C);
        this->set_target_state(my_state::A);
    }
    
    bool condition() override{
        return true;
    }
};


int main(){
    DecFSM::dec_fsm fsm(my_state::A);
    A_to_B trans1;
    A_to_C trans1_2;
    B_to_C trans2;
    C_to_A trans3;
    fsm.add_row(&trans1);
    fsm.add_row(&trans1_2);
    fsm.add_row(&trans2);
    fsm.add_row(&trans3);
    std::cout << fsm.get_current_state() << std::endl;
    fsm.process();
    std::cout << fsm.get_current_state() << std::endl;
    fsm.process();
    std::cout << fsm.get_current_state() << std::endl;
    fsm.process();
    std::cout << fsm.get_current_state() << std::endl;
    return 0;
}