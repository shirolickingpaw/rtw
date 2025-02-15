#include "color.hpp"
#include <fmt/core.h>

void write_color(const arma::vec3& pixel_color) {
    int rbyte = int(255.999 * pixel_color[0]);
    int gbyte = int(255.999 * pixel_color[1]);
    int bbyte = int(255.999 * pixel_color[2]);

    fmt::print("{} {} {}\n", rbyte, gbyte, bbyte);
}
