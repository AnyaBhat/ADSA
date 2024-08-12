#include <bits/stdc++.h>
using namespace std;
void bubbleSort(int arr[],int n){
    int i,j;
    bool swapped;
    for(i=0;i<n-1;i++){
        swapped=false;
        for(j=0;j<n-i-1;j++){
            if(arr[j]>arr[j+1]){
                swap(arr[j],arr[j+1]);
                swapped=true;
            }

        }
        if(swapped==false)
            break;
    }
}
// Function to print an array
void printArray(int arr[], int size)
{
    int i;
    for (i = 0; i < size; i++)
        cout << " " << arr[i];
}

// Driver program to test above functions
int main()
{
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
    cout<<"\n";

    bubbleSort(arr, N);

    cout << "Sorted array: \n";
    printArray(arr, N);
    cout<<"\n";
    return 0;
}
