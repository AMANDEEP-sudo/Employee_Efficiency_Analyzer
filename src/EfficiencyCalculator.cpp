#include "EfficiencyCalculator.h"
#include "Constants.h"
#include <iostream>
#include <iomanip>
using namespace std;

EfficiencyCalculator::EfficiencyCalculator() {}

double EfficiencyCalculator::calculateCompletionRate(int completed, int total)
{
    if (total == 0)
        return 0.0;
    return (double)completed / total;
}

double EfficiencyCalculator::calculateAverageRating(vector<int> &ratings)
{
    if (ratings.empty())
        return 0.0;

    int sum = 0;
    for (int rating : ratings)
    {
        sum += rating;
    }

    double average = (double)sum / ratings.size();
    // Normalize to 0-100 scale
    return (average / RATING_MAX) * 100;
}

double EfficiencyCalculator::calculateOnTimePercentage(int completed_ontime, int total)
{
    if (total == 0)
        return 0.0;
    return (double)completed_ontime / total;
}

double EfficiencyCalculator::applyDelayPenalty(double penalty_factor)
{
    return penalty_factor * DELAY_PENALTY_PER_TASK;
}

double EfficiencyCalculator::computeFinalScore(double comp_rate, double avg_rating, double ontime_pct)
{
    double score = (comp_rate * 100 * COMPLETION_RATE_WEIGHT) +
                   (avg_rating * AVERAGE_RATING_WEIGHT) +
                   (ontime_pct * 100 * ON_TIME_PERCENTAGE_WEIGHT);

    // Clamp score between min and max
    if (score < MIN_EFFICIENCY_SCORE)
        score = MIN_EFFICIENCY_SCORE;
    if (score > MAX_EFFICIENCY_SCORE)
        score = MAX_EFFICIENCY_SCORE;

    return score;
}

void EfficiencyCalculator::updateAllEmployeeScores(vector<Employee> &employees)
{
    cout << "\n========== UPDATING EFFICIENCY SCORES ==========" << endl;

    for (Employee &emp : employees)
    {
        double old_score = emp.getEfficiencyScore();
        double new_score = emp.calculateEfficiency();

        cout << "Employee: " << emp.getName()
             << " | Old Score: " << fixed << setprecision(2) << old_score
             << " | New Score: " << fixed << setprecision(2) << new_score << endl;
    }

    cout << "================================================\n"
         << endl;
}
