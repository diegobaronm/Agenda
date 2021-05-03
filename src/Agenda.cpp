#include<string>
#include"Task.hpp"
#include"Event.hpp"
#include"DataBase.hpp"
#include"Menus.hpp"

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

    std::vector<Menu*> Menus;

    Menu_1 m1;
    Menu_2 m2;
    Menu_3 m3;
    Menu_4 m4;

    Menus.push_back(&m1);
    Menus.push_back(&m2);
    Menus.push_back(&m3);
    Menus.push_back(&m4);

    m1.Execute(Menus);


    if(new_agenda){
        Event e1("19 of April","Take my flights");
        Event e2("20 of April","Apple event");

        MainTask task1("9 of April","Order food.");
        MainTask task2("10 of April","Make Love!.");
        SubTask sub_task1("11 April.","Take my flight.");
        SubTask sub_task2("12 April.","Make my bed.");
        SubTask sub_task3("13 April.","Eat my steak.");

        e1.Add_Task(&task1);
        e2.Add_Task(&task2);

        task1.Add_SubTask(&sub_task1);
        task1.Add_SubTask(&sub_task2);
        task2.Add_SubTask(&sub_task3);

        std::cout<<e1;
        std::cout<<e2;

        /*Execute_Query(e1.Generate_SQL_Query(),db);
        Execute_Query(e2.Generate_SQL_Query(),db);
        Execute_Query(task1.Generate_SQL_Query(),db);
        Execute_Query(task2.Generate_SQL_Query(),db);
        Execute_Query(sub_task1.Generate_SQL_Query(),db);
        Execute_Query(sub_task2.Generate_SQL_Query(),db);
        Execute_Query(sub_task3.Generate_SQL_Query(),db);*/
    }
    return 0;
}