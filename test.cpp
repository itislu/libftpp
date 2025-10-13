#include "libftpp/string.hpp"
#include <iostream>
#include <string>
#include <vector>
#include <cstring> // For std::strlen
#include <ctime>   // For clock()

// v1: Uses the compare overload that implicitly finds the prefix length
template <typename CharT, typename Traits, typename Allocator>
bool starts_with_v1(const std::basic_string<CharT, Traits, Allocator>& str, const char* prefix)
{
    size_t prefix_len = std::strlen(prefix);
    if (prefix_len > str.length()) {
        return false;
    }
    // This overload will internally re-calculate the length of the C-style string 'prefix'
    return str.compare(0, prefix_len, prefix) == 0;
    return Traits::compare(str.data(), prefix, prefix_len) == 0;
}

// v2: Uses the compare overload that takes the prefix length explicitly
bool starts_with_v2(const std::string& str, const char* prefix)
{
    // size_t prefix_len = std::string::traits_type::length(prefix);
    size_t prefix_len = std::strlen(prefix);
    if (prefix_len > str.length()) {
        return false;
    }
    // This overload uses the length we already calculated, avoiding a redundant strlen
    return str.compare(0, prefix_len, prefix, prefix_len) == 0;
}

int main()
{
    // Make prefix huge to emphasize the cost of strlen.
    const size_t PREFIX_SIZE = 10 * 1000 * 1000; // 10 million chars
    const size_t EXTRA_SIZE = 100;
    // High iteration count to get a measurable duration.
    const int ITERATIONS = 100;

    std::cout << "Setting up " << PREFIX_SIZE / 1000000 << " million character strings..." << std::endl;

    // Use a vector to build the C-style string to avoid string reallocation overhead
    // and ensure it's on the heap, not the stack.
    std::vector<char> prefix_vec(PREFIX_SIZE + 1, 'a');
    prefix_vec[PREFIX_SIZE] = '\0'; // Null-terminate it
    
    // The main text is the prefix plus a little extra
    std::string text(&prefix_vec[0]);
    text.append(EXTRA_SIZE, 'b');

    const char* prefix_cstr = &prefix_vec[0];

    std::cout << "Setup complete. Starting benchmark..." << std::endl;
    std::cout << "----------------------------------------" << std::endl;

    // --- Benchmark v1 (Implicit length) ---
    std::cout << "Testing v1 (implicit length)..." << std::endl;
    clock_t start_v1 = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        starts_with_v2(text, prefix_cstr);
    }
    clock_t end_v1 = clock();
    double elapsed_v1 = double(end_v1 - start_v1) / CLOCKS_PER_SEC;
    std::cout << "v1 took: " << elapsed_v1 << " seconds." << std::endl;
    std::cout << std::endl;


    // --- Benchmark v2 (Explicit length) ---
    std::cout << "Testing v2 (explicit length)..." << std::endl;
    clock_t start_v2 = clock();
    for (int i = 0; i < ITERATIONS; ++i) {
        ft::starts_with(text, prefix_cstr);
    }
    clock_t end_v2 = clock();
    double elapsed_v2 = double(end_v2 - start_v2) / CLOCKS_PER_SEC;
    std::cout << "v2 took: " << elapsed_v2 << " seconds." << std::endl;
    std::cout << "----------------------------------------" << std::endl;
    
    // --- Conclusion ---
    if (elapsed_v1 > elapsed_v2) {
        std::cout << "Result: v2 was significantly faster as predicted." << std::endl;
    }

    return 0;
}
