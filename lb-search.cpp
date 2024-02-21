#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


unsigned linearSearch(int search_for, int array[], unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        if (array[i] == search_for) return i;
    }
    return size;
}


unsigned binarySearch(int search_for, int array[], unsigned lhs, unsigned rhs) {
    unsigned fail = rhs;
    unsigned mid;
    while (rhs - lhs > 1) {
        mid = (rhs + lhs) / 2;
        if (array[mid] < search_for) lhs = mid;
        else if (array[mid] > search_for) rhs = mid;
        else return mid;
    }
    if (array[lhs] == search_for) return lhs;
    return fail;
}


int main() {
    int array_size = 200000;
    int a[200000];

    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(1, 200'000);

    unsigned b = 0;
    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        while (true) {
            b = dstr(rng);
            if (b != 125000) break;
        }
        a[cnt] = b;
    }

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::ofstream fout;
    fout.open("linear.csv");
    fout.clear();
    fout << "n, std, worst\n";
    
    for (unsigned n = 100; n <= array_size; n += 1999) {
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearch(dstr(rng), a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << ",";

        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearch(300'000, a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << time_span.count() << '\n';
        std::cout << n << std::endl;
    }
    fout.close();

    std::cout << std::endl << "Linear done" << std::endl;

    fout.open("binary.csv");
    fout.clear();
    fout << "n, std, worst\n";

    std::sort(a, a + 200'000);

    for (unsigned n = 100; n <= array_size; n += 1500) {
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 5'000'000; ++cnt) {
            binarySearch(dstr(rng), a, 0, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << ",";

        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 5'000'000; ++cnt) {
            binarySearch(0, a, 0, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << time_span.count() << '\n';
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Binary done";
}