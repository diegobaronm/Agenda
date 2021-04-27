#include<string>
#include<filesystem>
#include<map>

#include"Task.hpp"
#include"Event.hpp"
#include"DataBase.hpp"


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

int Menu(std::vector<std::string> options){
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

void Organize_Tasks(std::vector<MainTask> &MTs,std::vector<SubTask> &STs){
    for(auto& p : MTs){
        for(auto& q : STs){
            if(q.Get_ID()==p.Get_ID()){
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






int main(){

    //dummy objects
    MainTask mt;
    SubTask st;
    Event e;

    bool executing{true};
    bool new_agenda{false};
    /*std::vector<std::string> Options = {"Hello","World","How","Are","You?"};

    Menu(Options);*/

    std::string db = Select_Agenda(new_agenda);
    std::cout<<db<<std::endl;
    if(new_agenda){
        std::cout<<"Creating new agenda named "<<db<<std::endl;
        CreateDB(db);
    }else{
        std::cout<<"Selecting agenda named "<<db<<std::endl;
    }


    std::vector<Event> Es=e.Fill(Es,db);
    std::vector<MainTask> MTs=mt.Fill(MTs,db);
    std::vector<SubTask> STs=st.Fill(STs,db);

    Organize_Tasks(MTs,STs);
    Organize_Events(Es,MTs);

    for(auto& i : Es){
        std::cout<<i<<std::endl;
    }

    /*for(auto& i : MTs){
        std::cout<<i<<std::endl;
    }*/


    /*CreateDB(db);

    Event e1("19 of April","Take my flights",10);
    Event e2("20 of April","Apple event",9);

    MainTask task1("9 of April","Order food.",1,10);
    MainTask task2("10 of April","Make Love!.",2,9);
    SubTask sub_task1("11 April.","Take my flight.",1,1);
    SubTask sub_task2("12 April.","Make my bed.",1,2);
    SubTask sub_task3("13 April.","Eat my steak.",2,3);


    Execute_Query(e1.Generate_SQL_Query(),db);
    Execute_Query(e2.Generate_SQL_Query(),db);
    Execute_Query(task1.Generate_SQL_Query(),db);
    Execute_Query(task2.Generate_SQL_Query(),db);
    Execute_Query(sub_task1.Generate_SQL_Query(),db);
    Execute_Query(sub_task2.Generate_SQL_Query(),db);
    Execute_Query(sub_task3.Generate_SQL_Query(),db);*/


    //Event Test_Event{"13 of April","Hello world"};

    /*task2.Add_SubTask(&sub_task);

    Test_Event.Add_Task(&task1);
    Test_Event.Add_Task(&task2);

    std::cout<<Test_Event<<std::endl;

    task1.Complete();
    task2.Tick();

    std::cout<<Test_Event<<std::endl;

    task2.Tick();

    std::cout<<Test_Event<<std::endl;*/


    return 0;
}