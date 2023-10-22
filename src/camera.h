#pragma once

#include "rtweekend.h"
#include "hittable.h"
#include "color.h"
#include "vec3.h"
#include "material.h"

#include <iostream>
#include <math.h>

class camera {
public:
  double aspect_ratio      = 1.0; // Ratio of image width over height
  int    image_width       = 100; // Rendered image width in pixel count
  int    samples_per_pixel = 10;  // Count of random samples for each pixel
  int    max_depth         = 10;  // Maximum number of raybounces into scene
  
  double vfov = 90;          // Vertical view angle (fov) in degrees
  point3 lookfrom{0, 0, -1}; // Point camera is looking from
  point3 lookat{0, 0, 0};    // Ponit camera is looking at
  vec3<double> vup{0, 1, 0}; // Camera-relative "up" direction
  
  double defocus_angle = 0;  // Variation angle of rays through each pixel
  double focus_dist = 10;    // Distance from camera lookform point to plane of perfect focus

  auto render(const hittable& world) -> void {
    initialize();

    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; ++j) {
      std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
      for (int i = 0; i < image_width; ++i) {
        color pixel_color(0,0,0);
        for (int sample = 0; sample < samples_per_pixel; ++sample) {
          ray r = get_ray(i, j);
          pixel_color += ray_color(r, max_depth, world);
        }
        write_color(std::cout, pixel_color, samples_per_pixel);
      }
    }

    std::clog << "\rDone.                 \n";
  }

private:
  int image_height;            // Rendered image height
  point3 center;               // Camera center
  point3 pixel00_loc;          // Location of pixel 0, 0
  vec3<double> pixel_delta_u;  // Offset to pixel to the right
  vec3<double> pixel_delta_v;  // Offset to pixel below
  vec3<double> u, v, w;        // Camera frame basis vectors
  vec3<double> defocus_disk_u; // Defocus disk horizontal radius
  vec3<double> defocus_disk_v; // Defocus disk vertical radius
  
  auto initialize() -> void {
    image_height = static_cast<int>(image_width / aspect_ratio);
    image_height = (image_height < 1) ? 1 : image_height;

    center = lookfrom;

    // Determine viewport dimensions
    /* auto focal_length = (lookfrom - lookat).length(); */
    auto theta = rt::degrees_to_radians(vfov);
    auto h = tan(theta/2);
    auto viewport_height = 2.0 * h * focus_dist;
    auto viewport_width = viewport_height * (static_cast<double>(image_width)/image_height);

    // Calculate the u, v, w, unit basis vectors for the camera coordinate frame.
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    // Calculate the vectors across the horizontal and down the vertical viewport edges.
    vec3<double> viewport_u = viewport_width * u;
    auto viewport_v = viewport_height * -v;

    // Calculate the horizonal and vertical delta vectors from pixel to pixel
    pixel_delta_u = viewport_u / image_width;
    pixel_delta_v = viewport_v / image_height;

    // Calculate the location of the upper left pixel 
    auto viewport_upper_left = center - (focus_dist * w) - viewport_u/2 - viewport_v/2;
    pixel00_loc = viewport_upper_left + 0.5 * (pixel_delta_u + pixel_delta_v);

    // Calculate the camera defocus disk basis vectors
    auto defocus_radius = focus_dist * tan(rt::degrees_to_radians(defocus_angle/2));
    defocus_disk_u = u * defocus_radius;
    defocus_disk_v = v * defocus_radius;
  }

  auto ray_color(const ray& r, int depth, const hittable& world) const -> color {
    hit_record rec;

    if (depth <= 0)
      return color(0,0,0);

    if (world.hit(r, interval(0.001, rt::infinity), rec)) {
      ray scattered;
      color attenuation;
      if (rec.mat->scatter(r, rec, attenuation, scattered)) {
        return attenuation * ray_color(scattered, depth-1, world);
      }
      return color(0,0,0);
    }

    vec3<double> unit_direction = unit_vector(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - a) * color(1.0,1.0,1.0) + a * color(0.5, 0.7, 1.0);
  }

  auto get_ray(int i, int j) const -> ray {
    // Get a randomly sampled camera ray for the pixel at location i,j originating from the camera defocus disk
    auto pixel_center = pixel00_loc + (i * pixel_delta_u) + (j * pixel_delta_v);
    auto pixel_sample = pixel_center + pixel_sample_square();

    auto ray_origin = (defocus_angle <= 0) ? center : defocus_disk_sample();
    auto ray_direction = pixel_sample - ray_origin;

    return ray(ray_origin, ray_direction);
  }

  auto pixel_sample_square() const -> vec3<double> {
    // Returns a random point in the square surrounding a pixel at the origin.
    auto px = -0.5 + rt::random_double();
    auto py = -0.5 + rt::random_double();
    return (px * pixel_delta_u) + (py * pixel_delta_v);
  }

  auto defocus_disk_sample() const -> point3 {
    // Returns a random point in the camera defocus disk
    auto p = random_in_unit_disk();
    return center + (p[0] * defocus_disk_u) + (p[1] * defocus_disk_v);
  }
};

