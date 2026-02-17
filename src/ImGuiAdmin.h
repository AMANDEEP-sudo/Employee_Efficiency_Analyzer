#ifndef IMGUI_ADMIN_H
#define IMGUI_ADMIN_H

#include <imgui.h>
#include <string>
#include <vector>
#include "Admin.h"

class ImGuiAdmin
{
private:
    Admin admin;
    
    // State variables for UI
    int current_menu;  // 0=login, 1=main, 2=operations, 3=reports
    int selected_option;
    bool show_add_employee;
    bool show_add_department;
    bool show_assign_task;
    bool show_view_employees;
    bool show_filter_employees;
    bool show_generate_report;
    bool show_feedback_portal;
    bool show_login;
    
    // Form inputs
    char employee_name[128];
    char employee_dept[64];
    char task_desc[512];
    int filter_type;
    
    ImVec4 header_color;
    ImVec4 button_color;

public:
    ImGuiAdmin();
    
    void renderMainWindow();
    void renderLoginWindow();
    void renderDashboard();
    void renderAddEmployee();
    void renderAddDepartment();
    void renderAssignTask();
    void renderViewEmployees();
    void renderFilterEmployees();
    void renderReports();
    void renderFeedbackPortal();
    void renderSidebar();
    void applyTheme();
};

#endif // IMGUI_ADMIN_H
