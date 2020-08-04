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

typedef dyn::suc_bv sbv;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<8>, 8192, 16>>
    bbv;

void opt_main() {

    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Type\tavg" << std::endl;
    
    uint64_t N = 5e8;
    uint64_t m = 1e6;

    auto tree = new bbv();

    tree->push_back(0);

    for (uint64_t i = 1; i < (N - m); i++) {
        tree->insert(gen() % i, i % 2);
    }

    std::vector<uint32_t> pos;
    std::vector<uint32_t> val;

    for (uint64_t i = 0; i < m; i++) {
        pos.push_back(gen() % (N - (m - i)));
        val.push_back(gen() & 2);
    }

    auto start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        tree->insert(pos[i], val[i]);
    }
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double> elapsed = end - start;
    std::cout << "B-ins\t";
    std::cout << std::setw(5) << (elapsed.count() /  m) << std::endl;

    uint64_t num_ones = 0;
    for (uint64_t i = 0; i < m; i++) {
        pos[i] = gen() % N;
    }

    start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        num_ones += tree->at(pos[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "B-at\t";
    std::cout << std::setw(5) << (elapsed.count() / m) << "\t" << num_ones << std::endl;

    num_ones = 0;
    for (uint64_t i = 0; i < m; i++) {
        pos[i] = gen() % N;
    }

    start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        num_ones += tree->rank(pos[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "B-rank\t";
    std::cout << std::setw(5) << (elapsed.count() / m) << "\t" << num_ones << std::endl;

    num_ones = 0;
    uint64_t limit = tree->rank(N - 1);

    for (uint64_t i = 0; i < m; i++) {
        pos[i] = gen() % limit;
    }
    start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        num_ones += tree->select(pos[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "B-select\t";
    std::cout << std::setw(5) << (elapsed.count() / m) << "\t" << num_ones << std::endl;

    delete tree;

    auto ctree = new sbv();

    tree->push_back(0);

    for (uint64_t i = 1; i < (N - m); i++) {
        ctree->insert(gen() % i, i % 2);
    }

    for (uint64_t i = 0; i < m; i++) {
        pos[i] = gen() % (N - (m - i));
        val[i] = gen() & 2;
    }
    start = std::chrono::steady_clock::now();
    for(uint64_t i = 0; i < m; i++) {
        ctree->insert(pos[i], val[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "U-ins\t";
    std::cout << std::setw(5) << (elapsed.count() / m) << std::endl;

    num_ones = 0;
    for (uint64_t i = 0; i < m; i++) {
        pos[i] = gen() % N;
    }
    start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        num_ones += ctree->at(pos[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "U-at\t";
    std::cout << std::setw(5) << (elapsed.count() / m) << "\t" << num_ones << std::endl;

    num_ones = 0;
    for (uint64_t i = 0; i < m; i++) {
        pos[i] = gen() % N;
    }
    start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        num_ones += ctree->rank(pos[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "C-rank\t";
    std::cout << std::setw(5) << (elapsed.count() / m) << "\t" << num_ones << std::endl;
    
    num_ones = 0;
    limit = ctree->rank(N - 1);

    for (uint64_t i = 0; i < m; i++) {
        pos[i] = gen() % limit;
    }
    start = std::chrono::steady_clock::now();
    for (uint64_t i = 0; i < m; i++) {
        num_ones += ctree->select(pos[i]);
    }
    end = std::chrono::steady_clock::now();
    elapsed = end - start;
    std::cout << "C-select\t";
    std::cout << std::setw(5) << (elapsed.count() / m) << "\t" << num_ones << std::endl;

    delete ctree;
}

int main(int argc, char **argv) {

    if (argc > 1) {
        opt_main();
        return 0;
    }

    std::random_device rd;
    std::mt19937 gen(rd());

    std::cout << "Type\tavg\tmin\tmax" << std::endl;
    
    uint64_t N = 5e8;
    uint64_t out = 1e6;
    uint64_t at = 1e6;

    auto tree = new bbv();

    double tot = 0;
    double min = 1;
    double max = 0;

    tree->push_back(0);

    for (uint64_t i = 1; i < (N - out); i++) {
        tree->insert(gen() % i, i % 2);
    }

    for (uint64_t i = 0; i < out; i++) {
        uint64_t pos = gen() % (N - (out - i));
        uint64_t val = gen() & 2;
        auto start = std::chrono::steady_clock::now();
        tree->insert(pos, val);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "B-ins\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << std::endl;

    tot = 0;
    min = 1;
    max = 0;

    uint64_t num_ones = 0;
    for (uint64_t i = 0; i < at; i++) {
        uint64_t pos = gen() % N;
        auto start = std::chrono::steady_clock::now();
        num_ones += tree->at(pos);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "B-at\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << "\t";
    std::cout << num_ones << std::endl;

    tot = 0;
    min = 1;
    max = 0;

    num_ones = 0;
    for (uint64_t i = 0; i < at; i++) {
        uint64_t pos = gen() % N;
        auto start = std::chrono::steady_clock::now();
        num_ones += tree->rank(pos);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "B-rank\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << "\t";
    std::cout << num_ones << std::endl;

    tot = 0;
    min = 1;
    max = 0;

    num_ones = 0;

    uint64_t limit = tree->rank(N - 1);

    for (uint64_t i = 0; i < at; i++) {
        uint64_t pos = gen() % limit;
        auto start = std::chrono::steady_clock::now();
        num_ones += tree->select(pos);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "B-select\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << "\t";
    std::cout << num_ones << std::endl;

    delete tree;

    auto ctree = new sbv();

    tot = 0;
    min = 1;
    max = 0;

    tree->push_back(0);

    for (uint64_t i = 1; i < (N - out); i++) {
        ctree->insert(gen() % i, i % 2);
    }

    for (uint64_t i = 0; i < out; i++) {
        uint64_t pos = gen() % (N - (out - i));
        uint64_t val = gen() & 2;
        auto start = std::chrono::steady_clock::now();
        ctree->insert(pos, val);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "U-ins\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << std::endl;

    tot = 0;
    min = 1;
    max = 0;

    num_ones = 0;
    for (uint64_t i = 0; i < at; i++) {
        uint64_t pos = gen() % N;
        auto start = std::chrono::steady_clock::now();
        num_ones += ctree->at(pos);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "U-at\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << "\t";
    std::cout << num_ones << std::endl;

    tot = 0;
    min = 1;
    max = 0;

    num_ones = 0;
    for (uint64_t i = 0; i < at; i++) {
        uint64_t pos = gen() % N;
        auto start = std::chrono::steady_clock::now();
        num_ones += ctree->rank(pos);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "B-rank\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << "\t";
    std::cout << num_ones << std::endl;

    tot = 0;
    min = 1;
    max = 0;

    num_ones = 0;

    limit = ctree->rank(N - 1);

    for (uint64_t i = 0; i < at; i++) {
        uint64_t pos = gen() % limit;
        auto start = std::chrono::steady_clock::now();
        num_ones += ctree->select(pos);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed = end - start;
        double time = elapsed.count();
        tot += time;
        min = min < time ? min : time;
        max = max > time ? max : time;
    }
    std::cout << "B-select\t";
    std::cout << std::setw(5) << (tot / out) << "\t";
    std::cout << std::setw(5) << min << "\t";
    std::cout << std::setw(5) << max << "\t";
    std::cout << num_ones << std::endl;

    delete ctree;
}
