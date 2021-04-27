#include<vector>
#include<string>
#include<iostream>

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

class Menu{
    protected:
    std::vector<std::string> options;
    int selection{-1};
    int Menu_id{-1};

    public :
    Menu()=default;
    Menu(std::vector<std::string> opt) : options{opt}{}
    //~Menu();
    virtual void Execute(std::vector<Menu*> vec_menus)=0;
    virtual void Deploy()=0;
    int Get_Selection(){return selection;}
};

class Menu_1 : public Menu {
    public:
    Menu_1(){
        Menu_id=1;
        options={"Say Hello","Menu 2","Say Bye","Go Back"};
    }
    void Deploy(){selection=HelperMenu(options);}
    void Execute(std::vector<Menu*> vec_menus){
        int selected=selection;
        if(selected==-1){this->Deploy();}
        if(selected==1){std::cout<<"Say Hello"<<std::endl;selection=-1;}
        if(selected==2){vec_menus.at(1)->Execute(vec_menus);}
        if(selected==3){std::cout<<"Say Bye"<<std::endl;selection=-1;}
        this->Execute(vec_menus);
    }


};

class Menu_2 : public Menu {
    public:
    Menu_2(){
        Menu_id=2;
        options={"Say Hello","Say Bye","Go Back"};
    }
    void Deploy(){selection=HelperMenu(options);}
    void Execute(std::vector<Menu*> vec_menus){
        int selected=selection;
        if(selected==-1){this->Deploy();}
        if(selected==1){std::cout<<"Say Hello"<<std::endl;selection=-1;}
        if(selected==2){std::cout<<"Say Bye"<<std::endl;selection=-1;}
        this->Execute(vec_menus);
    }


};


/*int main(){

    Menu_1 m1;
    Menu_2 m2;

    std::vector<Menu*> menus{&m1,&m2};

    m1.Execute(menus);

    return 0;
}*/