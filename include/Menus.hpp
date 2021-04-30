#include<vector>
#include<string>
#include<iostream>
#include"Event.hpp"
#include"Task.hpp"

int HelperMenu(std::vector<std::string> options);

class Menu{
    protected:
    std::vector<std::string> options;
    int selection{-1};
    int Menu_id{-1};

    public :
    static std::vector<Event> All_E;
    static std::vector<MainTask> All_MT;
    static std::vector<SubTask> All_ST;

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
        options={"Show Full Agenda.","Add Event.","Select Event.","Save and Finish."};
    }
    void Deploy(){selection=HelperMenu(options);}
    void Execute(std::vector<Menu*> vec_menus);
};

class Menu_2 : public Menu {
    public:
    Menu_2(){
        Menu_id=2;
        options={"Show Full Event.","Change Event.","Add Task.","Select Task.","Go Back."};
    }
    void Deploy(){selection=HelperMenu(options);}
    void Execute(std::vector<Menu*> vec_menus);
};

class Menu_3 : public Menu {
    public:
    Menu_3(){
        Menu_id=3;
        options={"Show Full Task.","Change Task.","Add SubTask.","Select SubTask.","Complete.","Go Back."};
    }
    void Deploy(){selection=HelperMenu(options);}
    void Execute(std::vector<Menu*> vec_menus);
};

class Menu_4 : public Menu {
    public:
    Menu_4(){
        Menu_id=4;
        options={"Show Full SubTask.","Change SubTask.","Complete.","Go Back."};
    }
    void Deploy(){selection=HelperMenu(options);}
    void Execute(std::vector<Menu*> vec_menus);
};
