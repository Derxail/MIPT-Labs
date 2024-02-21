#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>


unsigned linearSearchA(unsigned search_for, unsigned array[], unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        if (array[i] == search_for) {
            if (i != 0) {
                unsigned temp = array[0];
                array[0] = array[i];
                array[i] = temp;
            }
            return i;
        }
    }
    return size;
}


unsigned linearSearchB(unsigned search_for, unsigned array[], unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        if (array[i] == search_for) {
            if (i != 0) {
                unsigned temp = array[i - 1];
                array[i - 1] = array[i];
                array[i] = temp;
            }
            return i;
        }
    }
    return size;
}


unsigned linearSearchC(unsigned search_for, unsigned array[], unsigned size, unsigned count[]) {
    for (unsigned i = 0; i < size; ++i) {
        if (array[i] == search_for) {
            if (i != 0) {
                if (count[i] > count[i - 1]) {
                    unsigned temp = array[0];
                    array[0] = array[i];
                    array[i] = temp;
                }
            }
            return i;
        }
    }
    return size;
}


int main() {
    unsigned array_size = 100000;
    unsigned a[100000];
    unsigned count[100000];

    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> uniform(1, 100'000);
    std::binomial_distribution<unsigned> binomial(99'999, 0.5);

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::ofstream fout;

    fout.open("freq-linear-uniform-a.csv");
    fout.clear();
    fout << "n,std\n";

    unsigned dn = (array_size - 100) / 100;

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearchA(uniform(rng), a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform A done." << std::endl;

    fout.open("freq-linear-uniform-b.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearchB(uniform(rng), a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform B done." << std::endl;

    fout.open("freq-linear-uniform-c.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            count[cnt] = 0;
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearchC(uniform(rng), a, n, count);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform C done." << std::endl;


    fout.open("freq-linear-binomial-a.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearchA(binomial(rng) + 1, a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Binomial A done." << std::endl;

    fout.open("freq-linear-binomial-b.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearchB(binomial(rng) + 1, a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Binomial B done." << std::endl;

    fout.open("freq-linear-binomial-c.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            count[cnt] = 0;
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearchC(binomial(rng) + 1, a, n, count);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Binomial C done." << std::endl;
}