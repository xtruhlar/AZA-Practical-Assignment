#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;

const int INF = numeric_limits<int>::max();
int count_zeros(const vector<int>& row);

// Comparison function to sort the matrix based on the number of zeros in each row
struct CompareRows {
    bool operator()(const vector<int>& row1, const vector<int>& row2) {
        return count_zeros(row1) < count_zeros(row2);
    }
};

// Function to count the number of zeros in a row
int count_zeros(const vector<int>& row) {
    int count = 0;
    for (int value : row) {
        if (value == 0) {
            count++;
        }
    }
    return count;
}

// Function to reduce the matrix with minimal cost that has to be paid - no matter what the assignment is
vector<vector<int>> matrix_reduction(vector<vector<int>>& costMatrix, int n, vector<vector<int>>& costMatrixCopy) {
    // Subtract the minimum value from each row
    for (int i = 0; i < n; ++i) {
        int min_val = INF;
        for (int j = 0; j < n; ++j) {
            min_val = min(min_val, costMatrix[i][j]);
        }
        for (int j = 0; j < n; ++j) {
            costMatrixCopy[i][j] -= min_val;
        }
    }

    // Vectors to keep track of covered rows and columns
    vector<int> row_covered(n, 0);
    vector<int> col_covered(n, 0);

    // Cover all zeros in the matrix
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (costMatrixCopy[i][j] == 0) {
                // Star the zero
                row_covered[i] = 1;
                col_covered[j] = 1;
            }
        }
    }

    // Cover all columns that have a starred zero
    for (int j = 0; j < n; ++j) {
        if (col_covered[j] == 0) {
            int min_val = INF;
            for (int i = 0; i < n; ++i) {
                min_val = min(min_val, costMatrixCopy[i][j]);
            }
            for (int i = 0; i < n; ++i) {
                costMatrixCopy[i][j] -= min_val;
            }
        }
    }

    return costMatrixCopy;

}

// Function to cover all zeros with minimum number of vertical/horizontal lines or both
vector<vector<int>> line_rows_and_columns(int n, vector<vector<int>>& costMatrixCopy) {
    // Cover all zeros with minimum number of vertical/horizontal lines or both
    vector<int> rowZeros(n, 0);
    vector<int> colZeros(n, 0);

    // Count total number of zeros in the matrix
    int totalZeros = 0;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (costMatrixCopy[i][j] == 0) {
                totalZeros++;
            }
        }
    }

    vector<vector<int>> costMatrixCopy2 = costMatrixCopy;
    int total = totalZeros;
    // Repeat until all zeros are covered
    while (totalZeros > 0) {
        totalZeros = total;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if (costMatrixCopy2[i][j] == 0 && rowZeros[i] != -1 && colZeros[j] != -1) {
                    rowZeros[i]++;
                    colZeros[j]++;
                }
            }
        }
        // Find the row and column with the maximum number of zeros
        int maxRowZeros = *max_element(rowZeros.begin(), rowZeros.end());
        int maxColZeros = *max_element(colZeros.begin(), colZeros.end());

        // If a row or column has a common zero, subtract it only once
        if (maxRowZeros >= maxColZeros) {
            for (int i = 0; i < n; ++i) {
                if (rowZeros[i] == maxRowZeros) {
                    rowZeros[i] = -1;
                }
            }
        } else {
            for (int j = 0; j < n; ++j) {
                if (colZeros[j] == maxColZeros) {
                    colZeros[j] = -1;
                }
            }
        }

        // Count the number of covered zeros careful not to count the same zero twice if it is covered by both a row and a column
        int coveredZeros = 0;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                if ((rowZeros[i] == -1 || colZeros[j] == -1) && costMatrixCopy[i][j] == 0) {
                    costMatrixCopy2[i][j] = -2;
                    coveredZeros++;
                }
            }
        }

        // Subtract the covered zeros from the total number of zeros
        totalZeros -= coveredZeros;
    }


    // Find the minimum uncovered value
    int minUncovered = INF;
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if ((rowZeros[i] != -1 && colZeros[j] != -1) && costMatrixCopy[i][j] < minUncovered) {
                minUncovered = costMatrixCopy[i][j];
            }
        }
    }

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (rowZeros[i] != -1 && colZeros[j] != -1) {
                costMatrixCopy[i][j] -= minUncovered;
            }
            if (rowZeros[i] == -1 && colZeros[j] == -1) {
                costMatrixCopy[i][j] += minUncovered;
            }
        }

    }
    return costMatrixCopy;
}

// Function to assign workers to tasks
auto task_assignment(int n, vector<vector<int>>& costMatrixCopy2, vector<int>assigned, vector<vector<int>>& costMatrix) {
    vector<int> rowZeros(n, 0);

    // Count the number of zeros in each row
    for (int i = 0; i < n; ++i) {
        rowZeros[i] = count_zeros(costMatrixCopy2[i]);
    }

    // Sort the matrix based on the number of zeros in each row
    vector<vector<int>> cost3 = costMatrixCopy2;
    sort(cost3.begin(), cost3.end(), CompareRows());

    // Map original matrix and sorted matrix
    vector<int> map(n, 0);
    for (int i = 0; i < n; ++i) {
        int index = 0;
        for (int j = 0; j < n; ++j) {
            if (costMatrixCopy2[i] == cost3[j]) {
                index = j;
                break;
            }
        }
        map[i] = index;
    }

    // Count the number of zeros in each row of the sorted matrix
    for (int i = 0; i < n; ++i) {
        rowZeros[i] = count_zeros(cost3[i]);
    }

    // Assign workers to tasks
    for (int i = 0; i < n; ++i) {
        if (rowZeros[i] == 1) {
            for (int j = 0; j < n; ++j) {
                if (cost3[i][j] == 0) {
                    assigned[j] = i;
                    cost3[i][j] = -2;
                    for (int k = 0; k < n; ++k) {
                        if (cost3[k][j] == 0) {
                            cost3[k][j] = -1;
                            rowZeros[k]--;
                        }
                    }
                }
            }
        }
    }

    // Using map get the original matrix
    for (int i = 0; i < n; ++i) {
        if (assigned[i] != -1) {
            assigned[i] = map[assigned[i]];
        }
    }

    int totalCost = 0;
    // Print the assignment of workers to tasks and cost from the original matrix
    for (int i = 0; i < n; ++i) {
        if (assigned[i] != -1) {
            cout << "J" << i + 1 << "\tP" << assigned[i] + 1 << "\t" << costMatrix[assigned[i]][i] << "\n";
            totalCost += costMatrix[assigned[i]][i];
        }
    }
    cout << "Total cost = " << totalCost << "\n";
}

//int main() {
//    // Example matrix
//    vector<vector<int>> costMatrix = {
//            {10, 5, 5},
//            {2,  4, 10},
//            {5,  1, 7}
//    };
//
////    vector<vector<int>> costMatrix = {
////            {80, 40, 50, 46},
////            {40, 70, 20, 25},
////            {30, 10, 20, 30},
////            {35, 20, 25, 30}
////    };
//
//    int n = costMatrix.size();
//    vector<vector<int>> costMatrixCopy = costMatrix;
//    vector<int> assigned(n, -1);
//
//    vector<vector<int>> matrix_reduced = matrix_reduction(costMatrix, n, costMatrixCopy);
//    vector<vector<int>> matrix_lined = line_rows_and_columns(n, matrix_reduced);
//    task_assignment(n, matrix_lined, assigned, costMatrix);
//
//    return 0;
//}