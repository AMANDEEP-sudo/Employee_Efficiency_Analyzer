#ifndef ADMIN_H
#define ADMIN_H

#include <vector>
#include <string>
#include "Employee.h"
#include "Task.h"
#include "Citizen.h"
#include "Feedback.h"
#include "Department.h"
#include "Database.h"
#include "OTPManager.h"
#include "EfficiencyCalculator.h"
using namespace std;

class Admin {
private:
    vector<Employee> employees;
    vector<Task> tasks;
    vector<Citizen> citizens;
    vector<Feedback> feedbacks;
    vector<Department> departments;
    Database db;
    OTPManager otp_manager;
    EfficiencyCalculator efficiency_calc;
    int next_employee_id;
    int next_task_id;
    int next_feedback_id;
    bool is_logged_in;

public:
    Admin();
    
    // Admin Operations
    void addEmployee();
    void addDepartment();
    void assignTask();
    void markTaskComplete();
    void viewEmployeeDetails();
    void viewAllEmployees();
    void filterEmployees();
    void generateEfficiencyReport();
    void departmentWiseRanking();
    void viewAllFeedback();
    void monthlyPerformanceSummary();
    void viewAuditLog();
    void updateEfficiencyScores();
    
    // Citizen Operations (Feedback)
    void citizenFeedbackPortal();
    void requestOTP();
    void submitFeedback();
    
    // Public Reports
    void viewPublicReports();
    
    // Menu Display
    void displayMainMenu();
    void displayAdminMenu();
    void displayCitizenMenu();
    
    // Authentication
    bool handleAdminLogin();
    
    // Main run method
    void run();
};

#endif
