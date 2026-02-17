#include "OTPManager.h"
#include "Constants.h"
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <sstream>
using namespace std;

OTPManager::OTPManager() : otp_expiry_minutes(OTP_EXPIRY_MINUTES), max_attempts(MAX_OTP_ATTEMPTS) {}

string OTPManager::generateOTP(string hashed_aadhaar)
{
    // Generate random 6-digit OTP
    srand(time(0));
    int otp_num = 100000 + (rand() % 900000);
    string otp = to_string(otp_num);

    // Store OTP with current timestamp
    time_t now = time(0);
    otp_store[hashed_aadhaar] = make_pair(otp, now);
    attempt_counter[hashed_aadhaar] = 0;

    cout << "OTP Generated: " << otp << endl;
    cout << "OTP will expire in " << otp_expiry_minutes << " minutes." << endl;

    return otp;
}

bool OTPManager::verifyOTP(string hashed_aadhaar, string entered_otp)
{
    // Check if OTP exists for this citizen
    if (otp_store.find(hashed_aadhaar) == otp_store.end())
    {
        cout << "No OTP found for this Aadhaar ID!" << endl;
        return false;
    }

    // Check attempt count
    if (isMaxAttemptsExceeded(hashed_aadhaar))
    {
        cout << "Maximum OTP attempts exceeded! Please request a new OTP." << endl;
        return false;
    }

    // Get stored OTP and timestamp
    string stored_otp = otp_store[hashed_aadhaar].first;
    time_t otp_timestamp = otp_store[hashed_aadhaar].second;

    // Check expiry
    if (!checkExpiry(otp_timestamp))
    {
        cout << "OTP has expired!" << endl;
        otp_store.erase(hashed_aadhaar);
        return false;
    }

    // Verify OTP
    if (stored_otp == entered_otp)
    {
        cout << "OTP Verified Successfully!" << endl;
        otp_store.erase(hashed_aadhaar);
        attempt_counter.erase(hashed_aadhaar);
        return true;
    }
    else
    {
        attempt_counter[hashed_aadhaar]++;
        int remaining = max_attempts - attempt_counter[hashed_aadhaar];
        cout << "Invalid OTP! Attempts remaining: " << remaining << endl;
        return false;
    }
}

bool OTPManager::checkExpiry(time_t timestamp)
{
    time_t now = time(0);
    int elapsed_seconds = difftime(now, timestamp);
    int elapsed_minutes = elapsed_seconds / 60;

    return elapsed_minutes < otp_expiry_minutes;
}

bool OTPManager::isMaxAttemptsExceeded(string hash)
{
    if (attempt_counter.find(hash) == attempt_counter.end())
    {
        return false;
    }
    return attempt_counter[hash] >= max_attempts;
}

void OTPManager::clearExpiredOTPs()
{
    vector<string> expired_keys;
    time_t now = time(0);

    for (auto &entry : otp_store)
    {
        int elapsed_seconds = difftime(now, entry.second.second);
        int elapsed_minutes = elapsed_seconds / 60;

        if (elapsed_minutes >= otp_expiry_minutes)
        {
            expired_keys.push_back(entry.first);
        }
    }

    // Remove expired entries
    for (string key : expired_keys)
    {
        otp_store.erase(key);
        attempt_counter.erase(key);
    }

    cout << "Cleared " << expired_keys.size() << " expired OTP(s)." << endl;
}

void OTPManager::resetAttempts(string hash)
{
    attempt_counter[hash] = 0;
}

void OTPManager::displayOTP(string otp) const
{
    cout << "\n========== OTP NOTIFICATION ==========" << endl;
    cout << "Your OTP is: " << otp << endl;
    cout << "Valid for: " << otp_expiry_minutes << " minutes" << endl;
    cout << "Maximum attempts: " << max_attempts << endl;
    cout << "=====================================\n"
         << endl;
}
