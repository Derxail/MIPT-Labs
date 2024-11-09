#include <cassert>
#include <algorithm>
#include <iostream>

template<typename T, unsigned dim>
class Grid final
{
public:
    using value_type = T;
    using size_type = unsigned;
    Grid(Grid<T, dim>&&) = delete;
    Grid<T, dim>& operator=(Grid<T, dim>&&) = delete;
private:
    Grid<T, dim - 1>* data;
    size_type size;
public:
    Grid(Grid<T, dim - 1> *data , size_type size): data(data) {}
    template<typename... tail> Grid(size_type size, tail... rest): size{size} {
        data = static_cast<Grid<T, dim - 1> *>(operator new[](size * sizeof(Grid<T, dim - 1>)));
        for (auto it = data, end = data + size; it != end; ++it) new(it) Grid<T, dim - 1>(rest...);
    }
    Grid(T const& t): size(1) {
        data = new Grid<T, dim - 1>(t);
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
        delete data;
    }
public:
    Grid(Grid<T, dim> const& other): size(other.get_size()) {
        data = static_cast<Grid<T, dim - 1> *>(operator new[](size * sizeof(Grid<T, dim - 1>)));
        for (auto i = 0; i != size; ++i) new(data + i) Grid<T, dim - 1>(other[i]);
    }
    Grid<T, dim>& operator=(Grid<T, dim> const& other) {
        if (other.get_size() != size) {
            size = other.get_size();
            for (auto it = data, end = data + size; it != end; ++it) it->~Grid();
            data = static_cast<Grid<T, dim - 1> *>(operator new[](size * sizeof(Grid<T, dim - 1>)));
        }
        for (auto i = 0; i != size; ++i) data[i] = other[i];
        return *this;
    }
} ;

template<typename T>
class Grid<T, 1> final
{
public:
    using value_type = T;
    using size_type = unsigned;
    Grid(Grid<T, 1>&&) = delete;
    Grid<T, 1>& operator=(Grid<T, 1>&&) = delete;
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
        std::cout << "Grid 1 destroyed" << std::endl;
    }

public:
    Grid(Grid<T, 1> const& other): Grid(other.get_size()) {
        for (auto i = 0; i < size; ++i) data[i] = other[i];
    }
    Grid<T, 1>& operator=(Grid<T, 1> const& other) {
        if (other.get_size() != size) {
            size = other.get_size();
            this->~Grid();
            data = new T[size];
        }
        for (auto i = 0; i < size; ++i) data[i] = other[i];
        return *this;
    }
} ;

int main() {
    Grid<float, 3> const g3(2, 3, 4, 1.0f);
    assert(1.0f == g3(1, 1, 1));
    std::cout << "1";

    Grid<float, 2> g2(2, 5, 2.0f);
    assert(2.0f == g2(1, 1));
    std::cout << "2";

    g2 = g3[1];
    std::cout << 3;
    //assert(1.0f == g2(1, 1));
    std::cout << "done";
}
