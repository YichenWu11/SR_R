#include <iostream>

#include <tbb/parallel_for.h>

#include <glm/common.hpp>

#include <rapidjson/rapidjson.h>

#include <core/test.h>

int main() {
    tbb::parallel_for(size_t(0), size_t(5), [&](size_t n) {
        printf("%zu\n", n);
    });

    std::cout << "Hello SR_R" << std::endl;

    return 0;
}
