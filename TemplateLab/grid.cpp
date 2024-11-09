#include <cassert>
#include <algorithm>
#include <iostream>

template<typename T, unsigned dim>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;
private:
    Grid<T, dim - 1>* data;
    size_type size;
    void allocate_memory(size_type size) {
        data = static_cast<Grid<T, dim - 1> *>(operator new[](size * sizeof(Grid<T, dim - 1>)));
    }
public:
    template<typename... tail> Grid(size_type size, tail... rest): size{size} {
        allocate_memory(size);
        for (auto it = data, end = data + size; it != end; ++it) new(it) Grid<T, dim - 1>(rest...);
    }
    Grid(T const& t): size(1) {
        allocate_memory(1);
        new(data) Grid<T, dim - 1>(t);
    }

    template<typename... tail> T operator()(size_type idx, tail... rest) const
    {
        return data[idx](rest...);
    }

    template<typename... tail> T& operator()(size_type idx, tail... rest)
    {
        return data[idx](rest...);
    }

    const Grid<T, dim - 1>& operator[](size_type idx) const
    {
        return data[idx];
    }

    Grid<T, dim - 1>& operator[](size_type idx)
    {
        return data[idx];
    }

    Grid<T, dim>& operator=(T const& t)
    {
        for (auto it = data, end = data + size; it != end; ++it) *it = t;
        return *this;
    }

    size_type get_size() const { return size; }

    ~Grid() {
        for (auto it = data, end = data + size; it != end; ++it) it->~Grid();
        //delete[] data;
    }
public:
    Grid(Grid<T, dim> const& other): size(other.get_size()) {
        allocate_memory(size);
        for (auto i = 0; i != size; ++i) new(data + i) Grid<T, dim - 1>(other[i]);
    }
    Grid<T, dim>& operator=(Grid<T, dim> const& other) {
        Grid<T, dim> tmp(other);
        // Из функции класса можно получить private member любого другого члена класса... Целый новый мир открылся для меня этой строкой.
        std::swap(this->data, tmp.data);
        std::swap(this->size, tmp.size);
        return *this;
    }
    // С новым знанием о private, можно и перемещение написать
    Grid(Grid<T, dim>&& other): data(other.data), size(other.size()) {
        other.data = nullptr;
        other.size = 0;
    }
    Grid<T, dim>& operator=(Grid<T, dim>&& other) {
        std::swap(this->data, other.data);
        std::swap(this->size, other.size)
        return *this;
    }
} ;

template<typename T>
class Grid<T, 1> final
{
public:
    using value_type = T;
    using size_type = unsigned;
private:
    T* data;
    size_type size;
public:
    Grid(T *data , size_type size): data(data), size{size} {}
    Grid(size_type size): size(size) {
        data = new T[size];
    }
    Grid(T const& t): size(1) {
        data = new T[1];
        *data = t;
    }
    Grid(size_type size, T const& t): size{size} {
        data = new T[size];
        for (auto it = data, end = data + size; it != end; ++it) *it = t;
    }

    T operator()(size_type idx) const
    {
        return data[idx];
    }

    T& operator()(size_type idx)
    {
        return data[idx];
    }

    T operator[](size_type idx) const
    {
        return data[idx];
    }

    T& operator[](size_type idx)
    {
        return data[idx];
    }

    Grid<T, 1>& operator=(T const& t)
    {
        for (auto it = data, end = data + size; it != end; ++it) *it = t;
        return *this;
    }

    size_type get_size() const { return size; }

    ~Grid() {
        delete[] data;
    }

public:
    Grid(Grid<T, 1> const& other): Grid(other.get_size()) {
        for (auto i = 0; i != size; ++i) data[i] = other[i];
    }
    Grid<T, 1>& operator=(Grid<T, 1> const& other) {
        Grid<T, 1> tmp(other);
        std::swap(this->data, tmp.data);
        std::swap(this->size, tmp.size);
        return *this;
    }
    Grid(Grid<T, 1>&& other): data(other.data), size(other.size()) {
        other.data = nullptr;
        other.size = 0;
    }
    Grid<T, 1>& operator=(Grid<T, 1>&& other) {
        std::swap(this->data, other.data);
        std::swap(this->size, other.size)
        return *this;
    }
};

int main() {
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));

    g2 = g3[1];
    assert(1.0f == g2(1, 1));
    return 0;
}
