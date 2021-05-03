#include"DataBase.hpp"
#include"Task.hpp"
#include<sqlite3.h>
// MainTask class functionality

std::istream& operator>>(std::istream& is, MainTask& mt){
    std::cin.ignore();
    std::cout<<"Enter date: ";
    std::string date;
    std::getline(is,date);
    mt.Set_Date(date);
    std::cout<<"Enter assignment: ";
    std::string description;
    std::getline(is,description);
    mt.Set_Assignment(description);

    return is;
}

void MainTask::Complete(){
    Completed=true;
    for(auto& st : SubTasks ){
        st->Complete();
    }
}

void MainTask::Add_SubTask(Task* subtask){
    subtask->Set_Task_ID(ID);
    SubTasks.emplace_back(subtask);
}

void MainTask::print(){
    std::cout<<"* [ID:"<<this->Get_ID()<<"] "<<this->Get_Assignment()<<"  "<<"Due Date: "<<this->Get_Date();
    if (this->Get_Completed()){std::cout<<"  [Done!]"<<std::endl;}
    else {std::cout<<"  [To Do!]"<<std::endl;}
    for(auto it=SubTasks.begin();it!=SubTasks.end();it++){
        std::cout<<"   ";
        (*it)->print();
    }
}

std::ostream & operator<<(std::ostream &os, Task &task){
    task.print();
    return os;
}

std::string MainTask::Generate_SQL_Query(){
    std::string query{"INSERT INTO MainTasks VALUES("};
    query = query+std::to_string(ID)+","+std::to_string(Event_ID)+","+std::to_string(Completed)+","+"'"+Date+"'"+","+"'"+Assignment+"');";
    return query;
}

std::vector<MainTask> Fill(std::vector<MainTask> &MT,std::string database){
    sqlite3 *db;
    std::string query = "SELECT * FROM MainTasks";

    if (sqlite3_open(const_cast<char*>(database.c_str()), &db) != SQLITE_OK) {
        std::cerr << "Could not open database.\n";
    }

    std::vector<std::vector<std::string>> records = select_stmt(const_cast<char*>(query.c_str()),db);
    sqlite3_close(db);

    std::vector<MainTask> objects;

    for (auto& record : records) {
        objects.push_back(MainTask(record.at(3),record.at(4),std::stoi(record.at(0)),std::stoi(record.at(1))));
    }
    return objects;
}

// SubTask functionality
std::istream& operator>>(std::istream& is, SubTask& st){
    std::cin.ignore();
    std::cout<<"Enter date: ";
    std::string date;
    std::getline(is,date);
    st.Set_Date(date);
    std::cout<<"Enter assignment: ";
    std::string description;
    std::getline(is,description);
    st.Set_Assignment(description);

    return is;
}


void SubTask::print(){
        std::cout<<"- [ID:"<<this->Get_ID()<<"] "<<this->Get_Assignment()<<"  "<<"Due Date: "<<this->Get_Date();
        if (this->Get_Completed()){std::cout<<"  [Done!]"<<std::endl;}
        else {std::cout<<"  [To Do!]"<<std::endl;}
    }

std::ostream & operator<<(std::ostream &os, SubTask &task){
    task.print();
    return os;
}

std::string SubTask::Generate_SQL_Query(){
    std::string query{"INSERT INTO SubTasks VALUES("};
    query = query+std::to_string(ID)+","+std::to_string(Task_ID)+","+std::to_string(Completed)+","+"'"+Date+"'"+","+"'"+Assignment+"');";
    return query;
}

std::vector<SubTask> Fill(std::vector<SubTask> &ST,std::string database){
    sqlite3 *db;
    std::string query = "SELECT * FROM SubTasks";

    if (sqlite3_open(const_cast<char*>(database.c_str()), &db) != SQLITE_OK) {
        std::cerr << "Could not open database.\n";
    }

    std::vector<std::vector<std::string>> records = select_stmt(const_cast<char*>(query.c_str()),db);
    sqlite3_close(db);

    std::vector<SubTask> objects;

    for (auto& record : records) {
        objects.push_back(SubTask(record.at(3),record.at(4),std::stoi(record.at(0)),std::stoi(record.at(1))));
    }
    return objects;
}