#include<vector>
#include<string>
#include<iostream>
#include"Task.hpp"

#ifndef EVENT_H
#define EVENT_H

class Event{
    friend std::ostream & operator<<(std::ostream &os, const Event &event);

    private:
    std::string Date{"Default"};
    std::string Comment{"Default_Comment"};
    int Event_ID;
    std::vector<Task*> Tasks;

    public:
    Event()=default;
    Event(std::string date,std::string comment,int id) : Date{date},Comment{comment},Event_ID{id}{}

    void Set_Date(std::string date){Date=date;}
    void Set_Comment(std::string comment){Comment=comment;}

    std::string Get_Date(){return Date;}
    std::string Get_Comment(){return Comment;}
    int Get_ID(){return Event_ID;}

    void Add_Task(MainTask* task);

    std::string Generate_SQL_Query();

    std::vector<Event> Fill(std::vector<Event> &E,std::string database);
};

#endif