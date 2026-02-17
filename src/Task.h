#ifndef TASK_H
#define TASK_H

#include <string>
using namespace std;

class Task {
private:
    int task_id;
    int employee_id;
    string description;
    string deadline;
    string completion_date;
    bool is_completed;
    bool is_delayed;

public:
    Task();
    Task(int tid, int eid, string desc, string dl);
    
    // Setters
    void setTaskId(int id);
    void setEmployeeId(int id);
    void setDescription(string desc);
    void setDeadline(string date);
    void setCompletionDate(string date);
    void setIsCompleted(bool status);
    void setIsDelayed(bool status);
    
    // Getters
    int getTaskId() const;
    int getEmployeeId() const;
    string getDescription() const;
    string getDeadline() const;
    string getCompletionDate() const;
    bool getIsCompleted() const;
    bool getIsDelayed() const;
    
    // Methods
    void markComplete(string comp_date);
    bool checkDelay();
    bool isOverdue() const;
    void displayTask() const;
};

#endif
