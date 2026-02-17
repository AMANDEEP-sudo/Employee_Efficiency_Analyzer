#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <string>
#include <ctime>
using namespace std;

class Feedback {
private:
    int feedback_id;
    int employee_id;
    string hashed_citizen_aadhaar;
    int rating;
    string comment;
    string timestamp;
    bool is_submitted;

public:
    Feedback();
    Feedback(int fid, int eid, string hash);
    
    // Setters
    void setFeedbackId(int id);
    void setEmployeeId(int id);
    void setHashedCitizenAadhaar(string hash);
    void setRating(int r);
    void setComment(string c);
    void setTimestamp(string ts);
    void setIsSubmitted(bool status);
    
    // Getters
    int getFeedbackId() const;
    int getEmployeeId() const;
    string getHashedCitizenAadhaar() const;
    int getRating() const;
    string getComment() const;
    string getTimestamp() const;
    bool getIsSubmitted() const;
    
    // Methods
    void submitFeedback();
    void displayFeedback() const;
    void setCurrentTimestamp();
};

#endif
