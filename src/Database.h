#ifndef DATABASE_H
#define DATABASE_H

#include <fstream>
#include <vector>
#include <string>
#include "Employee.h"
#include "Task.h"
#include "Citizen.h"
#include "Feedback.h"
using namespace std;

class Database
{
private:
    string employees_file;
    string tasks_file;
    string citizens_file;
    string feedback_file;
    string audit_log_file;

    // Helper function to split strings
    vector<string> splitString(const string &str, char delimiter);

public:
    Database();

    // Employee operations
    void saveEmployee(const Employee &emp);
    void loadEmployees(vector<Employee> &employees);

    // Task operations
    void saveTask(const Task &task);
    void loadTasks(vector<Task> &tasks);

    // Citizen operations
    void saveCitizen(const Citizen &citizen);
    void loadCitizens(vector<Citizen> &citizens);

    // Feedback operations
    void saveFeedback(const Feedback &fb);
    void loadFeedback(vector<Feedback> &feedbacks);

    // Audit log operations
    void logAudit(const string &action, const string &user);
    void readAuditLog();

    // CSV Export operations
    void exportEmployeesToCSV(const vector<Employee> &employees, const vector<Task> &tasks);
};

#endif
