#include <fmt/core.h>

#include "color.hpp"
#include "interval.hpp"

void write_color(const arma::vec3& pixel_color) {
    auto r = pixel_color[0];
    auto g = pixel_color[1];
    auto b = pixel_color[2];

    static const interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.clamp(r));
    int gbyte = int(256 * intensity.clamp(g));
    int bbyte = int(256 * intensity.clamp(b));

    fmt::print("{} {} {}\n", rbyte, gbyte, bbyte);
}
