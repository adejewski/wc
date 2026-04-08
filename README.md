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
  taskset -c 0-11 build/wc_check_mmap_simd_thread_8 test_data/pg2600.txt ran
    1.00 ± 0.18 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_4 test_data/pg2600.txt
    1.04 ± 0.19 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_16 test_data/pg2600.txt
    1.04 ± 0.19 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_2 test_data/pg2600.txt
    1.10 ± 0.18 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_1 test_data/pg2600.txt
    1.14 ± 0.20 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_32 test_data/pg2600.txt
    1.26 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_16 test_data/pg2600.txt
    1.27 ± 0.21 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_8 test_data/pg2600.txt
    1.27 ± 0.23 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_4 test_data/pg2600.txt
    1.28 ± 0.26 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_32 test_data/pg2600.txt
    1.30 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_16 test_data/pg2600.txt
    1.30 ± 0.23 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_4 test_data/pg2600.txt
    1.34 ± 0.25 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_32 test_data/pg2600.txt
    1.35 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_8 test_data/pg2600.txt
    1.41 ± 0.23 times faster than taskset -c 0-11 build/wc_check_mmap_simd_thread_64 test_data/pg2600.txt
    1.44 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_64 test_data/pg2600.txt
    1.49 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_64 test_data/pg2600.txt
    1.50 ± 0.25 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_2 test_data/pg2600.txt
    1.51 ± 0.25 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_2 test_data/pg2600.txt
    1.51 ± 0.24 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_ptr_ test_data/pg2600.txt
    1.52 ± 0.24 times faster than taskset -c 0-11 build/wc_check_read_branchless_8192 test_data/pg2600.txt
    1.54 ± 0.25 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_8192 test_data/pg2600.txt
    1.57 ± 0.24 times faster than taskset -c 0-11 build/wc_check_read_branchless_4096 test_data/pg2600.txt
    1.57 ± 0.24 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_65535 test_data/pg2600.txt
    1.58 ± 0.25 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_252140 test_data/pg2600.txt
    1.58 ± 0.25 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_4096 test_data/pg2600.txt
    1.58 ± 0.23 times faster than taskset -c 0-11 build/wc_check_read_branchless_65535 test_data/pg2600.txt
    1.58 ± 0.24 times faster than taskset -c 0-11 build/wc_check_read_branchless_252140 test_data/pg2600.txt
    1.96 ± 0.31 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_no_populate_1 test_data/pg2600.txt
    1.98 ± 0.33 times faster than taskset -c 0-11 build/wc_check_mmap_branchless_threads_1 test_data/pg2600.txt
    2.27 ± 0.34 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_4194304 test_data/pg2600.txt
    2.28 ± 0.34 times faster than taskset -c 0-11 build/wc_check_read_branchless_4194304 test_data/pg2600.txt
    2.71 ± 0.37 times faster than taskset -c 0-11 build/wc_check_read_branchless_ptr_256 test_data/pg2600.txt
    2.73 ± 0.40 times faster than taskset -c 0-11 build/wc_check_read_branchless_256 test_data/pg2600.txt
    4.14 ± 0.57 times faster than taskset -c 0-11 build/wc_check_read_65535 test_data/pg2600.txt
    4.19 ± 0.58 times faster than taskset -c 0-11 build/wc_check_read_252140 test_data/pg2600.txt
    4.20 ± 0.57 times faster than taskset -c 0-11 build/wc_check_read_4096 test_data/pg2600.txt
    4.21 ± 0.57 times faster than taskset -c 0-11 build/wc_check_stream_4096 test_data/pg2600.txt
    4.25 ± 0.57 times faster than taskset -c 0-11 build/wc_check_read_8192 test_data/pg2600.txt
    4.25 ± 0.58 times faster than taskset -c 0-11 build/wc_check_stream_65535 test_data/pg2600.txt
    4.25 ± 0.57 times faster than taskset -c 0-11 build/wc_check_stream_8192 test_data/pg2600.txt
    4.31 ± 0.59 times faster than taskset -c 0-11 build/wc_check_stream_252140 test_data/pg2600.txt
    4.44 ± 0.60 times faster than taskset -c 0-11 build/wc_check_stream_256 test_data/pg2600.txt
    4.94 ± 0.68 times faster than taskset -c 0-11 build/wc_check_read_4194304 test_data/pg2600.txt
    5.03 ± 0.68 times faster than taskset -c 0-11 build/wc_check_stream_4194304 test_data/pg2600.txt
    5.50 ± 0.73 times faster than taskset -c 0-11 ./wc test_data/pg2600.txt
    5.55 ± 0.74 times faster than taskset -c 0-11 build/wc_check_read_256 test_data/pg2600.txt
    6.66 ± 0.87 times faster than taskset -c 0-11 wc test_data/pg2600.txt
```
You can see also `./wc` in above result, it is system `wc` which I compiled myself just to be sure it is optimized for my PC.

## Google benchmark:
```
----------------------------------------------------------------------------------------------------------------------
Benchmark                                                                            Time             CPU   Iterations
----------------------------------------------------------------------------------------------------------------------
BM_wc_check_stream_256/min_time:2.000/real_time                                6297298 ns      6296746 ns          446
BM_wc_check_stream_4096/min_time:2.000/real_time                               6376266 ns      6375431 ns          441
BM_wc_check_stream_8192/min_time:2.000/real_time                               6188676 ns      6188288 ns          450
BM_wc_check_stream_65535/min_time:2.000/real_time                              5944704 ns      5944520 ns          470
BM_wc_check_stream_262140/min_time:2.000/real_time                             6427393 ns      6426050 ns          458
BM_wc_check_stream_4194304/min_time:2.000/real_time                            6187093 ns      6186710 ns          410
BM_wc_check_read_256/min_time:2.000/real_time                                  8415180 ns      8414833 ns          336
BM_wc_check_read_4096/min_time:2.000/real_time                                 6173576 ns      6173401 ns          454
BM_wc_check_read_8192/min_time:2.000/real_time                                 6157485 ns      6157276 ns          460
BM_wc_check_read_65535/min_time:2.000/real_time                                6182642 ns      6182553 ns          458
BM_wc_check_read_262140/min_time:2.000/real_time                               6387876 ns      6387337 ns          439
BM_wc_check_read_4194304/min_time:2.000/real_time                              6214472 ns      6214278 ns          453
BM_wc_check_read_branchless_256/min_time:2.000/real_time                       3837878 ns      3837751 ns          728
BM_wc_check_read_branchless_4096/min_time:2.000/real_time                      1570210 ns      1570109 ns         1795
BM_wc_check_read_branchless_8192/min_time:2.000/real_time                      1508743 ns      1508593 ns         1851
BM_wc_check_read_branchless_65535/min_time:2.000/real_time                     1631664 ns      1631596 ns         1716
BM_wc_check_read_branchless_262140/min_time:2.000/real_time                    1627468 ns      1627376 ns         1690
BM_wc_check_read_branchless_4194304/min_time:2.000/real_time                   1601035 ns      1601000 ns         1761
BM_wc_check_read_branchless_ptr_256/min_time:2.000/real_time                   3860718 ns      3860507 ns          734
BM_wc_check_read_branchless_ptr_4096/min_time:2.000/real_time                  1584161 ns      1584012 ns         1752
BM_wc_check_read_branchless_ptr_8192/min_time:2.000/real_time                  1508855 ns      1508823 ns         1850
BM_wc_check_read_branchless_ptr_65535/min_time:2.000/real_time                 1618580 ns      1618554 ns         1734
BM_wc_check_read_branchless_ptr_262140/min_time:2.000/real_time                1649103 ns      1649067 ns         1702
BM_wc_check_read_branchless_ptr_4194304/min_time:2.000/real_time               1564758 ns      1564724 ns         1793
BM_wc_check_mmap_branchless_ptr/min_time:2.000/real_time                       1448450 ns      1448407 ns         1946
BM_wc_check_mmap_branchless_threads_1/min_time:2.000/real_time                 2153789 ns       214340 ns         1322
BM_wc_check_mmap_branchless_threads_2/min_time:2.000/real_time                 1335442 ns       230871 ns         2073
BM_wc_check_mmap_branchless_threads_4/min_time:2.000/real_time                  949677 ns       272108 ns         2955
BM_wc_check_mmap_branchless_threads_8/min_time:2.000/real_time                  968611 ns       350173 ns         2895
BM_wc_check_mmap_branchless_threads_16/min_time:2.000/real_time                1036834 ns       431680 ns         2682
BM_wc_check_mmap_branchless_threads_32/min_time:2.000/real_time                 791300 ns       759965 ns         3528
BM_wc_check_mmap_branchless_threads_64/min_time:2.000/real_time                1279174 ns      1243983 ns         2207
BM_wc_check_mmap_branchless_threads_no_populate_1/min_time:2.000/real_time     2131467 ns       143833 ns         1334
BM_wc_check_mmap_branchless_threads_no_populate_2/min_time:2.000/real_time     1278558 ns       152385 ns         2170
BM_wc_check_mmap_branchless_threads_no_populate_4/min_time:2.000/real_time      845448 ns       184334 ns         3246
BM_wc_check_mmap_branchless_threads_no_populate_8/min_time:2.000/real_time      800785 ns       231720 ns         3471
BM_wc_check_mmap_branchless_threads_no_populate_16/min_time:2.000/real_time     999359 ns       363159 ns         2772
BM_wc_check_mmap_branchless_threads_no_populate_32/min_time:2.000/real_time     833787 ns       805825 ns         3915
BM_wc_check_mmap_branchless_threads_no_populate_64/min_time:2.000/real_time    1294294 ns      1262410 ns         2142
BM_wc_check_mmap_simd_threads_1/min_time:2.000/real_time                        456906 ns        95685 ns         5787
BM_wc_check_mmap_simd_threads_2/min_time:2.000/real_time                        232224 ns        61479 ns        11419
BM_wc_check_mmap_simd_threads_4/min_time:2.000/real_time                        173436 ns        96140 ns        16315
BM_wc_check_mmap_simd_threads_8/min_time:2.000/real_time                        197562 ns       174140 ns        13598
BM_wc_check_mmap_simd_threads_16/min_time:2.000/real_time                       294924 ns       288010 ns         9508
BM_wc_check_mmap_simd_threads_32/min_time:2.000/real_time                       547820 ns       531667 ns         5027
BM_wc_check_mmap_simd_threads_64/min_time:2.000/real_time                      1032494 ns      1013359 ns         2681
```

# Hardware
For testing I am using DELL Precision 3480 with i7-1370p Intel processor. This means that some of the threaded implementation might run on a E-cores, which probably can lower the result. In the results above you can see that I used `taskset -c 0-11` to make sure I am using P-cores only, it is not commited in the code.

# Summary
Looks like my implmentation can be even 6.6x faster than system `wc` which is quite an achievement. Feel free to use this code however you want.
