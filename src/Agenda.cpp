#include<string>
#include"Task.hpp"
#include"Event.hpp"
#include"DataBase.hpp"
#include"Menus.hpp"

namespace fs=std::filesystem;

//Defintion of static variables containing objects IDs.
std::vector<int> Event::Event_IDs;
std::vector<int> MainTask::MainTask_IDs;
std::vector<int> SubTask::SubTask_IDs;

std::vector<Event> Menu::All_E;
std::vector<MainTask> Menu::All_MT;
std::vector<SubTask> Menu::All_ST;


int main(){
    // Flag to know if new agend needs to be created.
    bool new_agenda{false};

    //This function returns the name of the agenda to run over.
    std::string db = Select_Agenda(new_agenda);
    if(new_agenda){ //Create new agenda.
        std::cout<<"Creating new agenda named "<<db<<std::endl;
        CreateDB(db);
    }else{ //Opem existing agenda.
        std::cout<<"Selecting agenda named "<<db<<std::endl;
    }

    // Fill vectors of objects.
    std::vector<Event> Es;
    Menu::All_E=Fill(Es,db);
    Menu::All_E.reserve(Menu::All_E.size()+100);
    std::vector<MainTask> MTs;
    Menu::All_MT=Fill(MTs,db);
    Menu::All_MT.reserve(Menu::All_MT.size()+100);
    std::vector<SubTask> STs;
    Menu::All_ST=Fill(STs,db);
    Menu::All_ST.reserve(Menu::All_ST.size()+100);
    //Organize hierarchy of the agenda.
    Organize();

    // Intantiate menus
    std::vector<Menu*> Menus;
    Menu_1 m1;
    Menu_2 m2;
    Menu_3 m3;
    Menu_4 m4;
    Menus.push_back(&m1);
    Menus.push_back(&m2);
    Menus.push_back(&m3);
    Menus.push_back(&m4);

    // Execute main program
    m1.Execute(Menus);
    // Make a temp copy of the untouched database for safety
    if(!new_agenda){
        fs::copy(db,db+".old");
        fs::remove(db);
        CreateDB(db);
    }
    // Fill agenda
    for(auto &p : Menu::All_E){
        Execute_Query(p.Generate_SQL_Query(),db);
    }
    for(auto &p : Menu::All_MT){
        Execute_Query(p.Generate_SQL_Query(),db);
    }
    for(auto &p : Menu::All_ST){
        Execute_Query(p.Generate_SQL_Query(),db);
    }
    // Removing backup file
    if(!new_agenda){
        fs::remove(db+".old");
    }

    return 0;
}