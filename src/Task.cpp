#include "Task.h"
#include <iostream>
#include <ctime>
#include <iomanip>
using namespace std;

Task::Task() : task_id(0), employee_id(0), description(""), 
               deadline(""), completion_date(""), is_completed(false), 
               is_delayed(false) {}

Task::Task(int tid, int eid, string desc, string dl)
    : task_id(tid), employee_id(eid), description(desc), deadline(dl), 
      completion_date(""), is_completed(false), is_delayed(false) {}

void Task::setTaskId(int id) { task_id = id; }
void Task::setEmployeeId(int id) { employee_id = id; }
void Task::setDescription(string desc) { description = desc; }
void Task::setDeadline(string date) { deadline = date; }
void Task::setCompletionDate(string date) { completion_date = date; }
void Task::setIsCompleted(bool status) { is_completed = status; }
void Task::setIsDelayed(bool status) { is_delayed = status; }

int Task::getTaskId() const { return task_id; }
int Task::getEmployeeId() const { return employee_id; }
string Task::getDescription() const { return description; }
string Task::getDeadline() const { return deadline; }
string Task::getCompletionDate() const { return completion_date; }
bool Task::getIsCompleted() const { return is_completed; }
bool Task::getIsDelayed() const { return is_delayed; }

void Task::markComplete(string comp_date) {
    is_completed = true;
    completion_date = comp_date;
    
    // Check if delayed
    if (comp_date > deadline) {
        is_delayed = true;
    }
    
    cout << "Task " << task_id << " marked as completed!" << endl;
}

bool Task::checkDelay() {
    if (is_completed && completion_date > deadline) {
        is_delayed = true;
        return true;
    }
    return false;
}

bool Task::isOverdue() const {
    // Simplified: compare date strings
    if (!is_completed && deadline < "2024-02-16") { // Using current date for simulation
        return true;
    }
    return false;
}

void Task::displayTask() const {
    cout << "\n========== TASK DETAILS ==========" << endl;
    cout << "Task ID: " << task_id << endl;
    cout << "Assigned to Employee ID: " << employee_id << endl;
    cout << "Description: " << description << endl;
    cout << "Deadline: " << deadline << endl;
    if (is_completed) {
        cout << "Status: COMPLETED" << endl;
        cout << "Completion Date: " << completion_date << endl;
        cout << "Delayed: " << (is_delayed ? "YES" : "NO") << endl;
    } else {
        cout << "Status: PENDING" << endl;
        cout << "Overdue: " << (isOverdue() ? "YES" : "NO") << endl;
    }
    cout << "================================\n" << endl;
}
