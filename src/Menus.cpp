#include"Menus.hpp"

//Function that stores the selection given by the user.
int HelperMenu(std::vector<std::string> options){
    int aux_int{0};
    std::cout<<"///////////////////////////////////  MENU  /////////////////////////////////////"<<std::endl;
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
    std::cout<<std::endl<<"//////////////////////////////////////////////////////////////////////////////////"<<std::endl;
    return selected;
}

int valid_ID(std::vector<int> &ids){
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

MainTask* retrieve_task(int id){
    for(auto& task : Menu::All_MT){
        if(task.Get_ID()==id){
            return &task;
        }
    }
    return nullptr;
}

SubTask* retrieve_subtask(int id){
    for(auto& subtask : Menu::All_ST){
        if(subtask.Get_ID()==id){
            return &subtask;
        }
    }
    return nullptr;
}

void Organize_Tasks(std::vector<MainTask> &MTs,std::vector<SubTask> &STs){
    for(auto& p : MTs){
        for(auto& q : STs){
            if(q.Get_T_ID()==p.Get_ID()){
                p.Add_SubTask(&q);
            }
        }
    }
}

void Organize_Events(std::vector<Event> &Es,std::vector<MainTask> &MTs){
    for(auto& p : Es){
        for(auto& q : MTs){
            if(q.Get_eID()==p.Get_ID()){
                p.Add_Task(&q);
            }
        }
    }
}

void Organize(){
    Organize_Tasks(Menu::All_MT,Menu::All_ST);
    Organize_Events(Menu::All_E,Menu::All_MT);
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
static int ev_id{};
//Menu 1
void Menu_2::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(!ev_selected){
        ev_id=valid_ID(Event::Event_IDs);
        selected_event=retrieve_event(ev_id);
        ev_selected=true;
    }
    if(selected==-1){this->Deploy();}

    if(selected==1){std::cout<<"Showing full event..."<<std::endl;selection=-1;
        std::cout<<(*selected_event);
    }

    if(selected==2){std::cout<<"Changing event...."<<std::endl;
        std::cin>>(*selected_event);
        selection=-1;
    }
    if(selected==3){std::cout<<"Adding task..."<<std::endl;
        MainTask new_maintask;
        std::cin>>new_maintask;
        Menu::All_MT.push_back(new_maintask);
        selected_event->Add_Task(&(Menu::All_MT.at(Menu::All_MT.size()-1)));
        selection=-1;
    }
    if(selected==4){std::cout<<"Selecting task...."<<std::endl;selection=-1;
        for(auto& i : Menu::All_MT){
            if(i.Get_eID()==ev_id)
                std::cout<<i<<std::endl;
        }
        vec_menus.at(2)->Execute(vec_menus);
    }
    if(selected==5){std::cout<<"Going back...."<<std::endl;selection=-1;
        ev_selected=false;
        selected_event=nullptr;
        vec_menus.at(0)->Execute(vec_menus);
    }
    this->Execute(vec_menus);
}

static bool task_selected{false};
static MainTask* selected_task{nullptr};
static int task_id{};

void Menu_3::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(!task_selected){
        task_id=valid_ID(MainTask::MainTask_IDs);
        selected_task=retrieve_task(task_id);
        task_selected=true;
    }
    if(selected==-1){this->Deploy();}
    if(selected==1){std::cout<<"Showing full task..."<<std::endl;selection=-1;
        std::cout<<(*selected_task);
    }
    if(selected==2){std::cout<<"Changing task...."<<std::endl;
        std::cin>>(*selected_task);
        selection=-1;
    }
    if(selected==3){std::cout<<"Adding subtask..."<<std::endl;
        SubTask new_subtask;
        std::cin>>new_subtask;
        Menu::All_ST.push_back(new_subtask);
        selected_task->Add_SubTask(&(Menu::All_ST.at(Menu::All_ST.size()-1)));
        selected_event->Remove_Task(ev_id);
        selected_event->Add_Task(selected_task);
        selection=-1;
    }
    if(selected==4){std::cout<<"Selecting subtask...."<<std::endl;selection=-1;
        for(auto& i : Menu::All_ST){
            if(i.Get_T_ID()==task_id)
                std::cout<<i<<std::endl;
        }
        vec_menus.at(3)->Execute(vec_menus);
    }
    if(selected==5){std::cout<<"Completing..."<<std::endl;
        selected_task->Complete();
        selected_event->Remove_Task(ev_id);
        selected_event->Add_Task(selected_task);
        selection=-1;
    }
    if(selected==6){std::cout<<"Going back...."<<std::endl;selection=-1;
        task_selected=false;
        selected_task=nullptr;
        vec_menus.at(1)->Execute(vec_menus);
    }
    this->Execute(vec_menus);
}

static bool subtask_selected{false};
static SubTask* selected_subtask{nullptr};
static int subtask_id{};

void Menu_4::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(!subtask_selected){
        subtask_id=valid_ID(SubTask::SubTask_IDs);
        selected_subtask=retrieve_subtask(subtask_id);
        subtask_selected=true;
    }
    if(selected==-1){this->Deploy();}
    if(selected==1){std::cout<<"Showing full subtask..."<<std::endl;selection=-1;
        std::cout<<(*selected_subtask);
    }
    if(selected==2){std::cout<<"Changing subtask...."<<std::endl;
        std::cin>>(*selected_subtask);
        selection=-1;
    }
    if(selected==3){std::cout<<"Completing..."<<std::endl;
        selected_subtask->Complete();
        Organize();
        selection=-1;
    }
    if(selected==4){std::cout<<"Going back...."<<std::endl;selection=-1;
        subtask_selected=false;
        selected_subtask=nullptr;
        vec_menus.at(2)->Execute(vec_menus);
    }
    this->Execute(vec_menus);
}