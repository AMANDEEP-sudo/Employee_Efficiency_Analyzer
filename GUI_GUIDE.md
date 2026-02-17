# GUI Application Setup Guide

## Overview

The Employee Efficiency Tracker now includes a modern GUI (Graphical User Interface) built with Python and tkinter, providing an easy-to-use dashboard for managing employees and tracking efficiency.

## Requirements

- Python 3.7 or higher
- tkinter (comes built-in with Python on Windows)

## How to Run the GUI

### Windows

```powershell
cd e:\AREA_51_CODES\Employee_efficiency_tool
python gui_app.py
```

### Linux/Mac

```bash
cd /path/to/Employee_efficiency_tool
python3 gui_app.py
```

## Features

### 1. Login Screen

- Default credentials: Username: `admin`, Password: `admin123`
- Secure login interface

### 2. Admin Dashboard

The main menu provides access to:

#### Employee Management

- **Add Employee**: Create new employee with smart ID generation
- **View All Employees**: See all employees in a formatted table
- **Filter Employees**: Search by:
  - Department
  - Joining Year
  - Efficiency Score (threshold-based)
- **View Employee Details**: Look up specific employee by ID

#### Tasks & Reports

- **Assign Task**: Create new tasks for employees
- **Mark Task Complete**: Update task status
- **Efficiency Report**: View performance analysis
- **Department Ranking**: Compare department efficiency

### 3. Data Display

- Professional table view with all employee information
- Sortable columns
- Employee ID, Name, Department, Year, Tasks, Completed, Efficiency, Feedback

## Loop Error Fixes Applied

### Fixed Issues:

1. **Filter Input Buffer**: Added `cin.ignore()` after each numeric input
2. **Filter Exit Handling**: Added proper return statements
3. **Filter Display Logic**: Fixed conditional logic for showing results
4. **Invalid Choice Handling**: Added return for invalid choices

### Code Improvements:

- Proper stream flushing after user input
- Clear return paths for all branches
- Explicit `show_results` flag to control output
- Better exception handling

## Data Format

### Employee Data Storage

**Location**: `data/employees.dat`

**Format**: `ID|Name|Department|Year|Tasks|Completed|Score|Feedback`

**Example**:

```
12428932|John Doe|IT|2024|5|3|85.50|2
12324567|Jane Smith|HR|2023|4|4|92.30|1
```

## Smart ID Generation

### ID Structure: [DeptCode][Year][Random]

- **Position 1**: Department code (0-9)
- **Position 2-3**: Last 2 digits of joining year
- **Position 4-8**: 5-digit random number

### Example: 12428932

- `1` = IT Department
- `24` = Year 2024
- `28932` = Unique random identifier

## Department Codes

| Code | Department |
| ---- | ---------- |
| 1    | IT         |
| 2    | HR         |
| 3    | Finance    |
| 4    | Operations |
| 5    | CSE        |
| 6    | Civil      |
| 7    | Mechanical |
| 8    | Electrical |
| 9    | Sales      |

## Console Mode

For advanced operations like OTP management and feedback portal, use the console interface:

```powershell
.\efficiency_tracker.exe
```

## File Structure

```
Employee_efficiency_tool/
├── gui_app.py              # Python GUI application
├── efficiency_tracker.exe  # C++ backend
├── src/                    # C++ source files
├── data/
│   ├── employees.dat      # Employee data
│   ├── tasks.dat          # Task data
│   ├── employees_report.csv # Auto-generated CSV
│   └── audit_log.dat      # System logs
└── Makefile               # Build configuration
```

## Troubleshooting

### GUI Won't Open

1. Ensure Python is installed: `python --version`
2. Check if tkinter is available: `python -m tkinter`
3. Run from the project root directory

### Data Not Showing

1. Ensure `data/employees.dat` exists
2. Delete old data and start fresh: `del data\employees.dat`
3. Add new employees through GUI first

### Compilation Errors

Recompile the C++ backend:

```powershell
g++ -std=c++17 -o efficiency_tracker.exe src/*.cpp
```

## Future Enhancements

- Export data to Excel/PDF
- Real-time notifications
- Multi-user support
- Email integration
- Advanced reporting dashboard
- Dark mode theme option
- Database backend support (MySQL/PostgreSQL)

## Support

For issues or feature requests, ensure:

1. Python version is 3.7+
2. All data files exist in `data/` directory
3. Compilation is successful before running GUI
