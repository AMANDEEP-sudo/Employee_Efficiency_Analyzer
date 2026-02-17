#ifndef CITIZEN_H
#define CITIZEN_H

#include <string>
#include <vector>
using namespace std;

class Citizen
{
private:
    string hashed_aadhaar;
    string name;
    string address;
    string mobile;
    vector<int> feedback_ids;

public:
    Citizen();
    Citizen(string hash, string n, string addr, string mob);

    // Setters
    void setHashedAadhaar(string hash);
    void setName(string n);
    void setAddress(string addr);
    void setMobile(string mob);

    // Getters
    string getHashedAadhaar() const;
    string getName() const;
    string getAddress() const;
    string getMobile() const;
    vector<int> getFeedbackIds() const;

    // Methods
    string hashAadhaar(string aadhaar);
    bool validateAadhaar(string aadhaar);
    void addFeedback(int feedback_id);
    int getFeedbackCount() const;
    void displayInfo() const;
};

#endif
