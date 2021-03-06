#include<vector>
#include<string>
#include<iostream>
#include <stdlib.h>
#include<algorithm>
#include"Task.hpp"

#ifndef EVENT_H
#define EVENT_H
// Class declaration to store events.
class Event{
    friend std::ostream & operator<<(std::ostream &os, const Event &event);
    friend std::istream & operator>>(std::istream &is, Event& event);

    private:
    std::string Date{"Default"};
    std::string Comment{"Default_Comment"};
    int Event_ID;



    public:
    static std::vector<int> Event_IDs;
    std::vector<MainTask*> Tasks;
    //Constructors.
    Event(){
        int random_id=rand()%1000+1;
        while(std::find(Event_IDs.begin(),Event_IDs.end(),random_id)!=Event_IDs.end()){
            random_id=rand()%1000+1;
        }
        Event_IDs.emplace_back(random_id);
        Event_ID=random_id;
    }
    Event(std::string date,std::string comment,int id) : Date{date},Comment{comment},Event_ID{id}{
        Event_IDs.emplace_back(id);}
    Event(std::string date,std::string comment) : Date{date},Comment{comment}{
        int random_id=rand()%1000+1;
        while(std::find(Event_IDs.begin(),Event_IDs.end(),random_id)!=Event_IDs.end()){
            random_id=rand()%1000+1;
        }
        Event_IDs.emplace_back(random_id);
        Event_ID=random_id;
    }
    //Seter functions.
    void Set_Date(std::string date){Date=date;}
    void Set_Comment(std::string comment){Comment=comment;}
    //Getters.
    std::string Get_Date(){return Date;}
    std::string Get_Comment(){return Comment;}
    int Get_ID(){return Event_ID;}

    void Add_Task(MainTask* task);
    void Remove_Task(int task);
    //SQL related methods.
    std::string Generate_SQL_Query();
    friend std::vector<Event> Fill(std::vector<Event> &E,std::string database);
};

#endif