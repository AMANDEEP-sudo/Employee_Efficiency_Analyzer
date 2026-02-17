#include "Department.h"
#include <iostream>
#include <iomanip>
#include <algorithm>
using namespace std;

Department::Department() : dept_name(""), avg_efficiency(0.0) {}

Department::Department(string name) : dept_name(name), avg_efficiency(0.0) {}

void Department::setDeptName(string name) { dept_name = name; }
void Department::setAvgEfficiency(double avg) { avg_efficiency = avg; }

string Department::getDeptName() const { return dept_name; }
vector<int> Department::getEmployeeIds() const { return employee_ids; }
double Department::getAvgEfficiency() const { return avg_efficiency; }

void Department::addEmployee(int emp_id) {
    employee_ids.push_back(emp_id);
    cout << "Employee " << emp_id << " added to department " << dept_name << endl;
}

void Department::calculateDepartmentAverage(vector<Employee>& employees) {
    if (employee_ids.empty()) {
        avg_efficiency = 0.0;
        return;
    }
    
    double total_efficiency = 0.0;
    for (int emp_id : employee_ids) {
        for (const Employee& emp : employees) {
            if (emp.getEmployeeId() == emp_id) {
                total_efficiency += emp.getEfficiencyScore();
                break;
            }
        }
    }
    
    avg_efficiency = total_efficiency / employee_ids.size();
}

void Department::generateDepartmentReport(vector<Employee>& employees) const {
    cout << "\n========== DEPARTMENT REPORT: " << dept_name << " ==========" << endl;
    cout << "Total Employees: " << employee_ids.size() << endl;
    cout << "Average Efficiency: " << fixed << setprecision(2) << avg_efficiency << "/100" << endl;
    cout << "\nEmployee Details:" << endl;
    cout << "-------------------------------------------" << endl;
    
    for (int emp_id : employee_ids) {
        for (const Employee& emp : employees) {
            if (emp.getEmployeeId() == emp_id) {
                cout << "ID: " << emp.getEmployeeId() << " | Name: " << emp.getName() 
                     << " | Efficiency: " << fixed << setprecision(2) 
                     << emp.getEfficiencyScore() << endl;
                break;
            }
        }
    }
    
    cout << "====================================================\n" << endl;
}

void Department::rankEmployees(vector<Employee>& employees) const {
    cout << "\n========== DEPARTMENT RANKING: " << dept_name << " ==========" << endl;
    
    vector<pair<int, double>> emp_efficiency;
    for (int emp_id : employee_ids) {
        for (const Employee& emp : employees) {
            if (emp.getEmployeeId() == emp_id) {
                emp_efficiency.push_back(make_pair(emp_id, emp.getEfficiencyScore()));
                break;
            }
        }
    }
    
    // Sort by efficiency score (descending)
    sort(emp_efficiency.begin(), emp_efficiency.end(), 
         [](const pair<int, double>& a, const pair<int, double>& b) {
             return a.second > b.second;
         });
    
    cout << "Rank | Employee ID | Efficiency Score" << endl;
    cout << "----+--------------+-----------------" << endl;
    
    for (int i = 0; i < emp_efficiency.size(); i++) {
        cout << i + 1 << "    | " << emp_efficiency[i].first << "           | " 
             << fixed << setprecision(2) << emp_efficiency[i].second << endl;
    }
    
    cout << "==============================================\n" << endl;
}

void Department::displayDepartmentStats() const {
    cout << "\n========== DEPARTMENT STATS: " << dept_name << " ==========" << endl;
    cout << "Department Name: " << dept_name << endl;
    cout << "Total Employees: " << employee_ids.size() << endl;
    cout << "Average Efficiency Score: " << fixed << setprecision(2) << avg_efficiency << "/100" << endl;
    cout << "=============================================\n" << endl;
}
