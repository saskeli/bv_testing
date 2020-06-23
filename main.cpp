#include <iostream>
#include <vector>
#include <chrono>

#include "bufferedbv.hpp"

#define N 1000000

int main(int, char**) {
    std::cout << "Generating input..." << std::endl;
    std::srand(1337);
    auto vec = new uint32_t[N]();
    auto vals = std::bitset<N>();
    for (size_t i = 0; i < N; i++) {
        vec[i] = std::rand() % (100 + i);
        vals.set(i, std::rand() % 2);
    }

    std::cout << "Timing 2 element buffer" << std::endl;
    auto bv2 = dyn::packed_vector<2>();
    auto t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        bv2.insert(vec[i], vals.test(i));
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\t" << N << " operation in " << duration << "us" << std::endl;

    std::cout << "Timing 4 element buffer" << std::endl;
    auto bv4 = dyn::packed_vector<4>();
    t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        bv4.insert(vec[i], vals.test(i));
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\t" << N << " operation in " << duration << "us" << std::endl;

    std::cout << "Timing 8 element buffer" << std::endl;
    auto bv8 = dyn::packed_vector<8>();
    t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        bv8.insert(vec[i], vals.test(i));
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\t" << N << " operation in " << duration << "us" << std::endl;

    std::cout << "Timing 16 element buffer" << std::endl;
    auto bv16 = dyn::packed_vector<16>();
    t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        bv16.insert(vec[i], vals.test(i));
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\t" << N << " operation in " << duration << "us" << std::endl;

    std::cout << "Timing 32 element buffer" << std::endl;
    auto bv32 = dyn::packed_vector<32>();
    t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        bv32.insert(vec[i], vals.test(i));
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\t" << N << " operation in " << duration << "us" << std::endl;

    std::cout << "Timing 64 element buffer" << std::endl;
    auto bv64 = dyn::packed_vector<64>();
    t1 = std::chrono::high_resolution_clock::now();
    for (size_t i = 0; i < N; i++) {
        bv64.insert(vec[i], vals.test(i));
    }
    t2 = std::chrono::high_resolution_clock::now();
    duration = std::chrono::duration_cast<std::chrono::microseconds>(t2 - t1).count();
    std::cout << "\t" << N << " operation in " << duration << "us" << std::endl;

 }
