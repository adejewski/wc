# This repository is meant to benchmark my own implementation of wc

I was trying different implementaitions to show how to speed up simple application like wc. Of course it is not 1:1 replacment for system wc because we do not cover all edge cases here.

# Running example 
To test it `just build_all` and `just hyperfine ./test_data/pg2600.txt` from main folder of this repository.
You can clearly see that you get best results using simd with threads. But if you do not have simd branchless approach gives also really got results

# Example results:
```
Summary
  build/wc_check_mmap_simd_thread_8 ./test_data/pg2600.txt ran
    1.02 ± 0.29 times faster than build/wc_check_mmap_simd_thread_4 ./test_data/pg2600.txt
    1.10 ± 0.26 times faster than build/wc_check_mmap_simd_thread_2 ./test_data/pg2600.txt
    1.11 ± 0.28 times faster than build/wc_check_mmap_simd_thread_16 ./test_data/pg2600.txt
    1.34 ± 0.29 times faster than build/wc_check_mmap_simd_thread_32 ./test_data/pg2600.txt
    1.40 ± 0.26 times faster than build/wc_check_mmap_simd_thread_1 ./test_data/pg2600.txt
    1.43 ± 0.55 times faster than build/wc_check_mmap_branchless_threads_no_populate_8 ./test_data/pg2600.txt
    1.46 ± 0.30 times faster than build/wc_check_mmap_branchless_threads_no_populate_16 ./test_data/pg2600.txt
    1.53 ± 0.30 times faster than build/wc_check_mmap_branchless_threads_16 ./test_data/pg2600.txt
    1.56 ± 0.31 times faster than build/wc_check_mmap_branchless_threads_no_populate_32 ./test_data/pg2600.txt
    1.59 ± 0.39 times faster than build/wc_check_mmap_branchless_threads_32 ./test_data/pg2600.txt
    1.69 ± 0.31 times faster than build/wc_check_mmap_branchless_threads_no_populate_4 ./test_data/pg2600.txt
    1.77 ± 0.50 times faster than build/wc_check_mmap_branchless_threads_no_populate_64 ./test_data/pg2600.txt
    1.78 ± 0.36 times faster than build/wc_check_mmap_branchless_threads_8 ./test_data/pg2600.txt
    1.79 ± 0.37 times faster than build/wc_check_mmap_branchless_threads_4 ./test_data/pg2600.txt
    1.90 ± 0.41 times faster than build/wc_check_mmap_simd_thread_64 ./test_data/pg2600.txt
    1.92 ± 0.49 times faster than build/wc_check_mmap_branchless_threads_64 ./test_data/pg2600.txt
    2.07 ± 0.62 times faster than build/wc_check_read_branchless_4096 ./test_data/pg2600.txt
    2.10 ± 0.42 times faster than build/wc_check_mmap_branchless_threads_2 ./test_data/pg2600.txt
    2.20 ± 0.40 times faster than build/wc_check_mmap_branchless_threads_no_populate_2 ./test_data/pg2600.txt
    2.20 ± 0.55 times faster than build/wc_check_read_branchless_ptr_252140 ./test_data/pg2600.txt
    2.23 ± 0.60 times faster than build/wc_check_read_branchless_ptr_8192 ./test_data/pg2600.txt
    2.24 ± 0.56 times faster than build/wc_check_mmap_branchless_ptr_ ./test_data/pg2600.txt
    2.26 ± 0.54 times faster than build/wc_check_read_branchless_8192 ./test_data/pg2600.txt
    2.31 ± 0.54 times faster than build/wc_check_read_branchless_ptr_4096 ./test_data/pg2600.txt
    2.32 ± 0.48 times faster than build/wc_check_read_branchless_252140 ./test_data/pg2600.txt
    2.34 ± 0.56 times faster than build/wc_check_read_branchless_ptr_65535 ./test_data/pg2600.txt
    2.36 ± 0.55 times faster than build/wc_check_read_branchless_65535 ./test_data/pg2600.txt
    2.83 ± 0.80 times faster than build/wc_check_mmap_branchless_threads_1 ./test_data/pg2600.txt
    3.07 ± 0.54 times faster than build/wc_check_mmap_branchless_threads_no_populate_1 ./test_data/pg2600.txt
    3.11 ± 0.91 times faster than build/wc_check_read_branchless_4194304 ./test_data/pg2600.txt
    3.31 ± 0.82 times faster than build/wc_check_read_branchless_ptr_4194304 ./test_data/pg2600.txt
    3.86 ± 1.18 times faster than build/wc_check_read_branchless_256 ./test_data/pg2600.txt
    4.09 ± 1.14 times faster than build/wc_check_read_branchless_ptr_256 ./test_data/pg2600.txt
    4.86 ± 1.71 times faster than build/wc_check_read_256 ./test_data/pg2600.txt
    4.95 ± 1.57 times faster than build/wc_check_stream_65535 ./test_data/pg2600.txt
    5.00 ± 1.50 times faster than build/wc_check_stream_8192 ./test_data/pg2600.txt
    5.01 ± 1.58 times faster than build/wc_check_stream_252140 ./test_data/pg2600.txt
    5.02 ± 1.54 times faster than build/wc_check_read_65535 ./test_data/pg2600.txt
    5.08 ± 1.53 times faster than build/wc_check_read_8192 ./test_data/pg2600.txt
    5.12 ± 1.54 times faster than build/wc_check_stream_256 ./test_data/pg2600.txt
    5.19 ± 1.50 times faster than build/wc_check_read_252140 ./test_data/pg2600.txt
    5.24 ± 1.53 times faster than build/wc_check_stream_4096 ./test_data/pg2600.txt
    5.25 ± 1.58 times faster than build/wc_check_read_4096 ./test_data/pg2600.txt
    5.48 ± 1.63 times faster than build/wc_check_stream_4194304 ./test_data/pg2600.txt
    5.53 ± 1.75 times faster than build/wc_check_read_4194304 ./test_data/pg2600.txt
    6.26 ± 1.93 times faster than wc ./test_data/pg2600.txt
```
