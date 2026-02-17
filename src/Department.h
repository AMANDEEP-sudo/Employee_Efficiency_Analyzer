#ifndef DEPARTMENT_H
#define DEPARTMENT_H

#include <string>
#include <vector>
#include "Employee.h"
using namespace std;

class Department
{
private:
    string dept_name;
    vector<int> employee_ids;
    double avg_efficiency;

public:
    Department();
    Department(string name);

    // Setters
    void setDeptName(string name);
    void setAvgEfficiency(double avg);

    // Getters
    string getDeptName() const;
    vector<int> getEmployeeIds() const;
    double getAvgEfficiency() const;

    // Methods
    void addEmployee(int emp_id);
    void calculateDepartmentAverage(vector<Employee> &employees);
    void generateDepartmentReport(vector<Employee> &employees) const;
    void rankEmployees(vector<Employee> &employees) const;
    void displayDepartmentStats() const;
};

#endif
