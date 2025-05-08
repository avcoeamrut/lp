#include <iostream>
#include <omp.h>
#include <climits>
using namespace std;
int main() {
   const int n = 8;
   int arr[n] = {15, 3, 7, 20, 9, 11, 2, 18};
    int minVal = INT_MAX;
    int maxVal = INT_MIN;
    int sum = 0;
    double average = 0.0;

    // Parallel reduction for minimum
    #pragma omp parallel for reduction(min:minVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] < minVal)
            minVal = arr[i];
    }

    // Parallel reduction for maximum
    #pragma omp parallel for reduction(max:maxVal)
    for (int i = 0; i < n; i++) {
        if (arr[i] > maxVal)
            maxVal = arr[i];
    }

    // Parallel reduction for sum
    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    // Calculate average (outside parallel region)
    average = static_cast<double>(sum) / n;

    // Output results
    cout << "Array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << "\n";

    cout << "Minimum: " << minVal << endl;
    cout << "Maximum: " << maxVal << endl;
    cout << "Sum:     " << sum << endl;
    cout << "Average: " << average << endl;

    return 0;
}