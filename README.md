# Attempt at a buffered leaf bitvector implementation for [DYNAMIC](https://github.com/xxsds/DYNAMIC)

## Based on prvious work by Uula: [dynamic-b-tree-bit-vector](https://github.com/uulau/dynamic-b-tree-bit-vector)

Currently `insert`, `remove`, `at`, `rank`, `select`, `push_back`, `psum` and `set` have efficient buffered implementations that work.

Initial benchmarking indicates that this buffered implementation is significantly faster that the "dynamic succinct bitvector" structure of DYNAMIC. 

A lagre portion of this speed increase is due to using a bit vector tailored data structure instead of the more general packed_vector structure of DYNAMIC. Essentially `% int_per_word` and `/ int_per_word` can be changed to `& 63` and `>> 6`. When similar changes are done to DYNAMIC: [https://github.com/saskeli/DYNAMIC/tree/breaking_speed](https://github.com/saskeli/DYNAMIC/tree/breaking_speed), the succinct bit vectors speed up significantly.

Buffering does also seem to provide a significant benefit to insert and remove operations without massive slowdowns for other operations. This does require more testing tho.

Space requirement of leaves should increase by `8 + 32 * k` bits where `k` is the buffer size. For the entire tree this should be no more than `(1 + b/n) * (8 + 32 * k)` bits where `n` is the number of elements int he tree and `b` the b-value for the leaves. How significant this increase is needs to be determined.

## TODO:

* Possibly create tests for non-core operations to ensure that they work as expected

* Read through code to clean up hacks

* More benchmarking

**Note:** I have no idea how Cmake works. But it seems to...
