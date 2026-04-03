# This repository is meant to benchmark my own implementation of wc

I was trying different implementaitions to show how to speed up simple application like wc. Of course it is not 1:1 replacment for system wc because we do not cover all edge cases here. Nevertheless for the prepared test_data my implementation and system `wc` gives exactly the same results.

# Running example 
To test it `just build_all` and `just hyperfine ./test_data/pg2600.txt` from main folder of this repository.
You can clearly see that you get best results using simd with threads. But if you do not have simd branchless approach gives also really got results

# Test
There are unit tests which can be started by `just test`. Requires gtest installed.

# Example results:
## Hyperfine:
```
Summary
  taskset -c 0-11 build/wc_check_mmap_simd_thread_8 ./test_data/pg2600.txt ran
    1.00 ± 0.23 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_2 ./test_data/pg2600.txt
    1.02 ± 0.23 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_16 ./test_data/pg2600.txt
    1.06 ± 0.22 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_4 ./test_data/pg2600.txt
    1.11 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_32 ./test_data/pg2600.txt
    1.14 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_1 ./test_data/pg2600.txt
    1.25 ± 0.36 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_64 ./test_data/pg2600.txt
    1.29 ± 0.31 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_32 ./test_data/pg2600.txt
    1.29 ± 0.31 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_16 ./test_data/pg2600.txt
    1.34 ± 0.32 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_16 ./test_data/pg2600.txt
    1.35 ± 0.34 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_32 ./test_data/pg2600.txt
    1.37 ± 0.33 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_64 ./test_data/pg2600.txt
    1.38 ± 0.30 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_8 ./test_data/pg2600.txt
    1.38 ± 0.37 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_64 ./test_data/pg2600.txt
    1.40 ± 0.35 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_8 ./test_data/pg2600.txt
    1.43 ± 0.32 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_4 ./test_data/pg2600.txt
    1.47 ± 0.33 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_4 ./test_data/pg2600.txt
    1.60 ± 0.34 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_2 ./test_data/pg2600.txt
    1.74 ± 0.34 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_2 ./test_data/pg2600.txt
    1.75 ± 0.36 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_ptr_ ./test_data/pg2600.txt
    1.77 ± 0.37 times faster than taskset -c 0-11 build/wc_check_read_branchless_8192 ./test_data/pg2600.txt
    1.80 ± 0.36 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_8192 ./test_data/pg2600.txt
    1.80 ± 0.41 times faster than taskset -c 0-11 build/wc_check_read_branchless_252140 ./test_data/pg2600.txt
    1.82 ± 0.43 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_65535 ./test_data/pg2600.txt
    1.82 ± 0.40 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_252140 ./test_data/pg2600.txt
    1.82 ± 0.40 times faster than taskset -c 0-11 build/wc_check_read_branchless_4096 ./test_data/pg2600.txt
    1.82 ± 0.41 times faster than taskset -c 0-11 build/wc_check_read_branchless_65535 ./test_data/pg2600.txt
    1.83 ± 0.39 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_4096 ./test_data/pg2600.txt
    2.15 ± 0.54 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_1 ./test_data/pg2600.txt
    2.26 ± 0.49 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_1 ./test_data/pg2600.txt
    2.36 ± 0.58 times faster than taskset -c 0-11 build/wc_check_read_branchless_4194304 ./test_data/pg2600.txt
    2.40 ± 0.62 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_4194304 ./test_data/pg2600.txt
    2.54 ± 0.81 times faster than taskset -c 0-11 build/wc_check_read_branchless_256 ./test_data/pg2600.txt
    2.63 ± 0.80 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_256 ./test_data/pg2600.txt
    3.02 ± 1.04 times faster than taskset -c 0-11 build/wc_check_stream_4096 ./test_data/pg2600.txt
    3.20 ± 1.10 times faster than taskset -c 0-11 build/wc_check_read_8192 ./test_data/pg2600.txt
    3.20 ± 1.08 times faster than taskset -c 0-11 build/wc_check_read_252140 ./test_data/pg2600.txt
    3.21 ± 1.11 times faster than taskset -c 0-11 build/wc_check_stream_252140 ./test_data/pg2600.txt
    3.22 ± 1.10 times faster than taskset -c 0-11 build/wc_check_read_4096 ./test_data/pg2600.txt
    3.22 ± 1.11 times faster than taskset -c 0-11 build/wc_check_read_65535 ./test_data/pg2600.txt
    3.24 ± 1.10 times faster than taskset -c 0-11 build/wc_check_stream_8192 ./test_data/pg2600.txt
    3.24 ± 1.09 times faster than taskset -c 0-11 build/wc_check_stream_65535 ./test_data/pg2600.txt
    3.25 ± 1.09 times faster than taskset -c 0-11 build/wc_check_stream_256 ./test_data/pg2600.txt
    3.50 ± 1.16 times faster than taskset -c 0-11 build/wc_check_read_4194304 ./test_data/pg2600.txt
    3.53 ± 1.08 times faster than taskset -c 0-11 ./wc ./test_data/pg2600.txt
    3.53 ± 1.08 times faster than taskset -c 0-11 build/wc_check_read_256 ./test_data/pg2600.txt
    3.55 ± 1.18 times faster than taskset -c 0-11 build/wc_check_stream_4194304 ./test_data/pg2600.txt
    4.00 ± 1.05 times faster than taskset -c 0-11 wc ./test_data/pg2600.txt
```
You can see also `./wc` in above result, it is system `wc` which I compiled myself just to be sure it is optimized for my PC.

## Google benchmark:
```
---------------------------------------------------------------------------------------------
Benchmark                                                   Time             CPU   Iterations
---------------------------------------------------------------------------------------------
BM_wc_check_stream_256                                5945732 ns      5945488 ns          111
BM_wc_check_stream_4096                               5951931 ns      5950386 ns          117
BM_wc_check_stream_8192                               5847266 ns      5846830 ns          119
BM_wc_check_stream_65535                              5644695 ns      5644626 ns          124
BM_wc_check_stream_262140                             5820055 ns      5819953 ns          117
BM_wc_check_stream_4194304                            5737640 ns      5737523 ns          121
BM_wc_check_read_256                                  7806846 ns      7806621 ns           90
BM_wc_check_read_4096                                 5765135 ns      5765034 ns          121
BM_wc_check_read_8192                                 5762600 ns      5762330 ns          116
BM_wc_check_read_65535                                5700965 ns      5698228 ns          123
BM_wc_check_read_262140                               5906345 ns      5903839 ns          119
BM_wc_check_read_4194304                              5691398 ns      5688578 ns          122
BM_wc_check_read_branchless_256                       3399702 ns      3398263 ns          206
BM_wc_check_read_branchless_4096                      1384029 ns      1383951 ns          507
BM_wc_check_read_branchless_8192                      1323959 ns      1323951 ns          522
BM_wc_check_read_branchless_65535                     1425898 ns      1425890 ns          490
BM_wc_check_read_branchless_262140                    1483853 ns      1483821 ns          471
BM_wc_check_read_branchless_4194304                   1381814 ns      1381733 ns          509
BM_wc_check_read_branchless_ptr_256                   3407543 ns      3407404 ns          206
BM_wc_check_read_branchless_ptr_4096                  1384685 ns      1384425 ns          504
BM_wc_check_read_branchless_ptr_8192                  1325071 ns      1324348 ns          528
BM_wc_check_read_branchless_ptr_65535                 1428491 ns      1428483 ns          490
BM_wc_check_read_branchless_ptr_262140                1484330 ns      1484238 ns          469
BM_wc_check_read_branchless_ptr_4194304               1384330 ns      1384287 ns          509
BM_wc_check_mmap_branchless_ptr                       1285867 ns      1285820 ns          544
BM_wc_check_mmap_branchless_threads_1                 4209581 ns       330888 ns         1000
BM_wc_check_mmap_branchless_threads_2                 2298024 ns       345863 ns         1985
BM_wc_check_mmap_branchless_threads_4                  654577 ns       172149 ns         4084
BM_wc_check_mmap_branchless_threads_8                  663141 ns       223228 ns         3136
BM_wc_check_mmap_branchless_threads_16                 941342 ns       357007 ns         1952
BM_wc_check_mmap_branchless_threads_32                 654388 ns       626483 ns         1106
BM_wc_check_mmap_branchless_threads_64                1048836 ns      1027261 ns          709
BM_wc_check_mmap_branchless_threads_no_populate_1     3654777 ns       124961 ns         1000
BM_wc_check_mmap_branchless_threads_no_populate_2     1866108 ns       172652 ns         4298
BM_wc_check_mmap_branchless_threads_no_populate_4      615710 ns       106388 ns         6494
BM_wc_check_mmap_branchless_threads_no_populate_8      620179 ns       160474 ns         4359
BM_wc_check_mmap_branchless_threads_no_populate_16     908379 ns       312701 ns         2245
BM_wc_check_mmap_branchless_threads_no_populate_32     624855 ns       599733 ns         1186
BM_wc_check_mmap_branchless_threads_no_populate_64     955422 ns       935571 ns          764
BM_wc_check_mmap_simd_threads_1                        666763 ns       112015 ns         6764
BM_wc_check_mmap_simd_threads_2                        329095 ns        97816 ns        10780
BM_wc_check_mmap_simd_threads_4                        147212 ns        83850 ns         8290
BM_wc_check_mmap_simd_threads_8                        166091 ns       145946 ns         4842
BM_wc_check_mmap_simd_threads_16                       255040 ns       250005 ns         2827
BM_wc_check_mmap_simd_threads_32                       478368 ns       464143 ns         1481
BM_wc_check_mmap_simd_threads_64                       911911 ns       886741 ns          793
```

# Hardware
For testing I am using DELL Precision 3480 with i7-1370p Intel processor. This means that some of the threaded implementation might run on a E-cores, which probably can lower the result. In the results above you can see that I used `taskset -c 0-11` to make sure I am using P-cores only, it is not commited in the code.

# Summary
Looks like my implmentation can be even 4.0x faster than system `wc` which is quite an achievement. Feel free to use this code however you want.
