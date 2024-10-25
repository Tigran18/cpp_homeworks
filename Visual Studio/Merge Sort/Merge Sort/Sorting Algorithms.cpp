#include <iostream>
#include <iomanip>
#include <cmath>
#include <chrono>

using namespace std;
using namespace std::chrono;

static void fill_arr(int* arr, int n, int max, int min) {
	for (int i = 0; i < n; i++) {
		arr[i] = rand() % (max-min+1)+min;
	}
}

static int num_digits(int num) {
    if (num == 0) return 1;
    int i = static_cast<int>(log10(abs(num)));
    return  i+ 1;
}

static void print_arr(int* arr, int n) {
	for (int i = 0; i < n; i++) {
		cout << setw(num_digits(arr[i])+3) << arr[i];
	}
	cout << "\n"<<endl;
}

static void merge(int* arr, int start, int mid, int end) {
    int n1 = mid - start + 1;
    int n2 = end - mid;
    int* left = new int[n1];
    int* right = new int[n2];
    for (int i = 0; i < n1; i++) left[i] = arr[start + i];
    for (int i = 0; i < n2; i++) right[i] = arr[mid + 1 + i];
    int i = 0, j = 0, k = start;
    while (i < n1 && j < n2) {
        if (left[i] <= right[j]) {
            arr[k++] = left[i++];
        }
        else {
            arr[k++] = right[j++];
        }
    }
    while (i < n1) arr[k++] = left[i++];
    while (j < n2) arr[k++] = right[j++];
    delete[] left;
    delete[] right;
}

static void merge_sort(int* arr, int start, int end) {//O(nlogn)
    if (start < end) {
        int mid = start + (end - start) / 2;
        merge_sort(arr, start, mid);
        merge_sort(arr, mid + 1, end);
        merge(arr, start, mid, end);
    }
}

static void bubble_sort(int* arr, int n) {//O(n^2)
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (arr[i]>arr[j]) {
                int temp = arr[i];
                arr[i] = arr[j];
                arr[j] = temp;
            }
        }
    }
}

static void arr_equal(int* arr1, int* arr2, int n) {
    for (int i = 0; i < n; i++) {
        arr2[i] = arr1[i];
    }
}

static bool binary_search(int* arr, int start, int end, int num) {
    if (start > end) {
        return false;
    }
    int mid = (start + end) / 2;
    if (arr[mid] == num) { 
        return true;
    }
    else if (arr[mid] > num) { 
        return binary_search(arr, start, mid - 1, num);
    }
    else {
        return binary_search(arr, mid + 1, end, num);
    }
}

int main() {
	while (true) {
        srand(time(0));
        int n, min, max;
		cout << "Enter the size of the array or press any key to exit: ";
		cin >> n;
        cout << "Enter the max and min intervals relatively: ";
        cin >> max >> min;
        int* arr1 = new int[n];
        int* arr2 = new int[n];
        if (cin.fail()) {
            break;
        }
		fill_arr(arr1, n, max, min);
        arr_equal(arr1, arr2, n);
        cout << "Unsorted array: ";
        print_arr(arr1, n);
		auto start1 = steady_clock::now();
        bubble_sort(arr1, n);
		auto finish1 = steady_clock::now();
        auto start2 = steady_clock::now();
        merge_sort(arr2, 0, n-1);
        auto finish2 = steady_clock::now();
        cout << "Sorted array:";
		print_arr(arr1, n);
		auto duration1 = duration_cast<microseconds>(finish1 - start1).count();
        auto duration2 = duration_cast<microseconds>(finish2 - start2).count();
		cout <<"\nBubble sort duration(mcs): " << duration1 << "\n" <<"Merge sort duration(mcs): " << duration2<<"\n" << endl;
        int num;
        cout << "Choose a number you want to get from the array: ";
        cin >> num;
        if (cin.fail()) {
            break;
        }
        if (binary_search(arr2, 0, n-1, num)) {
            cout << "\nThere is such a number\n"<< endl;
        }
        else {
            cout << "\nThere isn't such a number\n" << endl;
        }
        delete[] arr1;
        delete[] arr2;
	}
	return 0;
}