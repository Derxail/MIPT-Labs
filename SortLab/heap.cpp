#include <iostream>
#include <random>

void print(int a[], unsigned size) {
    for (unsigned cnt = 0; cnt < size; ++cnt) {
        std::cout << a[cnt] << ' ';
    }
    std::cout << std::endl;
}

void heapParentSwap(int a[], unsigned size, unsigned parent_ind) {
    int child1_ind = 2 * parent_ind + 1;
    int child2_ind = 2 * parent_ind + 2;
    if (child1_ind >= size) child1_ind = parent_ind;
    if (child2_ind >= size) child2_ind = parent_ind;
    if (a[child1_ind] >= a[child2_ind] && a[child1_ind] > a[parent_ind]) {
        std::swap(a[parent_ind], a[child1_ind]);
        if (2 * child1_ind + 1 >= size) return;
        heapParentSwap(a, size, child1_ind);
    }
    else if (a[child2_ind] > a[child1_ind] && a[child2_ind] > a[parent_ind]) {
        std::swap(a[parent_ind], a[child2_ind]);
        if (2 * child2_ind + 1 >= size) return;
        heapParentSwap(a, size, child2_ind);
    }
}

void arrayToHeap(int a[], unsigned size) {
    unsigned layer_start = 0;
    while (2 * layer_start + 1 < size) {
        layer_start = 2 * layer_start + 1;
    }
    layer_start /= 2;
    while (layer_start != 0){
        for (int parent_num = 0; parent_num <= layer_start && layer_start + parent_num < size; ++parent_num) {
            heapParentSwap(a, size, layer_start + parent_num);
        }
        layer_start /= 2;
    }
    heapParentSwap(a, size, 0);
}

void heapSort(int a[], unsigned size) {
    if (size == 1) return;
    arrayToHeap(a, size);
    std::swap(a[0], a[size - 1]);
    heapSort(a, size - 1);
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
    print(a, array_size);
    std::cout << std::endl << std::endl;
    heapSort(a, array_size);
    print(a, array_size);
    return 0;
}
