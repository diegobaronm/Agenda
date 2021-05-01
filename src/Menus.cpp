#include"Menus.hpp"

//Function that stores the selection given by the user.
int HelperMenu(std::vector<std::string> options){
    int aux_int{0};
    std::cout<<"//////////////////////////////////  MENU  ////////////////////////////////////"<<std::endl;
    for(auto opt : options){
        aux_int++;
        std::cout<<aux_int<<"  ";
        std::cout<<opt<<std::endl;
    }
    int selected{};
    std::cout<<std::endl;
    std::cout<<"Select an option: ";
    std::cin>>selected;
    while(std::cin.fail() || selected>aux_int){
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cout<<"Enter a valid option:";
        std::cin>>selected;
    }
    std::cout<<std::endl<<"////////////////////////////////////////////////////////////////////////////////"<<std::endl;
    return selected;
}

int valid_ID(std::vector<int> &ids){
    for(auto& i:ids){std::cout<<i<<std::endl;}
    int id{};
    bool event_found=false;
    while(!event_found){
        std::cout<<"Enter valid [ID]: ";
        std::cin>>id;
        while(std::cin.fail()){
            std::cout<<"Invalid input";
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout<<"Enter valid [ID]: ";
            std::cin>>id;
        }
        event_found=(std::find(ids.begin(),ids.end(),id)!=ids.end());
        if(!event_found){std::cout<<"Event not found!"<<std::endl;}
    }
    return id;

}

Event* retrieve_event(int id){
    for(auto& event : Menu::All_E){
        if(event.Get_ID()==id){
            return &event;
        }
    }
    return nullptr;
}


//Functionalities of the Menus in the program

//Menu 1
void Menu_1::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(selected==-1){this->Deploy();}
    if(selected==1){
        std::cout<<"Showing full agenda: "<<std::endl;selection=-1;
        for(auto& i : Menu::All_E){
            std::cout<<i<<std::endl;
        }
    }
    if(selected==2){std::cout<<"Adding Event...."<<std::endl;
        Event new_event;
        std::cin>>new_event;
        Menu::All_E.emplace_back(new_event);
        selection=-1;
    }

    if(selected==3){std::cout<<"Selecting Event...."<<std::endl;selection=-1;
        for(auto& i : Menu::All_E){
            std::cout<<i<<std::endl;
        }
        vec_menus.at(1)->Execute(vec_menus);}

    if(selected==4){std::cout<<"Saving and finishing...."<<std::endl;selection=-1;}

    this->Execute(vec_menus);
}

static bool ev_selected{false};
static Event* selected_event{nullptr};
//Menu 1
void Menu_2::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(!ev_selected){
        int ev_id=valid_ID(Event::Event_IDs);
        selected_event=retrieve_event(ev_id);
        ev_selected=true;
    }
    if(selected==-1){this->Deploy();}

    if(selected==1){std::cout<<"Showing full event..."<<std::endl;selection=-1;
        std::cout<<(*selected_event);
    }

    if(selected==2){std::cout<<"Changing event...."<<std::endl;selection=-1;}
    if(selected==3){std::cout<<"Adding task..."<<std::endl;selection=-1;}
    if(selected==4){std::cout<<"Selecting task...."<<std::endl;selection=-1;
        vec_menus.at(2)->Execute(vec_menus);
    }
    if(selected==5){std::cout<<"Going back...."<<std::endl;selection=-1;
        ev_selected=false;
        selected_event=nullptr;
        vec_menus.at(0)->Execute(vec_menus);
    }
    this->Execute(vec_menus);
}

void Menu_3::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(selected==-1){this->Deploy();}
    if(selected==1){std::cout<<"Showing full task..."<<std::endl;selection=-1;}
    if(selected==2){std::cout<<"Changing task...."<<std::endl;selection=-1;}
    if(selected==3){std::cout<<"Adding subtask..."<<std::endl;selection=-1;}
    if(selected==4){std::cout<<"Selecting subtask...."<<std::endl;selection=-1;
    vec_menus.at(3)->Execute(vec_menus);}
    if(selected==5){std::cout<<"Completing..."<<std::endl;selection=-1;}
    if(selected==6){std::cout<<"Going back...."<<std::endl;selection=-1;
    vec_menus.at(1)->Execute(vec_menus);}
    this->Execute(vec_menus);
}

void Menu_4::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(selected==-1){this->Deploy();}
    if(selected==1){std::cout<<"Showing full subtask..."<<std::endl;selection=-1;}
    if(selected==2){std::cout<<"Changing subtask...."<<std::endl;selection=-1;}
    if(selected==3){std::cout<<"Completing..."<<std::endl;selection=-1;}
    if(selected==4){std::cout<<"Going back...."<<std::endl;selection=-1;
    vec_menus.at(2)->Execute(vec_menus);}
    this->Execute(vec_menus);
}