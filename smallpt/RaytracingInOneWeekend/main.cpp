#include <iostream>
#include <fstream>
// #include "vec3.h"
#include "ray.h" // including vec3
using namespace std;

/*
Sphere: dot((p-c),(p-c))=R*R --> any point p that satisfies this equation is on the sphere. Ray: p(t) = A + t*B
dot((p(t)-c),(p(t)-c))=R*R
dot(A + t*B - c),(A + t*B - c))=R*R
t*t*dot(B,B) + 2*t*dot(B,A-C) + dot(A-C,A-C) - R*R = 0
a = dot(B,B)
b = 2*dot(B,A-C)
c = dot(A-C,A-C) - R*R
*/
bool hit_sphere(const vec3& center, float radius, const ray& r){
    vec3 oc = r.origin() - center; // A-C
    float a = dot(r.direction(), r.direction());
    float b = 2.0 * dot(r.direction(), oc);
    float c = dot(oc,oc) - radius*radius;
    float discriminant = b*b - 4*a*c;
    return (discriminant>0);
}

// the core of a raytracer is to send rays through pixels and compute what color is seen in the direction od those rays. This is of the form calculate which ray goes from the eye to a pixel, compute what that ray intersects, and compute a color for that intersection point.
vec3 color(const ray& r){
    if(hit_sphere(vec3(0,0,1), 0.5, r))
        return vec3(1,0,0);
    vec3 unit_direction = unit_vector(r.direction());
    float t = 0.5*(unit_direction.y()+1.0); // -1~1 --> 0~1
    return (1.0-t)*vec3(1.0,1.0,1.0)+t*vec3(0.5,0.7,1.0); // lerp
    // blended_value = (1-t)*start_value + t*end_value
}

int main(){
    int nx = 200;
    int ny = 100;

    // 将结果输出到文件
    ofstream outfile("test.ppm", ios_base::out);
    outfile << "P3\n" << nx << " " << ny << "\n255\n";
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";

    /*
    Followed the right-handed coordinate system, z is pointing out of screen. So pointing into the screen is the negative z-axis.
    Tranverse the screen from lower_left_corner and use 2 offset vectors along the screen sides to move the ray endpoint across the screen
    */
    vec3 lower_left_corner(-2.0,-1.0,-1.0);
    vec3 horizontal(4.0,0.0,0.0);
    vec3 vertical(0.0,2.0,0.0);
    vec3 origin(0.0,0.0,0.0);

    for(int j=ny-1; j>=0; j--){
        for(int i=0; i<nx; i++){
            // float r = float(i)/float(nx);
            // float g = float(j)/float(ny);
            // float b = 0.2;
            float u = float(i)/float(nx); // 0~1
            float v = float(j)/float(ny);
            ray r(origin, lower_left_corner + u*horizontal + v* vertical);
            // vec3 col(float(i)/float(nx), float(j)/float(ny), 0.2);
            // 根据光线对每一个像素点上色
            vec3 col = color(r);
            int ir = int(255.99*col[0]);
            int ig = int(255.99*col[1]);
            int ib = int(255.99*col[2]);

            outfile   << ir << " " << ig << " " << ib << "\n";
            //std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    cout << "Image output succeeded! :)" << "\n";
}
