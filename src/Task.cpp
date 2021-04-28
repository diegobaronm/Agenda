#include"DataBase.hpp"
#include"Task.hpp"
#include<sqlite3.h>
// MainTask class functionality

void MainTask::Add_SubTask(Task* subtask){
    subtask->Set_Task_ID(ID);
    SubTasks.push_back(subtask);
}

void MainTask::print(Task &task){
    std::cout<<"* [ID:"<<task.Get_ID()<<"] "<<task.Get_Assignment()<<"  "<<"Due Date: "<<task.Get_Date();
    if (task.Get_Completed()){std::cout<<"  [Done!]"<<std::endl;}
    else {std::cout<<"  [To Do!]"<<std::endl;}
    for(auto it=SubTasks.begin();it!=SubTasks.end();it++){
        std::cout<<"    ";
        (*it)->print(**it);
    }
}

std::ostream & operator<<(std::ostream &os, MainTask &task){
    task.print(task);
    return os;
}

std::string MainTask::Generate_SQL_Query(){
    std::string query{"INSERT INTO MainTasks VALUES("};
    query = query+std::to_string(ID)+","+std::to_string(Event_ID)+","+std::to_string(Completed)+","+"'"+Date+"'"+","+"'"+Assignment+"');";
    return query;
}

std::vector<MainTask> MainTask::Fill(std::vector<MainTask> &MT,std::string database){
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
void SubTask::print(Task &task){
        std::cout<<"- [ID:"<<task.Get_ID()<<"] "<<task.Get_Assignment()<<"  "<<"Due Date: "<<task.Get_Date();
        if (task.Get_Completed()){std::cout<<"  [Done!]"<<std::endl;}
        else {std::cout<<"  [To Do!]"<<std::endl;}
    }

std::ostream & operator<<(std::ostream &os, SubTask &task){
    task.print(task);
    return os;
}

std::string SubTask::Generate_SQL_Query(){
    std::string query{"INSERT INTO SubTasks VALUES("};
    query = query+std::to_string(ID)+","+std::to_string(Task_ID)+","+std::to_string(Completed)+","+"'"+Date+"'"+","+"'"+Assignment+"');";
    return query;
}

std::vector<SubTask> SubTask::Fill(std::vector<SubTask> &ST,std::string database){
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