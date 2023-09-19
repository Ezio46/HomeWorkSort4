#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <algorithm>

using namespace std;

// Counting Sort
void countingSort(vector<int>& arr) {
    int n = arr.size();
    if (n <= 1) {
        return;
    }

    int minVal = arr[0];
    int maxVal = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] < minVal) {
            minVal = arr[i];
        }
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    int range = maxVal - minVal + 1;

    vector<double> count(range, 0);

    for (int i = 0; i < n; i++) {
        count[arr[i] - minVal]++;
    }

    int index = 0;
    for (int i = 0; i < range; i++) {
        while (count[i] > 0) {
            arr[index] = i + minVal;
            index++;
            count[i]--;
        }
    }
}

// Radix Sort
void radixSort(vector<int>& arr) {

    int maxVal = arr[0];
    int n = arr.size();

    for (int i = 1; i < n; i++) {
        if (arr[i] > maxVal) {
            maxVal = arr[i];
        }
    }

    for (int exp = 1; maxVal / exp > 0; exp *= 10) {
        vector<int> output(n);
        vector<int> count(10, 0);

        for (int i = 0; i < n; i++) {
            count[(arr[i] / exp) % 10]++;
        }

        for (int i = 1; i < 10; i++) {
            count[i] += count[i - 1];
        }

        for (int i = n - 1; i >= 0; i--) {
            output[count[(arr[i] / exp) % 10] - 1] = arr[i];
            count[(arr[i] / exp) % 10]--;
        }

        for (int i = 0; i < n; i++) {
            arr[i] = output[i];
        }
    }
}

// Bucket Sort
void bucketSort(vector<int>& arr) {
    int n = arr.size();

    int maxVal = *max_element(arr.begin(), arr.end());

    vector<vector<int>> buckets(maxVal + 1);

    for (int i = 0; i < n; i++) {
        buckets[arr[i]].push_back(arr[i]);
    }

    int index = 0;
    for (int i = 0; i <= maxVal; i++) {
        for (int num : buckets[i]) {
            arr[index++] = num;
        }
    }
}

int main() {

    int N = 1000000;

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distribution(1, N);
    vector<int> arr(N);
    for (int i = 0; i < N; ++i) {
        arr[i] = distribution(gen);
    }

    // countingSort
    auto start = chrono::high_resolution_clock::now();

    countingSort(arr);

    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "countingSort time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // radixSort
    start = chrono::high_resolution_clock::now();

    radixSort(arr);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "radixSort time: " << duration.count() << " ms." << endl;
    random_shuffle(arr.begin(), arr.end());

    // bucketSort
    start = chrono::high_resolution_clock::now();

    bucketSort(arr);

    stop = chrono::high_resolution_clock::now();
    duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    cout << "bucketSort time: " << duration.count() << " ms." << endl;

    return 0;
}
