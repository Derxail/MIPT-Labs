#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <algorithm>


void squareFindAddendums(unsigned sum, unsigned array[], unsigned size, unsigned res[2]) {
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


void linearFindAddendums(unsigned sum, unsigned array[], unsigned size, unsigned res[2]) {
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


unsigned array_size = 1'000'000;
unsigned a[1'000'000];


int main() {
    unsigned res[2];

    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> dstr(1, array_size);

    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        a[cnt] = dstr(rng);
    }
    std::sort(a, a + 200'000);

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    unsigned x; 
    unsigned long long time = 0;

    std::ofstream fout;

    /* fout.open("./data/fa-linear.csv");
    fout.clear();
    fout << "n,std,worst\n";

    for (unsigned n = 100; n <= array_size; n += 19998) {
        time = 0;
        for (unsigned cnt = 0; cnt != 10'000; ++cnt) {
            x = dstr(rng) % n;
            begin = std::chrono::steady_clock::now();
            linearFindAddendums(x, a, n, res);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << n << "," << time << ",";

        time = 0;
        x = 0;
        for (unsigned cnt = 0; cnt != 10'000; ++cnt) {
            begin = std::chrono::steady_clock::now();
            linearFindAddendums(x, a, n, res);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << time << '\n';
        std::cout << n << std::endl;
    }
    fout.close(); */
    
    std::cout << "Linear done." << std::endl;

    fout.open("./data/fa-square.csv");
    fout.clear();
    fout << "n,std,worst\n";

    for (unsigned n = 100; n <= array_size; n += 49995) {
        time = 0;
        for (unsigned cnt = 0; cnt < 100; ++cnt) {
            x = dstr(rng) % n;
            begin = std::chrono::steady_clock::now();
            for (unsigned i = 0; i < 30; ++i) squareFindAddendums(x, a, n, res);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        }
        fout << n << "," << (double)time_span.count() / 3000. << ",";

        x = 4'000'000;
        begin = std::chrono::steady_clock::now();
        squareFindAddendums(x, a, n, res);
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << time_span.count() << '\n';
        std::cout << n << std::endl;
    }
    fout.close();

    std::cout << "Square done." << std::endl;
}