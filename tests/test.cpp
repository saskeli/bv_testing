#include "gtest.h"
#include "helpers.hpp"
#include "succinct_bitvector.hpp"
#include "../bufferedbv.hpp"
#include "spsi.hpp"
#include "dynamic.hpp"

using namespace dyn;

typedef succinct_bitvector<spsi<buffered_packed_vector<18>, 8192, 16>> bbv;
typedef buffered_packed_vector<8> pv;

TEST(PV, push_back) {
    pv_pushback_test<pv>();
}

TEST(PV, insert) {
    pv_insert_test<pv>();
}

TEST(PV, remove) {
    pv_remove_test<pv>();
}

TEST(PV, Insertion10) {
    insert_test<pv>(10);
}

TEST(PV, Insertion100) {
	insert_test<pv>(100);
}

TEST(PV, Insertion1000) {
	insert_test<pv>(1000);
}

TEST(PV, Insertion10000) {
	insert_test<pv>(10000);
}

TEST(PV, Mixture10) {
	mixture_test<pv>(10);
}

TEST(PV, Mixture100) {
	mixture_test<pv>(100);
}

TEST(PV, Mixture1000) {
	mixture_test<pv>(1000);
}

TEST(PV, Mixture10000) {
	mixture_test<pv>(10000);
}

TEST(PV, Rank10) {
	rank_test<pv>(10);
}

TEST(PV, Rank100) {
	rank_test<pv>(100);
}

TEST(PV, Rank1000) {
	rank_test<pv>(1000);
}

TEST(PV, Rank10000) {
	rank_test<pv>(10000);
}

TEST(PV, Remove10) {
	remove_test<pv>(10);
}

TEST(PV, Remove100) {
	remove_test<pv>(100);
}

TEST(PV, Remove1000) {
	remove_test<pv>(1000);
}

TEST(PV, Remove10000) {
	remove_test<pv>(10000);
}

TEST(PV, Update10) {
	update_test<pv>(10);
}

TEST(PV, Update100) {
	update_test<pv>(100);
}

TEST(PV, Update1000) {
	update_test<pv>(1000);
}

TEST(PV, Update10000) {
	update_test<pv>(10000);
}

TEST(PV, Select10) {
	select_test<pv>(10);
}

TEST(PV, Select100) {
	select_test<pv>(100);
}

TEST(PV, Select1000) {
	select_test<pv>(1000);
}

TEST(PV, Select10000) {
	select_test<pv>(10000);
}

TEST(BBV, Insertion10) {
	insert_test<bbv>(10);
}

TEST(BBV, Insertion100) {
	insert_test<bbv>(100);
}

TEST(BBV, Insertion1000) {
	insert_test<bbv>(1000);
}

TEST(BBV, Insertion10000) {
	insert_test<bbv>(10000);
}

TEST(BBV, Insertion100000) {
	insert_test<bbv>(100000);
}

TEST(BBV, Insertion1000000) {
	insert_test<bbv>(1000000);
}

TEST(BBV, Mixture10) {
	mixture_test<bbv>(10);
}

TEST(BBV, Mixture100) {
	mixture_test<bbv>(100);
}

TEST(BBV, Mixture1000) {
	mixture_test<bbv>(1000);
}

TEST(BBV, Mixture10000) {
	mixture_test<bbv>(10000);
}

TEST(BBV, Mixture100000) {
	mixture_test<bbv>(100000);
}
/*
TEST(BBV, Mixture1000000) {
	mixture_test<bbv>(1000000);
}*/

TEST(BBV, Rank10) {
	rank_test<bbv>(10);
}

TEST(BBV, Rank100) {
	rank_test<bbv>(100);
}

TEST(BBV, Rank1000) {
	rank_test<bbv>(1000);
}

TEST(BBV, Rank10000) {
	rank_test<bbv>(10000);
}

TEST(BBV, Rank100000) {
	rank_test<bbv>(100000);
}

TEST(BBV, Rank1000000) {
	rank_test<bbv>(1000000);
}

TEST(BBV, Remove10) {
	remove_test<bbv>(10);
}

TEST(BBV, Remove100) {
	remove_test<bbv>(100);
}

TEST(BBV, Remove1000) {
	remove_test<bbv>(1000);
}

TEST(BBV, Remove10000) {
	remove_test<bbv>(10000);
}

TEST(BBV, Remove100000) {
	remove_test<bbv>(100000);
}

TEST(BBV, Remove1000000) {
	remove_test<bbv>(1000000);
}

TEST(BBV, Update10) {
	update_test<bbv>(10);
}

TEST(BBV, Update100) {
	update_test<bbv>(100);
}

TEST(BBV, Update1000) {
	update_test<bbv>(1000);
}

TEST(BBV, Update10000) {
	update_test<bbv>(10000);
}

TEST(BBV, Update100000) {
	update_test<bbv>(100000);
}

TEST(BBV, Update1000000) {
	update_test<bbv>(1000000);
}

TEST(BBV, Select10) {
	select_test<bbv>(10);
}

TEST(BBV, Select100) {
	select_test<bbv>(100);
}

TEST(BBV, Select1000) {
	select_test<bbv>(1000);
}

TEST(BBV, Select10000) {
	select_test<bbv>(10000);
}

TEST(BBV, Select100000) {
	select_test<bbv>(100000);
}

TEST(BBV, Select1000000) {
	select_test<bbv>(1000000);
}

TEST(CTRL, Insertion10) {
	insert_test<suc_bv>(10);
}

TEST(CTRL, Insertion100) {
	insert_test<suc_bv>(100);
}

TEST(CTRL, Insertion1000) {
	insert_test<suc_bv>(1000);
}

TEST(CTRL, Insertion10000) {
	insert_test<suc_bv>(10000);
}

TEST(CTRL, Insertion100000) {
	insert_test<suc_bv>(100000);
}

TEST(CTRL, Insertion1000000) {
	insert_test<suc_bv>(1000000);
}

TEST(CTRL, Mixture10) {
	mixture_test<suc_bv>(10);
}

TEST(CTRL, Mixture100) {
	mixture_test<suc_bv>(100);
}

TEST(CTRL, Mixture1000) {
	mixture_test<suc_bv>(1000);
}

TEST(CTRL, Mixture10000) {
	mixture_test<suc_bv>(10000);
}

TEST(CTRL, Mixture100000) {
	mixture_test<suc_bv>(100000);
}
/*
TEST(CTRL, Mixture1000000) {
	mixture_test<suc_bv>(1000000);
}*/

TEST(CTRL, Rank10) {
	rank_test<suc_bv>(10);
}

TEST(CTRL, Rank100) {
	rank_test<suc_bv>(100);
}

TEST(CTRL, Rank1000) {
	rank_test<suc_bv>(1000);
}

TEST(CTRL, Rank10000) {
	rank_test<suc_bv>(10000);
}

TEST(CTRL, Rank100000) {
	rank_test<suc_bv>(100000);
}

TEST(CTRL, Rank1000000) {
	rank_test<suc_bv>(1000000);
}

TEST(CTRL, Remove10) {
	remove_test<suc_bv>(10);
}

TEST(CTRL, Remove100) {
	remove_test<suc_bv>(100);
}

TEST(CTRL, Remove1000) {
	remove_test<suc_bv>(1000);
}

TEST(CTRL, Remove10000) {
	remove_test<suc_bv>(10000);
}

TEST(CTRL, Remove100000) {
	remove_test<suc_bv>(100000);
}

TEST(CTRL, Remove1000000) {
	remove_test<suc_bv>(1000000);
}

TEST(CTRL, Update10) {
	update_test<suc_bv>(10);
}

TEST(CTRL, Update100) {
	update_test<suc_bv>(100);
}

TEST(CTRL, Update1000) {
	update_test<suc_bv>(1000);
}

TEST(CTRL, Update10000) {
	update_test<suc_bv>(10000);
}

TEST(CTRL, Update100000) {
	update_test<suc_bv>(100000);
}

TEST(CTRL, Update1000000) {
	update_test<suc_bv>(1000000);
}

TEST(CTRL, Select10) {
	select_test<suc_bv>(10);
}

TEST(CTRL, Select100) {
	select_test<suc_bv>(100);
}

TEST(CTRL, Select1000) {
	select_test<suc_bv>(1000);
}

TEST(CTRL, Select10000) {
	select_test<suc_bv>(10000);
}

TEST(CTRL, Select100000) {
	select_test<suc_bv>(100000);
}

TEST(CTRL, Select1000000) {
    select_test<suc_bv>(1000000);
}