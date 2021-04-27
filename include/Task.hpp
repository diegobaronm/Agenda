#include<iostream>
#include<vector>

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
    Task(std::string date,std::string assignment, int id) : Date{date},Assignment{assignment},ID{id}{}
    //Setters.
    void Set_Date(std::string date){Date=date;}
    void Set_Assignment(std::string assignment){Assignment=assignment;}
    virtual void Set_ID(int id)=0;

    void Tick(){Completed=!Completed;}
    void Complete(){Completed=true;}
    //Getters.
    std::string Get_Date(){return Date;}
    std::string Get_Assignment(){return Assignment;}
    bool Get_Completed(){return Completed;}
    int Get_ID(){return ID;}

    virtual void print(Task &task)=0;

    //Pure virtual function related with SQL querys.
    virtual std::string Generate_SQL_Query()=0;

    virtual std::string getType() const = 0;


};

#endif

#ifndef MAINTASK_H
#define MAINTASK_H
//Class declaration for Main Tasks, inherited from Task.
class MainTask: public Task{
    protected:
    std::vector<Task*> SubTasks;
    int Event_ID;

    public:
    //Constructors.
    MainTask()=default;
    MainTask(std::string date,std::string assignment, int id, int e_id): Task(date,assignment,id), Event_ID(e_id){}


    void Add_SubTask(Task* subtask);

    void Set_ID(int id){ID=id;}
    void Set_eID(int id){Event_ID=id;};

    void print(Task &task);

    friend std::ostream & operator<<(std::ostream &os, MainTask &task);

    std::string Generate_SQL_Query();

    std::string getType() const{return "MainTask";}

    std::vector<MainTask> Fill(std::vector<MainTask> &MT,std::string database);

    int Get_eID(){return Event_ID;}

};

#endif

#ifndef SUBTASK_H
#define SUBTASK_H
//Class declaration for Sub Tasks, inherited from Task.
class SubTask : public Task {
    protected:
    int SubTask_ID;

    public:
    //Constructors.
    SubTask()=default;
    SubTask(std::string date,std::string assignment, int id) : Task(date,assignment,id){}
    SubTask(std::string date,std::string assignment, int id, int sub_id) : Task(date,assignment,id){
        SubTask_ID=sub_id;
    }

    void Set_ID(int id){ID=id;}

    void print(Task &task);

    friend std::ostream & operator<<(std::ostream &os, SubTask &task);

    std::string Generate_SQL_Query();

    std::string getType() const{return "SubTask";}

    std::vector<SubTask> Fill(std::vector<SubTask> &ST,std::string database);

};

#endif
