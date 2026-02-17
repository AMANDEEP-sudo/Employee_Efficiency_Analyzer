# Government Employee Efficiency Tracker with Aadhaar-Based OTP Verified Feedback System

A comprehensive C++ console-based application for monitoring employee performance with simulated Aadhaar-based OTP authentication and public feedback collection.

## Features

### Core Functionality

- **Employee Management**: Add, view, and manage employee records
- **Task Management**: Assign tasks with deadlines and track completion
- **Efficiency Calculation**: Automatic computation of efficiency scores based on:
  - Task completion rate (50%)
  - Average feedback rating (30%)
  - On-time task completion percentage (20%)
  - Delay penalties

### Security & Verification

- **Simulated Aadhaar Authentication**: 12-digit Aadhaar format validation
- **OTP Generation & Verification**: 6-digit random OTP with:
  - 5-minute expiry
  - Maximum 3 attempt limit
  - Timestamp-based verification
- **Duplicate Feedback Prevention**: One feedback per citizen per employee

### Reporting & Analytics

- **Efficiency Reports**: Individual and aggregate employee performance
- **Department-wise Ranking**: Compare employees within departments
- **Monthly Performance Summary**: Overall system statistics
- **Audit Logging**: Track all system actions with timestamps

## Project Structure

```
Employee_efficiency_tool/
├── src/
│   ├── main.cpp
│   ├── Employee.h / Employee.cpp
│   ├── Task.h / Task.cpp
│   ├── Citizen.h / Citizen.cpp
│   ├── OTPManager.h / OTPManager.cpp
│   ├── Feedback.h / Feedback.cpp
│   ├── Department.h / Department.cpp
│   ├── EfficiencyCalculator.h / EfficiencyCalculator.cpp
│   ├── Database.h / Database.cpp
│   ├── Admin.h / Admin.cpp
│   ├── Utils.h / Utils.cpp
│   └── Constants.h
├── data/ (auto-created)
│   ├── employees.dat
│   ├── tasks.dat
│   ├── citizens.dat
│   ├── feedback.dat
│   └── audit_log.dat
├── Makefile
└── README.md
```

## Compilation

### Using G++ (Direct Compilation)

**Windows:**

```bash
cd Employee_efficiency_tool
g++ -std=c++17 -o efficiency_tracker.exe src/*.cpp
efficiency_tracker.exe
```

**Linux/Mac:**

```bash
cd Employee_efficiency_tool
g++ -std=c++17 -o efficiency_tracker src/*.cpp
./efficiency_tracker
```

### Using Makefile

```bash
make          # Compile the project
make run      # Compile and run
make clean    # Remove build artifacts
make help     # Show available targets
```

## Usage

### Main Menu

```
1. Admin Login
2. Citizen Feedback Portal
3. View Public Reports
4. Exit
```

### Admin Login

- **Default Username:** admin
- **Default Password:** admin123

### Admin Features

- Add employees and departments
- Assign tasks with deadlines
- Track task completion
- View efficiency reports
- Generate department rankings
- Monitor citizen feedback
- View audit logs

### Citizen Feedback Process

1. Enter 12-digit Aadhaar ID
2. Receive OTP (displayed in console for demo)
3. Verify OTP (5-minute expiry)
4. Submit feedback with rating (1-5)
5. Efficiency scores auto-update

## Efficiency Score Formula

```
Score = (completion_rate × 50) + (avg_rating × 30)
        + (on_time_pct × 20) - delay_penalty

Range: 0-100
```

## Data Files

All data persists in pipe-delimited `.dat` files:

**employees.dat format:**

```
id|name|department|total_tasks|completed_tasks|efficiency_score|feedback_count
```

**feedback.dat format:**

```
id|employee_id|hashed_aadhaar|rating|comment|timestamp|submitted
```

## Requirements

- C++17 compiler (GCC, Clang, Visual Studio)
- Standard C++ Library (STL)
- No external dependencies

## Class Overview

| Class                  | Purpose                                  |
| ---------------------- | ---------------------------------------- |
| `Employee`             | Employee records and efficiency tracking |
| `Task`                 | Task management and deadline tracking    |
| `Citizen`              | Citizen registry and Aadhaar validation  |
| `OTPManager`           | OTP generation and verification          |
| `Feedback`             | Feedback submission and storage          |
| `Department`           | Department management and reporting      |
| `Database`             | File I/O and data persistence            |
| `Admin`                | Main control panel and menu system       |
| `EfficiencyCalculator` | Score computation                        |
| `Utils`                | Utility functions                        |

## Testing Workflow

1. **Run the application**

   ```bash
   ./efficiency_tracker
   ```

2. **Admin Login (option 1)**
   - Username: `admin`
   - Password: `admin123`

3. **Add employees and departments**
   - Menu option 1: Add Employee
   - Menu option 2: Add Department

4. **Assign tasks**
   - Menu option 3: Assign Task (requires employee ID)

5. **Complete tasks**
   - Menu option 4: Mark Task Complete

6. **Test citizen feedback (option 2)**
   - Enter Aadhaar: `123456789012`
   - OTP will be displayed
   - Enter displayed OTP
   - Submit feedback with rating 1-5

7. **View reports (option 3)**
   - Check efficiency reports
   - View department rankings

## Known Limitations

- Console UI (no GUI)
- File-based storage (no database)
- Simulated Aadhaar (for demonstration)
- Simple hashing (not cryptographically secure)
- Single-threaded execution

## Future Enhancements

- Qt/wxWidgets GUI implementation
- MySQL/PostgreSQL backend
- Real SMS API for OTP delivery
- Web interface (Node.js/Flask)
- Mobile application
- Real Aadhaar API integration
- Sentiment analysis for feedback
- Data visualization dashboard

## Configuration

Edit `src/Constants.h` to modify:

- OTP expiry time (default: 5 minutes)
- Maximum OTP attempts (default: 3)
- Efficiency score weights
- Data file locations

## Support

For detailed implementation information, see:

- `C++_IMPLEMENTATION_GUIDE.txt` - Comprehensive design documentation
- `employee_efficiency.txt` - Original SRS document
- Source files (.h/.cpp) - Inline comments

## License

Academic project for educational purposes.

---

**Version:** 1.0 | **Date:** February 2024
