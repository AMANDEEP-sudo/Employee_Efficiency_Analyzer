# VS Code Quick Reference - Employee Efficiency Tracker

## 🎯 **Quick Start (30 seconds)**

```powershell
cd e:\AREA_51_CODES\Employee_efficiency_tool
code employee_efficiency.code-workspace
```

Then:
1. **Install Extensions** → Notifications appear → Click "Install All"
2. **Build** → Press `Ctrl + Shift + B` → Select `build_cpp`
3. **Run** → Press `Ctrl + Shift + D` → Select your app → Click Run

---

## 📁 **VS Code Files Created**

| File | Purpose |
|------|---------|
| `.vscode/settings.json` | Editor formatting, C++17 standard, Python linting |
| `.vscode/launch.json` | Run/Debug configurations (C++, Python) |
| `.vscode/tasks.json` | Build tasks, clean, run commands |
| `.vscode/c_cpp_properties.json` | C++ IntelliSense, include paths, compiler |
| `.vscode/extensions.json` | Recommended extensions list |
| `employee_efficiency.code-workspace` | **← Open this file in VS Code** |
| `.gitignore` | Exclude .exe, __pycache__, *.o from git |
| `VSCODE_SETUP.md` | Complete setup documentation |

---

## ⌨️ **Essential Keyboard Shortcuts**

```
Ctrl + Shift + B           Build C++ (g++ compile)
Ctrl + Shift + D           Open Debug/Run view
Ctrl + Shift + '           Open Run Task menu
Ctrl + '                   Toggle Terminal

Ctrl + P                   Quick open file
Ctrl + G                   Go to line number
Ctrl + Shift + F           Find in all files
Shift + Alt + F            Format selected code
Ctrl + /                   Toggle comment

F5                         Start debugging
F10                        Step over
F11                        Step into
Shift + F11                Step out
Ctrl + Shift + D           Stop debugging
```

---

## 🔨 **Available Build Tasks**

**Run any with: `Ctrl + Shift + '`**

| Task Name | Purpose |
|-----------|---------|
| `build_cpp` | Compile C++ with `-std=c++17` |
| `build_cpp_debug` | Compile with debug symbols and `-g -O0` |
| `clean` | Delete .exe and .o files |
| `run_gui` | Run Python GUI application |
| `run_console` | Run C++ console application |
| `make_all` | Run Makefile all target |
| `make_run` | Compile and run |

---

## ▶️ **Run Configurations**

**Access with: `Ctrl + Shift + D`**

1. **Run C++ (efficiency_tracker.exe)**
   - Compiles → Runs console app → Opens external terminal

2. **Run Python (GUI App)**
   - Runs Python GUI in VS Code terminal
   - Recommended for GUI testing

3. **Debug Python (GUI App)**
   - Same as above but stops on breakpoints
   - Use for debugging Python code

4. **Debug C++ (main.cpp)**
   - Requires MinGW GDB
   - Stops at breakpoints, use step controls

---

## 🐛 **How to Debug**

### **Debug C++ Code**

```
1. Open src/Admin.cpp (or any .cpp file)
2. Click line number where you want breakpoint
   → Red dot appears
3. Press Ctrl + Shift + D
4. Select "Debug C++ (main.cpp)"
5. Click green Run button
6. Program pauses at breakpoint
7. Use F10/F11 to step through code
8. Inspect variables in left panel
9. Press F5 to continue
```

### **Debug Python GUI**

```
1. Open gui_app.py
2. Click line number for breakpoint
3. Press Ctrl + Shift + D
4. Select "Debug Python (GUI App)"
5. Click green Run button
6. GUI launches, breakpoints stop execution
7. Hover over variables to see values
8. Debug console shows output
9. Press F5 to continue
```

---

## 📊 **Project Structure**

```
Employee_Efficiency_Tracker/
├── .vscode/                  ← VS Code Configuration
│   ├── settings.json
│   ├── launch.json
│   ├── tasks.json
│   ├── c_cpp_properties.json
│   └── extensions.json
│
├── src/                      ← C++ Source (22 files)
│   ├── Admin.h/cpp
│   ├── Employee.h/cpp
│   ├── Task.h/cpp
│   ├── Database.h/cpp
│   ├── Utils.h/cpp
│   └── ... (6 more pairs)
│
├── data/                     ← Runtime Data
│   ├── employees.dat
│   ├── tasks.dat
│   ├── audit_log.dat
│   └── employees_report.csv (auto-generated)
│
├── gui_app.py                ← Python GUI
├── efficiency_tracker.exe    ← Compiled Binary
├── Makefile                  ← Build configuration
├── employee_efficiency.code-workspace
├── .gitignore
├── VSCODE_SETUP.md
└── ... (other docs)
```

---

## 🔌 **Recommended Extensions**

**Auto-installed from extensions.json:**

- ✅ **C/C++ Extension Pack** - C++ support
- ✅ **Python** - Python support with debugger
- ✅ **Pylance** - Python type checking
- ✅ **GitLens** - Enhanced git info
- ✅ **GitHub Copilot** - AI code assistant
- ✅ **Makefile Tools** - Makefile support

**Install manually after opening:**
1. Bottom right notification appears
2. Click "Show Recommendations"
3. Click "Install All"

---

## 💡 **Common Workflows**

### **Add New Feature to C++**

```
1. Create new .h and .cpp file in src/
2. Press Ctrl + Shift + B to build
3. Check errors in Problems panel (Ctrl + Shift + M)
4. Fix errors, rebuild
5. Press Ctrl + Shift + D → Run C++ → Test
```

### **Add New Feature to Python GUI**

```
1. Edit gui_app.py
2. Press Ctrl + ' to open terminal
3. Type: python gui_app.py
4. Test GUI
5. Use Ctrl + Shift + D to debug if needed
```

### **Build and Run**

```
Ctrl + Shift + B    → Select build_cpp
Ctrl + Shift + '    → Select run_console
                    (or run_gui for Python)
```

### **Find and Replace**

```
Ctrl + H            → Opens Find & Replace
Type search term    → Sees all matches
Type replacement    → Click Replace/Replace All
```

---

## 🚨 **Troubleshooting**

| Problem | Solution |
|---------|----------|
| IntelliSense broken | Ctrl+Shift+P → "C/C++: Reset IntelliSense" |
| Extensions not showing | Click Extensions icon (left sidebar) |
| Build fails | Check MinGW installed: `g++ --version` |
| Breakpoints not working | Rebuild with debug config: `build_cpp_debug` |
| Terminal won't open | Ctrl + Shift + P → "Toggle Integrated Terminal" |
| Python import errors | Ensure PYTHONPATH set in launch.json |

---

## 📝 **Before Pushing to GitHub**

```powershell
# In VS Code Terminal (Ctrl + ')
git init
git add .
git commit -m "Initial: Employee Efficiency Tracker with GUI"
git branch -M main
git remote add origin https://github.com/USERNAME/Employee_Efficiency_Analyzer.git
git push -u origin main
```

Or use:
- **Ctrl + Shift + G** → Source Control panel
- **Source Control** → **Initialize Repository**

---

## ✨ **Tips**

- **Split Editor**: Click file tab → Click split icon (top right)
- **Command Palette**: `Ctrl + Shift + P` → Search anything
- **File Explorer**: `Ctrl + B` → Toggle sidebar
- **Outline**: Click file icon in sidebar → See functions/classes
- **Problems**: `Ctrl + Shift + M` → See all errors
- **Output**: See build/debug output

---

## 🎓 **Next Steps**

1. ✅ Open `employee_efficiency.code-workspace`
2. ✅ Install extensions
3. ✅ Build project (`Ctrl + Shift + B`)
4. ✅ Run GUI (`Ctrl + Shift + D` → Run Python)
5. ✅ Add a breakpoint, debug it
6. ✅ Commit to GitHub

---

**Questions? Read [VSCODE_SETUP.md](VSCODE_SETUP.md) for detailed documentation!**

Happy coding! 🚀
