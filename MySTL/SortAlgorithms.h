#ifndef SORTALGORITHMS_H
#define SORTALGORITHMS_H

#include <vector>
#include <algorithm>
#include <iostream>
#include <chrono>
#include <functional>
using namespace std;

namespace SortAlgorithms {

    // Ã°ÅÝÅÅÐò
    template<typename T, typename Compare>
    void bubbleSort(vector<T>& arr, Compare comp) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (comp(arr[j + 1], arr[j])) {
                    swap(arr[j], arr[j + 1]);
                }
            }
        }
    }

    // Ñ¡ÔñÅÅÐò
    template<typename T, typename Compare>
    void selectionSort(vector<T>& arr, Compare comp) {
        int n = arr.size();
        for (int i = 0; i < n - 1; i++) {
            int minIdx = i;
            for (int j = i + 1; j < n; j++) {
                if (comp(arr[j], arr[minIdx])) {
                    minIdx = j;
                }
            }
            swap(arr[i], arr[minIdx]);
        }
    }

    // ²åÈëÅÅÐò
    template<typename T, typename Compare>
    void insertionSort(vector<T>& arr, Compare comp) {
        int n = arr.size();
        for (int i = 1; i < n; i++) {
            T key = arr[i];
            int j = i - 1;
            while (j >= 0 && comp(key, arr[j])) {
                arr[j + 1] = arr[j];
                j--;
            }
            arr[j + 1] = key;
        }
    }

    // ¿ìËÙÅÅÐò¸¨Öúº¯Êý
    template<typename T, typename Compare>
    int partition(vector<T>& arr, int low, int high, Compare comp) {
        T pivot = arr[high];
        int i = low - 1;

        for (int j = low; j < high; j++) {
            if (comp(arr[j], pivot)) {
                i++;
                swap(arr[i], arr[j]);
            }
        }
        swap(arr[i + 1], arr[high]);
        return i + 1;
    }

    // ¿ìËÙÅÅÐò
    template<typename T, typename Compare>
    void quickSortHelper(vector<T>& arr, int low, int high, Compare comp) {
        if (low < high) {
            int pi = partition(arr, low, high, comp);
            quickSortHelper(arr, low, pi - 1, comp);
            quickSortHelper(arr, pi + 1, high, comp);
        }
    }

    template<typename T, typename Compare>
    void quickSort(vector<T>& arr, Compare comp) {
        if (!arr.empty()) {
            quickSortHelper(arr, 0, arr.size() - 1, comp);
        }
    }

    // ¹é²¢ÅÅÐò¸¨Öúº¯Êý
    template<typename T, typename Compare>
    void merge(vector<T>& arr, int left, int mid, int right, Compare comp) {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        vector<T> L(n1), R(n2);

        for (int i = 0; i < n1; i++)
            L[i] = arr[left + i];
        for (int j = 0; j < n2; j++)
            R[j] = arr[mid + 1 + j];

        int i = 0, j = 0, k = left;

        while (i < n1 && j < n2) {
            if (comp(L[i], R[j])) {
                arr[k] = L[i];
                i++;
            }
            else {
                arr[k] = R[j];
                j++;
            }
            k++;
        }

        while (i < n1) {
            arr[k] = L[i];
            i++;
            k++;
        }

        while (j < n2) {
            arr[k] = R[j];
            j++;
            k++;
        }
    }

    // ¹é²¢ÅÅÐò
    template<typename T, typename Compare>
    void mergeSortHelper(vector<T>& arr, int left, int right, Compare comp) {
        if (left < right) {
            int mid = left + (right - left) / 2;
            mergeSortHelper(arr, left, mid, comp);
            mergeSortHelper(arr, mid + 1, right, comp);
            merge(arr, left, mid, right, comp);
        }
    }

    template<typename T, typename Compare>
    void mergeSort(vector<T>& arr, Compare comp) {
        if (!arr.empty()) {
            mergeSortHelper(arr, 0, arr.size() - 1, comp);
        }
    }

    // ¶ÑÅÅÐò¸¨Öúº¯Êý
    template<typename T, typename Compare>
    void heapify(vector<T>& arr, int n, int i, Compare comp) {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < n && comp(arr[left], arr[largest]))
            largest = left;

        if (right < n&& comp(arr[right], arr[largest]))
            largest = right;

        if (largest != i) {
            swap(arr[i], arr[largest]);
            heapify(arr, n, largest, comp);
        }
    }

    // ¶ÑÅÅÐò
    template<typename T, typename Compare>
    void heapSort(vector<T>& arr, Compare comp) {
        int n = arr.size();

        // ¹¹½¨×î´ó¶Ñ
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(arr, n, i, comp);

        // Ò»¸ö¸ö´Ó¶Ñ¶¥È¡³öÔªËØ
        for (int i = n - 1; i > 0; i--) {
            swap(arr[0], arr[i]);
            heapify(arr, i, 0, comp);
        }
    }
}

#endif // SORTALGORITHMS_H