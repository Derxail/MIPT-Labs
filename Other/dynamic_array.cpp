#include <iostream>
#include <stdexcept>

struct DynamicArray {
    int* arr;
    unsigned size;
    unsigned capacity;

    DynamicArray(unsigned capacity = 1, unsigned size = 1) {
        this->size = size;
        this->capacity = capacity;
        this->arr = new int[capacity];
    }

    void reserve(unsigned new_capacity) {
        int* old_arr = this->arr;
        this->arr = new int[new_capacity];
        if (this->size > new_capacity) {
            this->size = new_capacity;
        }
        for (unsigned i = 0; i < this->size; ++i) {
            this->arr[i] = old_arr[i];
        }
        this->capacity = new_capacity;
        delete[] old_arr;
    }

    void resize(unsigned new_size, int val = 0) {
        if (new_size < this->size) {
            this->size = new_size;
            return;
        }
        if (new_size > this->capacity) {
            this->reserve(new_size);
        }
        for (unsigned i = this->size; i < new_size; ++i) {
            this->arr[i] = val;
        }
        this->size = new_size;
    }

    void insert_back(int n) {
        if (this->size == this->capacity) {
            this->reserve(2 * this->capacity);
        }
        ++this->size;
        this->arr[this->size - 1] = n;
    }

    void insert(unsigned idx, int value) {
        if (this->size == this->capacity) {
            this->reserve(2 * this->capacity);
        }
        ++this->size;
        for (unsigned i = this->size - 1; i > idx; --i) {
            std::swap(this->arr[i], this->arr[i - 1]);
        }
        this->arr[idx] = value;
    }

    void remove(unsigned idx) {
        for (unsigned i = idx; i < this->size - 1; ++i) {
            std::swap(this->arr[i], this->arr[i + 1]);
        }
        --this->size;
    }

    void print() {
        for (unsigned i = 0; i < this->size; ++i) {
            std::cout << this->arr[i] << ' ';
        }
        std::cout << std::endl;
    }

    int& operator[](unsigned n) {
        if (n >= this->size) {
            std::cout << "Dynamic array index out of range";
            throw std::out_of_range("Dynamic array index out of range");
        }
        return this->arr[n];
    }
};

int main() {
    DynamicArray arr(5, 5);
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
    arr.resize(3);
    arr.print();
    arr.resize(11, 6);
    arr.print();
    arr.reserve(5);
    arr.print();
    arr.reserve(8);
    arr.print();
    std::cout << arr.size << ' ' << arr.capacity << std::endl;
    std::cout << arr[11];
}
