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
    if(selected==2){

        vec_menus.at(1)->Execute(vec_menus);

    }
    if(selected==3){std::cout<<"Say Bye"<<std::endl;selection=-1;}
    this->Execute(vec_menus);
}

//Menu 1
void Menu_2::Execute(std::vector<Menu*> vec_menus){
    int selected=selection;
    if(selected==-1){this->Deploy();}
    if(selected==1){std::cout<<"Say Hello"<<std::endl;selection=-1;}
    if(selected==2){std::cout<<"Say Bye"<<std::endl;selection=-1;}
    this->Execute(vec_menus);
}