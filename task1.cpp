#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Job structure
struct Job {
    int id;
    int deadline;
    int profit;
};

// isFeasible function for sorting jobs by deadline and profit
bool isFeasible(const Job &a, const Job &b) {
    if (a.deadline != b.deadline) {
        return a.deadline < b.deadline;
    } else {
        return a.profit > b.profit;
    }
}

// Schedule function
void schedule(int n, vector<Job>& jobs, vector<int>& optimalSequence) {
    int totalProfit = 0;
    // the K array is used to keep track of the jobs that have been scheduled
    vector<int> K(n, -1);

    // Sort jobs by deadline and profit (std:sort uses quicksort)
    sort(jobs.begin(), jobs.end(), isFeasible);

    // For each job, find the latest available slot and schedule the job
    for (int i = 1; i <= n; i++) {
        // Find the latest available slot
        int currentDeadline = jobs[i - 1].deadline;
        for (int j = min(n, currentDeadline) - 1; j >= 0; j--) {
            // if K[j] == -1, then the slot is available
            if (K[j] == -1) {
                // Calculate total profit and schedule the job
                totalProfit += jobs[i - 1].profit;
                K[j] = jobs[i - 1].id;
                optimalSequence.push_back(jobs[i - 1].id);
                break;
            }
        }
    }

    // Print the results
    cout << endl;
    cout << "Optimal sequence of jobs: " << endl;
    for (int jobId : optimalSequence) {
        cout << jobId << " ";
    }
    cout << endl << endl;
    cout << "Maximum Profit: " << endl;
    cout << totalProfit << endl;
}

// Main function
//int main() {
//    int n = 7;
//    // Table 1 from assignment
//    vector<Job> jobs = {
//            {1, 2, 40},
//            {2, 4, 15},
//            {3, 3, 60},
//            {4, 2, 20},
//            {5, 3, 10},
//            {6, 1, 45},
//            {7, 1, 55}
//    };
//
//    vector<int> optimalSequence;
//    schedule(n, jobs, optimalSequence);
//
//    return 0;
//}