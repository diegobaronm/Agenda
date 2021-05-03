#include"DataBase.hpp"
#include"Event.hpp"
#include<sqlite3.h>

void Event::Add_Task(MainTask* task){
    task->Set_eID(Event_ID);
    Tasks.emplace_back(task);
}

void Event::Remove_Task(int id){
    auto it=Tasks.begin();
    for(auto it=Tasks.begin();it!=Tasks.end();it++){
        if((*it)->Get_ID()==id){break; }
    }
    Tasks.erase(it);

}

std::ostream & operator<<(std::ostream &os, const Event &event){
    os<<"-----------------> Event"<<" [ID:"<<event.Event_ID<<"] <----------------------" <<std::endl<<std::endl<<"Date: "<<event.Date<<std::endl<<"Comment: "<<event.Comment<<std::endl<<std::endl;
    if (event.Tasks.empty()){os<<"No tasks!"<<std::endl;}
    else {
        std::cout<<"Tasks:"<<std::endl;
        for(size_t i=0; i<event.Tasks.size();i++){
            event.Tasks.at(i)->print();
        }
    }
    return os;
}

std::istream & operator>>(std::istream &is, Event& event){

    std::cin.ignore();
    std::cout<<"Enter date: ";
    std::string date;
    std::getline(is,date);
    event.Set_Date(date);
    std::cout<<"Enter comment: ";
    std::string description;
    std::getline(is,description);
    event.Set_Comment(description);

    return is;
}

std::string Event::Generate_SQL_Query(){
    std::string query{"INSERT INTO Events VALUES("};
    query = query+std::to_string(Event_ID)+","+"'"+Date+"'"+","+"'"+Comment+"');";
    return query;
}

std::vector<Event> Fill(std::vector<Event> &E,std::string database){
    sqlite3 *db;
    std::string query = "SELECT * FROM Events";

    if (sqlite3_open(const_cast<char*>(database.c_str()), &db)!=SQLITE_OK) {
        std::cerr << "Could not open database.\n";
    }

    std::vector<std::vector<std::string>> records = select_stmt(const_cast<char*>(query.c_str()),db);
    sqlite3_close(db);

    std::vector<Event> objects;

    for (auto& record : records) {
        objects.push_back(Event(record.at(1),record.at(2),std::stoi(record.at(0))));
    }
    return objects;
}
