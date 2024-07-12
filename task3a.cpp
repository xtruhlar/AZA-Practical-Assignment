#include <iostream>
#include <vector>
#include <climits>

using namespace std;

// Greedy approach
void greedyApproach(vector<vector<int>>& costs) {
    // Get the number of persons and initialize the total cost
    int n = costs.size();
    int totalCost = 0;

    // Initialize an array to store the assigned jobs
    vector<int> assignedJobs(n, -1);

    // Iterate through each person
    for (int P = 1; P < n; ++P) {
        // Find the job with minimum cost for the current person
        int minCost = INT_MAX;
        int minJob = -1;
        for (int J = 1; J < n; ++J) {
            if (costs[P][J] < minCost && assignedJobs[J] == -1) {
                minCost = costs[P][J];
                minJob = J;
            }
        }

        // Assign the person to the job with minimum cost
        assignedJobs[minJob] = P;
        totalCost += minCost;
    }

// Display the assignment and total cost in a linear format
    cout << "Job\tPerson\tCost\n";
    cout << "--------------------\n";
    for (int job = 1; job < n; ++job) {
        cout << "J" << job << "\tP" << assignedJobs[job] << "\t" << costs[assignedJobs[job]][job] << "\n";
    }
    cout << "--------------------\n";
// Calculate and display the total cost
    cout << "Total Cost: " << totalCost << "\n";
}

// Main function
//int main() {
//    // The table of jobs
//    vector<vector<int>> costs = {
//            {0, 0, 0, 0},
//            {0, 10, 5, 5},
//            {0, 2, 4, 10},
//            {0, 5, 1, 7}
//    };
//
//    // Greedy approach
//    greedyApproach(costs);
//
//    return 0;
//}
