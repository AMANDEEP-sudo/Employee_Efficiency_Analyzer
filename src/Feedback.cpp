#include "Feedback.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>
using namespace std;

Feedback::Feedback() : feedback_id(0), employee_id(0), 
                       hashed_citizen_aadhaar(""), rating(0), 
                       comment(""), timestamp(""), is_submitted(false) {}

Feedback::Feedback(int fid, int eid, string hash)
    : feedback_id(fid), employee_id(eid), hashed_citizen_aadhaar(hash), 
      rating(0), comment(""), timestamp(""), is_submitted(false) {}

void Feedback::setFeedbackId(int id) { feedback_id = id; }
void Feedback::setEmployeeId(int id) { employee_id = id; }
void Feedback::setHashedCitizenAadhaar(string hash) { hashed_citizen_aadhaar = hash; }
void Feedback::setRating(int r) { rating = r; }
void Feedback::setComment(string c) { comment = c; }
void Feedback::setTimestamp(string ts) { timestamp = ts; }
void Feedback::setIsSubmitted(bool status) { is_submitted = status; }

int Feedback::getFeedbackId() const { return feedback_id; }
int Feedback::getEmployeeId() const { return employee_id; }
string Feedback::getHashedCitizenAadhaar() const { return hashed_citizen_aadhaar; }
int Feedback::getRating() const { return rating; }
string Feedback::getComment() const { return comment; }
string Feedback::getTimestamp() const { return timestamp; }
bool Feedback::getIsSubmitted() const { return is_submitted; }

void Feedback::setCurrentTimestamp() {
    time_t now = time(0);
    char timestamp_str[100];
    struct tm timeinfo = *localtime(&now);
    strftime(timestamp_str, sizeof(timestamp_str), "%Y-%m-%d %H:%M:%S", &timeinfo);
    timestamp = timestamp_str;
}

void Feedback::submitFeedback() {
    if (rating < RATING_MIN || rating > RATING_MAX) {
        cout << "Invalid rating! Please enter rating between " 
             << RATING_MIN << " and " << RATING_MAX << endl;
        return;
    }
    
    if (comment.empty()) {
        cout << "Comment cannot be empty!" << endl;
        return;
    }
    
    setCurrentTimestamp();
    is_submitted = true;
    cout << "Feedback submitted successfully!" << endl;
}

void Feedback::displayFeedback() const {
    cout << "\n========== FEEDBACK DETAILS ==========" << endl;
    cout << "Feedback ID: " << feedback_id << endl;
    cout << "Employee ID: " << employee_id << endl;
    cout << "Citizen (Hashed Aadhaar): " << hashed_citizen_aadhaar << endl;
    cout << "Rating: " << rating << "/5" << endl;
    cout << "Comment: " << comment << endl;
    cout << "Submitted: " << (is_submitted ? "YES" : "NO") << endl;
    cout << "Timestamp: " << timestamp << endl;
    cout << "=====================================\n" << endl;
}
