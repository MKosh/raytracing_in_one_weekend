#include <iostream>
#include <string>
#include "vec3.h"

int main() {
  int image_width = 256;
  int image_height = 256;

  std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

  vec3<float> v1 = {1.1, 2.2, 3.3};
  std::cout << "v1 = " << v1 << '\n';
  vec3<double> v2 = {4.4, 5.5, 6.6};
  std::cout << "v2 = " << v2 << '\n';
  vec3 v3 = v1 + v2;
  std::cout << "v3 = " << v3 << '\n';
  vec3 v4 = v2 - v1;
  std::cout << "v4 = " << v4 << '\n';
  
  vec3 v5 = v1 + v1;
  std::cout << "v5 = " << v5 << '\n';
  
  vec3 v6 = v2 + v2;
  std::cout << "v6 = " << v6 << '\n';
  
  vec3<int> v7 = {7, 8, 9};
  vec3<float> v8 = v7;
  std::cout << "v8 = " << v8 << '\n';

  auto v9 = v7 + v8;
  std::cout << "v9 = " << v9 << '\n';

  vec3<double> v10 = v7 + v6;
  std::cout << "v10 = " << static_cast<vec3<int>>(v10) << '\n';

  std::cout << "v10 but float = " << static_cast<vec3<float>>(v10) << '\n';

  for (int j = 0; j < image_height; ++j) {
    std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;
    for (int i = 0; i < image_width; ++i) {
      auto r = double(i) / (image_width-1);
      auto g = double(j) / (image_height-1);
      auto b = 0;

      int ir = static_cast<int>(255.999 * r);
      int ig = static_cast<int>(255.999 * g);
      int ib = static_cast<int>(255.999 * b);

      // std::cout << ir << ' ' << ig << ' ' << ib << '\n';
    }
  }
  std::clog << "\rDone.                               \n";
}
