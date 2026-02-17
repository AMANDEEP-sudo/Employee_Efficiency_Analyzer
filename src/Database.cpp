#include "Database.h"
#include "Constants.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <ctime>
using namespace std;

vector<string> Database::splitString(const string &str, char delimiter)
{
    vector<string> tokens;
    string token;
    istringstream tokenStream(str);
    while (getline(tokenStream, token, delimiter))
    {
        tokens.push_back(token);
    }
    return tokens;
}

Database::Database()
    : employees_file(EMPLOYEES_FILE), tasks_file(TASKS_FILE),
      citizens_file(CITIZENS_FILE), feedback_file(FEEDBACK_FILE),
      audit_log_file(AUDIT_LOG_FILE) {}

// Employee operations
void Database::saveEmployee(const Employee &emp)
{
    ofstream file(employees_file, ios::app);
    if (!file.is_open())
    {
        cerr << "Error opening employees file!" << endl;
        return;
    }

    file << emp.getEmployeeId() << "|" << emp.getName() << "|"
         << emp.getDepartment() << "|" << emp.getJoiningYear() << "|"
         << emp.getTotalTasks() << "|" << emp.getCompletedTasks() << "|" << fixed << setprecision(2)
         << emp.getEfficiencyScore() << "|" << emp.getFeedbackCount() << endl;

    file.close();
    cout << "Employee saved to database!" << endl;
}

void Database::loadEmployees(vector<Employee> &employees)
{
    ifstream file(employees_file);
    if (!file.is_open())
    {
        cout << "Employee file does not exist yet." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        vector<string> fields = splitString(line, '|');
        if (fields.size() < 8)
            continue;

        Employee emp(stoi(fields[0]), fields[1], fields[2], stoi(fields[3]));
        emp.setTotalTasks(stoi(fields[4]));
        emp.setCompletedTasks(stoi(fields[5]));
        emp.setEfficiencyScore(stod(fields[6]));
        emp.setFeedbackCount(stoi(fields[7]));

        employees.push_back(emp);
    }

    file.close();
    cout << "Loaded " << employees.size() << " employees from database." << endl;
}

// Task operations
void Database::saveTask(const Task &task)
{
    ofstream file(tasks_file, ios::app);
    if (!file.is_open())
    {
        cerr << "Error opening tasks file!" << endl;
        return;
    }

    file << task.getTaskId() << "|" << task.getEmployeeId() << "|"
         << task.getDescription() << "|" << task.getDeadline() << "|"
         << task.getCompletionDate() << "|" << task.getIsCompleted() << "|"
         << task.getIsDelayed() << endl;

    file.close();
    cout << "Task saved to database!" << endl;
}

void Database::loadTasks(vector<Task> &tasks)
{
    ifstream file(tasks_file);
    if (!file.is_open())
    {
        cout << "Task file does not exist yet." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        vector<string> fields = splitString(line, '|');
        if (fields.size() < 7)
            continue;

        Task task(stoi(fields[0]), stoi(fields[1]), fields[2], fields[3]);
        task.setCompletionDate(fields[4]);
        task.setIsCompleted(fields[5] == "1");
        task.setIsDelayed(fields[6] == "1");

        tasks.push_back(task);
    }

    file.close();
    cout << "Loaded " << tasks.size() << " tasks from database." << endl;
}

// Citizen operations
void Database::saveCitizen(const Citizen &citizen)
{
    ofstream file(citizens_file, ios::app);
    if (!file.is_open())
    {
        cerr << "Error opening citizens file!" << endl;
        return;
    }

    file << citizen.getHashedAadhaar() << "|" << citizen.getName() << "|"
         << citizen.getAddress() << "|" << citizen.getMobile() << endl;

    file.close();
    cout << "Citizen saved to database!" << endl;
}

void Database::loadCitizens(vector<Citizen> &citizens)
{
    ifstream file(citizens_file);
    if (!file.is_open())
    {
        cout << "Citizen file does not exist yet." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        vector<string> fields = splitString(line, '|');
        if (fields.size() < 4)
            continue;

        Citizen citizen(fields[0], fields[1], fields[2], fields[3]);
        citizens.push_back(citizen);
    }

    file.close();
    cout << "Loaded " << citizens.size() << " citizens from database." << endl;
}

// Feedback operations
void Database::saveFeedback(const Feedback &fb)
{
    ofstream file(feedback_file, ios::app);
    if (!file.is_open())
    {
        cerr << "Error opening feedback file!" << endl;
        return;
    }

    file << fb.getFeedbackId() << "|" << fb.getEmployeeId() << "|"
         << fb.getHashedCitizenAadhaar() << "|" << fb.getRating() << "|"
         << fb.getComment() << "|" << fb.getTimestamp() << "|"
         << fb.getIsSubmitted() << endl;

    file.close();
    cout << "Feedback saved to database!" << endl;
}

void Database::loadFeedback(vector<Feedback> &feedbacks)
{
    ifstream file(feedback_file);
    if (!file.is_open())
    {
        cout << "Feedback file does not exist yet." << endl;
        return;
    }

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        vector<string> fields = splitString(line, '|');
        if (fields.size() < 7)
            continue;

        Feedback fb(stoi(fields[0]), stoi(fields[1]), fields[2]);
        fb.setRating(stoi(fields[3]));
        fb.setComment(fields[4]);
        fb.setTimestamp(fields[5]);
        fb.setIsSubmitted(fields[6] == "1");

        feedbacks.push_back(fb);
    }

    file.close();
    cout << "Loaded " << feedbacks.size() << " feedbacks from database." << endl;
}

// Audit log operations
void Database::logAudit(const string &action, const string &user)
{
    ofstream file(audit_log_file, ios::app);
    if (!file.is_open())
    {
        cerr << "Error opening audit log file!" << endl;
        return;
    }

    time_t now = time(0);
    char timestamp[100];
    struct tm timeinfo = *localtime(&now);
    strftime(timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S", &timeinfo);

    file << timestamp << "|" << action << "|" << user << endl;
    file.close();
}

void Database::readAuditLog()
{
    ifstream file(audit_log_file);
    if (!file.is_open())
    {
        cout << "Audit log file does not exist yet." << endl;
        return;
    }

    cout << "\n========== AUDIT LOG ==========" << endl;
    cout << "Timestamp            | Action               | User" << endl;
    cout << "---------------------+----------------------+----------" << endl;

    string line;
    while (getline(file, line))
    {
        if (line.empty())
            continue;

        vector<string> fields = splitString(line, '|');
        if (fields.size() >= 3)
        {
            cout << fields[0] << " | " << fields[1] << " | " << fields[2] << endl;
        }
    }

    cout << "==============================\n"
         << endl;
    file.close();
}

// CSV Export operations
void Database::exportEmployeesToCSV(const vector<Employee> &employees, const vector<Task> &tasks)
{
    string csv_file = "data/employees_report.csv";
    ofstream file(csv_file);

    if (!file.is_open())
    {
        cerr << "Error creating CSV file!" << endl;
        return;
    }

    // Write CSV header
    file << "Employee ID,Name,Department,Total Tasks,Completed Tasks,Efficiency Score,Feedback Count,Task ID,Task Description,Deadline,Completion Date,Status" << endl;

    // Write employee data with their tasks
    for (const auto &emp : employees)
    {
        bool first_task = true;

        // Find all tasks for this employee
        vector<Task> emp_tasks;
        for (const auto &task : tasks)
        {
            if (task.getEmployeeId() == emp.getEmployeeId())
            {
                emp_tasks.push_back(task);
            }
        }

        // If employee has tasks, write one row per task
        if (!emp_tasks.empty())
        {
            for (const auto &task : emp_tasks)
            {
                if (!first_task)
                {
                    file << ",,,,,,"; // Empty cells for duplicate employee info
                }

                file << emp.getEmployeeId() << ","
                     << emp.getName() << ","
                     << emp.getDepartment() << ","
                     << emp.getTotalTasks() << ","
                     << emp.getCompletedTasks() << ","
                     << fixed << setprecision(2) << emp.getEfficiencyScore() << ","
                     << emp.getFeedbackCount() << ","
                     << task.getTaskId() << ","
                     << "\"" << task.getDescription() << "\"" << ","
                     << task.getDeadline() << ","
                     << task.getCompletionDate() << ","
                     << (task.getIsCompleted() ? "Completed" : "Pending") << endl;

                first_task = false;
            }
        }
        else
        {
            // If employee has no tasks, just write employee info
            file << emp.getEmployeeId() << ","
                 << emp.getName() << ","
                 << emp.getDepartment() << ","
                 << emp.getTotalTasks() << ","
                 << emp.getCompletedTasks() << ","
                 << fixed << setprecision(2) << emp.getEfficiencyScore() << ","
                 << emp.getFeedbackCount() << ","
                 << "N/A,N/A,N/A,N/A,N/A" << endl;
        }
    }

    file.close();
    cout << "\n✓ CSV Report exported successfully to: data/employees_report.csv" << endl;
}
