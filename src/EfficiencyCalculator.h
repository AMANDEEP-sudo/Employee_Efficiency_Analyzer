#ifndef EFFICIENCYCALCULATOR_H
#define EFFICIENCYCALCULATOR_H

#include "Employee.h"
#include <vector>
using namespace std;

class EfficiencyCalculator
{
public:
    EfficiencyCalculator();

    // Calculation methods
    double calculateCompletionRate(int completed, int total);
    double calculateAverageRating(vector<int> &ratings);
    double calculateOnTimePercentage(int completed_ontime, int total);
    double applyDelayPenalty(double penalty_factor);
    double computeFinalScore(double comp_rate, double avg_rating, double ontime_pct);

    // Main calculation method for employees
    void updateAllEmployeeScores(vector<Employee> &employees);
};

#endif
