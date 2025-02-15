#include <armadillo>
#include <fmt/core.h>
#include <ranges>
#include <memory>
#include <vector>

#include "color.hpp"
#include "ray.hpp"
#include "helper.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

using std::make_shared;
using std::shared_ptr;

int main() {

    // image settings
    auto aspect_ratio = 16.0/9.0;
    int image_width = 1086;

    int image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; // at least 1

    // world settings
    hittable_list world;
    world.add(make_shared<sphere>(arma::vec3({0,0,-1}), 0.5));
    world.add(make_shared<sphere>(arma::vec3({0,-100.5,-1}), 100));

    // camera settings
    auto focal_length = 1.0;
    auto viewport_height = 2.0;
    auto viewport_width = viewport_height * (double(image_width)/image_height);
    arma::vec3 camera_center = {0,0,0};

    // vectors across the horizontal and down the vertical viewport edges
    arma::vec3 viewport_u = {viewport_width, 0, 0};
    arma::vec3 viewport_v = {0, -viewport_height, 0};

    // alculate the horizontal and vertical delta vectors from pixel to pixel.
    arma::vec3 pixel_delta_u = viewport_u / image_width;
    arma::vec3 pixel_delta_v = viewport_v / image_height;

    // location of upper left pixel
    arma::vec3 viewport_upper_left = camera_center 
        - arma::vec3({0,0,focal_length}) - viewport_u/2 -viewport_v/2;
    arma::vec3 pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);


    // render
    fmt::print("P3\n{} {}\n255\n", image_width, image_height);

    for (int j : std::views::iota(0, image_height)) {
        fmt::print(stderr, "Scanlines remaining: {}\n", image_height-j);
        // fflush(stderr);

        for (int i : std::views::iota(0, image_width)) {

            auto pixel_center = pixel00_loc
                + (i * pixel_delta_u) + (j * pixel_delta_v);
            auto ray_direction = pixel_center - camera_center;
            ray r(camera_center, ray_direction);

            arma::vec3 pixel_color = ray_color(r, world);
            write_color(pixel_color);
        }
    }

    fmt::print(stderr, "\nDone\n");
    // fflush(stderr);
}

