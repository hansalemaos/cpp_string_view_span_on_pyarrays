#include <string_view>
#include <iostream>
#include <span>
#ifdef _WIN32
#define DLL_EXPORT __declspec(dllexport)
#else
#define DLL_EXPORT
#endif
// zig c++ -shared -std=c++2a -O3 -g0 dlltest.cpp -o mytest.dll

/*
How to use it in Python
testlib = CDLL(r"C:\ProgramData\anaconda3\envs\strarraytest\mytest.dll")
add_vecs_int = testlib.add_vecs_int
add_vecs_int.argtypes = [
    c_size_t,
    c_size_t,
    c_size_t,
    c_size_t,
]
add_vecs_int.restype = None
*/
extern "C" DLL_EXPORT void add_vecs_int(size_t array1, size_t size_array1, size_t string2search, size_t size_string2search) {
    std::span<char> span_string2search{ (char*)string2search, size_string2search };
    std::string_view sv_string2search{ span_string2search.begin(), span_string2search.end() };
    size_t str_address_counter = 0;
    size_t str_size_counter = 1;
    uint64_t* ptr1{ (uint64_t*)array1 };
    for (size_t i{}; i < size_array1; i++) {
        if ((i % 2) == 0) {
            std::span<char> pystring{ (char*)ptr1[i], ptr1[i + 1] };
            std::string_view sv{ pystring.begin(), pystring.end() };
            size_t result = sv.find(sv_string2search);
            if (result != std::string_view::npos) {
                std::cout << sv_string2search << " found at position " << result << " in string " << sv << '\n';
                }
            }
        }
    }