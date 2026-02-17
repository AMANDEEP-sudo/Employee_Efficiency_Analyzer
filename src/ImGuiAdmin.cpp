#include "ImGuiAdmin.h"
#include <iostream>
#include <cstring>

ImGuiAdmin::ImGuiAdmin() : current_menu(0), selected_option(0),
    show_add_employee(false), show_add_department(false), show_assign_task(false),
    show_view_employees(false), show_filter_employees(false), show_generate_report(false),
    show_feedback_portal(false), show_login(true), filter_type(0)
{
    memset(employee_name, 0, sizeof(employee_name));
    memset(employee_dept, 0, sizeof(employee_dept));
    memset(task_desc, 0, sizeof(task_desc));
    
    header_color = ImVec4(0.2f, 0.4f, 0.8f, 1.0f);
    button_color = ImVec4(0.1f, 0.3f, 0.7f, 1.0f);
    
    applyTheme();
}

void ImGuiAdmin::applyTheme()
{
    ImGuiStyle& style = ImGui::GetStyle();
    ImVec4* colors = style.Colors;
    
    colors[ImGuiCol_Text] = ImVec4(0.95f, 0.96f, 0.98f, 1.00f);
    colors[ImGuiCol_TextDisabled] = ImVec4(0.36f, 0.42f, 0.47f, 1.00f);
    colors[ImGuiCol_WindowBg] = ImVec4(0.11f, 0.15f, 0.17f, 1.00f);
    colors[ImGuiCol_ChildBg] = ImVec4(0.15f, 0.18f, 0.22f, 1.00f);
    colors[ImGuiCol_Button] = ImVec4(0.20f, 0.35f, 0.60f, 1.00f);
    colors[ImGuiCol_ButtonHovered] = ImVec4(0.25f, 0.42f, 0.72f, 1.00f);
    colors[ImGuiCol_ButtonActive] = ImVec4(0.18f, 0.30f, 0.55f, 1.00f);
    colors[ImGuiCol_Header] = ImVec4(0.20f, 0.35f, 0.60f, 1.00f);
    colors[ImGuiCol_HeaderHovered] = ImVec4(0.25f, 0.42f, 0.72f, 1.00f);
    colors[ImGuiCol_HeaderActive] = ImVec4(0.18f, 0.30f, 0.55f, 1.00f);
}

void ImGuiAdmin::renderMainWindow()
{
    ImGuiIO& io = ImGui::GetIO();
    ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f));
    ImGui::SetNextWindowSize(io.DisplaySize);
    
    ImGui::Begin("##MainWindow", nullptr, 
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | 
        ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse);
    
    // Create layout with sidebar
    ImGui::BeginChild("##Sidebar", ImVec2(250, 0), true);
    renderSidebar();
    ImGui::EndChild();
    
    ImGui::SameLine();
    
    ImGui::BeginChild("##Content", ImVec2(0, 0), false);
    
    if (show_add_employee) renderAddEmployee();
    else if (show_add_department) renderAddDepartment();
    else if (show_assign_task) renderAssignTask();
    else if (show_view_employees) renderViewEmployees();
    else if (show_filter_employees) renderFilterEmployees();
    else if (show_generate_report) renderReports();
    else if (show_feedback_portal) renderFeedbackPortal();
    else renderDashboard();
    
    ImGui::EndChild();
    ImGui::End();
}

void ImGuiAdmin::renderLoginWindow()
{
    ImGuiIO& io = ImGui::GetIO();
    ImVec2 window_pos = ImVec2((io.DisplaySize.x - 400) * 0.5f, (io.DisplaySize.y - 300) * 0.5f);
    ImGui::SetNextWindowPos(window_pos, ImGuiCond_FirstUseEver);
    ImGui::SetNextWindowSize(ImVec2(400, 300));
    
    ImGui::Begin("Employee Efficiency Tracker - Login", nullptr, 
        ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    
    ImGui::TextColoredEx(header_color, "Welcome to \nEmployee Efficiency Tracker");
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::Text("Modern GUI Dashboard");
    ImGui::Spacing();
    ImGui::Text("Powered by ImGui + OpenGL");
    ImGui::Spacing();
    ImGui::Spacing();
    
    ImGui::SetCursorPosX((400 - 150) * 0.5f);
    if (ImGui::Button("Enter Admin Panel", ImVec2(150, 50)))
    {
        show_login = false;
        current_menu = 1;
    }
    
    ImGui::SetCursorPosX((400 - 150) * 0.5f);
    if (ImGui::Button("Exit Application", ImVec2(150, 30)))
    {
        exit(0);
    }
    
    ImGui::End();
}

void ImGuiAdmin::renderSidebar()
{
    ImGui::TextColored(header_color, "MENU");
    ImGui::Separator();
    ImGui::Spacing();
    
    // Employee Operations
    if (ImGui::CollapsingHeader("Employee Operations", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Selectable("Add Employee", show_add_employee))
        {
            show_add_employee = true;
            show_add_department = false;
            show_assign_task = false;
            show_view_employees = false;
            show_filter_employees = false;
            show_generate_report = false;
            show_feedback_portal = false;
        }
        if (ImGui::Selectable("View All Employees", show_view_employees))
        {
            show_add_employee = false;
            show_add_department = false;
            show_assign_task = false;
            show_view_employees = true;
            show_filter_employees = false;
            show_generate_report = false;
            show_feedback_portal = false;
        }
        if (ImGui::Selectable("Filter Employees", show_filter_employees))
        {
            show_add_employee = false;
            show_add_department = false;
            show_assign_task = false;
            show_view_employees = false;
            show_filter_employees = true;
            show_generate_report = false;
            show_feedback_portal = false;
        }
    }
    
    // Task Operations
    if (ImGui::CollapsingHeader("Task Management", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Selectable("Assign Task", show_assign_task))
        {
            show_add_employee = false;
            show_add_department = false;
            show_assign_task = true;
            show_view_employees = false;
            show_filter_employees = false;
            show_generate_report = false;
            show_feedback_portal = false;
        }
    }
    
    // Department Operations
    if (ImGui::CollapsingHeader("Department Management", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Selectable("Add Department", show_add_department))
        {
            show_add_employee = false;
            show_add_department = true;
            show_assign_task = false;
            show_view_employees = false;
            show_filter_employees = false;
            show_generate_report = false;
            show_feedback_portal = false;
        }
    }
    
    // Reports
    if (ImGui::CollapsingHeader("Reports & Analytics", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Selectable("Generate Efficiency Report", show_generate_report))
        {
            show_add_employee = false;
            show_add_department = false;
            show_assign_task = false;
            show_view_employees = false;
            show_filter_employees = false;
            show_generate_report = true;
            show_feedback_portal = false;
        }
    }
    
    // Feedback
    if (ImGui::CollapsingHeader("Citizen Feedback", ImGuiTreeNodeFlags_DefaultOpen))
    {
        if (ImGui::Selectable("Feedback Portal", show_feedback_portal))
        {
            show_add_employee = false;
            show_add_department = false;
            show_assign_task = false;
            show_view_employees = false;
            show_filter_employees = false;
            show_generate_report = false;
            show_feedback_portal = true;
        }
    }
}

void ImGuiAdmin::renderDashboard()
{
    ImGui::TextColored(header_color, "Dashboard");
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::TextWrapped(
        "Welcome to the Employee Efficiency Tracker - Modern GUI Edition!\n\n"
        "This application helps you:\n"
        "  • Manage employee records\n"
        "  • Assign and track tasks\n"
        "  • Calculate efficiency scores\n"
        "  • Generate comprehensive reports\n"
        "  • Collect citizen feedback\n\n"
        "Use the sidebar menu to navigate through different features."
    );
    
    ImGui::Spacing();
    ImGui::Spacing();
    ImGui::Separator();
    ImGui::Spacing();
    
    // Quick Stats
    ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "Quick Stats");
    ImGui::BulletText("Database Status: Connected");
    ImGui::BulletText("System Ready: Yes");
    ImGui::BulletText("GUI Framework: ImGui 1.89+");
}

void ImGuiAdmin::renderAddEmployee()
{
    ImGui::TextColored(header_color, "Add New Employee");
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::InputTextWithHint("##name", "Employee Name", employee_name, sizeof(employee_name));
    ImGui::InputTextWithHint("##dept", "Department", employee_dept, sizeof(employee_dept));
    
    ImGui::Spacing();
    if (ImGui::Button("Add Employee", ImVec2(150, 40)))
    {
        ImGui::OpenPopup("AddSuccess");
        memset(employee_name, 0, sizeof(employee_name));
        memset(employee_dept, 0, sizeof(employee_dept));
    }
    
    if (ImGui::BeginPopupModal("AddSuccess", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Employee added successfully!");
        if (ImGui::Button("OK", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void ImGuiAdmin::renderAddDepartment()
{
    ImGui::TextColored(header_color, "Add New Department");
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::TextWrapped("Department management interface coming soon...");
}

void ImGuiAdmin::renderAssignTask()
{
    ImGui::TextColored(header_color, "Assign Task to Employee");
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::InputTextWithHint("##task", "Task Description", task_desc, sizeof(task_desc));
    ImGui::Spacing();
    
    if (ImGui::Button("Assign Task", ImVec2(150, 40)))
    {
        ImGui::OpenPopup("TaskAssigned");
        memset(task_desc, 0, sizeof(task_desc));
    }
    
    if (ImGui::BeginPopupModal("TaskAssigned", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("Task assigned successfully!");
        if (ImGui::Button("OK", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}

void ImGuiAdmin::renderViewEmployees()
{
    ImGui::TextColored(header_color, "All Employees");
    ImGui::Separator();
    ImGui::Spacing();
    
    if (ImGui::BeginTable("employees_table", 5, ImGuiTableFlags_Borders | ImGuiTableFlags_RowBg))
    {
        ImGui::TableSetupColumn("ID");
        ImGui::TableSetupColumn("Name");
        ImGui::TableSetupColumn("Department");
        ImGui::TableSetupColumn("Efficiency");
        ImGui::TableSetupColumn("Status");
        ImGui::TableHeadersRow();
        
        // Sample data - in real implementation, pull from admin
        for (int i = 0; i < 5; i++)
        {
            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);
            ImGui::Text("EMP%03d", i + 1);
            ImGui::TableSetColumnIndex(1);
            ImGui::Text("Employee %d", i + 1);
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("IT");
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("85%%");
            ImGui::TableSetColumnIndex(4);
            ImGui::TextColored(ImVec4(0.2f, 0.8f, 0.2f, 1.0f), "Active");
        }
        ImGui::EndTable();
    }
}

void ImGuiAdmin::renderFilterEmployees()
{
    ImGui::TextColored(header_color, "Filter Employees");
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::Combo("Filter Type", &filter_type,
        "Department\0"
        "Efficiency Score\0"
        "Task Status\0",
        3);
    
    ImGui::Spacing();
    if (ImGui::Button("Apply Filter", ImVec2(150, 40)))
    {
        // Apply filter logic
    }
}

void ImGuiAdmin::renderReports()
{
    ImGui::TextColored(header_color, "Efficiency Reports & Analytics");
    ImGui::Separator();
    ImGui::Spacing();
    
    if (ImGui::BeginTabBar("##Reports"))
    {
        if (ImGui::BeginTabItem("Efficiency Report"))
        {
            ImGui::Text("Generating efficiency report...");
            ImGui::TextWrapped("Department-wise efficiency breakdown, top performers, performance trends");
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Monthly Summary"))
        {
            ImGui::Text("Monthly Performance Summary");
            ImGui::TextWrapped("Tasks completed this month, efficiency trends, department rankings");
            ImGui::EndTabItem();
        }
        
        if (ImGui::BeginTabItem("Department Ranking"))
        {
            ImGui::Text("Department-wise Ranking");
            ImGui::BulletText("IT - Avg Efficiency: 88%");
            ImGui::BulletText("HR - Avg Efficiency: 85%");
            ImGui::BulletText("Finance - Avg Efficiency: 82%");
            ImGui::EndTabItem();
        }
        ImGui::EndTabBar();
    }
    
    ImGui::Spacing();
    if (ImGui::Button("Export as CSV", ImVec2(150, 40)))
    {
        // Export logic
    }
}

void ImGuiAdmin::renderFeedbackPortal()
{
    ImGui::TextColored(header_color, "Citizen Feedback Portal");
    ImGui::Separator();
    ImGui::Spacing();
    
    ImGui::TextWrapped("This portal allows citizens to provide feedback about government services.");
    ImGui::Spacing();
    
    if (ImGui::Button("View All Feedback", ImVec2(200, 40)))
    {
        // Show feedback
    }
    
    ImGui::SameLine();
    if (ImGui::Button("Request OTP", ImVec2(200, 40)))
    {
        ImGui::OpenPopup("OTPRequest");
    }
    
    if (ImGui::BeginPopupModal("OTPRequest", NULL, ImGuiWindowFlags_AlwaysAutoResize))
    {
        ImGui::Text("OTP sent to registered phone number!");
        if (ImGui::Button("OK", ImVec2(120, 0))) {
            ImGui::CloseCurrentPopup();
        }
        ImGui::EndPopup();
    }
}
