#include <chrono>
#include <iomanip>
#include <iostream>
#include <random>
#include <vector>

#include "bufferedbv.hpp"
#include "dynamic.hpp"
#include "spsi.hpp"
#include "succinct_bitvector.hpp"

#include "runners.hpp"

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<1>, 8192, 16>>
    bbv1;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<2>, 8192, 16>>
    bbv2;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<3>, 8192, 16>>
    bbv3;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<4>, 8192, 16>>
    bbv4;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<6>, 8192, 16>>
    bbv6;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<8>, 8192, 16>>
    bbv8;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<16>, 8192, 16>>
    bbv16;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<32>, 8192, 16>>
    bbv32;    

typedef dyn::suc_bv sbv;

int8_t get_op(std::vector<uint32_t> &ops, std::mt19937 &gen, uint32_t size) {
    uint32_t selection = gen() % 7;
    ops.push_back(selection);
    switch (selection) {
        case 0:
            ops.push_back(size ? gen() % size : 0);
            ops.push_back(gen() % 2);
            return 1;
        case 1:
            ops.push_back(size ? gen() % size : 0);
            return -1;
        case 2:
            ops.push_back(size ? gen() % size : 0);
            ops.push_back(gen() % 2);
            return 0;
        case 3:
            ops.push_back(gen() % 2);
            return 1;
        case 4:
            ops.push_back(size ? gen() % size : 0);
            return 0;
        case 5:
            ops.push_back(gen());
            return 0;
        default:
            ops.push_back(size ? gen() % size: 0);
            return 0;
    }
}

int main(int argc, char **argv) {
    
    int w = 12;

    std::random_device rd;
    std::mt19937 gen(rd());

    if (argc > 1) {
        std::vector<uint32_t> b_ops;
        std::vector<uint32_t> c_ops;
        b_ops.push_back(20000);
        c_ops.push_back(20000);
        for (size_t i = 1; i < 7; i++) {
            b_ops.push_back(0);
            b_ops.push_back(0);
            b_ops.push_back(i % 2);
        }
        for (size_t i = 0; i < 20000; i++) {
            b_ops.push_back(6);
            c_ops.push_back(6);
            uint32_t v = gen() % 20000;
            b_ops.push_back(v);
            c_ops.push_back(v);
        }
        std::cout << "Control: " << std::setw(w) << run_timing<sbv>(c_ops) << std::endl;
        std::cout << "Buffer8: " << std::setw(w) << run_timing<bbv8>(b_ops) << std::endl;
        return 0;
    }

    uint32_t initial_size_limit = 100000;
    uint32_t num_ops = 100000;

    std::cout << "  buf:";
    auto a = {0, 1, 2, 3, 4, 6, 8, 16, 32};
    for (auto v : a) std::cout << std::setw(w) << v;
    std::cout << std::endl;
    for (size_t i = 0; i < 100; i++) {
        std::cout << "      ";
        std::vector<uint32_t> ops;
        uint16_t size = gen() % initial_size_limit;
        ops.push_back(size);
        for (size_t i = 0; i < num_ops; i++) {
            size += get_op(ops, gen, size);
        }
        std::cerr << "0, 1:" << std::endl;
        if (run_test<sbv, bbv1>(ops)) break;
        std::cout << std::setw(w) << run_timing<sbv>(ops);
        std::cerr << "1, 2:" << std::endl;
        if (run_test<bbv1, bbv2>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv1>(ops);
        std::cerr << "2, 3:" << std::endl;
        if (run_test<bbv2, bbv3>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv2>(ops);
        std::cerr << "3, 4:" << std::endl;
        if (run_test<bbv3, bbv4>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv3>(ops);
        std::cerr << "4, 6:" << std::endl;
        if (run_test<bbv4, bbv6>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv4>(ops);
        std::cerr << "6, 8:" << std::endl;
        if (run_test<bbv6, bbv8>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv6>(ops);
        std::cerr << "8, 16:" << std::endl;
        if (run_test<bbv8, bbv16>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv8>(ops);
        std::cerr << "16, 32:" << std::endl;
        if (run_test<bbv16, bbv32>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv16>(ops);
        std::cout << std::setw(w) << run_timing<bbv32>(ops);
        
        std::cout << std::endl;
    }
    return 0;
}
