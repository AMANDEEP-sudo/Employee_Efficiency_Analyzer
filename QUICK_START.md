# Quick Start Guide - GUI Application

## 🚀 Get Started in 3 Steps

### Step 1: Open PowerShell
```powershell
# Navigate to the project folder
cd e:\AREA_51_CODES\Employee_efficiency_tool
```

### Step 2: Run the GUI Application
```powershell
python gui_app.py
```

### Step 3: Login
- **Username**: `admin`
- **Password**: `admin123`
- Click **Login** button

---

## ✨ Main Features Available

### 📝 Add Employee
1. Click "➕ Add Employee" button
2. Enter employee name (e.g., "John Doe")
3. Select department from dropdown (IT, HR, Finance, etc.)
4. Enter joining year (default: current year)
5. Click "Save"
   - Smart ID auto-generated (e.g., 12428932)
   - Data saved to employees.dat
   - Visible in "View All Employees"

### 📊 View All Employees
1. Click "📋 View All Employees"
2. See table with:
   - Employee ID
   - Name
   - Department
   - Joining Year
   - Tasks assigned
   - Completed tasks
   - Efficiency score
   - Feedback count

### 🔍 Filter Employees
1. Click "🔍 Filter Employees"
2. Choose filter option:
   - **By Department**: Enter department name (IT, HR, etc.)
   - **By Joining Year**: Enter year (2024, 2023, etc.)
   - **By Efficiency Score**: Enter minimum score (0-100)

### 👤 View Employee Details
1. Click "👤 View Employee Details"
2. Enter Employee ID
3. View detailed employee information

---

## 🎯 Smart ID System

### How it Works
Every employee gets a unique **8-digit ID** with structure:

```
Example: [1][24][28932]
         │  │   └─ Random 5-digit number
         │  └───── Joining year (24 = 2024)
         └──────── Department code
```

### Department Codes
| Code | Department |
|------|-----------|
| 1 | IT |
| 2 | HR |
| 3 | Finance |
| 4 | Operations |
| 5 | CSE |
| 6 | Civil |
| 7 | Mechanical |
| 8 | Electrical |
| 9 | Sales |

### Example IDs
- **12420456** = IT, 2024, Random#20456
- **22421789** = HR, 2024, Random#21789
- **52323345** = CSE, 2023, Random#23345

---

## 📁 Important Folders

```
Employee_efficiency_tool/
├── gui_app.py                  ← Run this file
├── efficiency_tracker.exe      ← C++ backend
├── data/
│   ├── employees.dat          ← Employee database
│   ├── employees_report.csv   ← CSV export (auto-generated)
│   └── audit_log.dat          ← System logs
└── src/                        ← Source code files
```

---

## ⚙️ Console Mode (Advanced)

For features not in GUI, use console:
```powershell
.\efficiency_tracker.exe
```

### Console Features
- ✅ Task assignment and completion
- ✅ Citizen feedback portal
- ✅ OTP management
- ✅ Detailed reports
- ✅ Department rankings
- ✅ Audit log viewing

---

## 🐛 Troubleshooting

### Issue: GUI won't open
**Solution**: 
```powershell
# Check Python
python --version

# Check tkinter
python -m tkinter

# If errors, reinstall Python with tkinter
```

### Issue: No employees showing
**Solution**:
1. Add a new employee through GUI
2. Check that `data/employees.dat` exists
3. Data appears after clicking "View All Employees"

### Issue: Filter not working
**Solution**:
1. Ensure you have employees in the system
2. Use exact department names (IT, HR, Finance, etc.)
3. Use correct year format (YYYY)

### Issue: Can't compile C++ code
**Solution**:
```powershell
# Clean and rebuild
g++ -std=c++17 -o efficiency_tracker.exe src/*.cpp
```

---

## 📊 Data Export

CSV reports are automatically generated when you:
- Add a new employee
- Assign a task
- Update efficiency scores

**File Location**: `data/employees_report.csv`

**Open with**:
- Microsoft Excel
- Google Sheets
- Any text editor

---

## 🎓 Example Workflow

### 1. Add First Employee
```
Name: Alice Johnson
Department: IT
Year: 2024
→ Auto ID: 12428572
```

### 2. Add Second Employee
```
Name: Bob Smith
Department: HR
Year: 2023
→ Auto ID: 22237241
```

### 3. View All
Click "📋 View All Employees" to see both

### 4. Filter by Department
- Filter by "IT" → Shows Alice
- Filter by "HR" → Shows Bob

### 5. Check Reports
- Open `data/employees_report.csv` in Excel

---

## 🔐 Security Notes

- Default credentials are for demo purposes
- Change password in production (`src/Admin.cpp` line ~645)
- Sensitive data stored in unencrypted .dat files
- Implement database encryption for production

---

## 📞 Support

For help:
1. Read [GUI_GUIDE.md](GUI_GUIDE.md) for detailed documentation
2. Check [README.md](README.md) for full feature list
3. Review source code in `src/` folder

---

## 🎉 You're All Set!

Run `python gui_app.py` and start managing your employees!

**Keyboard Shortcuts** (in GUI):
- `Enter` - Confirm dialog
- `Esc` - Close dialog
- `Tab` - Move between fields

Happy tracking! 📈
