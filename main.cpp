#include <chrono>
#include <iostream>
#include <iomanip>
#include <random>
#include <vector>

#include "bufferedbv.hpp"
#include "dynamic.hpp"
#include "spsi.hpp"
#include "succinct_bitvector.hpp"

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<4>, 8192, 16>>
    bbv;

typedef dyn::buffered_packed_vector<8> pv;

typedef dyn::suc_bv sbv;

int8_t get_op(std::vector<uint16_t> &ops, std::mt19937 &gen, uint16_t size) {
    uint16_t selection = gen() % 6;
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
        default:
            ops.push_back(gen());
            return 0;
    }
}

uint8_t execute_op(bbv &buffered_tree, sbv &control_tree,
                   std::vector<uint16_t> &ops, size_t i) {
    uint8_t ret = 0;
    uint16_t selection = ops[i];
    uint64_t s = 0;
    switch (selection) {
        case 0:
            s = buffered_tree.size();
            buffered_tree.insert(s ? ops[i + 1] % s : 0, ops[i + 2]);
            s = control_tree.size();
            control_tree.insert(s ? ops[i + 1] % s : 0, ops[i + 2]);
            ret = 3;
            break;
        case 1:
            s = buffered_tree.size();
            if (s == 0) {
                ret = 2;
                break;
            }
            buffered_tree.remove(ops[i + 1] % buffered_tree.size());
            control_tree.remove(ops[i + 1] % control_tree.size());
            ret = 2;
            break;
        case 2:
            s = buffered_tree.size();
            if (s == 0) {
                ret = 3;
                break;
            }
            buffered_tree.set(ops[i + 1] % buffered_tree.size(), ops[i + 2]);
            control_tree.set(ops[i + 1] % control_tree.size(), ops[i + 2]);
            ret = 3;
            break;
        case 3:
            buffered_tree.push_back(ops[i + 1]);
            control_tree.push_back(ops[i + 1]);
            ret = 2;
            break;
        case 4: {
            s = buffered_tree.size();
            if (s == 0) {
                ret = 2;
                break;
            }
            uint64_t ib_r = ops[i + 1] % buffered_tree.size();
            uint64_t ic_r = ops[i + 1] % control_tree.size();
            uint64_t b_r = buffered_tree.rank(ib_r);
            uint64_t c_r = control_tree.rank(ic_r);
            if (b_r != c_r) {
                std::cout << " Unexpected result of rank(" << ib_r << ") query. Expected " << c_r << ", got " << b_r << std::endl;
                return 0;
            }
            ret = 2; }
            break;
        default:
            s = buffered_tree.size();
            if (s == 0) {
                ret = 2;
                break;
            }
            uint64_t ba_r = buffered_tree.rank(buffered_tree.size());
            uint64_t ca_r = control_tree.rank(control_tree.size());
            if (ba_r != ca_r) {
                std::cout << " Unexpected one count for rank query. Expected " << ca_r << ", got " << ba_r << std::endl;
                return 0;
            }
            if (ba_r == 0) {
                ret = 2;
                break;
            }
            auto loc = ops[i + 1] % ba_r;
            uint64_t b_s = buffered_tree.select(loc);
            uint64_t c_s = control_tree.select(loc);
            if (b_s != c_s) {
                std::cout << " Unexpected result of select(" << loc << ") query. Expected " << c_s << ", got " << b_s << std::endl;
                return 0;
            }
            ret = 2;
            break;
    }

    uint64_t size = control_tree.size();
    if (size != buffered_tree.size()) {
        std::cout << " Expected vector size of " << size << " but found " << buffered_tree.size() << std::endl;
        return 0;
    }
    for (size_t idx = 0; idx < size; idx++) {
        if (control_tree.at(idx) != buffered_tree.at(idx)) {
            std::cout << " Expected " << control_tree.at(idx) << " at position " << idx << std::endl;
            return 0;
        }
    }

    return ret;
}

void output_comparison(bbv &buffered_tree, sbv &control_tree) {
    size_t s_idx = 0;
    while (s_idx < buffered_tree.size() || s_idx < control_tree.size()) {
        std::cout << " pos " << s_idx << ":\n ";
        for (size_t idx = s_idx; idx < s_idx + 64; idx++) {
            if (idx >= control_tree.size()) break;
            std::cout << (control_tree.at(idx) ? 1 : 0);
        }
        std::cout << "\n ";
        for (size_t idx = s_idx; idx < s_idx + 64; idx++) {
            if (idx >= buffered_tree.size()) break;
            std::cout << (buffered_tree.at(idx) == control_tree.at(idx) ? "" : "\033[31m") << (buffered_tree.at(idx) ? 1 : 0) << "\033[0m";
        }
        std::cout << std::endl;
        s_idx += 64;
    }
}

bool run_test(std::vector<uint16_t> &ops) {
    auto buffered_tree = new bbv();
    auto control_tree = new sbv();

    for (size_t i = 0; i < ops[0]; i++) {
        buffered_tree->push_back(i % 2);
        control_tree->push_back(i % 2);
    }

    bool error = false;

    size_t i = 1;
    while (i < ops.size()) {
        if (i == 19) {
            std::cout << "States before:\nBuffered:\n";
            buffered_tree->print();
            std::cout << "Control:\n";
            control_tree->print();
            std::cout << std::endl;
        }
        // */
        uint8_t res = execute_op(*buffered_tree, *control_tree, ops, i);
        if (!res) {
            std::cout << "Problem at " << i << " with:\n";
            for (size_t idx = 0; idx < ops.size(); idx++) {
                std::cout << std::setw(6) << idx << " ";
            }
            std::cout << "\n";
            for (auto v : ops) {
                std::cout << std::setw(6) << v << " ";
            }
            std::cout << std::endl;
            std::cout << std::setw(0);
            output_comparison(*buffered_tree, *control_tree);

            std::cout << "Buffered:\n";
            buffered_tree->print();
            std::cout << "Control:\n";
            control_tree->print();

            error = true;
            break;
        }
        i += res;
    }

    delete buffered_tree;
    delete control_tree;

    return error;
}

bool run_random_test(size_t num_ops, uint16_t initial_size_limit) {
    std::vector<uint16_t> ops;

    std::random_device rd;
    size_t seed = rd();

    std::mt19937 gen(seed);

    auto buffered_tree = new bbv();
    auto control_tree = new sbv();

    uint16_t size = initial_size_limit ? gen() % initial_size_limit : 0;
    ops.push_back(size);

    for (size_t i = 0; i < num_ops; i++) {
        size += get_op(ops, gen, size);
    }

    std::cout << "\r";
    for (auto v : ops) std::cout << v << " ";

    return run_test(ops);
}

void run_manual_test() {
    auto buf = new bbv();
    auto cont = new sbv();
    
    // 145 2 56 1 1 92 2 13 1 1 3 1 3 0 89 1 2 92 1 1 129

    
    for (size_t i = 0; i < 192; i++) {
        buf->push_back(i % 2);
        cont->push_back(i % 2);
    }

    cont->insert(40, 0);
    buf->insert(40, 0);
    std::cout << "=======================================" << std::endl;

    cont->insert(76, 1);
    buf->insert(76, 1);

    std::cout << "=======================================" << std::endl;
    std::cout << "control:" << std::endl;
    cont->print();
    std::cout << "Buffered:" << std::endl;
    buf->print();
    std::cout << "Selects c: " << cont->select(59) << ", b: " << buf->select(59) << std::endl;



    delete buf;
    delete cont;
}

int main(int argc, char **argv) {
    std::cout << "argc: " << argc << std::endl;

    if (argc <= 1) {
        for (size_t i = 0; i < 1000000; i++) {
            if (i % 1000 == 0) std::cout << "\nRunning test " << i << "              " << std::endl;
            if (run_random_test(10, 200)) {
                std::cout << "Ran " << (i + 1) << " tests before terminating" << std::endl;
                break;
            }
        }
    } else if (argc == 2) {
        run_manual_test();
    } else {
        std::vector<uint16_t> ops;
        for (size_t i = 1; i < argc; i++) {
            ops.push_back(atoi(argv[i]));
        }
        if (!run_test(ops)) std::cout << "Passed!" << std::endl;
    }
    
}
