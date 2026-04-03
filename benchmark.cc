#include <benchmark/benchmark.h>

#include <fstream>

#include "wc.hh"

#define BENCHMARK_WC(NAME, FUNCTION)                              \
    static void BM_wc_check_##NAME(benchmark::State& state) {     \
        for (auto _ : state) {                                    \
            auto file_name = std::string("test_data/pg2600.txt"); \
            auto count = FUNCTION(file_name);                     \
            benchmark::DoNotOptimize(count);                      \
        }                                                         \
    }                                                             \
    BENCHMARK(BM_wc_check_##NAME);

BENCHMARK_WC(stream_256, check_stream<256>);
BENCHMARK_WC(stream_4096, check_stream<4096>);
BENCHMARK_WC(stream_8192, check_stream<8192>);
BENCHMARK_WC(stream_65535, check_stream<65535>);
BENCHMARK_WC(stream_262140, check_stream<262140>);
BENCHMARK_WC(stream_4194304, check_stream<4194304>);

BENCHMARK_WC(read_256, check_read<256>);
BENCHMARK_WC(read_4096, check_read<4096>);
BENCHMARK_WC(read_8192, check_read<8192>);
BENCHMARK_WC(read_65535, check_read<65535>);
BENCHMARK_WC(read_262140, check_read<262140>);
BENCHMARK_WC(read_4194304, check_read<4194304>);

BENCHMARK_WC(read_branchless_256, check_read_branchless<256>);
BENCHMARK_WC(read_branchless_4096, check_read_branchless<4096>);
BENCHMARK_WC(read_branchless_8192, check_read_branchless<8192>);
BENCHMARK_WC(read_branchless_65535, check_read_branchless<65535>);
BENCHMARK_WC(read_branchless_262140, check_read_branchless<262140>);
BENCHMARK_WC(read_branchless_4194304, check_read_branchless<4194304>);

BENCHMARK_WC(read_branchless_ptr_256, check_read_branchless_ptr<256>);
BENCHMARK_WC(read_branchless_ptr_4096, check_read_branchless_ptr<4096>);
BENCHMARK_WC(read_branchless_ptr_8192, check_read_branchless_ptr<8192>);
BENCHMARK_WC(read_branchless_ptr_65535, check_read_branchless_ptr<65535>);
BENCHMARK_WC(read_branchless_ptr_262140, check_read_branchless_ptr<262140>);
BENCHMARK_WC(read_branchless_ptr_4194304, check_read_branchless_ptr<4194304>);

BENCHMARK_WC(mmap_branchless_ptr, check_mmap_branchless_ptr);

BENCHMARK_WC(mmap_branchless_threads_1, check_mmap_branchless_threads<1>);
BENCHMARK_WC(mmap_branchless_threads_2, check_mmap_branchless_threads<2>);
BENCHMARK_WC(mmap_branchless_threads_4, check_mmap_branchless_threads<4>);
BENCHMARK_WC(mmap_branchless_threads_8, check_mmap_branchless_threads<8>);
BENCHMARK_WC(mmap_branchless_threads_16, check_mmap_branchless_threads<16>);
BENCHMARK_WC(mmap_branchless_threads_32, check_mmap_branchless_threads<32>);
BENCHMARK_WC(mmap_branchless_threads_64, check_mmap_branchless_threads<64>);

BENCHMARK_WC(mmap_branchless_threads_no_populate_1, check_mmap_branchless_threads_no_populate<1>);
BENCHMARK_WC(mmap_branchless_threads_no_populate_2, check_mmap_branchless_threads_no_populate<2>);
BENCHMARK_WC(mmap_branchless_threads_no_populate_4, check_mmap_branchless_threads_no_populate<4>);
BENCHMARK_WC(mmap_branchless_threads_no_populate_8, check_mmap_branchless_threads_no_populate<8>);
BENCHMARK_WC(mmap_branchless_threads_no_populate_16, check_mmap_branchless_threads_no_populate<16>);
BENCHMARK_WC(mmap_branchless_threads_no_populate_32, check_mmap_branchless_threads_no_populate<32>);
BENCHMARK_WC(mmap_branchless_threads_no_populate_64, check_mmap_branchless_threads_no_populate<64>);

BENCHMARK_WC(mmap_simd_threads_1, check_mmap_simd_thread<1>);
BENCHMARK_WC(mmap_simd_threads_2, check_mmap_simd_thread<2>);
BENCHMARK_WC(mmap_simd_threads_4, check_mmap_simd_thread<4>);
BENCHMARK_WC(mmap_simd_threads_8, check_mmap_simd_thread<8>);
BENCHMARK_WC(mmap_simd_threads_16, check_mmap_simd_thread<16>);
BENCHMARK_WC(mmap_simd_threads_32, check_mmap_simd_thread<32>);
BENCHMARK_WC(mmap_simd_threads_64, check_mmap_simd_thread<64>);

BENCHMARK_MAIN();
