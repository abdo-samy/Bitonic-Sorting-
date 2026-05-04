
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// ─────────────────────────────────────────────
//  Global counters (reset before each test)
// ─────────────────────────────────────────────
long long comparisons = 0;
long long swaps       = 0;

// ─────────────────────────────────────────────
//  Bubble Sort – ascending on subarray [lo..hi]
// ─────────────────────────────────────────────
void bubbleSortAscending(vector<int>& arr, int lo, int hi) {
    for (int i = lo; i <= hi; i++) {
        bool swapped = false;
        for (int j = lo; j < hi - (i - lo); j++) {
            comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swaps++;
                swapped = true;
            }
        }
        if (!swapped) break;
    }
}

// ─────────────────────────────────────────────
//  Selection Sort – descending on subarray [lo..hi]
// ─────────────────────────────────────────────
void selectionSortDescending(vector<int>& arr, int lo, int hi) {
    for (int i = lo; i <= hi; i++) {
        int maxIdx = i;
        for (int j = i + 1; j <= hi; j++) {
            comparisons++;
            if (arr[j] > arr[maxIdx])
                maxIdx = j;
        }
        if (maxIdx != i) {
            swap(arr[i], arr[maxIdx]);
            swaps++;
        }
    }
}

// ─────────────────────────────────────────────
//  Build Bitonic Array
//    - Sort full array ascending (bubble sort)
//    - Move global max to arr[mid]
//    - Reverse right half → descending
// ─────────────────────────────────────────────
void makeBitonic(vector<int>& arr) {
    int n   = arr.size();
    int mid = n / 2;

    // Sort entire array ascending
    bubbleSortAscending(arr, 0, n - 1);

    // Move the maximum (last element) to mid position
    int maxVal = arr[n - 1];
    for (int i = n - 1; i > mid; i--)
        arr[i] = arr[i - 1];
    arr[mid] = maxVal;

    // Reverse right half [mid+1 .. n-1] → descending
    reverse(arr.begin() + mid + 1, arr.end());
}

// ─────────────────────────────────────────────
//  Linear Search – counts its own comparisons
// ─────────────────────────────────────────────
int linearSearch(const vector<int>& arr, int target) {
    long long searchCmp = 0;
    int foundIdx = -1;
    for (int i = 0; i < (int)arr.size(); i++) {
        searchCmp++;
        if (arr[i] == target) { foundIdx = i; break; }
    }
    cout << "  Search comparisons : " << searchCmp << "\n";
    return foundIdx;
}

// ─────────────────────────────────────────────
//  Helpers
// ─────────────────────────────────────────────
void printArray(const vector<int>& arr, const string& label) {
    cout << "  " << label << ": [ ";
    for (int x : arr) cout << x << " ";
    cout << "]\n";
}

void runTest(const string& name, vector<int> arr, int target) {
    cout << "══════════════════════════════════════════\n";
    cout << "Test: " << name << "\n";
    printArray(arr, "Original array");
    cout << "  Target             : " << target << "\n";

    comparisons = swaps = 0;
    makeBitonic(arr);

    printArray(arr, "Bitonic  array");
    int mid = (int)arr.size() / 2;
    cout << "  Bitonic point      : arr[" << mid << "] = " << arr[mid] << "\n";
    cout << "  Sorting comparisons: " << comparisons << "\n";
    cout << "  Sorting swaps      : " << swaps       << "\n";

    int idx = linearSearch(arr, target);
    if (idx == -1)
        cout << "  Result             : " << target << " NOT FOUND\n\n";
    else
        cout << "  Result             : " << target
             << " found at index " << idx << "\n\n";
}

// ─────────────────────────────────────────────
//  Main – 5 required test cases
// ─────────────────────────────────────────────
int main() {
    // 1. Target at the bitonic point (maximum element)
    runTest("Target at bitonic point",
            {3, 1, 7, 5, 2, 9, 4}, 9);

    // 2. Target in left half (ascending portion)
    runTest("Target in left half (ascending)",
            {6, 2, 8, 3, 11, 5, 1}, 3);

    // 3. Target in right half (descending portion)
    runTest("Target in right half (descending)",
            {6, 2, 8, 3, 11, 5, 1}, 2);

    // 4. Target not present in the array
    runTest("Target not present",
            {4, 7, 1, 9, 3, 6, 2}, 10);

    // 5. Array with duplicate elements
    runTest("Array with duplicates",
            {3, 1, 4, 1, 5, 9, 2, 6, 5, 3}, 5);

    return 0;
}