#include "Admin.h"
#include "Constants.h"
#include "Utils.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
using namespace std;

Admin::Admin() : next_employee_id(1), next_task_id(1), next_feedback_id(1), is_logged_in(false)
{
    // Load data from files
    db.loadEmployees(employees);
    db.loadTasks(tasks);
    db.loadCitizens(citizens);
    db.loadFeedback(feedbacks);
}

void Admin::addEmployee()
{
    system("cls");
    cout << "\n========== ADD EMPLOYEE ==========" << endl;

    string name, department;
    int joining_year;

    cout << "Enter Employee Name: ";
    cin.ignore();
    getline(cin, name);

    cout << "Enter Department (IT/HR/Finance/Operations/CSE/Civil/Mechanical/Electrical/Sales): ";
    getline(cin, department);

    cout << "Enter Joining Year (e.g., 2024): ";
    cin >> joining_year;

    // Generate smart employee ID
    int smart_id = Utils::generateSmartEmployeeId(department, joining_year);

    Employee emp(smart_id, name, department, joining_year);
    employees.push_back(emp);
    db.saveEmployee(emp);
    db.logAudit("EMPLOYEE_ADDED", "admin");
    db.exportEmployeesToCSV(employees, tasks);

    cout << "\n✓ Employee added successfully!" << endl;
    cout << "  Generated Smart ID: " << smart_id << endl;
    cout << "  Format: [Dept][Year][Random]" << endl;
    cout << "  Department Code: " << Utils::getDepartmentCode(department) << endl;
    cout << "  Joining Year (last 2 digits): " << (joining_year % 100) << endl;

    cout << "\nPress Enter to continue...";
    cin.get();
}

void Admin::addDepartment()
{
    system("cls");
    cout << "\n========== ADD DEPARTMENT ==========" << endl;

    string dept_name;
    cout << "Enter Department Name: ";
    cin.ignore();
    getline(cin, dept_name);

    Department dept(dept_name);
    departments.push_back(dept);

    cout << "Department added successfully!" << endl;
    cout << "\nPress Enter to continue...";
    cin.get();
}

void Admin::assignTask()
{
    system("cls");
    cout << "\n========== ASSIGN TASK ==========" << endl;

    int emp_id;
    string description, deadline;

    cout << "Enter Employee ID: ";
    cin >> emp_id;

    // Check if employee exists
    bool emp_found = false;
    for (Employee &emp : employees)
    {
        if (emp.getEmployeeId() == emp_id)
        {
            emp_found = true;
            break;
        }
    }

    if (!emp_found)
    {
        cout << "Employee not found!" << endl;
        cin.get();
        cin.get();
        return;
    }

    cout << "Enter Task Description: ";
    cin.ignore();
    getline(cin, description);

    cout << "Enter Deadline (YYYY-MM-DD): ";
    getline(cin, deadline);

    Task task(next_task_id, emp_id, description, deadline);
    tasks.push_back(task);
    db.saveTask(task);

    // Add task to employee
    for (Employee &emp : employees)
    {
        if (emp.getEmployeeId() == emp_id)
        {
            emp.addTask(next_task_id);
            db.saveEmployee(emp);
            break;
        }
    }

    db.logAudit("TASK_ASSIGNED", "admin");
    db.exportEmployeesToCSV(employees, tasks);
    cout << "Task assigned successfully! Task ID: " << next_task_id << endl;
    next_task_id++;

    cout << "\nPress Enter to continue...";
    cin.get();
}

void Admin::markTaskComplete()
{
    system("cls");
    cout << "\n========== MARK TASK COMPLETE ==========" << endl;

    int task_id;
    string completion_date;

    cout << "Enter Task ID: ";
    cin >> task_id;

    cin.ignore();
    cout << "Enter Completion Date (YYYY-MM-DD): ";
    getline(cin, completion_date);

    bool task_found = false;
    for (Task &task : tasks)
    {
        if (task.getTaskId() == task_id)
        {
            task.markComplete(completion_date);
            task_found = true;

            // Update employee
            for (Employee &emp : employees)
            {
                if (emp.getEmployeeId() == task.getEmployeeId())
                {
                    emp.completeTask(task_id);
                    db.saveEmployee(emp);
                    break;
                }
            }

            db.saveTask(task);
            db.logAudit("TASK_COMPLETED", "admin");
            break;
        }
    }

    if (!task_found)
    {
        cout << "Task not found!" << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}

void Admin::viewEmployeeDetails()
{
    system("cls");
    cout << "\n========== VIEW EMPLOYEE DETAILS ==========" << endl;

    int emp_id;
    cout << "Enter Employee ID: ";
    cin >> emp_id;

    bool found = false;
    for (const Employee &emp : employees)
    {
        if (emp.getEmployeeId() == emp_id)
        {
            emp.displayInfo();
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Employee not found!" << endl;
    }

    cout << "\nPress Enter to continue...";
    cin.get();
    cin.get();
}

void Admin::viewAllEmployees()
{
    system("cls");
    cout << "\n========== ALL EMPLOYEES ==========" << endl;

    if (employees.empty())
    {
        cout << "No employees found!" << endl;
        cout << "\nPress Enter to continue...";
        cin.get();
        return;
    }

    cout << setw(12) << "Employee ID" << " | "
         << setw(20) << "Name" << " | "
         << setw(15) << "Department" << " | "
         << setw(5) << "Year" << " | "
         << setw(5) << "Tasks" << " | "
         << setw(9) << "Efficiency" << endl;
    cout << string(100, '-') << endl;

    for (const Employee &emp : employees)
    {
        cout << setw(12) << emp.getEmployeeId() << " | "
             << setw(20) << emp.getName().substr(0, 19) << " | "
             << setw(15) << emp.getDepartment() << " | "
             << setw(5) << emp.getJoiningYear() << " | "
             << setw(5) << emp.getTotalTasks() << " | "
             << fixed << setprecision(2) << setw(8) << emp.getEfficiencyScore() << "%" << endl;
    }

    cout << "\nTotal Employees: " << employees.size() << endl;
    cout << "\nPress Enter to continue...";
    cin.get();
    cin.get();
}

void Admin::filterEmployees()
{
    system("cls");
    cout << "\n========== FILTER EMPLOYEES ==========" << endl;
    cout << "1. Filter by Department" << endl;
    cout << "2. Filter by Joining Year" << endl;
    cout << "3. Filter by Efficiency Score (Above threshold)" << endl;
    cout << "4. Filter by Task Completion Status" << endl;
    cout << "5. Back to Menu" << endl;
    cout << "Enter your choice: ";

    int choice;
    cin >> choice;
    cin.ignore();

    vector<Employee> filtered_employees;
    bool show_results = false;

    if (choice == 1)
    {
        // Filter by Department
        string dept;
        cout << "Enter Department: ";
        getline(cin, dept);

        cout << "\n========== EMPLOYEES IN " << Utils::toUpper(dept) << " DEPARTMENT ==========" << endl;

        for (const Employee &emp : employees)
        {
            if (Utils::toLower(emp.getDepartment()) == Utils::toLower(dept))
            {
                filtered_employees.push_back(emp);
            }
        }
        show_results = true;
    }
    else if (choice == 2)
    {
        // Filter by Joining Year
        int year;
        cout << "Enter Joining Year: ";
        cin >> year;
        cin.ignore();

        cout << "\n========== EMPLOYEES JOINED IN " << year << " ==========" << endl;

        for (const Employee &emp : employees)
        {
            if (emp.getJoiningYear() == year)
            {
                filtered_employees.push_back(emp);
            }
        }
        show_results = true;
    }
    else if (choice == 3)
    {
        // Filter by Efficiency Score
        double threshold;
        cout << "Enter Minimum Efficiency Score (0-100): ";
        cin >> threshold;
        cin.ignore();

        cout << "\n========== EMPLOYEES WITH EFFICIENCY >= " << threshold << "% ==========" << endl;

        for (const Employee &emp : employees)
        {
            if (emp.getEfficiencyScore() >= threshold)
            {
                filtered_employees.push_back(emp);
            }
        }
        show_results = true;
    }
    else if (choice == 4)
    {
        // Filter by High/Low Task Completion
        cout << "1. Completed All Tasks" << endl;
        cout << "2. Pending Tasks" << endl;
        cout << "Enter choice: ";
        int sub_choice;
        cin >> sub_choice;
        cin.ignore();

        if (sub_choice == 1)
        {
            cout << "\n========== EMPLOYEES WITH COMPLETED TASKS ==========" << endl;
            for (const Employee &emp : employees)
            {
                if (emp.getCompletedTasks() > 0)
                {
                    filtered_employees.push_back(emp);
                }
            }
        }
        else if (sub_choice == 2)
        {
            cout << "\n========== EMPLOYEES WITH PENDING TASKS ==========" << endl;
            for (const Employee &emp : employees)
            {
                if (emp.getTotalTasks() > emp.getCompletedTasks())
                {
                    filtered_employees.push_back(emp);
                }
            }
        }
        show_results = true;
    }
    else if (choice == 5)
    {
        return;
    }
    else
    {
        cout << "Invalid choice!" << endl;
        cout << "\nPress Enter to continue...";
        cin.get();
        return;
    }

    // Display filtered results
    if (show_results)
    {
        if (!filtered_employees.empty())
        {
            cout << setw(12) << "Employee ID" << " | "
                 << setw(20) << "Name" << " | "
                 << setw(15) << "Department" << " | "
                 << setw(5) << "Year" << " | "
                 << setw(9) << "Efficiency" << endl;
            cout << string(85, '-') << endl;

            for (const Employee &emp : filtered_employees)
            {
                cout << setw(12) << emp.getEmployeeId() << " | "
                     << setw(20) << emp.getName().substr(0, 19) << " | "
                     << setw(15) << emp.getDepartment() << " | "
                     << setw(5) << emp.getJoiningYear() << " | "
                     << fixed << setprecision(2) << setw(8) << emp.getEfficiencyScore() << "%" << endl;
            }

            cout << "\nTotal Results: " << filtered_employees.size() << endl;
        }
        else
        {
            cout << "No employees match the filter criteria!" << endl;
        }
    }

    cout << "\nPress Enter to continue...";
    cin.get();
}

void Admin::generateEfficiencyReport()
{
    system("cls");
    cout << "\n========== GENERATE EFFICIENCY REPORT ==========" << endl;

    cout << "Calculating efficiency scores for all employees..." << endl;
    efficiency_calc.updateAllEmployeeScores(employees);

    cout << "\n========== ALL EMPLOYEES EFFICIENCY ==========" << endl;
    cout << "ID | Name              | Department         | Efficiency Score" << endl;
    cout << "---+-------------------+--------------------+------------------" << endl;

    for (const Employee &emp : employees)
    {
        cout << emp.getEmployeeId() << "  | " << setw(17) << left << emp.getName()
             << " | " << setw(18) << emp.getDepartment() << " | "
             << fixed << setprecision(2) << emp.getEfficiencyScore() << "/100" << endl;
    }

    cout << "============================================\n"
         << endl;

    cout << "\nPress Enter to continue...";
    cin.get();
    cin.get();
}

void Admin::departmentWiseRanking()
{
    system("cls");
    cout << "\n========== DEPARTMENT-WISE RANKING ==========" << endl;

    for (Department &dept : departments)
    {
        dept.calculateDepartmentAverage(employees);
        dept.rankEmployees(employees);
    }

    cout << "\nPress Enter to continue...";
    cin.get();
    cin.get();
}

void Admin::viewAllFeedback()
{
    system("cls");
    cout << "\n========== ALL FEEDBACK ==========" << endl;

    if (feedbacks.empty())
    {
        cout << "No feedback submitted yet!" << endl;
    }
    else
    {
        for (const Feedback &fb : feedbacks)
        {
            fb.displayFeedback();
        }
    }

    cout << "\nPress Enter to continue...";
    cin.get();
    cin.get();
}

void Admin::monthlyPerformanceSummary()
{
    system("cls");
    cout << "\n========== MONTHLY PERFORMANCE SUMMARY ==========" << endl;
    cout << "Current Time: 2024-02-16 (Simulated)" << endl;
    cout << "Month: February 2024" << endl
         << endl;

    double total_efficiency = 0;
    for (const Employee &emp : employees)
    {
        total_efficiency += emp.getEfficiencyScore();
    }

    double avg_efficiency = employees.size() > 0 ? total_efficiency / employees.size() : 0;

    cout << "Total Employees: " << employees.size() << endl;
    cout << "Total Tasks: " << tasks.size() << endl;
    cout << "Total Feedback: " << feedbacks.size() << endl;
    cout << "Average Efficiency Score: " << fixed << setprecision(2) << avg_efficiency
         << "/100" << endl;

    cout << "================================================\n"
         << endl;

    cout << "\nPress Enter to continue...";
    cin.get();
    cin.get();
}

void Admin::viewAuditLog()
{
    system("cls");
    db.readAuditLog();

    cout << "\nPress Enter to continue...";
    cin.get();
}

void Admin::updateEfficiencyScores()
{
    efficiency_calc.updateAllEmployeeScores(employees);

    for (Employee &emp : employees)
    {
        db.saveEmployee(emp);
    }

    cout << "All efficiency scores updated!" << endl;
}

void Admin::citizenFeedbackPortal()
{
    system("cls");
    cout << "\n========== CITIZEN FEEDBACK PORTAL ==========" << endl;

    string aadhaar;
    cout << "Enter your 12-digit Aadhaar ID: ";
    cin >> aadhaar;

    // Validate Aadhaar
    Citizen temp;
    if (!temp.validateAadhaar(aadhaar))
    {
        cout << "Invalid Aadhaar format! Please enter 12 digits." << endl;
        cin.get();
        cin.get();
        return;
    }

    string hashed_aadhaar = temp.hashAadhaar(aadhaar);

    // Check if citizen exists, if not register
    bool citizen_found = false;
    for (Citizen &cit : citizens)
    {
        if (cit.getHashedAadhaar() == hashed_aadhaar)
        {
            citizen_found = true;
            break;
        }
    }

    if (!citizen_found)
    {
        cout << "\nCitizen not registered. Registering..." << endl;
        string name, address, mobile;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter Address: ";
        getline(cin, address);
        cout << "Enter Mobile: ";
        getline(cin, mobile);

        Citizen new_citizen(hashed_aadhaar, name, address, mobile);
        citizens.push_back(new_citizen);
        db.saveCitizen(new_citizen);
        db.logAudit("CITIZEN_REGISTERED", aadhaar);
    }

    // Request OTP
    cout << "\nGenerating OTP for you..." << endl;
    string otp = otp_manager.generateOTP(hashed_aadhaar);
    cout << "OTP has been generated. Displaying for demonstration:" << endl;
    otp_manager.displayOTP(otp);

    // Verify OTP
    string entered_otp;
    cout << "Enter the OTP you received: ";
    cin >> entered_otp;

    if (otp_manager.verifyOTP(hashed_aadhaar, entered_otp))
    {
        // Allow feedback submission
        submitFeedback();
    }
    else
    {
        cout << "OTP verification failed!" << endl;
        cin.get();
        cin.get();
    }
}

void Admin::submitFeedback()
{
    cout << "\n========== SUBMIT FEEDBACK ==========" << endl;

    string hashed_aadhaar;
    int emp_id, rating;
    string comment;

    cout << "Enter Employee ID to give feedback: ";
    cin >> emp_id;

    // Check if employee exists
    bool emp_found = false;
    for (const Employee &emp : employees)
    {
        if (emp.getEmployeeId() == emp_id)
        {
            emp_found = true;
            break;
        }
    }

    if (!emp_found)
    {
        cout << "Employee not found!" << endl;
        return;
    }

    cout << "Enter Rating (1-5): ";
    cin >> rating;

    if (rating < RATING_MIN || rating > RATING_MAX)
    {
        cout << "Invalid rating!" << endl;
        return;
    }

    cin.ignore();
    cout << "Enter Comment: ";
    getline(cin, comment);

    // For demonstration, using a generic hash
    hashed_aadhaar = "generic_citizen_hash";

    // Check for duplicate feedback
    bool duplicate = false;
    for (const Feedback &fb : feedbacks)
    {
        if (fb.getEmployeeId() == emp_id && fb.getHashedCitizenAadhaar() == hashed_aadhaar)
        {
            duplicate = true;
            break;
        }
    }

    if (duplicate)
    {
        cout << "You have already submitted feedback for this employee!" << endl;
        return;
    }

    Feedback fb(next_feedback_id, emp_id, hashed_aadhaar);
    fb.setRating(rating);
    fb.setComment(comment);
    fb.submitFeedback();

    feedbacks.push_back(fb);
    db.saveFeedback(fb);

    // Update employee rating
    for (Employee &emp : employees)
    {
        if (emp.getEmployeeId() == emp_id)
        {
            emp.updateRating(rating);
            db.saveEmployee(emp);
            break;
        }
    }

    db.logAudit("FEEDBACK_SUBMITTED", hashed_aadhaar);
    next_feedback_id++;

    cout << "\nPress Enter to continue...";
    cin.get();
}

void Admin::viewPublicReports()
{
    system("cls");
    cout << "\n========== PUBLIC REPORTS ==========" << endl;
    cout << "1. Overall Efficiency Statistics" << endl;
    cout << "2. Department Rankings" << endl;
    cout << "3. Top Performers" << endl;
    cout << "\nSelect Option (1-3): ";

    int choice;
    cin >> choice;

    if (choice == 1)
    {
        system("cls");
        generateEfficiencyReport();
    }
    else if (choice == 2)
    {
        system("cls");
        departmentWiseRanking();
    }
    else if (choice == 3)
    {
        system("cls");
        cout << "========== TOP PERFORMERS ==========" << endl;
        // Implementation for top performers
        cout << "\nPress Enter to continue...";
        cin.get();
        cin.get();
    }
}

void Admin::displayMainMenu()
{
    cout << "\n-==============================================" << endl;
    cout << "|  GOVERNMENT EMPLOYEE EFFICIENCY TRACKER      |" << endl;
    cout << "=============================================-" << endl;
    cout << "1. Admin Login" << endl;
    cout << "2. Citizen Feedback Portal" << endl;
    cout << "3. View Public Reports" << endl;
    cout << "4. Exit" << endl;
    cout << "=============================================" << endl;
}

void Admin::displayAdminMenu()
{
    cout << "\n========== ADMIN MENU ==========" << endl;
    cout << "1. Add Employee" << endl;
    cout << "2. Add Department" << endl;
    cout << "3. Assign Task" << endl;
    cout << "4. Mark Task Complete" << endl;
    cout << "5. View Employee Details" << endl;
    cout << "6. View All Employees" << endl;
    cout << "7. Filter Employees" << endl;
    cout << "8. Generate Efficiency Report" << endl;
    cout << "9. Department-wise Ranking" << endl;
    cout << "10. View All Feedback" << endl;
    cout << "11. Monthly Performance Summary" << endl;
    cout << "12. View Audit Log" << endl;
    cout << "13. Logout" << endl;
    cout << "============================\n"
         << endl;
}

void Admin::displayCitizenMenu()
{
    cout << "\n-===== CITIZEN FEEDBACK MENU =====" << endl;
    cout << "1. Submit Feedback" << endl;
    cout << "2. Exit" << endl;
    cout << "==================================\n"
         << endl;
}

bool Admin::handleAdminLogin()
{
    system("cls");
    cout << "\n========== ADMIN LOGIN ==========" << endl;

    string username, password;
    cout << "Username (default: admin): ";
    cin >> username;
    cout << "Password (default: admin123): ";
    cin >> password;

    // Simple authentication (for demonstration)
    if (username == "admin" && password == "admin123")
    {
        cout << "Login successful!" << endl;
        db.logAudit("ADMIN_LOGIN", username);
        return true;
    }
    else
    {
        cout << "Invalid credentials!" << endl;
        cin.get();
        cin.get();
        return false;
    }
}

void Admin::run()
{
    int choice;
    bool running = true;

    while (running)
    {
        system("cls");
        displayMainMenu();
        cout << "Enter your choice (1-4): ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            if (handleAdminLogin())
            {
                int admin_choice;
                bool admin_menu = true;

                while (admin_menu)
                {
                    system("cls");
                    displayAdminMenu();
                    cout << "Enter your choice (1-13): ";
                    cin >> admin_choice;

                    switch (admin_choice)
                    {
                    case 1:
                        addEmployee();
                        break;
                    case 2:
                        addDepartment();
                        break;
                    case 3:
                        assignTask();
                        break;
                    case 4:
                        markTaskComplete();
                        break;
                    case 5:
                        viewEmployeeDetails();
                        break;
                    case 6:
                        viewAllEmployees();
                        break;
                    case 7:
                        filterEmployees();
                        break;
                    case 8:
                        generateEfficiencyReport();
                        break;
                    case 9:
                        departmentWiseRanking();
                        break;
                    case 10:
                        viewAllFeedback();
                        break;
                    case 11:
                        monthlyPerformanceSummary();
                        break;
                    case 12:
                        viewAuditLog();
                        break;
                    case 13:
                    {
                        cout << "Logging out..." << endl;
                        db.logAudit("ADMIN_LOGOUT", "admin");
                        admin_menu = false;
                        cout << "\nPress Enter to continue...";
                        cin.get();
                        cin.get();
                        break;
                    }
                    default:
                        cout << "Invalid choice!" << endl;
                    }
                }
            }
            break;
        }
        case 2:
            citizenFeedbackPortal();
            break;
        case 3:
            viewPublicReports();
            break;
        case 4:
        {
            cout << "Exiting system..." << endl;
            running = false;
            break;
        }
        default:
        {
            cout << "Invalid choice!" << endl;
            cin.get();
            cin.get();
        }
        }
    }
}
