#include "../bufferedbv.hpp"
#include "dynamic.hpp"
#include "gtest.h"
#include "helpers.hpp"
#include "spsi.hpp"
#include "succinct_bitvector.hpp"

using namespace dyn;

typedef succinct_bitvector<spsi<buffered_packed_vector<18>, 8192, 16>> bbv;
typedef buffered_packed_vector<8> pv;

TEST(PV, push_back) { pv_pushback_test<pv>(); }

TEST(PV, insert) { pv_insert_test<pv>(); }

TEST(PV, remove) { pv_remove_test<pv>(); }

TEST(PV, Insertion10) { insert_test<pv>(10); }

TEST(PV, Insertion100) { insert_test<pv>(100); }

TEST(PV, Insertion1000) { insert_test<pv>(1000); }

TEST(PV, Insertion10000) { insert_test<pv>(10000); }

TEST(PV, Mixture10) { mixture_test<pv>(10); }

TEST(PV, Mixture100) { mixture_test<pv>(100); }

TEST(PV, Mixture1000) { mixture_test<pv>(1000); }

TEST(PV, Mixture10000) { mixture_test<pv>(10000); }

TEST(PV, Rank10) { rank_test<pv>(10); }

TEST(PV, Rank100) { rank_test<pv>(100); }

TEST(PV, Rank1000) { rank_test<pv>(1000); }

TEST(PV, Rank10000) { rank_test<pv>(10000); }

TEST(PV, Remove10) { remove_test<pv>(10); }

TEST(PV, Remove100) { remove_test<pv>(100); }

TEST(PV, Remove1000) { remove_test<pv>(1000); }

TEST(PV, Remove10000) { remove_test<pv>(10000); }

TEST(PV, Update10) { update_test<pv>(10); }

TEST(PV, Update100) { update_test<pv>(100); }

TEST(PV, Update1000) { update_test<pv>(1000); }

TEST(PV, Update10000) { update_test<pv>(10000); }

TEST(PV, Select10) { select_test<pv>(10); }

TEST(PV, Select100) { select_test<pv>(100); }

TEST(PV, Select1000) { select_test<pv>(1000); }

TEST(PV, Select10000) { select_test<pv>(10000); }

TEST(BBV, Random1) {
    std::vector<uint16_t> ops{3, 1, 0, 0, 1, 1, 2, 0, 0, 1,
                              0, 2, 0, 1, 3, 0, 0, 0, 1};
    run_test<bbv>(ops);
}

TEST(BBV, Random2) {
    std::vector<uint16_t> ops{1, 3, 1, 1, 1, 1, 0, 2, 0, 1, 3,
                              0, 1, 0, 3, 0, 0, 0, 1, 5, 0};
    run_test<bbv>(ops);
}

TEST(BBV, Random3) {
    std::vector<uint16_t> ops{47, 3, 1,     5, 15391, 4, 19, 3, 0, 5, 10556, 4,
                              47, 5, 27092, 5, 24392, 4, 3,  0, 3, 1};
    run_test<bbv>(ops);
}

TEST(BBV, Random4) {
    std::vector<uint16_t> ops{98, 5,  21266, 1, 64, 2, 9, 1,  3, 1, 5, 26631,
                              0,  87, 1,     2, 94, 0, 1, 63, 3, 1, 5, 4707};
    run_test<bbv>(ops);
}

TEST(BBV, Random5) {
    std::vector<uint16_t> ops{34, 1,  5, 5, 54003, 1, 5, 3, 1,     3, 1,
                              4,  19, 3, 0, 0,     5, 1, 5, 17609, 4, 8};
    run_test<bbv>(ops);
}

TEST(BBV, Insertion10) { insert_test<bbv>(10); }

TEST(BBV, Insertion100) { insert_test<bbv>(100); }

TEST(BBV, Insertion1000) { insert_test<bbv>(1000); }

TEST(BBV, Insertion10000) { insert_test<bbv>(10000); }

TEST(BBV, Insertion100000) { insert_test<bbv>(100000); }

TEST(BBV, Insertion1000000) { insert_test<bbv>(1000000); }

TEST(BBV, Mixture10) { mixture_test<bbv>(10); }

TEST(BBV, Mixture100) { mixture_test<bbv>(100); }

TEST(BBV, Mixture1000) { mixture_test<bbv>(1000); }

TEST(BBV, Mixture10000) { mixture_test<bbv>(10000); }

TEST(BBV, Rank10) { rank_test<bbv>(10); }

TEST(BBV, Rank100) { rank_test<bbv>(100); }

TEST(BBV, Rank1000) { rank_test<bbv>(1000); }

TEST(BBV, Rank10000) { rank_test<bbv>(10000); }

TEST(BBV, Rank100000) { rank_test<bbv>(100000); }

TEST(BBV, Rank1000000) { rank_test<bbv>(1000000); }

TEST(BBV, Remove10) { remove_test<bbv>(10); }

TEST(BBV, Remove100) { remove_test<bbv>(100); }

TEST(BBV, Remove1000) { remove_test<bbv>(1000); }

TEST(BBV, Remove10000) { remove_test<bbv>(10000); }

TEST(BBV, Remove100000) { remove_test<bbv>(100000); }

TEST(BBV, Remove1000000) { remove_test<bbv>(1000000); }

TEST(BBV, Update10) { update_test<bbv>(10); }

TEST(BBV, Update100) { update_test<bbv>(100); }

TEST(BBV, Update1000) { update_test<bbv>(1000); }

TEST(BBV, Update10000) { update_test<bbv>(10000); }

TEST(BBV, Update100000) { update_test<bbv>(100000); }

TEST(BBV, Update1000000) { update_test<bbv>(1000000); }

TEST(BBV, Select10) { select_test<bbv>(10); }

TEST(BBV, Select100) { select_test<bbv>(100); }

TEST(BBV, Select1000) { select_test<bbv>(1000); }

TEST(BBV, Select10000) { select_test<bbv>(10000); }

TEST(BBV, Select100000) { select_test<bbv>(100000); }

TEST(BBV, Select1000000) { select_test<bbv>(1000000); }