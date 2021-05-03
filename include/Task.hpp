#include<iostream>
#include<vector>
#include <stdlib.h>
#include<algorithm>

#ifndef TASK_H
#define TASK_H
// Base class declaration for taks in the agenda.
class Task {
    protected:
    std::string Date;
    std::string Assignment;
    bool Completed{false};
    int ID;

    public:
    //Constructors.
    Task()=default;
    Task(std::string date,std::string assignment) : Date{date},Assignment{assignment}{}
    //Setters.
    void Set_Date(std::string date){Date=date;}
    void Set_Assignment(std::string assignment){Assignment=assignment;}
    virtual void Set_ID(int id)=0;
    virtual void Set_Task_ID(int id)=0;

    void Tick(){Completed=!Completed;}
    virtual void Complete()=0;
    //Getters.
    std::string Get_Date(){return Date;}
    std::string Get_Assignment(){return Assignment;}
    bool Get_Completed(){return Completed;}
    int Get_ID(){return ID;}

    virtual void print()=0;

    //Pure virtual function related with SQL querys.
    virtual std::string Generate_SQL_Query()=0;

    virtual std::string getType() const = 0;


};

#endif

#ifndef MAINTASK_H
#define MAINTASK_H
//Class declaration for Main Tasks, inherited from Task.
class MainTask: public Task{
    friend std::istream& operator>>(std::istream& is, MainTask& mt);

    protected:
    int Event_ID{};


    public:
    std::vector<Task*> SubTasks;
    static std::vector<int> MainTask_IDs;
    //Constructors.
    MainTask(){
        int random_id=rand()%1000+1;
        while(std::find(MainTask_IDs.begin(),MainTask_IDs.end(),random_id)!=MainTask_IDs.end()){
            random_id=rand()%1000+1;
        }
        MainTask_IDs.emplace_back(random_id);
        ID=random_id;
    };
    MainTask(std::string date,std::string assignment,int id,int ev_id): Task(date,assignment){
        ID=id;
        Event_ID=ev_id;
        MainTask_IDs.emplace_back(id);
    }
    MainTask(std::string date,std::string assignment): Task(date,assignment){
        int random_id=rand()%1000+1;
        while(std::find(MainTask_IDs.begin(),MainTask_IDs.end(),random_id)!=MainTask_IDs.end()){
            random_id=rand()%1000+1;
        }
        MainTask_IDs.emplace_back(random_id);
        ID=random_id;
    }

    void Complete();

    void Add_SubTask(Task* subtask);

    void Set_ID(int id){ID=id;}
    void Set_eID(int id){Event_ID=id;};
    void Set_Task_ID(int id){};


    void print() override;

    friend std::ostream & operator<<(std::ostream &os, Task &task);

    std::string Generate_SQL_Query();

    std::string getType() const{return "MainTask";}

    friend std::vector<MainTask> Fill(std::vector<MainTask> &MT,std::string database);

    int Get_eID(){return Event_ID;}

};

#endif

#ifndef SUBTASK_H
#define SUBTASK_H
//Class declaration for Sub Tasks, inherited from Task.
class SubTask : public Task {
    friend std::istream& operator>>(std::istream& is, SubTask& st);
    protected:
    int Task_ID{};


    public:
    static std::vector<int> SubTask_IDs;
    //Constructors.
    SubTask(){
        int random_id=rand()%1000+1;
        while(std::find(SubTask_IDs.begin(),SubTask_IDs.end(),random_id)!=SubTask_IDs.end()){
            random_id=rand()%1000+1;
        }
        SubTask_IDs.emplace_back(random_id);
        ID=random_id;
    }
    SubTask(std::string date,std::string assignment,int id,int t_id) : Task(date,assignment){
        ID=id;
        Task_ID=t_id;
        SubTask_IDs.emplace_back(id);
    }
    SubTask(std::string date,std::string assignment) : Task(date,assignment){
        int random_id=rand()%1000+1;
        while(std::find(SubTask_IDs.begin(),SubTask_IDs.end(),random_id)!=SubTask_IDs.end()){
            random_id=rand()%1000+1;
        }
        SubTask_IDs.emplace_back(random_id);
        ID=random_id;
    }

    void Complete(){Completed=true;}

    int Get_T_ID(){return Task_ID;}

    void Set_ID(int id){ID=id;}
    void Set_Task_ID(int id){Task_ID=id;}

    void print() override;

    friend std::ostream & operator<<(std::ostream &os, SubTask &task);

    std::string Generate_SQL_Query();

    std::string getType() const{return "SubTask";}

    friend std::vector<SubTask> Fill(std::vector<SubTask> &ST,std::string database);

};

#endif
