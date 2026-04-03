#include <fstream>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <print>
#include <unistd.h>
#include <fcntl.h>
#include <thread>
#include <vector>
#include <immintrin.h>

struct Count{
    uint bytes;
    uint words;
    uint lines;

    bool operator==(const Count& other) const noexcept {
        if(bytes != other.bytes) return false;
        if(words != other.words) return false;
        if(lines != other.lines) return false;
        return true;
    }
};
// Avoid hitting same cache line
struct alignas(64) PaddedCount : Count {};

constexpr auto newline_lut = [] {
    std::array<unsigned char, 256> lut{};
    lut['\n'] = 1;
    return lut;
}();


constexpr auto is_word = [] {
    std::array<unsigned char, 256> lut{};
    for (int i = 0; i <= 255; i++) {
        lut[i] = 1;
    }
    lut[' '] = 0;
    lut['\t'] = 0;
    lut['\n'] = 0;
    lut['\r'] = 0;
    return lut;
}();

constexpr auto is_delim = [] {
    std::array<unsigned char, 256> lut{};
    lut[' '] = 1;
    lut['\t'] = 1;
    lut['\n'] = 1;
    lut['\r'] = 1;
    return lut;
}();

template<size_t BUFFER_SIZE>
[[nodiscard]] Count check_stream(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    auto stream = std::fstream(file_name);
    if(!stream) {
        std::print("Error opening file ");
        return result;
    }
    char buffer[BUFFER_SIZE];
    int word_started = 0;
    while(!stream.eof()) {
        stream.read(buffer, BUFFER_SIZE);
        result.bytes += stream.gcount();
        for(auto i = 0; i < stream.gcount(); ++i){
            switch(buffer[i]){
                case '\n': {
                    result.lines++;
                }
                case ' ': 
                case '\r':
                case '\t': {
                    result.words += word_started;
                    word_started = 0;
                } break;
                default: {
                    word_started = 1;
                } break;
            }
        }
    }
    result.words += word_started;
    stream.close();
    return result;
}


template<size_t BUFFER_SIZE>
[[nodiscard]] Count check_read(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        std::print("Error opening file ");
        return result;
    }
    char buffer[BUFFER_SIZE];
    int word_started = 0;
    ssize_t n;
    while((n = read(fd, buffer, BUFFER_SIZE)) > 0) {
        result.bytes += n;
        for(auto i = 0; i < n; ++i){
            switch(buffer[i]){
                case '\n': {
                    result.lines++;
                }
                case ' ':
                case '\t':
                case '\r': {
                    result.words += word_started;
                    word_started = 0;
                } break;
                default: {
                    word_started = 1;
                } break;
            }
        }
    }
    result.words += word_started;
    close(fd);
    return result;
}

template<size_t BUFFER_SIZE>
[[nodiscard]] Count check_read_branchless(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        std::print("Error opening file ");
        return result;
    }
    char buffer[BUFFER_SIZE];
    int word_started = 0;
    ssize_t n;
    while((n = read(fd, buffer, BUFFER_SIZE)) > 0) {
        result.bytes += n;
        for(auto i = 0; i < n; ++i){
            unsigned char c = buffer[i];

            result.lines += newline_lut[c];
            result.words += word_started & is_delim[c];
            word_started = is_word[c];
        }
    }
    result.words += word_started;
    close(fd);
    return result;
}


template<size_t BUFFER_SIZE>
[[nodiscard]] Count check_read_branchless_ptr(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        std::print("Error opening file ");
        return result;
    }
    unsigned char buffer[BUFFER_SIZE];
    int word_started = 0;
    ssize_t n;
    while((n = read(fd, buffer, BUFFER_SIZE)) > 0) {
        result.bytes += n;
        unsigned char* ptr = buffer;
        auto end = ptr + n;
        while(ptr < end) {
            unsigned char c = *ptr++;

            result.lines += newline_lut[c];
            result.words += word_started & is_delim[c];
            word_started = is_word[c];
        }
    }
    result.words += word_started;
    close(fd);
    return result;
}

[[nodiscard]] Count check_mmap_branchless_ptr(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        std::print("Error opening file ");
        return result;
    }
    
    struct stat st;
    if (fstat(fd, &st) == -1) {
        return result;
    }

    size_t size = st.st_size;
    
    unsigned char *buffer = (unsigned char *)mmap(NULL, size, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0);
    if (buffer == MAP_FAILED) {
        return result;
    }

    result.bytes += size;
    unsigned char* ptr = buffer;
    auto end = ptr + size;
    int word_started = 0;
    while(ptr < end) {
        unsigned char c = *ptr++;

        result.lines += newline_lut[c];
        result.words += word_started & is_delim[c];
        word_started = is_word[c];
    }
    result.words += word_started;

    munmap(buffer, size);
    close(fd);
    return result;
}

template<size_t THREAD_NUM>
[[nodiscard]] Count check_mmap_branchless_threads(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        std::print("Error opening file ");
        return result;
    }
    
    struct stat st;
    if (fstat(fd, &st) == -1) {
        return result;
    }

    size_t size = st.st_size;
    
    unsigned char *buffer = (unsigned char *)mmap(NULL, size, PROT_READ, MAP_SHARED | MAP_POPULATE, fd, 0);
    if (buffer == MAP_FAILED) {
        return result;
    }

    result.bytes += size;

    std::vector<std::thread> threads;
    threads.reserve(THREAD_NUM);
    std::vector<uint8_t> starts(THREAD_NUM, false);
    std::vector<uint8_t> ends(THREAD_NUM, false);
    std::vector<PaddedCount> count(THREAD_NUM, {0, 0, 0});

    auto chunk_size = size / THREAD_NUM;
    for(auto i = 0; i < THREAD_NUM; ++i){
        threads.emplace_back([&, i]() {
             unsigned char* ptr = buffer + i * chunk_size;
             unsigned char* end = (i == THREAD_NUM - 1) ? buffer + size : ptr + chunk_size;
             starts[i] = is_word[(unsigned char)*ptr];
             ends[i] = is_word[(unsigned char)*(end - 1)];
             unsigned char word_started = 0;
             while(ptr < end) {
                unsigned char c = *ptr++;

                count[i].lines += newline_lut[c];
                count[i].words += word_started & is_delim[c];
                word_started = is_word[c];
             }
             count[i].words += word_started;
        });
    }

    for(auto i = 0; i < THREAD_NUM; ++i){
        threads[i].join();
        result.words += count[i].words;
        result.lines += count[i].lines;
    }
    for(auto i = 1; i < THREAD_NUM; ++i) {
        result.words -= ends[i - 1] & starts[i]; 
    }


    munmap(buffer, size);
    close(fd);
    return result;
}

template<size_t THREAD_NUM>
[[nodiscard]] Count check_mmap_branchless_threads_no_populate(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        std::print("Error opening file ");
        return result;
    }
    
    struct stat st;
    if (fstat(fd, &st) == -1) {
        return result;
    }

    size_t size = st.st_size;
    
    unsigned char *buffer = (unsigned char *)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (buffer == MAP_FAILED) {
        return result;
    }

    result.bytes += size;

    std::vector<std::thread> threads;
    threads.reserve(THREAD_NUM);
    std::vector<uint8_t> starts(THREAD_NUM, false);
    std::vector<uint8_t> ends(THREAD_NUM, false);
    std::vector<PaddedCount> count(THREAD_NUM, {0, 0, 0});

    auto chunk_size = size / THREAD_NUM;
    for(auto i = 0; i < THREAD_NUM; ++i){
        threads.emplace_back([&, i]() {
             unsigned char* ptr = buffer + i * chunk_size;
             unsigned char* end = (i == THREAD_NUM - 1) ? buffer + size : ptr + chunk_size;
             starts[i] = is_word[(unsigned char)*ptr];
             ends[i] = is_word[(unsigned char)*(end - 1)];
             unsigned char word_started = 0;
             while(ptr < end) {
                unsigned char c = *ptr++;

                count[i].lines += newline_lut[c];
                count[i].words += word_started & is_delim[c];
                word_started = is_word[c];
             }
             count[i].words += word_started;
        });
    }

    for(auto i = 0; i < THREAD_NUM; ++i){
        threads[i].join();
        result.words += count[i].words;
        result.lines += count[i].lines;
    }
    for(auto i = 1; i < THREAD_NUM; ++i) {
        result.words -= ends[i - 1] & starts[i]; 
    }


    munmap(buffer, size);
    close(fd);
    return result;
}

template<size_t THREAD_NUM>
[[nodiscard]] Count check_mmap_simd_thread(std::string& file_name) noexcept {
    auto result = Count{0, 0, 0};
    int fd = open(file_name.c_str(), O_RDONLY);
    if (fd == -1) {
        std::print("Error opening file ");
        return result;
    }
    
    struct stat st;
    if (fstat(fd, &st) == -1) {
        return result;
    }

    size_t size = st.st_size;
    
    unsigned char *buffer = (unsigned char *)mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (buffer == MAP_FAILED) {
        return result;
    }

    result.bytes += size;

    std::vector<std::thread> threads;
    threads.reserve(THREAD_NUM);
    std::vector<uint8_t> starts(THREAD_NUM, false);
    std::vector<uint8_t> ends(THREAD_NUM, false);
    std::vector<PaddedCount> count(THREAD_NUM, {0, 0, 0});

    auto chunk_size = size / THREAD_NUM;
    for(auto i = 0; i < THREAD_NUM; ++i){
        threads.emplace_back([&, i]() {
                __m256i space = _mm256_set1_epi8(' ');
                __m256i newline = _mm256_set1_epi8('\n');
                __m256i tab = _mm256_set1_epi8('\t');
                __m256i cr = _mm256_set1_epi8('\r');

                unsigned char* ptr = buffer + i * chunk_size;
                unsigned char* end = (i == THREAD_NUM - 1) ? buffer + size : ptr + chunk_size;
                starts[i] = is_word[(unsigned char)*ptr];
                ends[i] = is_word[(unsigned char)*(end - 1)];
                unsigned char prev_space = 1;
                for(; ptr + 32 <= end; ptr += 32) 
                {
                    __m256i data = _mm256_loadu_si256(reinterpret_cast<const __m256i*>(ptr));
                    auto newlines = _mm256_movemask_epi8(_mm256_cmpeq_epi8(data, newline));
                    count[i].lines += std::popcount((uint)newlines);

                    auto is_whitespace = newlines | _mm256_movemask_epi8(_mm256_cmpeq_epi8(data, space)) | _mm256_movemask_epi8(_mm256_cmpeq_epi8(data, tab)) | _mm256_movemask_epi8(_mm256_cmpeq_epi8(data, cr));

                    auto non_whitespace = (~is_whitespace) & 0xFFFFFFFF;
                    auto prev_whitespace = (is_whitespace << 1) | prev_space;
                    auto word_starts = non_whitespace & prev_whitespace;

                    count[i].words += std::popcount((uint)word_starts);
                    prev_space = (is_whitespace >> 31) & 1;
                }

                while(ptr < end) {
                    unsigned char c = *ptr++;
                    count[i].lines += newline_lut[c];
                    count[i].words += prev_space & is_word[c];
                    prev_space = is_delim[c];
                }
        });
    }

    for(auto i = 0; i < THREAD_NUM; ++i){
        threads[i].join();
        result.words += count[i].words;
        result.lines += count[i].lines;
    }
    for(auto i = 1; i < THREAD_NUM; ++i) {
        result.words -= ends[i - 1] & starts[i]; 
    }

    munmap(buffer, size);
    close(fd);
    return result;
}
