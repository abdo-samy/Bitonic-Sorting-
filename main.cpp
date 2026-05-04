#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

using namespace std;

struct SortResult {
    int comparisons = 0;
    int swaps = 0;
};

SortResult bubbleSort(vector<int>& arr, int start, int end) {
    SortResult res;
    int n = end - start + 1;
    bool swapped; 
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = start; j < start + n - 1 - i; j++) {
            res.comparisons++;
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                res.swaps++;
                swapped = true;
            }
        }
        if (!swapped) break; 
    }
    return res;
}

SortResult selectionSort(vector<int>& arr, int start, int end) {
    SortResult res;
    for (int i = start; i < end; i++) {
        int max_idx = i;
        for (int j = i + 1; j <= end; j++) {
            res.comparisons++;
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
            }
        }
        if (max_idx != i) {
            swap(arr[i], arr[max_idx]);
            res.swaps++;
        }
    }
    return res;
}

int bitonicSearch(const vector<int>& arr, int target) {
    for (int i = 0; i < (int)arr.size(); i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}

void runTestCase(vector<int> arr, int target, string description) {
    cout << "--- Case: " << description << " ---\nOriginal: ";
    for (int x : arr) cout << x << " ";
    
    int mid = (int)arr.size() / 2;
    SortResult r1 = bubbleSort(arr, 0, mid - 1);
    SortResult r2 = selectionSort(arr, mid, (int)arr.size() - 1);

    cout << "\nBitonic:  ";
    for (int x : arr) cout << x << " ";
    
    cout << "\nTotal Comparisons: " << (r1.comparisons + r2.comparisons)
         << "\nTotal Swaps:       " << (r1.swaps + r2.swaps) << endl;

    int index = bitonicSearch(arr, target);
    if (index != -1)
        cout << "Target " << target << " found at index: " << index << endl;
    else
        cout << "Target " << target << " not found." << endl;
    cout << "---------------------------------------\n" << endl;
}

int main() {
    runTestCase({5, 2, 9, 1, 7, 3}, 9, "Bitonic Point");
    runTestCase({10, 40, 20, 50, 30}, 20, "Left Side");
    runTestCase({12, 5, 8, 2, 10, 15}, 5, "Right Side");
    runTestCase({4, 1, 8, 3}, 100, "Target Not Found");
    runTestCase({5, 3, 5, 8, 2, 8}, 5, "Duplicate Elements");
    return 0;
}

