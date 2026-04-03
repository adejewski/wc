BUILD_DIR := "build/"
WC_SIZE := "check_stream check_read check_read_branchless check_read_branchless_ptr"
NUM := "256 4096 8192 65535 252140 4194304"

WC_SINGLE := "check_mmap_branchless_ptr"

WC_THREADED := "check_mmap_branchless_threads check_mmap_branchless_threads_no_populate check_mmap_simd_thread"
THREADS := "1 2 4 8 16 32 64"

benchmark:
    g++ benchmark.cc -O3 -std=c++23 -mavx2 -isystem benchmark/include -Lbenchmark/build/src -lbenchmark -lpthread -o benchmark-wc
    ./benchmark-wc

build_threaded:
    mkdir -p {{BUILD_DIR}}
    for impl in {{WC_THREADED}}; do \
        for t in {{THREADS}}; do \
            just build "$impl" "$t"; \
        done \
    done


build_all:
    mkdir -p {{BUILD_DIR}}
    for impl in {{WC_SIZE}}; do \
        for t in {{NUM}}; do \
            just build "$impl" "$t"; \
        done \
    done
    for impl in {{WC_SINGLE}}; do \
        just build "$impl" ""; \
    done
    just build_threaded

build FUNCTION NUM:
    @echo "Building {{FUNCTION}} {{NUM}}"
    if [ -z "{{NUM}}" ]; then \
        g++ -DFUNCTION={{FUNCTION}} main.cc -O3 -std=c++23 -mavx2 -o {{BUILD_DIR}}wc_{{FUNCTION}}_{{NUM}}; \
    else \
        g++ -DFUNCTION={{FUNCTION}} -DNUM={{NUM}} main.cc -O3 -mavx2 -std=c++23 -o {{BUILD_DIR}}wc_{{FUNCTION}}_{{NUM}}; \
    fi

RUNS := "500"
WARMUP := "5"

hyperfine FILE:
    @bash -c ' \
        cmds=("wc {{FILE}}"); \
        for bin in $(find {{BUILD_DIR}} -type f -executable); do \
            cmds+=("$bin {{FILE}}"); \
        done; \
        echo "Commands: ${cmds[@]}"; \
        hyperfine --warmup {{WARMUP}} --runs {{RUNS}} -N "${cmds[@]}"; \
    '

test:
    g++ -std=c++23 test.cc -mavx2 -lgtest -lgtest_main -lpthread -o test_wc
    ./test_wc
