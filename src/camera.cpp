#include <fmt/core.h>
#include <ranges>

#include "camera.hpp"

arma::vec3 camera::ray_color(const ray& r, const hittable& world) const {
    hit_record rec;
    if (world.hit(r, interval(0, arma::datum::inf), rec))
        return 0.5 * (rec.normal + arma::vec3({1,1,1}));

    arma::vec3 unit_direction = arma::normalise(r.direction());
    auto a = 0.5 * (unit_direction[1] + 1.0);
    return (1.0 - a) * arma::vec3({1.0,1.0,1.0}) + a*arma::vec3({0.5,0.7,1.0});
}

void camera::render(const hittable& world) {
    initialize();
    fmt::print("P3\n{} {}\n255\n", image_width, image_height);

    for (int j : std::views::iota(0, image_height)) {
        fmt::print(stderr, "Scanlines remaining: {}\n", image_height-j);

        for (int i : std::views::iota(0, image_width)) {

            auto pixel_center = pixel00_loc
                + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - center;
            ray r(center, ray_direction);

            arma::vec3 pixel_color = ray_color(r, world);
            write_color(pixel_color);
        }
    }

    fmt::print(stderr, "\nDone\n");
}

void camera::initialize() {
    image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; // at least 1

    center = arma::vec3({0,0,0});
    
    // viewport dimensions
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    // vectors across the horizontal and down the vertical viewport edges
    arma::vec3 viewport_u = {viewport_width, 0, 0};
    arma::vec3 viewport_v = {0, -viewport_height, 0};
    
    // alculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // location of upper left pixel
    auto viewport_upper_left = center 
        - arma::vec3({0,0,focal_length}) - viewport_u/2 -viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);
}
