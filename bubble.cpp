// File: parallel_bubble_sort.cpp

#include <iostream>
#include <omp.h>
using namespace std;

void parallelBubbleSort(int arr[], int n) 
{
    for (int i = 0; i < n; i++) 
    {
        int phase = i % 2;

        #pragma omp parallel for
        for (int j = phase; j < n - 1; j += 2) 
        {
            if (arr[j] > arr[j + 1]) 
            {
              swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    int arr[] = {64, 34, 25, 12, 22, 11, 90};
    int n = sizeof(arr) / sizeof(arr[0]);

    cout << "Original array: ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    parallelBubbleSort(arr, n);

    cout << "Sorted array (Parallel Bubble Sort): ";
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;

    return 0;
}