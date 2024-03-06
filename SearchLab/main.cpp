#include <iostream>
#include <chrono>
#include <random>
#include <fstream>
#include <string>


unsigned linearSearch(int search_for, unsigned array[], unsigned size) {
    for (unsigned i = 0; i < size; ++i) {
        if (array[i] == search_for) return i;
    }
    return size;
}


unsigned binarySearch(int search_for, unsigned array[], unsigned lhs, unsigned rhs) {
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


void squareFindAddendums(int sum, unsigned array[], unsigned size, unsigned res[2]) {
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


void linearFindAddendums(int sum, unsigned array[], unsigned size, unsigned res[2]) {
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
    unsigned array_size = 100000;
    unsigned a[100000];
    unsigned count[100000];
    unsigned res[2];

    unsigned dn = (array_size - 100) / 100;

    unsigned seed = 1001;
    std::default_random_engine rng(seed);
    std::uniform_int_distribution<unsigned> uniform(1, 100'000);
    std::binomial_distribution<unsigned> binomial(99'999, 0.5);

    for (unsigned cnt = 0; cnt < array_size; ++cnt) {
        a[cnt] = uniform(rng);
    }

    auto begin = std::chrono::steady_clock::now();
    auto end = std::chrono::steady_clock::now();
    auto time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);

    std::ofstream fout;

    fout.open("linear.csv");
    fout.clear();
    fout << "n,std,worst\n";
    
    for (unsigned n = 100; n <= array_size; n += 1999) {
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearch(uniform(rng), a, n);
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
    fout << "n,std,worst\n";

    std::sort(a, a + 200'000);

    for (unsigned n = 100; n <= array_size; n += 1500) {
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 5'000'000; ++cnt) {
            binarySearch(uniform(rng), a, 0, n);
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

    fout.open("fa-linear.csv");
    fout.clear();
    fout << "n,std,worst\n";

    for (unsigned n = 100; n <= array_size; n += 1999) {
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 100'000; ++cnt) {
            linearFindAddendums(uniform(rng), a, n, res);
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
    fout << "n,std,worst\n";

    for (unsigned n = 100; n <= array_size; n += 1999) {
        begin = std::chrono::steady_clock::now();
        squareFindAddendums(uniform(rng), a, n, res);
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() / 10 << ",";

        begin = std::chrono::steady_clock::now();
        squareFindAddendums(0, a, n, res);
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << time_span.count() << '\n';
        std::cout << n << std::endl;
    }
    fout.close();

    std::cout << "Square done." << std::endl;

    fout.open("freq-linear-uniform-0.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearch(uniform(rng), a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform 0 done." << std::endl;


    fout.open("freq-linear-uniform-a.csv");
    fout.clear();
    fout << "n,std\n";

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


    fout.open("freq-linear-binomial-0.csv");
    fout.clear();
    fout << "n,std\n";

    for (unsigned n = 100; n <= array_size; n += dn) {
        for (unsigned cnt = 0; cnt < array_size; ++cnt) {
            a[cnt] = uniform(rng);
        }
        begin = std::chrono::steady_clock::now();
        for (unsigned cnt = 0; cnt != 200'000; ++cnt) {
            linearSearch(binomial(rng), a, n);
        }
        end = std::chrono::steady_clock::now();
        time_span = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
        fout << n << "," << time_span.count() << "\n";
        std::cout << n << std::endl;
    }
    fout.close();
    
    std::cout << "Uniform 0 done." << std::endl;

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