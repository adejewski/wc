#include <gtest/gtest.h>

#include "wc.hh"

// Data comes from `wc ./test_data/pg2600.txt`
Count expected_result_pg2600{3359613, 566333, 66041};
std::string pg2600 = "./test_data/pg2600.txt";

TEST(check_stream, pg2600) {
    EXPECT_EQ(check_stream<256>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_stream<4096>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_stream<8192>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_stream<65535>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_stream<262140>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_stream<4194304>(pg2600), expected_result_pg2600);
}

TEST(check_read, pg2600) {
    EXPECT_EQ(check_read<256>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read<4096>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read<8192>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read<65535>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read<262140>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read<4194304>(pg2600), expected_result_pg2600);
}

TEST(check_read_branchless, pg2600) {
    EXPECT_EQ(check_read_branchless<256>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless<4096>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless<8192>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless<65535>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless<262140>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless<4194304>(pg2600), expected_result_pg2600);
}

TEST(check_read_branchless_ptr, pg2600) {
    EXPECT_EQ(check_read_branchless_ptr<256>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless_ptr<4096>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless_ptr<8192>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless_ptr<65535>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless_ptr<262140>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_read_branchless_ptr<4194304>(pg2600), expected_result_pg2600);
}

TEST(check_mmap_branchless_ptr, pg2600) {
    EXPECT_EQ(check_mmap_branchless_ptr(pg2600), expected_result_pg2600);
}

TEST(check_mmap_branchless_threads, pg2600) {
    EXPECT_EQ(check_mmap_branchless_threads<1>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads<2>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads<4>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads<8>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads<16>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads<32>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads<64>(pg2600), expected_result_pg2600);
}

TEST(check_mmap_branchless_threads_no_populate, pg2600) {
    EXPECT_EQ(check_mmap_branchless_threads_no_populate<1>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads_no_populate<2>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads_no_populate<4>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads_no_populate<8>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads_no_populate<16>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads_no_populate<32>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_branchless_threads_no_populate<64>(pg2600), expected_result_pg2600);
}

TEST(check_mmap_simd_thread, pg2600) {
    EXPECT_EQ(check_mmap_simd_thread<1>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_simd_thread<2>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_simd_thread<4>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_simd_thread<8>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_simd_thread<16>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_simd_thread<32>(pg2600), expected_result_pg2600);
    EXPECT_EQ(check_mmap_simd_thread<64>(pg2600), expected_result_pg2600);
}
