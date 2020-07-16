# Attempt at a buffered leaf bitvector implementation for [DYNAMIC](https://github.com/xxsds/DYNAMIC)

## Based on prvious work by Uula: [dynamic-b-tree-bit-vector](https://github.com/uulau/dynamic-b-tree-bit-vector)

Currently `insert`, `remove`, `at`, `rank`, `select`, `push_back`, `psum` and `set` have reasonably efficient buffered implementations that work most of the time.

All of the implementations are likely buggy and most buffer sizes will not yield a green test suite.

## TODO:

* Make more tests

* Fix broken stuff

* Do some code optimizations (e.g. when to sort the buffer?)

* Figure out if it's actually faster than DYNAMIC

* Make the rest of the opearations consider the buffered elements

**Note:** I have no idea how Cmake works. But it seems to...
