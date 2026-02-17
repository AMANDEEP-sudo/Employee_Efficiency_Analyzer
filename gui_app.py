import tkinter as tk
from tkinter import ttk, messagebox, simpledialog, filedialog
import subprocess
import json
import os
from datetime import datetime
import sys

class EmployeeEfficiencyGUI:
    def __init__(self, root):
        self.root = root
        self.root.title("Employee Efficiency Tracker - GUI")
        self.root.geometry("1000x700")
        self.root.resizable(True, True)
        
        # Style Configuration
        style = ttk.Style()
        style.theme_use('clam')
        
        # Colors
        self.bg_color = "#f0f0f0"
        self.primary_color = "#2196F3"
        self.success_color = "#4CAF50"
        self.warning_color = "#FF9800"
        self.danger_color = "#f44336"
        
        # Configure styles
        style.configure('TButton', font=('Arial', 10))
        style.configure('Title.TLabel', font=('Arial', 16, 'bold'))
        style.configure('Header.TLabel', font=('Arial', 12, 'bold'))
        
        self.root.configure(bg=self.bg_color)
        self.load_employee_data()
        self.show_login_screen()
    
    def load_employee_data(self):
        """Load employee data from .dat file"""
        self.employees = []
        try:
            if os.path.exists('data/employees.dat'):
                with open('data/employees.dat', 'r') as f:
                    for line in f:
                        if line.strip():
                            parts = line.strip().split('|')
                            if len(parts) >= 8:
                                self.employees.append({
                                    'id': parts[0],
                                    'name': parts[1],
                                    'department': parts[2],
                                    'year': parts[3],
                                    'tasks': parts[4],
                                    'completed': parts[5],
                                    'efficiency': parts[6],
                                    'feedback': parts[7]
                                })
        except Exception as e:
            messagebox.showerror("Error", f"Failed to load employee data: {e}")
    
    def clear_window(self):
        """Clear all widgets from window"""
        for widget in self.root.winfo_children():
            widget.destroy()
    
    def show_login_screen(self):
        """Display login screen"""
        self.clear_window()
        
        # Main frame
        main_frame = ttk.Frame(self.root)
        main_frame.pack(expand=True, fill='both')
        
        # Center frame
        center_frame = ttk.Frame(main_frame)
        center_frame.pack(expand=True)
        
        # Title
        title = ttk.Label(center_frame, text="Employee Efficiency Tracker", style='Title.TLabel')
        title.pack(pady=20)
        
        subtitle = ttk.Label(center_frame, text="Admin Login", font=('Arial', 12))
        subtitle.pack(pady=10)
        
        # Login form
        form_frame = ttk.LabelFrame(center_frame, text="Login", padding=20)
        form_frame.pack(pady=20)
        
        ttk.Label(form_frame, text="Username:").grid(row=0, column=0, sticky='e', padx=5, pady=10)
        username_entry = ttk.Entry(form_frame, width=25)
        username_entry.grid(row=0, column=1, padx=5, pady=10)
        username_entry.insert(0, "admin")
        
        ttk.Label(form_frame, text="Password:").grid(row=1, column=0, sticky='e', padx=5, pady=10)
        password_entry = ttk.Entry(form_frame, width=25, show="*")
        password_entry.grid(row=1, column=1, padx=5, pady=10)
        password_entry.insert(0, "admin123")
        
        # Buttons
        button_frame = ttk.Frame(form_frame)
        button_frame.grid(row=2, column=0, columnspan=2, pady=20)
        
        def login():
            username = username_entry.get()
            password = password_entry.get()
            if username == "admin" and password == "admin123":
                self.show_main_menu()
            else:
                messagebox.showerror("Error", "Invalid credentials!")
        
        ttk.Button(button_frame, text="Login", command=login, width=15).pack(side='left', padx=5)
        ttk.Button(button_frame, text="Exit", command=self.root.quit, width=15).pack(side='left', padx=5)
    
    def show_main_menu(self):
        """Display main admin menu"""
        self.clear_window()
        
        # Header
        header_frame = ttk.Frame(self.root)
        header_frame.pack(fill='x', padx=20, pady=15)
        
        ttk.Label(header_frame, text="Admin Dashboard", style='Title.TLabel').pack(anchor='w')
        ttk.Label(header_frame, text="Manage employees and track efficiency", font=('Arial', 10)).pack(anchor='w')
        
        # Main content
        content_frame = ttk.Frame(self.root)
        content_frame.pack(fill='both', expand=True, padx=20, pady=10)
        
        # Left column
        left_frame = ttk.LabelFrame(content_frame, text="Employee Management", padding=10)
        left_frame.pack(side='left', fill='both', expand=True, padx=5)
        
        buttons_left = [
            ("➕ Add Employee", self.show_add_employee),
            ("📋 View All Employees", self.show_all_employees),
            ("🔍 Filter Employees", self.show_filter_menu),
            ("👤 View Employee Details", self.show_view_details),
        ]
        
        for text, cmd in buttons_left:
            btn = ttk.Button(left_frame, text=text, command=cmd, width=30)
            btn.pack(pady=8, fill='x')
        
        # Right column
        right_frame = ttk.LabelFrame(content_frame, text="Tasks & Reports", padding=10)
        right_frame.pack(side='left', fill='both', expand=True, padx=5)
        
        buttons_right = [
            ("✏️  Assign Task", self.show_assign_task),
            ("✅ Mark Task Complete", self.show_mark_complete),
            ("📊 Efficiency Report", self.show_efficiency_report),
            ("🏆 Department Ranking", self.show_department_ranking),
        ]
        
        for text, cmd in buttons_right:
            btn = ttk.Button(right_frame, text=text, command=cmd, width=30)
            btn.pack(pady=8, fill='x')
        
        # Bottom frame
        bottom_frame = ttk.Frame(self.root)
        bottom_frame.pack(fill='x', padx=20, pady=15)
        
        ttk.Button(bottom_frame, text="🚪 Logout", command=self.show_login_screen, width=20).pack(side='left', padx=5)
        ttk.Button(bottom_frame, text="❌ Exit", command=self.root.quit, width=20).pack(side='left', padx=5)
    
    def show_add_employee(self):
        """Show add employee dialog"""
        dialog = tk.Toplevel(self.root)
        dialog.title("Add Employee")
        dialog.geometry("400x300")
        dialog.resizable(False, False)
        
        # Form fields
        form_frame = ttk.Frame(dialog, padding=20)
        form_frame.pack(fill='both', expand=True)
        
        ttk.Label(form_frame, text="Employee Name:").grid(row=0, column=0, sticky='w', pady=10)
        name_entry = ttk.Entry(form_frame, width=30)
        name_entry.grid(row=0, column=1, pady=10)
        
        ttk.Label(form_frame, text="Department:").grid(row=1, column=0, sticky='w', pady=10)
        dept_var = tk.StringVar(value="IT")
        dept_combo = ttk.Combobox(form_frame, textvariable=dept_var, 
                                   values=["IT", "HR", "Finance", "Operations", "CSE", "Civil", "Mechanical", "Electrical", "Sales"],
                                   state="readonly", width=27)
        dept_combo.grid(row=1, column=1, pady=10)
        
        ttk.Label(form_frame, text="Joining Year:").grid(row=2, column=0, sticky='w', pady=10)
        year_entry = ttk.Entry(form_frame, width=30)
        year_entry.insert(0, str(datetime.now().year))
        year_entry.grid(row=2, column=1, pady=10)
        
        # Buttons
        button_frame = ttk.Frame(form_frame)
        button_frame.grid(row=3, column=0, columnspan=2, pady=20)
        
        def save_employee():
            name = name_entry.get()
            dept = dept_var.get()
            year = year_entry.get()
            
            if not name or not dept or not year:
                messagebox.showerror("Error", "Please fill all fields!")
                return
            
            try:
                # Call C++ backend through subprocess
                result = subprocess.run(['./efficiency_tracker.exe'], 
                                      input=f"1\nadmin\nadmin123\n1\n{name}\n{dept}\n{year}\n11\nq\n4\n",
                                      capture_output=True, text=True, timeout=5)
                
                # Reload data
                self.load_employee_data()
                messagebox.showinfo("Success", f"Employee '{name}' added successfully!")
                dialog.destroy()
            except Exception as e:
                messagebox.showerror("Error", f"Failed to add employee: {e}")
        
        ttk.Button(button_frame, text="Save", command=save_employee).pack(side='left', padx=5)
        ttk.Button(button_frame, text="Cancel", command=dialog.destroy).pack(side='left', padx=5)
    
    def show_all_employees(self):
        """Show all employees in a table"""
        self.create_table_window("All Employees", self.employees)
    
    def show_view_details(self):
        """Show single employee details"""
        emp_id = simpledialog.askstring("View Details", "Enter Employee ID:")
        if emp_id:
            emp = next((e for e in self.employees if e['id'] == emp_id), None)
            if emp:
                self.create_table_window(f"Employee Details - {emp['name']}", [emp])
            else:
                messagebox.showerror("Error", "Employee not found!")
    
    def show_filter_menu(self):
        """Show filter options"""
        dialog = tk.Toplevel(self.root)
        dialog.title("Filter Employees")
        dialog.geometry("400x250")
        dialog.resizable(False, False)
        
        frame = ttk.Frame(dialog, padding=20)
        frame.pack(fill='both', expand=True)
        
        ttk.Label(frame, text="Filter By:", style='Header.TLabel').pack(pady=10)
        
        # Filter options
        def filter_department():
            dialog.destroy()
            dept = simpledialog.askstring("Filter", "Enter Department:")
            if dept:
                filtered = [e for e in self.employees if e['department'].lower() == dept.lower()]
                self.create_table_window(f"Employees - {dept} Department", filtered)
        
        def filter_year():
            dialog.destroy()
            year = simpledialog.askstring("Filter", "Enter Joining Year:")
            if year:
                filtered = [e for e in self.employees if e['year'] == year]
                self.create_table_window(f"Employees - Joined {year}", filtered)
        
        def filter_efficiency():
            dialog.destroy()
            threshold = simpledialog.askfloat("Filter", "Enter Minimum Efficiency Score:")
            if threshold is not None:
                filtered = [e for e in self.employees if float(e['efficiency']) >= threshold]
                self.create_table_window(f"Employees - Efficiency >= {threshold}%", filtered)
        
        buttons = [
            ("Department", filter_department),
            ("Joining Year", filter_year),
            ("Efficiency Score", filter_efficiency),
        ]
        
        for text, cmd in buttons:
            ttk.Button(frame, text=text, command=cmd, width=25).pack(pady=8, fill='x')
    
    def create_table_window(self, title, data):
        """Create table window to display data"""
        table_window = tk.Toplevel(self.root)
        table_window.title(title)
        table_window.geometry("1000x500")
        
        # Create treeview
        columns = ('ID', 'Name', 'Department', 'Year', 'Tasks', 'Completed', 'Efficiency', 'Feedback')
        tree = ttk.Treeview(table_window, columns=columns, height=20, show='headings')
        
        # Define column headings and widths
        col_widths = [100, 150, 120, 80, 70, 90, 100, 80]
        for col, width in zip(columns, col_widths):
            tree.column(col, width=width, anchor='center')
            tree.heading(col, text=col)
        
        # Add scrollbar
        scrollbar = ttk.Scrollbar(table_window, orient='vertical', command=tree.yview)
        tree.configure(yscroll=scrollbar.set)
        
        tree.pack(side='left', fill='both', expand=True, padx=10, pady=10)
        scrollbar.pack(side='right', fill='y', padx=5, pady=10)
        
        # Populate data
        for emp in data:
            values = (emp['id'], emp['name'], emp['department'], emp['year'], 
                     emp['tasks'], emp['completed'], emp['efficiency'], emp['feedback'])
            tree.insert('', 'end', values=values)
        
        # Status bar
        status_frame = ttk.Frame(table_window)
        status_frame.pack(fill='x', padx=10, pady=5)
        ttk.Label(status_frame, text=f"Total Records: {len(data)}").pack(anchor='w')
        
        ttk.Button(status_frame, text="Close", command=table_window.destroy).pack(anchor='e')
    
    def show_assign_task(self):
        """Show assign task dialog"""
        messagebox.showinfo("Assign Task", "This feature opens in console mode.\nPlease use the console interface for task assignment.")
    
    def show_mark_complete(self):
        """Show mark complete dialog"""
        messagebox.showinfo("Mark Task Complete", "This feature opens in console mode.\nPlease use the console interface to mark tasks complete.")
    
    def show_efficiency_report(self):
        """Show efficiency report"""
        messagebox.showinfo("Efficiency Report", "This feature opens in console mode.\nPlease use the console interface to view detailed reports.")
    
    def show_department_ranking(self):
        """Show department ranking"""
        messagebox.showinfo("Department Ranking", "This feature opens in console mode.\nPlease use the console interface to view department rankings.")


def main():
    root = tk.Tk()
    app = EmployeeEfficiencyGUI(root)
    root.mainloop()


if __name__ == "__main__":
    main()
