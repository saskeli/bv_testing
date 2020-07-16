#include <chrono>
#include <iostream>
#include <vector>

#include "bufferedbv.hpp"
#include "spsi.hpp"
#include "succinct_bitvector.hpp"
#include "dynamic.hpp"

typedef dyn::succinct_bitvector<dyn::spsi<dyn::buffered_packed_vector<8>, 4056, 256>>
    bbv;

typedef dyn::buffered_packed_vector<8> pv;

int main(int, char**) {
    uint64_t size = 10000;
    auto tree = new bbv();

    for (uint64_t i = 0; i < size; i++) {
        auto set = i % 2;
        tree->insert(i, set);
        auto val = tree->at(i);
        if (val != set) {
            std::cout << "1" << std::endl;
            return 1;
        }
        auto s = tree->size();
        if (s != i + 1) {
            std::cout << "2" << std::endl;
            return 1;
        }
    }

    for (uint64_t i = 0; i < size; i++) {
        auto val = tree->at(i);
        if (val != i % 2) {
            std::cout << "3" << std::endl;
            return 1;
        }
    }

    for (uint64_t i = 1; i < size; i++) {
        tree->remove(0);
        auto new_size = tree->size();
        if (size - i != new_size) {
            std::cout << "4" << std::endl;
            return 1;
        }
        bool prev = tree->at(0);
        for (uint64_t j = 1; j < new_size; j++) {
            bool cur = tree->at(j);
            if (prev == cur) {
                std::cout << "problem!" << std::endl;
                tree->print();
            }
            prev = cur;
        }

        if (i == 9882) tree->print();
    }

    delete tree;
}

