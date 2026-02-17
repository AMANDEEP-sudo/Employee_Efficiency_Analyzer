#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <vector>
using namespace std;

class Utils
{
public:
    // Input validation
    static bool isValidInteger(const string &str);
    static bool isValidDouble(const string &str);
    static bool isValidDate(const string &date);

    // String utilities
    static string toLower(string str);
    static string toUpper(string str);
    static string trim(string str);

    // Display utilities
    static void clearScreen();
    static void displayHeader(const string &title);
    static void displaySeparator();

    // Date utilities
    static string getCurrentDate();
    static string getCurrentTime();

    // Hash utilities
    static string simpleHash(const string &input);

    // Smart ID Generation
    static int getDepartmentCode(const string &department);
    static int generateSmartEmployeeId(const string &department, int joining_year);
    static string getDepartmentFromCode(int code);
};

#endif
