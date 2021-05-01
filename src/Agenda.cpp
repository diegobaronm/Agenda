#include<string>
#include<filesystem>
#include<map>

#include"Task.hpp"
#include"Event.hpp"
#include"DataBase.hpp"
#include"Menus.hpp"


namespace fs=std::filesystem;

std::string Select_Agenda(bool& new_agenda){
    std::string cwd = fs::current_path();
    std::map<int,std::string> agenda;
    int c{};

    for(auto& p: fs::recursive_directory_iterator(cwd)){
        if (p.path().extension()==".db"){
            c++;
            agenda.insert({c,p.path().filename()});
        }
    }

    if(agenda.empty()){
        std::cout<<"No available agendas, insert new agenda name:"<<std::endl;
        std::string new_agenda_name;
        std::cin>>new_agenda_name;
        while(std::cin.fail() || new_agenda_name==""){
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout<<"Enter a valid agenda name!"<<std::endl;
            std::cin>>new_agenda_name;
        }
        new_agenda=true;
        return new_agenda_name+".db";
    } else {
        std::cout<<"The avaliable Agendas are:"<<std::endl;
        std::cout<<"0.  Create agenda"<<std::endl;
        for(auto& ag :agenda){
            std::cout<<std::to_string(ag.first)<<". "<<ag.second<<std::endl;
        }
        int selected_key{};
        std::cin>>selected_key;
        while(std::cin.fail() || selected_key>agenda.size() || selected_key < 0){
            std::cin.clear();
            std::cin.ignore(1000,'\n');
            std::cout<<"Select existing agenda number!"<<std::endl;
            std::cin>>selected_key;
        }
        if(!selected_key){
            std::string new_agenda_name;
            std::cout<<"New agenda name:"<<std::endl;
            std::cin>>new_agenda_name;
            while(std::cin.fail() || new_agenda_name==""){
                std::cin.clear();
                std::cin.ignore(1000,'\n');
                std::cout<<"Enter a valid agenda name!"<<std::endl;
                std::cin>>new_agenda_name;
            }
            new_agenda=true;
            return new_agenda_name+".db";
        } else {
            auto selected = agenda.find(selected_key);
            return selected->second;
        }
    }
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



//Defintion of static variables containing objects IDs.
std::vector<int> Event::Event_IDs;
std::vector<int> MainTask::MainTask_IDs;
std::vector<int> SubTask::SubTask_IDs;

std::vector<Event> Menu::All_E;
std::vector<MainTask> Menu::All_MT;
std::vector<SubTask> Menu::All_ST;

int main(){

    //Dummy objects used to fill the vector with the objects from the database
    MainTask mt;
    SubTask st;
    Event e;

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
    std::vector<Event> Es=e.Fill(Es,db);
    std::vector<MainTask> MTs=mt.Fill(MTs,db);
    std::vector<SubTask> STs=st.Fill(STs,db);
    //Organize hierarchy of the agenda.
    Organize_Tasks(MTs,STs);
    Organize_Events(Es,MTs);

    Menu::All_E=Es;
    Menu::All_MT=MTs;
    Menu::All_ST=STs;

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

        Execute_Query(e1.Generate_SQL_Query(),db);
        Execute_Query(e2.Generate_SQL_Query(),db);
        Execute_Query(task1.Generate_SQL_Query(),db);
        Execute_Query(task2.Generate_SQL_Query(),db);
        Execute_Query(sub_task1.Generate_SQL_Query(),db);
        Execute_Query(sub_task2.Generate_SQL_Query(),db);
        Execute_Query(sub_task3.Generate_SQL_Query(),db);
    }
    std::cout<<"HELO";
    return 0;
}