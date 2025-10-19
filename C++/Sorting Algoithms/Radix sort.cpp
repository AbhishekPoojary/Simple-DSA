#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Function to get the maximum value in the array
int getMax(vector<int>& arr) {
    return *max_element(arr.begin(), arr.end());
}

// A function to perform Counting Sort based on a specific digit (exp)
void countingSort(vector<int>& arr, int exp) {
    int n = arr.size();
    vector<int> output(n);      // Output array
    int count[10] = {0};        // Count array for digits 0–9

    // Count occurrences of each digit at current place (exp)
    for(int i = 0; i < n; i++)
        count[(arr[i] / exp) % 10]++;

    // Convert count[i] to position index
    for(int i = 1; i < 10; i++)
        count[i] += count[i - 1];

    // Build the output array (stable sort)
    for(int i = n - 1; i >= 0; i--) {
        int digit = (arr[i] / exp) % 10;
        output[count[digit] - 1] = arr[i];
        count[digit]--;
    }

    // Copy the output array back to arr[]
    for(int i = 0; i < n; i++)
        arr[i] = output[i];
}

// Main Radix Sort function
void radixSort(vector<int>& arr) {
    int maxNum = getMax(arr);

    // Do counting sort for every digit (1s, 10s, 100s, ...)
    for(int exp = 1; maxNum / exp > 0; exp *= 10)
        countingSort(arr, exp);
}

// Driver code
int main() {
    vector<int> arr = {170, 45, 75, 90, 802, 24, 2, 66};

    cout << "Original array:\n";
    for(int num : arr) cout << num << " ";
    cout << endl;

    radixSort(arr);

    cout << "\nSorted array:\n";
    for(int num : arr) cout << num << " ";
    cout << endl;

    return 0;
}
