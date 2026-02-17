#include "Employee.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>
using namespace std;

Employee::Employee() : employee_id(0), name(""), department(""), joining_year(2024),
                       total_tasks(0), completed_tasks(0), 
                       efficiency_score(0.0), total_rating(0.0), 
                       feedback_count(0) {}

Employee::Employee(int id, string n, string d, int year) 
    : employee_id(id), name(n), department(d), joining_year(year), total_tasks(0), 
      completed_tasks(0), efficiency_score(0.0), total_rating(0.0), 
      feedback_count(0) {}

void Employee::setEmployeeId(int id) { employee_id = id; }
void Employee::setName(string n) { name = n; }
void Employee::setDepartment(string d) { department = d; }
void Employee::setJoiningYear(int year) { joining_year = year; }
void Employee::setTotalTasks(int t) { total_tasks = t; }
void Employee::setCompletedTasks(int c) { completed_tasks = c; }
void Employee::setEfficiencyScore(double score) { efficiency_score = score; }
void Employee::setTotalRating(double rating) { total_rating = rating; }
void Employee::setFeedbackCount(int count) { feedback_count = count; }

int Employee::getEmployeeId() const { return employee_id; }
string Employee::getName() const { return name; }
string Employee::getDepartment() const { return department; }
int Employee::getJoiningYear() const { return joining_year; }
int Employee::getTotalTasks() const { return total_tasks; }
int Employee::getCompletedTasks() const { return completed_tasks; }
double Employee::getEfficiencyScore() const { return efficiency_score; }
double Employee::getTotalRating() const { return total_rating; }
int Employee::getFeedbackCount() const { return feedback_count; }
vector<int> Employee::getTaskIds() const { return task_ids; }

void Employee::addTask(int task_id) {
    task_ids.push_back(task_id);
    total_tasks++;
    cout << "Task " << task_id << " added to employee " << name << endl;
}

void Employee::completeTask(int task_id) {
    for (int i = 0; i < task_ids.size(); i++) {
        if (task_ids[i] == task_id) {
            completed_tasks++;
            cout << "Task " << task_id << " marked complete!" << endl;
            return;
        }
    }
    cout << "Task not found!" << endl;
}

void Employee::updateRating(double rating) {
    if (rating >= RATING_MIN && rating <= RATING_MAX) {
        total_rating += rating;
        feedback_count++;
        cout << "Rating updated successfully!" << endl;
    } else {
        cout << "Invalid rating! Please enter rating between " 
             << RATING_MIN << " and " << RATING_MAX << endl;
    }
}

double Employee::calculateEfficiency() {
    if (total_tasks == 0) {
        efficiency_score = 0.0;
        return efficiency_score;
    }
    
    double completion_rate = (double)completed_tasks / total_tasks;
    double average_rating = (feedback_count > 0) ? (total_rating / feedback_count) : 0.0;
    
    // Normalize average rating to 0-100 scale
    average_rating = (average_rating / RATING_MAX) * 100;
    
    // Assuming on-time percentage is 90% (simplified for this version)
    double on_time_percentage = 0.9;
    double delay_penalty = (total_tasks - completed_tasks) * DELAY_PENALTY_PER_TASK;
    
    efficiency_score = (completion_rate * (100 * COMPLETION_RATE_WEIGHT / 0.50)) + 
                       (average_rating * AVERAGE_RATING_WEIGHT) + 
                       (on_time_percentage * (100 * ON_TIME_PERCENTAGE_WEIGHT / 0.20)) - 
                       delay_penalty;
    
    if (efficiency_score < MIN_EFFICIENCY_SCORE) efficiency_score = MIN_EFFICIENCY_SCORE;
    if (efficiency_score > MAX_EFFICIENCY_SCORE) efficiency_score = MAX_EFFICIENCY_SCORE;
    
    return efficiency_score;
}

void Employee::displayInfo() const {
    cout << "\n========== EMPLOYEE DETAILS ==========" << endl;
    cout << "Employee ID: " << employee_id << endl;
    cout << "Name: " << name << endl;
    cout << "Department: " << department << endl;
    cout << "Total Tasks: " << total_tasks << endl;
    cout << "Completed Tasks: " << completed_tasks << endl;
    cout << "Feedback Count: " << feedback_count << endl;
    cout << "Average Rating: " << fixed << setprecision(2) 
         << (feedback_count > 0 ? total_rating / feedback_count : 0.0) << "/5" << endl;
    cout << "Efficiency Score: " << fixed << setprecision(2) 
         << efficiency_score << "/100" << endl;
    cout << "======================================\n" << endl;
}
