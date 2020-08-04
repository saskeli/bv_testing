#include <iostream>
#include <random>
#include <sstream>

#include "bufferedbv.hpp"
#include "dynamic.hpp"
#include "spsi.hpp"
#include "succinct_bitvector.hpp"

typedef dyn::suc_bv sbv;

typedef dyn::succinct_bitvector<
    dyn::spsi<dyn::buffered_packed_vector<8>, 8192, 16>>
    bbv;

int main(int argc, char **argv) {

    std::random_device rd;
    std::mt19937 gen(rd());

    if (argc < 2) {
        std::cerr << "Number of elements required" << std::endl;
        return 1;
    }

    std::istringstream ss(argv[1]);
    int x;
    if (!(ss >> x)) {
        std::cerr << "Invalid number: " << argv[1] << '\n';
        return 1;
    }

    auto tree = new bbv();
    tree->push_back(0);

    for (size_t i = 1; i < x; i++) {
        tree->insert(gen() % i, gen() % 2);
    }

    std::cout << "Tree with " << tree->size() << " elements and " << tree->rank(x - 1) << " ones. Taking " << tree->bit_size() << " bits of space." << std::endl;

}