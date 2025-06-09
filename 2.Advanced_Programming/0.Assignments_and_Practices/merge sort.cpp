//Merge sort (rec) (https://www.scaler.com/topics/merge-sort-cpp/)
#include <iostream>
#include <vector>
using namespace std;

void printArray(int * arr, int length) {
    for (int i = 0; i < length; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void merge(int * arr, int low, int mid, int high)
{
    int i, j, k;
    int lengthLeft = mid - low + 1;
    int lengthRight = high - mid;

    // Creating two temp arrays to store left and right sub-arrays.
    int arrLeft[lengthLeft], arrRight[lengthRight];

    // Copying the data from the actual array to left and right temp arrays.
    for (int a = 0; a < lengthLeft; a++) 
    {
        arrLeft[a] = arr[low + a];
    }
    for (int a = 0; a < lengthRight; a++) 
    {
        arrRight[a] = arr[mid + 1 + a];
    }

    // Merging the temp arrays back into the actual array.
    i = 0; // Starting index of arrLeft[].
    j = 0; // Staring index of arrRight[].
    k = low; // Starting index of merged subarray.

    while (i < lengthLeft && j < lengthRight) {
        // Checking and placing the smaller number of both temp arrays into the main array.
        if (arrLeft[i] <= arrRight[j]) {
            arr[k] = arrLeft[i];
            i++;
        } else {
            arr[k] = arrRight[j];
            j++;
        }
        k++;
    }

    // copying the remaining elements of the left subarray (if remaining).
    while (i < lengthLeft) 
    {
        arr[k] = arrLeft[i];
        k++;
        i++;
    }
    // Copying the remaining elements of the right sub array (if remaining).
    while (j < lengthRight) {
        arr[k] = arrRight[j];
        k++;
        j++;
    }
}

void mergeSort(int * arr, int low, int high) {
    int mid;
    if (low < high) {
        mid = (low + high) / 2;

        // Calling the function mergeSort() recursively and breaking down the given array into smaller sub arrays.
        mergeSort(arr, low, mid);
        mergeSort(arr, mid + 1, high);

        // Calling the merge() function to merge the sorted subarrays into the main array.
        merge(arr, low, mid, high);
    }
}