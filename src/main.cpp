#include <armadillo>
#include <memory>
#include <vector>
#include <ranges>

#include "material.hpp"
#include "helper.hpp"
#include "color.hpp"
#include "ray.hpp"
#include "camera.hpp"
#include "hittable.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"

using std::make_shared;
using std::shared_ptr;

int main() {

    // world settings
    hittable_list world;
 
    auto ground_material = make_shared<lambertian>(arma::vec3({0.5,0.5,0.5})); // color
    world.add(make_shared<sphere>(arma::vec3({0,1000,0}), 1000, ground_material));

    for (int a : std::views::iota(-11, 11)) {
        for (int b : std::views::iota(-11,11)) {
            auto choose_mat = random_double();
            arma::vec3 center = {a+0.9*random_double(), 0.2, b+0.9*random_double()};

            if (arma::norm(center-arma::vec3({4,0.2,0}),2) > 9) {
                shared_ptr<material> sphere_material;

                if (choose_mat < 0.8) {
                    // diffuse
                    auto albedo = arma::vec3(arma::randu<arma::vec>(3))
                        %arma::vec3(arma::randu<arma::vec>(3));
                    sphere_material = make_shared<lambertian>(albedo);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else if (choose_mat < 0.95) {
                    // metal
                    auto albedo = 0.5 + 0.5*arma::vec3(arma::randu<arma::vec>(3));
                    auto fuzz = random_double(0,0.5);
                    sphere_material = make_shared<metal>(albedo, fuzz);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                } else {
                    // glass
                    sphere_material = make_shared<dielectric>(1.5);
                    world.add(make_shared<sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = make_shared<dielectric>(1.5);
    world.add(make_shared<sphere>(arma::vec3({0,1,0}), 1.0, material1));

    // vec3 is color
    auto material2 = make_shared<lambertian>(arma::vec3({0.4, 0.2, 0.1}));
    world.add(make_shared<sphere>(arma::vec3({-4, 1, 0}), 1.0, material2));

    // vec3 is color
    auto material3 = make_shared<metal>(arma::vec3({0.7, 0.6, 0.5}), 0.0);
    world.add(make_shared<sphere>(arma::vec3({4, 1, 0}), 1.0, material3));

    camera cam;
    cam.aspect_ratio = 16.0/9.0;
    cam.image_width = 1024;
    cam.samples_per_pixel = 500;
    cam.max_depth = 50;

    cam.vfov = 20;
    cam.lookfrom = arma::vec3({13,2,3});
    cam.lookat = arma::vec3({0,0,0});
    cam.vup = arma::vec3({0,1,0});

    cam.defocus_angle = 0.6;
    cam.focus_dist = 10.0;
    
    cam.render(world);
}

