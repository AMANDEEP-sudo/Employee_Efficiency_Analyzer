#include "Citizen.h"
#include "Constants.h"
#include <iostream>
#include <sstream>
#include <cctype>
using namespace std;

Citizen::Citizen() : hashed_aadhaar(""), name(""), address(""), mobile("") {}

Citizen::Citizen(string hash, string n, string addr, string mob)
    : hashed_aadhaar(hash), name(n), address(addr), mobile(mob) {}

void Citizen::setHashedAadhaar(string hash) { hashed_aadhaar = hash; }
void Citizen::setName(string n) { name = n; }
void Citizen::setAddress(string addr) { address = addr; }
void Citizen::setMobile(string mob) { mobile = mob; }

string Citizen::getHashedAadhaar() const { return hashed_aadhaar; }
string Citizen::getName() const { return name; }
string Citizen::getAddress() const { return address; }
string Citizen::getMobile() const { return mobile; }
vector<int> Citizen::getFeedbackIds() const { return feedback_ids; }

string Citizen::hashAadhaar(string aadhaar) {
    // Simple hash function for demonstration
    // In production, use MD5 or SHA-256
    string hash = "";
    for (char c : aadhaar) {
        hash += (c + 1);
    }
    return hash;
}

bool Citizen::validateAadhaar(string aadhaar) {
    // Check length
    if (aadhaar.length() != AADHAAR_LENGTH) {
        return false;
    }
    
    // Check if all characters are digits
    for (char c : aadhaar) {
        if (!isdigit(c)) {
            return false;
        }
    }
    
    return true;
}

void Citizen::addFeedback(int feedback_id) {
    feedback_ids.push_back(feedback_id);
    cout << "Feedback " << feedback_id << " added to citizen " << name << endl;
}

int Citizen::getFeedbackCount() const {
    return feedback_ids.size();
}

void Citizen::displayInfo() const {
    cout << "\n========== CITIZEN DETAILS ==========" << endl;
    cout << "Hashed Aadhaar: " << hashed_aadhaar << endl;
    cout << "Name: " << name << endl;
    cout << "Address: " << address << endl;
    cout << "Mobile: " << mobile << endl;
    cout << "Feedbacks Submitted: " << feedback_ids.size() << endl;
    cout << "====================================\n" << endl;
}
