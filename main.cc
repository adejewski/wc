#include <print>

#include "wc.hh"

#define ERR_NOT_ENOUGH_ARGUMENTS 1
#ifdef NUM
#define FUNCTION_NAME FUNCTION<NUM>
#else
#define FUNCTION_NAME FUNCTION
#endif

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::print("Usage: wc <file_name>");
        return -ERR_NOT_ENOUGH_ARGUMENTS;
    }
    std::string file_name = argv[1];
    auto count = FUNCTION_NAME(file_name);
    std::print("{2} {1} {0} {3}\n", count.bytes, count.words, count.lines, file_name);
    return 0;
}
