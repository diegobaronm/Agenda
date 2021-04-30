#include"Menus.hpp"

//Function that stores the selection given by the user.
int HelperMenu(std::vector<std::string> options){
    int aux_int{0};
    for(auto opt : options){
        aux_int++;
        std::cout<<aux_int<<"  ";
        std::cout<<opt<<std::endl;
    }
    int selected{};
    std::cout<<"Select an option:"<<std::endl;
    std::cin>>selected;
    while(std::cin.fail() || selected>aux_int){
        std::cin.clear();
        std::cin.ignore(1000,'\n');
        std::cout<<"Enter a valid option"<<std::endl;
        std::cin>>selected;
    }
    return selected;
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
    if(selected==2){std::cout<<"Adding Event...."<<std::endl;selection=-1;}

    if(selected==3){std::cout<<"Selecting Event...."<<std::endl;selection=-1;
        vec_menus.at(1)->Execute(vec_menus);}

    if(selected==4){std::cout<<"Saving and finishing...."<<std::endl;selection=-1;}

    this->Execute(vec_menus);
}

//Menu 1
void Menu_2::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(selected==-1){this->Deploy();}
    if(selected==1){std::cout<<"Showing full event..."<<std::endl;selection=-1;}
    if(selected==2){std::cout<<"Changing event...."<<std::endl;selection=-1;}
    if(selected==3){std::cout<<"Adding task..."<<std::endl;selection=-1;}
    if(selected==4){std::cout<<"Selecting task...."<<std::endl;selection=-1;
    vec_menus.at(2)->Execute(vec_menus);}
    if(selected==5){std::cout<<"Going back...."<<std::endl;selection=-1;
    vec_menus.at(0)->Execute(vec_menus);}
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