#include <fmt/core.h>
#include <ranges>
#include <random>

#include "ray.hpp"
#include "helper.hpp"
#include "camera.hpp"
#include "material.hpp"

arma::vec3 camera::ray_color(const ray& r, int depth, const hittable& world) const {
    if (depth <= 0)
        return arma::vec3({0,0,0});
    hit_record rec;

    // the following code highly depend on the diffusion model you choose
    if (world.hit(r, interval(0.001, arma::datum::inf), rec)) {
        ray scattered;
        arma::vec3 attenuation;
        if (rec.mat->scatter(r, rec, attenuation, scattered))
            // % for element wise multiplication and get a third vec
            return attenuation%ray_color(scattered, depth-1, world);
        return arma::vec3({0,0,0});
    }


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
            arma::vec3 pixel_color = {0,0,0};
            for (int k : std::views::iota(0, samples_per_pixel)) {
                ray r = get_ray(i, j);
                pixel_color += ray_color(r, max_depth, world);
            }
            write_color(pixel_samples_scale * pixel_color);
        }
    }

    fmt::print(stderr, "\nDone\n");
}

void camera::initialize() {
    image_height = int(image_width/aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height; // at least 1

    pixel_samples_scale = 1.0 / samples_per_pixel;

    center = lookfrom;
    
    // viewport dimensions
    auto theta = vfov*arma::datum::pi/180.0;
    auto h = std::tan(theta/2);
    auto viewport_height = 2*h*focus_dist;
    auto viewport_width = viewport_height * (double(image_width)/image_height);

    w = arma::normalise(lookfrom-lookat);
    u = arma::normalise(cross(vup, w));
    v = cross(w,u);

    // vectors across the horizontal and down the vertical viewport edges
    arma::vec3 viewport_u = viewport_width*u;
    arma::vec3 viewport_v = viewport_height*-v;
    
    // alculate the horizontal and vertical delta vectors from pixel to pixel.
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // location of upper left pixel
    auto viewport_upper_left = center 
        - (focus_dist*w) 
        - viewport_u/2 -viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    auto defocus_radius = focus_dist*std::tan(degrees_to_radian(defocus_angle/2));
    defocus_disk_u = u*defocus_radius;
    defocus_disk_v = v*defocus_radius;
}

ray camera::get_ray(int i, int j) const {
    auto offset = sample_square();
    auto pixel_sample = pixel00_loc
        + ((i + offset[0]) * pixel_delta_u)
        + ((j + offset[1]) * pixel_delta_v);

    auto ray_origin = (defocus_angle<=0) ? center: defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
}

arma::vec3 camera::sample_square() const {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_real_distribution<double> dist(0.0,1.0);
    double random = dist(gen);
    
    return arma::vec3({random-0.5, random-0.5,0});
}

arma::vec3 camera::defocus_disk_sample() const {
    auto p = random_in_unit_disk();
    return center + (p[0]*defocus_disk_u) + (p[1]*defocus_disk_v);
}

