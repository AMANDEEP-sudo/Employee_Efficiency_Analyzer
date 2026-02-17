#include "Utils.h"
#include <iostream>
#include <sstream>
#include <cctype>
#include <ctime>
#include <algorithm>
#include <cstdlib>
using namespace std;

bool Utils::isValidInteger(const string &str)
{
    try
    {
        stoi(str);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool Utils::isValidDouble(const string &str)
{
    try
    {
        stod(str);
        return true;
    }
    catch (...)
    {
        return false;
    }
}

bool Utils::isValidDate(const string &date)
{
    // Simple format validation: YYYY-MM-DD
    if (date.length() != 10)
        return false;
    if (date[4] != '-' || date[7] != '-')
        return false;

    // Check if parts are digits
    for (int i = 0; i < date.length(); i++)
    {
        if (i != 4 && i != 7)
        {
            if (!isdigit(date[i]))
                return false;
        }
    }

    return true;
}

string Utils::toLower(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::tolower);
    return str;
}

string Utils::toUpper(string str)
{
    transform(str.begin(), str.end(), str.begin(), ::toupper);
    return str;
}

string Utils::trim(string str)
{
    // Trim leading spaces
    size_t first = str.find_first_not_of(" ");
    if (first == string::npos)
        return "";

    // Trim trailing spaces
    size_t last = str.find_last_not_of(" ");
    return str.substr(first, (last - first + 1));
}

void Utils::clearScreen()
{
    system("cls"); // Works on Windows
    // For Linux/Mac, use: system("clear");
}

void Utils::displayHeader(const string &title)
{
    cout << "\n========== " << title << " ==========" << endl;
}

void Utils::displaySeparator()
{
    cout << "===========================================" << endl;
}

string Utils::getCurrentDate()
{
    time_t now = time(0);
    char date_str[11]; // YYYY-MM-DD
    struct tm timeinfo = *localtime(&now);
    strftime(date_str, sizeof(date_str), "%Y-%m-%d", &timeinfo);
    return date_str;
}

string Utils::getCurrentTime()
{
    time_t now = time(0);
    char time_str[20]; // HH:MM:SS
    struct tm timeinfo = *localtime(&now);
    strftime(time_str, sizeof(time_str), "%H:%M:%S", &timeinfo);
    return time_str;
}

string Utils::simpleHash(const string &input)
{
    // Simple hash function for demonstration
    // In production, use MD5 or SHA-256
    string hash = "";
    for (char c : input)
    {
        hash += (c + 1);
    }
    return hash;
}

// Smart ID Generation Functions
int Utils::getDepartmentCode(const string &department)
{
    // Map departments to single digit codes
    string dept_lower = toLower(department);

    if (dept_lower == "it")
        return 1;
    if (dept_lower == "hr")
        return 2;
    if (dept_lower == "finance")
        return 3;
    if (dept_lower == "operations")
        return 4;
    if (dept_lower == "cse")
        return 5;
    if (dept_lower == "civil")
        return 6;
    if (dept_lower == "mechanical")
        return 7;
    if (dept_lower == "electrical")
        return 8;
    if (dept_lower == "sales")
        return 9;

    return 0; // Unknown department
}

int Utils::generateSmartEmployeeId(const string &department, int joining_year)
{
    // Format: [DeptCode][LastTwoDigitsOfYear][5DigitRandom]
    // Example: 1|24|28932 = 12428932
    // 1 = IT department
    // 24 = Joined in 2024
    // 28932 = Random 5-digit number

    int dept_code = getDepartmentCode(department);
    if (dept_code == 0)
        dept_code = 9; // Default code for unknown departments

    int year_code = joining_year % 100; // Get last 2 digits of year

    // Generate random 5-digit number (10000-99999)
    srand(time(0) + rand());
    int random_part = 10000 + (rand() % 90000);

    // Combine: [1 digit] [2 digits] [5 digits] = 8 digits
    int smart_id = (dept_code * 10000000) + (year_code * 100000) + random_part;

    return smart_id;
}

string Utils::getDepartmentFromCode(int code)
{
    switch (code)
    {
    case 1:
        return "IT";
    case 2:
        return "HR";
    case 3:
        return "Finance";
    case 4:
        return "Operations";
    case 5:
        return "CSE";
    case 6:
        return "Civil";
    case 7:
        return "Mechanical";
    case 8:
        return "Electrical";
    case 9:
        return "Sales";
    default:
        return "Unknown";
    }
}
