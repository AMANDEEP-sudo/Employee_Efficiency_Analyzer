# VS Code Integration Guide - Employee Efficiency Tracker

## 📋 Overview

This guide explains how to set up and use VS Code with the Employee Efficiency Tracker project.

---

## 🚀 Quick Setup (3 Steps)

### Step 1: Open Project Folder
```powershell
cd e:\AREA_51_CODES\Employee_efficiency_tool
code .
```

### Step 2: Install Recommended Extensions
When VS Code opens, you'll see a notification:
- Click **"Show Recommendations"**
- Click **"Install All"** to install recommended extensions

### Step 3: Open Workspace File
- **File** → **Open Workspace from File**
- Select `employee_efficiency.code-workspace`

---

## 📁 VS Code Configuration Files

### **1. `.vscode/settings.json`**
- Editor formatting and style
- C++ and Python configurations
- Terminal defaults
- File exclusions

### **2. `.vscode/launch.json`**
- Debug configurations
- Run C++ application
- Run Python GUI
- Debug modes

### **3. `.vscode/tasks.json`**
- Build tasks (g++ compilation)
- Run tasks
- Clean tasks
- Make commands

### **4. `.vscode/c_cpp_properties.json`**
- C++ intellisense
- Include paths
- Compiler settings
- MinGW configuration

### **5. `.vscode/extensions.json`**
- Recommended extensions list
- Auto-suggests extensions to install

### **6. `employee_efficiency.code-workspace`**
- Workspace configuration
- Folder structure
- Settings overrides

---

## 🔧 How to Use

### **Building the Project**

**Option 1: Using Build Task**
1. Press `Ctrl + Shift + B` (Run Build Task)
2. Select `build_cpp`

**Option 2: Using Terminal**
```powershell
g++ -std=c++17 -o efficiency_tracker.exe src/*.cpp
```

**Option 3: Using Make**
```powershell
make
```

---

### **Running the Application**

**Option 1: GUI Mode**
1. Press `Ctrl + Shift + D` (Debug View)
2. Select **"Run Python (GUI App)"**
3. Click **"Run"** (green play button)

Or use terminal:
```powershell
python gui_app.py
```

**Option 2: Console Mode**
1. Press `Ctrl + Shift + D` (Debug View)
2. Select **"Run C++ (efficiency_tracker.exe)"**
3. Click **"Run"** (green play button)

Or use terminal:
```powershell
.\efficiency_tracker.exe
```

---

### **Debugging**

**Debug C++ Code**
1. Set breakpoint in `src/Admin.cpp` (click line number)
2. Press `Ctrl + Shift + D`
3. Select **"Debug C++ (main.cpp)"**
4. Click **Run**
5. Use debug controls:
   - **F10**: Step over
   - **F11**: Step into
   - **Shift + F11**: Step out
   - **F5**: Continue
   - **Ctrl + Shift + D**: Stop

**Debug Python GUI**
1. Set breakpoint in `gui_app.py`
2. Press `Ctrl + Shift + D`
3. Select **"Debug Python (GUI App)"**
4. Click **Run**
5. Use same debug controls

---

## 🎯 Command Palette Shortcuts

Press `Ctrl + Shift + P` to open Command Palette:

| Command | Shortcut |
|---------|----------|
| Build C++ | `Ctrl + Shift + B` |
| Debug | `Ctrl + Shift + D` |
| Run Task | `Ctrl + Shift + '` |
| Open Terminal | `Ctrl + '` |
| Format Document | `Shift + Alt + F` |
| Find in Files | `Ctrl + Shift + F` |
| Git: Open Repository | `Ctrl + K Ctrl + O` |

---

## 📁 Project Structure in VS Code

```
Employee_Efficiency_Tracker/
├── .vscode/                          ← VS Code Configuration
│   ├── settings.json                 (Editor settings)
│   ├── launch.json                   (Debug configurations)
│   ├── tasks.json                    (Build tasks)
│   ├── c_cpp_properties.json         (C++ intellisense)
│   └── extensions.json               (Recommended extensions)
├── src/                              ← Source Code
│   ├── Admin.h/cpp
│   ├── Employee.h/cpp
│   ├── Task.h/cpp
│   └── ... (11 more files)
├── data/                             ← Data Files
│   ├── employees.dat
│   └── audit_log.dat
├── gui_app.py                        ← Python GUI
├── efficiency_tracker.exe            ← Compiled Binary
├── employee_efficiency.code-workspace  ← Workspace File
├── .gitignore                        ← Git Ignore Rules
└── Documentation files
```

---

## 🔌 Recommended Extensions

### **C++ Development**
- **C/C++ Extension Pack** (ms-vscode.cpptools-extension-pack)
- **C/C++** (ms-vscode.cpptools)
- **Makefile Tools** (ms-vscode.makefile-tools)

### **Python Development**
- **Python** (ms-python.python)
- **Pylance** (ms-python.vscode-pylance)
- **Debugpy** (ms-python.debugpy)

### **Git & Version Control**
- **GitLens** (eamodio.gitlens)
- **Git History** (donjayamanne.githistory)
- **Git Graph** (mhutchie.git-graph)

### **Productivity**
- **GitHub Copilot** (GitHub.copilot)
- **Codeium** (Codeium.codeium)
- **TODO Tree** (gruntfuggly.todo-tree)

### **Code Quality**
- **Ruff** (charliermarsh.ruff)
- **Clang Format** (xaver.clang-format)

---

## ⚙️ Configuration Details

### **C++ Compilation Settings**

```json
"command": "g++",
"args": [
    "-std=c++17",        // C++17 standard
    "-Wall",             // All warnings
    "-Wextra",           // Extra warnings
    "-o",                // Output
    "efficiency_tracker.exe",
    "src/*.cpp"          // All source files
]
```

### **Python Execution Settings**

```json
"console": "integratedTerminal",  // Use VS Code terminal
"justMyCode": true,               // Debug user code only
"env": {
    "PYTHONPATH": "${workspaceFolder}"
}
```

---

## 📊 Common Tasks

### **Display Available Tasks**
Press `Ctrl + Shift + '` and search for:
- `build_cpp`
- `run_gui`
- `run_console`
- `clean`

### **View Output**
- **Debug Console**: `Ctrl + Shift + Y`
- **Terminal**: `Ctrl + '`
- **Problems**: `Ctrl + Shift + M`

### **Source Control**
- **Source Control Panel**: `Ctrl + Shift + G`
- Shows git status, commits, branches

---

## 🐛 Troubleshooting

### **Issue: IntelliSense Not Working**

**Solution:**
1. Press `Ctrl + Shift + P`
2. Type "C/C++: Reset IntelliSense"
3. Close and reopen files

### **Issue: Can't Find Compiler**

**Solution:**
1. Check MinGW is installed: `g++ --version`
2. Update Path in `c_cpp_properties.json`
3. Restart VS Code

### **Issue: Python Debugger Not Stopping**

**Solution:**
1. Ensure Python extension is installed
2. Check breakpoint is set correctly
3. Use `F9` to toggle breakpoint

### **Issue: Build Task Not Found**

**Solution:**
1. Open terminal: `Ctrl + '`
2. Manually run: `g++ -std=c++17 -o efficiency_tracker.exe src/*.cpp`
3. Verify folder structure

---

## 📝 File Navigation

Use these shortcuts to navigate quickly:

| Action | Shortcut |
|--------|----------|
| Go to File | `Ctrl + P` |
| Go to Line | `Ctrl + G` |
| Open Symbol | `Ctrl + Shift + O` |
| Replace | `Ctrl + H` |
| Toggle Sidebar | `Ctrl + B` |
| Toggle Terminal | `Ctrl + '` |
| Split Editor | `Ctrl + \` |

---

## 🔄 Git Integration

### **Initialize and Commit**

```powershell
# In terminal (Ctrl + ')
git init
git add .
git commit -m "Initial commit: Employee Efficiency Tracker"
git branch -M main
git remote add origin https://github.com/YOUR-USERNAME/Employee_Efficiency_Analyzer.git
git push -u origin main
```

### **Using GitLens**
- Hover over code to see git blame
- Click author to see commit history
- Right-click repository to see options

---

## 💡 Tips & Tricks

1. **Multi-file Editing**
   - Hold `Ctrl` and click files to open multiple tabs
   - Click file tabs to switch

2. **Quick Search**
   - `Ctrl + F`: Find in current file
   - `Ctrl + Shift + F`: Find across all files

3. **Formatting**
   - `Shift + Alt + F`: Format select code
   - Auto-format on save (enabled)

4. **Comment Code**
   - `Ctrl + /`: Toggle comment for line(s)

5. **Minimap**
   - Right sidebar shows code overview
   - Hover to quickly navigate

---

## 📚 Resources

- [VS Code Documentation](https://code.visualstudio.com/docs)
- [C++ Development in VS Code](https://code.visualstudio.com/docs/languages/cpp)
- [Python Development in VS Code](https://code.visualstudio.com/docs/languages/python)
- [Debugging Guide](https://code.visualstudio.com/docs/editor/debugging)

---

## 🎓 Next Steps

1. ✅ Open workspace file
2. ✅ Install recommended extensions
3. ✅ Build project (`Ctrl + Shift + B`)
4. ✅ Run GUI (`Ctrl + Shift + D` → Run Python)
5. ✅ Set breakpoints and debug
6. ✅ Commit to GitHub

---

**You're ready to develop!** 🚀
