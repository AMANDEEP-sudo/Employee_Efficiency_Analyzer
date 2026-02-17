#ifndef OTPMANAGER_H
#define OTPMANAGER_H

#include <map>
#include <vector>
#include <string>
#include <ctime>
using namespace std;

class OTPManager {
private:
    map<string, pair<string, time_t>> otp_store;  // {hash_aadhaar, {OTP, timestamp}}
    int otp_expiry_minutes;
    int max_attempts;
    map<string, int> attempt_counter;

public:
    OTPManager();
    
    // Methods
    string generateOTP(string hashed_aadhaar);
    bool verifyOTP(string hashed_aadhaar, string entered_otp);
    bool checkExpiry(time_t timestamp);
    bool isMaxAttemptsExceeded(string hash);
    void clearExpiredOTPs();
    void resetAttempts(string hash);
    void displayOTP(string otp) const;
};

#endif
