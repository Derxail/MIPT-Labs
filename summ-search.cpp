#include <iostream>
#include <chrono>
#include <random>
#include <fstream>


void squareFindAddendums(int sum, int array[], unsigned size, unsigned res[2]) {
    for (unsigned i = 0; i < size; ++i) {
        for (unsigned j = i + 1; j < size; ++j) {
            if (array[i] + array[j] == sum) {
                res[0] = i;
                res[1] = j;
                return;
            }
        }
    }
    res[0] = 0;
    res[1] = 0;
}


void linearFindAddendums(int sum, int array[], unsigned size, unsigned res[2]) {
    unsigned i = 0, j = size - 1;
    while (i < j) {
        if (array[i] + array[j] < sum) ++i;
        else if (array[i] + array[j] > sum) --j;
        else {
            res[0] = i;
            res[1] = j;
            return;
        }
    }
    res[0] = 0;
    res[1] = 0;
}


int main() {
    int array_size = 200000;
    int a[200000];
    unsigned res[2];

    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(1, 200'000);

    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        a[cnt] = dstr(rng);
    }
    std::sort(a, a + 200'000);

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::ofstream fout;

    fout.open("fa-linear.csv");
    fout.clear();
    fout << "n, std, worst\n";

    for (unsigned n = 100; n <= array_size; n += 1999) {
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 100'000; ++cnt) {
            linearFindAddendums(dstr(rng), a, n, res);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << ",";

        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 100'000; ++cnt) {
            linearFindAddendums(0, a, n, res);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << time_span.count() << '\n';
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Linear done." << std::endl;

    fout.open("fa-square.csv");
    fout.clear();
    fout << "n, std, worst\n";

    for (unsigned n = 100; n <= array_size; n += 1999) {
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 100'000; ++cnt) {
            squareFindAddendums(dstr(rng), a, n, res);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << ",";

        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 100'000; ++cnt) {
            squareFindAddendums(0, a, n, res);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << time_span.count() << '\n';
        std::cout << n << std::endl;
    }
    fout.close();

    std::cout << "Square done." << std::endl;
}