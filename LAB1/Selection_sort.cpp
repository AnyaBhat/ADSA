// C++ program for implementation of
// selection sort
#include <bits/stdc++.h>
using namespace std;

// Function for Selection sort
void selectionSort(int arr[], int n)
{
    int i, j, min_idx;

    // One by one move boundary of
    // unsorted subarray
    for (i = 0; i < n - 1; i++) {

        // Find the minimum element in
        // unsorted array
        min_idx = i;
        for (j = i + 1; j < n; j++) {
            if (arr[j] < arr[min_idx])
                min_idx = j;
        }

        // Swap the found minimum element
        // with the first element
        if (min_idx != i)
            swap(arr[min_idx], arr[i]);
    }
}

// Function to print an array
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++) {
        cout << arr[i] << " ";
        cout << endl;
    }
}

// Driver program
int main()
{
    // Define the size of the array
    int N;
    cout << "Enter the size of the array: ";
    cin >> N;

    // Create an array of size N
    int arr[N];

    // Seed the random number generator
    srand(time(0));

    for (int i = 0; i < N; i++) {
        arr[i] = rand() % 100;
    }

    // Print the unsorted array
    cout << "Unsorted array: \n";
    printArray(arr, N);

    // Function Call
    selectionSort(arr, N);

    // Print the sorted array
    cout << "Sorted array: \n";
    printArray(arr, N);

    return 0;
}
