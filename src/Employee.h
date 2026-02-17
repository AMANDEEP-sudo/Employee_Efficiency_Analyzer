#ifndef EMPLOYEE_H
#define EMPLOYEE_H

#include <vector>
#include <string>
using namespace std;

class Employee {
private:
    int employee_id;
    string name;
    string department;
    int joining_year;
    int total_tasks;
    int completed_tasks;
    double efficiency_score;
    double total_rating;
    int feedback_count;
    vector<int> task_ids;

public:
    Employee();
    Employee(int id, string n, string d, int year);
    
    // Setters
    void setEmployeeId(int id);
    void setName(string n);
    void setDepartment(string d);
    void setJoiningYear(int year);
    void setTotalTasks(int t);
    void setCompletedTasks(int c);
    void setEfficiencyScore(double score);
    void setTotalRating(double rating);
    void setFeedbackCount(int count);
    
    // Getters
    int getEmployeeId() const;
    string getName() const;
    string getDepartment() const;
    int getJoiningYear() const;
    int getTotalTasks() const;
    int getCompletedTasks() const;
    double getEfficiencyScore() const;
    double getTotalRating() const;
    int getFeedbackCount() const;
    vector<int> getTaskIds() const;
    
    // Methods
    void addTask(int task_id);
    void completeTask(int task_id);
    void updateRating(double rating);
    double calculateEfficiency();
    void displayInfo() const;
    
};

#endif
