#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_ELEMENTS = 10; //Number of elements

typedef int ElementIndex;
typedef ElementIndex SetPointer;

// Job structure
struct Job {
    int id;
    int deadline;
    int profit;
};

// Set structure
struct SetNode {
    ElementIndex parent;
    int depth;
    int smallest;
};

// Universe of sets
typedef SetNode Universe[MAX_ELEMENTS + 1];

// Function to initialize a set for a given element
void initializeSet(ElementIndex element, Universe& sets) {
    sets[element].parent = element;
    sets[element].depth = 0;
    sets[element].smallest = element;
}

// Function to find the set of element
SetPointer findSet(ElementIndex element, Universe& sets) {
    if (element != sets[element].parent) {
        sets[element].parent = findSet(sets[element].parent, sets);
    }
    return sets[element].parent;
}

// Function to merge two sets based on their depths
void mergeSets(SetPointer set1, SetPointer set2, Universe& sets) {
    if (sets[set1].depth == sets[set2].depth) {
        sets[set1].depth = sets[set1].depth + 1;
        sets[set2].parent = set1;
        if (sets[set2].smallest < sets[set1].smallest)
            sets[set1].smallest = sets[set2].smallest;
    } else if (sets[set1].depth < sets[set2].depth) {
        sets[set1].parent = set2;
        if (sets[set1].smallest < sets[set2].smallest)
            sets[set2].smallest = sets[set1].smallest;
    } else {
        sets[set2].parent = set1;
        if (sets[set2].smallest < sets[set1].smallest)
            sets[set1].smallest = sets[set2].smallest;
    }
}

// Function to get the smallest element in a set
int smallestElement(SetPointer set, const Universe& sets) {
    return sets[set].smallest;
}

// Function to compare jobs based on profit in descending order
bool isFeasible2(const Job& job1, const Job& job2) {
    if (job1.deadline != job2.deadline) {
        return job1.deadline < job2.deadline;
    } else {
        return job1.profit > job2.profit;
    }}

// Function to perform job scheduling and print the optimal sequence
void schedule2(int maxElements, vector<Job>& jobs, vector<int>& optimalSequence) {
    int totalProfit = 0;
    optimalSequence.clear();
    Universe sets;

    // Initialize disjoint sets
    for (ElementIndex element = 0; element <= maxElements; element++) {
        initializeSet(element, sets);
    }

    // Sort jobs by profit in descending order
    sort(jobs.begin(), jobs.end(), isFeasible2);

    // Iterate through jobs and schedule them based on profit
    for (int i = 0; i < maxElements; i++) {
        // Find the latest set
        int currentDeadline = jobs[i].deadline;
        // Find the latest set with a deadline less than or equal to the current deadline
        SetPointer currentSet = findSet(min(currentDeadline, maxElements), sets);

        // If the latest set is not empty, schedule the job and merge the sets
        if (smallestElement(currentSet, sets) != 0) {
            optimalSequence.push_back(jobs[i].id);
            mergeSets(currentSet, findSet(smallestElement(currentSet, sets) - 1, sets), sets);
            totalProfit += jobs[i].profit;
        }
        // Or reject the job
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
//    int maxElements = 7;
//    // Table 1 from the assignment
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
//    schedule2(maxElements, jobs, optimalSequence);
//
//    return 0;
//}
