/**
 * QuickSort
 */

#include<bits/stdc++.h>

#define NMAX 100000

using namespace std;

int arr[NMAX];
long CMP = 0;

void swap_num(int *x, int *y) {
    int temp;

    temp = *x;
    *x = *y;
    *y = temp;
}

int cmp(int *x, int *y) {
    return (*x - *y);
}

int partition(int arr[], int l, int r) {
    int i = l+1;
    int p = arr[l];
    bool flag = false;

    for(int j = i; j <= r; j++, CMP++) {
        if ((cmp(&p, &arr[j]) > 0)) {
            if (flag) swap_num(&arr[i], &arr[j]);
            i++;
        } else {
            flag = true;
        }
    }

    swap_num(&arr[l], &arr[i-1]);

    return i-1;
}

void pivot(int arr[], int n) {
    int ran = rand() % n;

    swap_num(&arr[ran], arr);
}

void quick_sort(int arr[], int n) {
    if(n <= 1) return;

    pivot(arr, n);

    int p_index = partition(arr, 0, n-1);

    quick_sort(arr, p_index);
    quick_sort(&arr[p_index+1], n-p_index-1);
}

int main() {
    int arr[NMAX], n, i=0;
    clock_t start, end;

    cout << "Quicksort. Enter numbers to be sorted: ";
    cin >> n;

    cout << "Enter numbers below: " << endl;
    while(i<n) {
        cin >> arr[i++];
    }

    start = clock();

    quick_sort(arr, n);

    end = clock();

    double time_diff = ((double)end - (double)start) / CLOCKS_PER_SEC;

    i=0;
    cout << "Sorted numbers below:" << endl;
    while(i<n) {
        cout << arr[i++] << " ";
    }
    cout << endl;
    cout << "No. of comparisons: " << CMP << endl;

    cout << "Runtime is " << time_diff << " seconds." << endl;

   return 0;
}
