#include <iostream>

struct DynamicArray {
    int* arr;
    unsigned size;

    DynamicArray(unsigned size = 2) {
        this->size = size;
        this->arr = new int[size];
    }

    void resize(unsigned new_size) {
        int* old_arr = this->arr;
        this->arr = new int[new_size];
        for (unsigned i = 0; i < std::min(this->size, new_size); ++i) {
            this->arr[i] = old_arr[i];
        }
        this->size = new_size;
        delete[] old_arr;
    }

    void insert_back(int n) {
        this->resize(this->size + 1);
        this->arr[this->size - 1] = n;
    }

    void insert(unsigned idx, int value) {
        this->resize(this->size + 1);
        for (unsigned i = this->size - 1; i > idx; --i) {
            std::swap(this->arr[i], this->arr[i - 1]);
        }
        this->arr[idx] = value;
    }

    void remove(unsigned idx) {
        for (unsigned i = idx; i < this->size - 1; ++i) {
            std::swap(this->arr[i], this->arr[i + 1]);
        }
        this->resize(this->size - 1);
    }

    void print() {
        for (unsigned i = 0; i < this->size; ++i) {
            std::cout << this->arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    int& operator[](unsigned n) {
        return this->arr[n];
    }
};

int main() {
    DynamicArray arr(5);
    arr[0] = 1;
    arr[1] = 2;
    arr[2] = 3;
    arr[3] = 4;
    arr[4] = 5;
    arr.insert_back(6);
    arr.print();
    arr.insert(2, 7);
    arr.print();
    arr.remove(3);
    arr.print();
}
