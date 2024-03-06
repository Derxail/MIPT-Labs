#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>


unsigned linearSearch(unsigned search_for, unsigned array[], unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        if (array[i] == search_for) return i;
    }
    return size;
}


unsigned nonuniformDistribution(std::default_random_engine &rng, unsigned minmax, unsigned maxmax, unsigned chance_percent) {
    std::uniform_int_distribution<unsigned> uniform1(1, minmax);
    std::uniform_int_distribution<unsigned> uniform2(1, maxmax);
    std::uniform_int_distribution<unsigned> uniform0(1, 100);
    if (uniform0(rng) > chance_percent) {
        return uniform1(rng);
    } else {
        return uniform2(rng);
    }
}


unsigned array_size = 1'000'000;
unsigned a[1'000'000];
unsigned count[1'000'000];
unsigned ran[500'000];


int main() {
    unsigned repeat = 10'000;

    unsigned seed = 1001;
    unsigned max_value = array_size;
    unsigned chance_percent = 20;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> uniform(1, max_value);

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);

    unsigned x;
    unsigned long long time;
    unsigned i;
    std::ofstream fout;

    unsigned dn = (array_size - 100) / 20;

    fout.open("./data/freq-linear-uniform-0.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = uniform(rng);
            begin = std::chrono::steady_clock::now();
            linearSearch(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform 0 done." << std::endl;


    /* fout.open("./data/freq-linear-uniform-a.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = uniform(rng);
            begin = std::chrono::steady_clock::now();
            linearSearchA(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform A done." << std::endl;

    fout.open("./data/freq-linear-uniform-b.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = uniform(rng);
            begin = std::chrono::steady_clock::now();
            linearSearchB(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform B done." << std::endl;

    fout.open("./data/freq-linear-uniform-c.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            count[cnt] = 0;
        }
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = uniform(rng);
            begin = std::chrono::steady_clock::now();
            linearSearchC(x, a, n, count);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform C done." << std::endl; */


    /*fout.open("./data/freq-linear-binomial-0.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        //std::shuffle(&a[0], &a[n], rng);
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = nonuniformDistribution(rng, 100'000, 1'000'000, chance_percent);
            begin = std::chrono::steady_clock::now();
            i = linearSearch(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
        }
        
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Nonuniform 0 done." << std::endl;

    fout.open("./data/freq-linear-binomial-a.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        //std::shuffle(&a[0], &a[n], rng);
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = nonuniformDistribution(rng, 100'000, 1'000'000, chance_percent);
            begin = std::chrono::steady_clock::now();
            i = linearSearch(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
            if (i != 0) {
                std::swap(a[0], a[i]);
            }
        }
        
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Nonuniform A done." << std::endl;

    fout.open("./data/freq-linear-binomial-b.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        //std::shuffle(&a[0], &a[n], rng);
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = nonuniformDistribution(rng, 100'000, 1'000'000, chance_percent);
            begin = std::chrono::steady_clock::now();
            i = linearSearch(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
            if (i != 0) {
                std::swap(a[i - 1], a[i]);
            }
        }
        
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Nonuniform B done." << std::endl;

    fout.open("./data/freq-linear-binomial-c.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            count[cnt] = 0;
        }
        for (unsigned cnt = 0; cnt < n; ++cnt) {
            a[cnt] = uniform(rng);
        }
        //std::shuffle(&a[0], &a[n], rng);
        time = 0;
        for (unsigned cnt = 0; cnt != repeat; ++cnt) {
            x = nonuniformDistribution(rng, 100'000, 1'000'000, chance_percent);
            begin = std::chrono::steady_clock::now();
            i = linearSearch(x, a, n);
            end = std::chrono::steady_clock::now();
            time_span = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
            time += time_span.count();
            ++count[i];
            if (i != 0) {
                if (count[i] > count[i - 1]) {
                    std::swap(a[i - 1], a[i]);
                }
            }
        }
        
        fout << n << "," << time << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Nonuniform C done." << std::endl;*/
}