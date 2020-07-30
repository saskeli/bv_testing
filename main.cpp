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
    dyn::spsi<dyn::buffered_packed_vector<3>, 8192, 16>>
    bbv3;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<4>, 8192, 16>>
    bbv4;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<5>, 8192, 16>>
    bbv5;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<6>, 8192, 16>>
    bbv6;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<7>, 8192, 16>>
    bbv7;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<8>, 8192, 16>>
    bbv8;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<9>, 8192, 16>>
    bbv9;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<10>, 8192, 16>>
    bbv10;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<11>, 8192, 16>>
    bbv11;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<12>, 8192, 16>>
    bbv12;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<16>, 8192, 16>>
    bbv16;

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
    auto a = {0, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 16};
    for (auto v : a) std::cout << std::setw(w) << v;
    std::cout << std::endl;
    for (size_t i = 0; i < 1000; i++) {
        std::cout << "      ";
        std::vector<uint32_t> ops;
        uint16_t size = gen() % initial_size_limit;
        ops.push_back(size);
        for (size_t i = 0; i < num_ops; i++) {
            size += get_op(ops, gen, size);
        }
        if (run_test<sbv, bbv3>(ops)) break;
        std::cout << std::setw(w) << run_timing<sbv>(ops);
        if (run_test<bbv3, bbv4>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv3>(ops);
        if (run_test<bbv4, bbv5>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv4>(ops);
        if (run_test<bbv5, bbv6>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv5>(ops);
        if (run_test<bbv6, bbv7>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv6>(ops);
        if (run_test<bbv7, bbv8>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv7>(ops);
        if (run_test<bbv8, bbv9>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv8>(ops);
        if (run_test<bbv9, bbv10>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv9>(ops);
        if (run_test<bbv10, bbv11>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv10>(ops);
        if (run_test<bbv11, bbv12>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv11>(ops);
        if (run_test<bbv12, bbv16>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv12>(ops);
        if (run_test<bbv16, sbv>(ops)) break;
        std::cout << std::setw(w) << run_timing<bbv16>(ops);
        
        std::cout << std::endl;
    }
    return 0;
}
