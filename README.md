# This repository is meant to benchmark my own implementation of wc

I was trying different implementaitions to show how to speed up simple application like wc. Of course it is not 1:1 replacment for system wc because we do not cover all edge cases here. Nevertheless for the prepared test_data my implementation and system `wc` gives exactly the same results.

# Running example 
To test it `just build_all` and `just hyperfine ./test_data/pg2600.txt` from main folder of this repository.
You can clearly see that you get best results using simd with threads. But if you do not have simd branchless approach gives also really got results

# Test
There are unit tests which can be started by `just test`. Requires gtest installed.

# Example results:
```
Summary
  build/wc_check_mmap_simd_thread_8 ./test_data/pg2600.txt ran
    1.13 ± 0.33 times faster than build/wc_check_mmap_simd_thread_2 ./test_data/pg2600.txt
    1.16 ± 0.36 times faster than build/wc_check_mmap_simd_thread_16 ./test_data/pg2600.txt
    1.22 ± 0.30 times faster than build/wc_check_mmap_simd_thread_4 ./test_data/pg2600.txt
    1.30 ± 0.40 times faster than build/wc_check_mmap_branchless_threads_no_populate_8 ./test_data/pg2600.txt
    1.31 ± 0.39 times faster than build/wc_check_mmap_branchless_threads_no_populate_16 ./test_data/pg2600.txt
    1.35 ± 0.45 times faster than build/wc_check_mmap_branchless_threads_16 ./test_data/pg2600.txt
    1.40 ± 0.43 times faster than build/wc_check_mmap_branchless_threads_8 ./test_data/pg2600.txt
    1.41 ± 0.36 times faster than build/wc_check_mmap_simd_thread_1 ./test_data/pg2600.txt
    1.41 ± 0.40 times faster than build/wc_check_mmap_simd_thread_32 ./test_data/pg2600.txt
    1.53 ± 0.38 times faster than build/wc_check_mmap_branchless_threads_no_populate_32 ./test_data/pg2600.txt
    1.59 ± 0.45 times faster than build/wc_check_mmap_branchless_threads_32 ./test_data/pg2600.txt
    1.62 ± 0.47 times faster than build/wc_check_mmap_branchless_threads_no_populate_4 ./test_data/pg2600.txt
    1.69 ± 0.64 times faster than build/wc_check_read_branchless_4096 ./test_data/pg2600.txt
    1.75 ± 0.65 times faster than build/wc_check_mmap_branchless_threads_64 ./test_data/pg2600.txt
    1.75 ± 0.72 times faster than build/wc_check_read_branchless_65535 ./test_data/pg2600.txt
    1.76 ± 0.63 times faster than build/wc_check_mmap_branchless_threads_2 ./test_data/pg2600.txt
    1.80 ± 0.43 times faster than build/wc_check_mmap_branchless_threads_4 ./test_data/pg2600.txt
    1.81 ± 0.66 times faster than build/wc_check_read_branchless_ptr_252140 ./test_data/pg2600.txt
    1.85 ± 0.59 times faster than build/wc_check_mmap_branchless_threads_no_populate_64 ./test_data/pg2600.txt
    1.88 ± 0.69 times faster than build/wc_check_mmap_branchless_ptr_ ./test_data/pg2600.txt
    1.91 ± 0.77 times faster than build/wc_check_read_branchless_ptr_4096 ./test_data/pg2600.txt
    1.92 ± 0.52 times faster than build/wc_check_mmap_simd_thread_64 ./test_data/pg2600.txt
    2.05 ± 0.69 times faster than build/wc_check_read_branchless_252140 ./test_data/pg2600.txt
    2.07 ± 0.57 times faster than build/wc_check_mmap_branchless_threads_no_populate_2 ./test_data/pg2600.txt
    2.07 ± 0.66 times faster than build/wc_check_read_branchless_ptr_8192 ./test_data/pg2600.txt
    2.09 ± 0.71 times faster than build/wc_check_read_branchless_8192 ./test_data/pg2600.txt
    2.13 ± 0.71 times faster than build/wc_check_read_branchless_ptr_65535 ./test_data/pg2600.txt
    2.89 ± 0.75 times faster than build/wc_check_mmap_branchless_threads_no_populate_1 ./test_data/pg2600.txt
    3.01 ± 0.79 times faster than build/wc_check_mmap_branchless_threads_1 ./test_data/pg2600.txt
    3.19 ± 0.96 times faster than build/wc_check_read_branchless_ptr_4194304 ./test_data/pg2600.txt
    3.28 ± 0.96 times faster than build/wc_check_read_branchless_4194304 ./test_data/pg2600.txt
    3.86 ± 1.24 times faster than build/wc_check_read_branchless_ptr_256 ./test_data/pg2600.txt
    3.97 ± 1.15 times faster than build/wc_check_read_branchless_256 ./test_data/pg2600.txt
    4.09 ± 1.51 times faster than build/wc_check_read_65535 ./test_data/pg2600.txt
    5.15 ± 1.69 times faster than build/wc_check_stream_8192 ./test_data/pg2600.txt
    5.20 ± 1.68 times faster than build/wc_check_read_252140 ./test_data/pg2600.txt
    5.24 ± 1.70 times faster than build/wc_check_stream_65535 ./test_data/pg2600.txt
    5.29 ± 1.66 times faster than build/wc_check_stream_4096 ./test_data/pg2600.txt
    5.33 ± 1.68 times faster than build/wc_check_read_8192 ./test_data/pg2600.txt
    5.34 ± 1.68 times faster than build/wc_check_stream_252140 ./test_data/pg2600.txt
    5.55 ± 1.77 times faster than build/wc_check_stream_256 ./test_data/pg2600.txt
    5.61 ± 1.68 times faster than build/wc_check_read_4096 ./test_data/pg2600.txt
    5.72 ± 1.93 times faster than build/wc_check_read_4194304 ./test_data/pg2600.txt
    5.74 ± 1.80 times faster than build/wc_check_stream_4194304 ./test_data/pg2600.txt
    5.93 ± 2.01 times faster than build/wc_check_read_256 ./test_data/pg2600.txt
    6.46 ± 1.97 times faster than wc ./test_data/pg2600.txt
```

# Hardware
For testing I am using DELL Precision 3480 with i7-1370p Intel processor. This means that some of the threaded implementation might run on a E-cores, which probably can lower the result.

# Summary
Looks like my implmentation can be even 6.5x faster than system `wc` which is quite an achievement. Feel free to use this code however you want.
