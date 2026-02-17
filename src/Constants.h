#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>
using namespace std;

// OTP Configuration
constexpr int OTP_LENGTH = 6;
constexpr int OTP_EXPIRY_MINUTES = 5;
constexpr int MAX_OTP_ATTEMPTS = 3;

// Aadhaar Configuration
constexpr int AADHAAR_LENGTH = 12;

// Rating Configuration
constexpr int RATING_MIN = 1;
constexpr int RATING_MAX = 5;

// Efficiency Score Configuration
constexpr double MIN_EFFICIENCY_SCORE = 0.0;
constexpr double MAX_EFFICIENCY_SCORE = 100.0;
constexpr double COMPLETION_RATE_WEIGHT = 0.50;
constexpr double AVERAGE_RATING_WEIGHT = 0.30;
constexpr double ON_TIME_PERCENTAGE_WEIGHT = 0.20;
constexpr double DELAY_PENALTY_PER_TASK = 2.0;

// File Names (using #define instead)
#define EMPLOYEES_FILE "data/employees.dat"
#define TASKS_FILE "data/tasks.dat"
#define CITIZENS_FILE "data/citizens.dat"
#define FEEDBACK_FILE "data/feedback.dat"
#define AUDIT_LOG_FILE "data/audit_log.dat"

#endif
