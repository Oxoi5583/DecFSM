#include <DecFSM2.h>
#include <iostream>

class Player{
public:
    void action_idle(){std::cout << "Idling" << std::endl;};
    void action_walk(){std::cout << "Walking" << std::endl;};
    void action_run(){std::cout << "Running" << std::endl;};

    void enter_idle(){std::cout << "Start Idle" << std::endl;};
    void enter_walk(){std::cout << "Start Walk" << std::endl;};
    void enter_run(){std::cout << "Start Run" << std::endl;};


    bool is_walking(){return walking;};
    bool is_running(){return running;}

    bool walking = false;
    bool running = false;
private:

};


int main(){
    Player* player = new Player();

    State<Player>* idle_state = new State<Player>(&Player::action_idle,&Player::enter_idle);
    State<Player>* walk_state = new State<Player>(&Player::action_walk,&Player::enter_walk);
    State<Player>* run_state = new State<Player>(&Player::action_run,&Player::enter_run);

    Transition<Player>* idle_to_walk_transition = new Transition(idle_state,walk_state,&Player::is_walking,false);
    Transition<Player>* walk_to_idle_transition = new Transition(walk_state,idle_state,&Player::is_walking, true);
    Transition<Player>* walk_to_run_transition = new Transition(walk_state,run_state,&Player::is_running, false);
    Transition<Player>* run_to_walk_transition = new Transition(run_state,walk_state,&Player::is_running, true);

    DecFSM<Player>* fsm = new DecFSM<Player>(player,idle_state);
    fsm->add_transition(idle_to_walk_transition);
    fsm->add_transition(walk_to_idle_transition);
    fsm->add_transition(walk_to_run_transition);
    fsm->add_transition(run_to_walk_transition);


    for(int i = 0; i < 100; i++){
        fsm->_process();
        if(i == 10){
            std::cout << i << " : " << "Player Start Walking" << std::endl;
            player->walking = true;
        }
        if(i == 50){
            std::cout << i << " : " << "Player Start Running" << std::endl;
            player->running = true;
        }
        if(i == 70){
            std::cout << i << " : " << "Player Stop Running" << std::endl;
            player->running = false;
        }
        if(i == 80){
            std::cout << i << " : " << "Player Stop Walking" << std::endl;
            player->walking = false;
        }
        
    }


    return 0;
}



