#include <iostream>
#include <cstdlib>
#include "DecFSM.h"

enum my_state{
    IDLE = 0,
    WALK = 1,
    RUN = 2,
};

const char* my_state_name(int st){
    switch (st)
    {
    case my_state::IDLE:
        return "IDLE";
        break;
    case my_state::WALK:
        return "WALK";
        break;
    case my_state::RUN:
        return "RUN";
        break;
    default:
        return "UNKNOWN";
        break;
    };
}

struct evt{
    float speed = 0;
};

float run_speed = 250;

struct IDLE_to_WALK : public DecFSM::base_transition<evt>
{
    IDLE_to_WALK() : base_transition(){
        this->set_from_state(my_state::IDLE);
        this->set_target_state(my_state::WALK);
        this->set_priority(254);
    }
    
    bool condition(evt _evt) override{
        bool ret;
        ret = abs(_evt.speed) != 0;
        return ret;
    }
};

struct IDLE_to_RUN : public DecFSM::base_transition<evt>
{
    IDLE_to_RUN() : base_transition(){
        this->set_from_state(my_state::IDLE);
        this->set_target_state(my_state::RUN);
    }
    
    bool condition(evt _evt) override{
        return abs(_evt.speed) >= run_speed;
    }
};

struct WALK_to_RUN : public DecFSM::base_transition<evt>
{
    WALK_to_RUN() : base_transition(){
        this->set_from_state(my_state::WALK);
        this->set_target_state(my_state::RUN);
    }
    
    bool condition(evt _evt) override{
        return abs(_evt.speed) >= run_speed;
    }
};
struct WALK_to_IDLE : public DecFSM::base_transition<evt>
{
    WALK_to_IDLE() : base_transition(){
        this->set_from_state(my_state::WALK);
        this->set_target_state(my_state::IDLE);
    }
    
    bool condition(evt _evt) override{
        return abs(_evt.speed) == 0;
    }
};

struct RUN_to_IDLE : public DecFSM::base_transition<evt>
{
    RUN_to_IDLE() : base_transition(){
        this->set_from_state(my_state::RUN);
        this->set_target_state(my_state::IDLE);
    }
    
    bool condition(evt _evt) override{
        return abs(_evt.speed) == 0;
    }
};

struct RUN_to_WALK : public DecFSM::base_transition<evt>
{
    RUN_to_WALK() : base_transition(){
        this->set_from_state(my_state::RUN);
        this->set_target_state(my_state::WALK);
    }
    
    bool condition(evt _evt) override{
        return abs(_evt.speed) != 0 && abs(_evt.speed) < run_speed; 
    }
};

struct RUN_action : public DecFSM::base_action{
    RUN_action(){
        this->set_on_state(my_state::RUN);
    };
    void enter() override{
        std::cout << "Enter Run State" << std::endl;
    };
    void exit() override{
        std::cout << "Exit Run State" << std::endl;
    };
};

struct WALK_action : public DecFSM::base_action{
    WALK_action(){
        this->set_on_state(my_state::WALK);
    };
    void enter() override{
        std::cout << "Enter Walk State" << std::endl;
    };
    void exit() override{
        std::cout << "Exit Walk State" << std::endl;
    };
};

struct IDLE_action : public DecFSM::base_action{
    IDLE_action(){
        this->set_on_state(my_state::IDLE);
    };
    void enter() override{
        std::cout << "Enter IDLE State" << std::endl;
    };
    void exit() override{
        std::cout << "Exit IDLE State" << std::endl;
    };
};



int main(){
    // Instance fsm and give a Entry state
    DecFSM::dec_fsm<evt> fsm(my_state::IDLE);

    // Instance all transitions
    IDLE_to_WALK trans1;
    IDLE_to_WALK trans2;
    WALK_to_IDLE trans3;
    WALK_to_RUN trans4;
    RUN_to_IDLE trans5;
    RUN_to_WALK trans6;
    
    // register all transitions
    fsm.register_transition(&trans1);
    fsm.register_transition(&trans2);
    fsm.register_transition(&trans3);
    fsm.register_transition(&trans4);
    fsm.register_transition(&trans5);
    fsm.register_transition(&trans6);

    // Instance all actions
    WALK_action action1;
    IDLE_action action2;
    RUN_action action3;

    // register all action
    fsm.register_action(&action1);
    fsm.register_action(&action2);
    fsm.register_action(&action3);

    // Instance event data
    evt _evt;

    for (size_t i = 0; i < 1000; i++)
    {
        // change event data
        if(i == 150){
            _evt.speed = run_speed/2;
        }
        if(i == 350){
            _evt.speed = run_speed;
        }
        if(i == 600){
            _evt.speed = run_speed/2;
        }
        if(i == 800){
            _evt.speed = 0;
        }
        if(i%20 == 0){
            std::cout 
            << i 
            << " : " 
            << my_state_name(fsm.get_current_state()) 
            << "(speed = " 
            << _evt.speed << ")" 
            << std::endl;
        }
        // pass the event data to FSM and check transition
        fsm.process(_evt);
    }
    


    return 0;
}



