#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


unsigned linearSearch(unsigned search_for, unsigned array[], unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        if (array[i] == search_for) return i;
    }
    return size;
}


unsigned binarySearch(unsigned search_for, unsigned array[], unsigned lhs, unsigned rhs) {
    unsigned fail = rhs;
    unsigned mid;
    while (rhs - lhs > 1) {
        mid = (rhs + lhs) / 2;
        if (array[mid] < search_for) lhs = mid + 1;
        else if (array[mid] > search_for) rhs = mid;
        else return mid;
    }
    if (array[lhs] == search_for) return lhs;
    return fail;
}

unsigned array_size = 1'000'000;
unsigned a[1'000'000];

int main() {
    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(1, array_size);
    
    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        a[cnt] = dstr(rng);
    }

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    unsigned x; 
    unsigned long long time = 0;

    std::ofstream fout;

    fout.open("./data/linear.csv");
    fout.clear();
    fout << "n,std,worst\n";
    
    for (unsigned n = 100; n <= array_size; n += 19998) {
        time = 0;
        for (unsigned cnt = 0; cnt != 10'000; ++cnt) {
            x = dstr(rng);
            begin = std::chrono::steady_clock::now();
            linearSearch(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << n << "," << time << ",";

        time = 0;
        x = 0;
        for (unsigned cnt = 0; cnt != 10'000; ++cnt) {
            begin = std::chrono::steady_clock::now();
            linearSearch(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << time << '\n';
        std::cout << n << std::endl;
    }
    fout.close();

    std::cout << std::endl << "Linear done" << std::endl;

    fout.open("./data/binary.csv");
    fout.clear();
    fout << "n,std,worst\n";

    std::sort(a, a + array_size);

    for (unsigned n = 100; n <= array_size; n += 9999) {
        time = 0;
        for (unsigned cnt = 0; cnt != 2'000'000; ++cnt) {
            if (cnt % 1000 == 0) x = dstr(rng) % n;
            begin = std::chrono::steady_clock::now();
            binarySearch(x, a, 0, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << n << "," << time << ",";

        time = 0;
        x = 4'000'000;
        for (unsigned cnt = 0; cnt != 2'000'000; ++cnt) {
            begin = std::chrono::steady_clock::now();
            binarySearch(x, a, 0, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << time << '\n';
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Binary done";
}