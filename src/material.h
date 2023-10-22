#pragma once

#include "rtweekend.h"
#include "hittable.h"
#include "color.h"
#include "vec3.h"
#include <cmath>

class hit_record;

class material {
public:
  virtual ~material() = default;

  virtual auto scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool = 0;
};

////////////////////////////////////////////////////////////////////////////////
/// Lambertian
class lambertian : public material {
public:
  lambertian(const color& a) : albedo(a) {}

  auto scatter([[maybe_unused]] const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool override {
    auto scatter_direction = rec.normal + random_unit_vector<double>();

    // Catch degenerate scatter direction
    if (scatter_direction.near_zero()) {
      scatter_direction = rec.normal;
    }

    scattered = ray(rec.p, scatter_direction);
    attenuation = albedo;
    return true;
  }
private:
  color albedo;
};

////////////////////////////////////////////////////////////////////////////////
/// Metal
class metal : public material {
public:
  metal(const color& a, double f) : albedo(a), fuzz(f < 1 ? f : 1) {}

  auto scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool override {
    vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
    scattered = ray(rec.p, reflected + fuzz * random_unit_vector<double>());
    attenuation = albedo;
    return (dot(scattered.direction(), rec.normal) > 0);
  }

private:
  color albedo;
  double fuzz;
};

////////////////////////////////////////////////////////////////////////////////
/// Dielectric
class dielectric : public material {
public:
  dielectric(double index_of_refraction) : ir(index_of_refraction) {}

  auto scatter(const ray& r_in, const hit_record& rec, color& attenuation, ray& scattered) const -> bool override {
    attenuation = color(1.0, 1.0, 1.0);
    double refraction_ratio = rec.front_face ? (1.0/ir) : ir;

    vec3<double> unit_direction = unit_vector(r_in.direction());
    double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
    double sin_theta = sqrt(1.0 - cos_theta*cos_theta);

    bool cannot_refract = refraction_ratio * sin_theta > 1.0;
    vec3<double> direction;

    if (cannot_refract || reflectance(cos_theta, refraction_ratio) > rt::random_double()) {
      direction = reflect(unit_direction, rec.normal);
    } else {
      direction = refract(unit_direction, rec.normal, refraction_ratio);
    }

    scattered = ray(rec.p, direction);
    return true;
  }

private:
  double ir; // index of refraction
  
  static auto reflectance(double cosine, double ref_idx) -> double {
    auto r0 = (1-ref_idx) / (1+ref_idx);
    r0 = r0*r0;
    return r0 + (1-r0) * std::pow((1-cosine), 5);
  }
};
