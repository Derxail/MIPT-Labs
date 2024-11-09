#include <iostream>

// Это было... сложно
template<int P>
float pow(int n) {
    if (P % 2 == 0) return pow<P / 2>(n) * pow<P / 2>(n);
    else return pow<(0 < P) - (P < 0)>(n) * pow<P - ((0 < P) - (P < 0))>(n);
}

template<>
float pow<1>(int n) {
    return n;
}

template<>
float pow<0>(int n) {
    return 1;
}

template<>
float pow<-1>(int n) {
    return (float)1 / n;
}

int main() {
    std::cout << pow<1>(2) << std::endl;
    std::cout << pow<-1>(2) << std::endl;
    std::cout << pow<0>(2) << std::endl;
    std::cout << pow<10>(2) << std::endl;
    std::cout << pow<-10>(2) << std::endl;
    return 0;
}
