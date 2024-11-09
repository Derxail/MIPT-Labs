#include <iostream>

template <typename T, unsigned N>
class Array
{
public:
    Array() = default;
    explicit Array(const T& value) {
        fill(value);
    }
    Array(const Array &other) {
        for (unsigned int i = 0u; i < N; ++i) arr[i] = other[i];
    }
    ~Array() = default;
    Array& operator=(const Array& other) {
        for (unsigned int i = 0u; i < N; ++i) arr[i] = other[i];
        return *this;
    }
    size_t size() const {
        return N;
    }
    T& operator[](unsigned n) {
        return arr[n];
    }
    const T& operator[](unsigned n) const {
        return arr[n];
    }
    T* front() {
        if (this->empty()) return nullptr;
        return arr;
    }
    T* back() {
        if (this->empty()) return nullptr;
        return arr + N - 1;
    }
    bool empty() {return (N == 0);}
    void fill(const T& value) {
        for (unsigned i = 0; i < N; ++i) {
            arr[i] = value;
        }
    }
private:
    T arr[N];
};

int main() {
    Array<int, 0> d(1);
    d.fill(2);
    std::cout << d.back() << std::endl;
    for (unsigned i = 0; i < d.size(); ++i) {
        std::cout << d[i] << ' ';
    }
    std::cout << std::endl;
    Array<int, 10> a(0);
    Array<int, 10> b(1);
    for (unsigned i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
    for (unsigned i = 0; i < b.size(); ++i) {
        std::cout << b[i] << ' ';
    }
    std::cout << std::endl;
    a.fill(2);
    b.fill(3);
    Array<int, 10> c(b);
    b = a;
    for (unsigned i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
    for (unsigned i = 0; i < b.size(); ++i) {
        std::cout << b[i] << ' ';
    }
    std::cout << std::endl;
    for (unsigned i = 0; i < c.size(); ++i) {
        std::cout << c[i] << ' ';
    }
    std::cout << std::endl;
    a[0] = 4;
    a[1] = c[0];
    *(a.back()) = 5;
    for (unsigned i = 0; i < a.size(); ++i) {
        std::cout << a[i] << ' ';
    }
    std::cout << std::endl;
}
