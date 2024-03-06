#include <iostream>
#include <vector>
#include <random>

unsigned partition(int a[], unsigned lhs, unsigned rhs) {
    int pivot = a[(lhs + rhs) / 2];
    while (true) {
        while (a[lhs] < pivot) ++lhs;
        while (a[rhs] > pivot) --rhs;
        if (rhs <= lhs) {
            return rhs;
        }
        std::swap(a[lhs], a[rhs]);
        ++lhs;
        --rhs;
    }
}

void quickSort(int a[], unsigned lhs, unsigned rhs) {
    unsigned p;
    if (lhs < rhs) {
        p = partition(a, lhs, rhs);
        quickSort(a, lhs, p);
        quickSort(a, p + 1, rhs);
    }
}

void merge(int a[], int lhs1, int rhs1, int lhs2, int rhs2) {
    std::vector<int> c(rhs1 - lhs1 + rhs2 - lhs2 + 2);
    int k = 0, i = lhs1, j = lhs2;
    while (i <= rhs1 || j <= rhs2) {
        if (j > rhs2 || i <= rhs1 && a[i] <= a[j]) {
            c[k] = a[i];
            ++i;
            ++k;
        }
        else {
            c[k] = a[j];
            ++j;
            ++k;
        }
    }
    for (int k = 0; k < c.size(); ++k) {
        a[lhs1 + k] = c[k];
    }
}


void mergeSort(int a[], int lhs, int rhs) {
    if (lhs == rhs) {
        return;
    }
    mergeSort(a, lhs, (lhs + rhs) / 2);
    mergeSort(a, (lhs + rhs) / 2 + 1, rhs);
    merge(a, lhs, (lhs + rhs) / 2, (lhs + rhs) / 2 + 1, rhs);
    return;
}


void bubbleSort(int a[], unsigned size) {
    unsigned count = 0;
    while (true) {
        count = 0;
        for (unsigned i = 0; i < size - 1; ++i) {
            if (a[i] > a[i + 1]) {
                ++count;
                std::swap(a[i], a[i + 1]);
            }
        }
        if (count == 0) break;
    }
}

void selectionSort(int a[], unsigned size) {
    unsigned min_ind = 0;
    for (unsigned i = 0; i < size; ++i) {
        min_ind = i;
        for (unsigned j = i; j < size; ++j) {
            if (a[min_ind] > a[j]) min_ind = j;
        }
        std::swap(a[i], a[min_ind]);
    }
}

void insertionSort(int a[], unsigned size) {
    int key;
    unsigned j;
    for (unsigned i = 1; i < size; ++i) {
        key = a[i];
        j = i - 1;
        while (j >= 0 && a[j] > key) {
            a[j + 1] = a[j];
            --j;
        }
        a[j + 1] = key;
    }
}

unsigned array_size = 100;
int a[100];

int main() {
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(1, array_size);
    
    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        a[cnt] = dstr(rng);
    }
    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        std::cout << a[cnt] << ' ';
    }
    std::cout << std::endl << std::endl;
    quickSort(a, 0, array_size);
    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        std::cout << a[cnt] << ' ';
    }
    return 0;
}
