#include <iostream>
#include <fstream>
#include "vec3.h"

using namespace std;

int main(){
    int nx = 200;
    int ny = 200;

    // 将结果输出到文件
    ofstream outfile("test.ppm", ios_base::out);
    outfile << "P3\n" << nx << " " << ny << "\n255\n";
    //std::cout << "P3\n" << nx << " " << ny << "\n255\n";
    
    for(int j=ny-1; j>=0; j--){
        for(int i=0; i<nx; i++){
            // float r = float(i)/float(nx);
            // float g = float(j)/float(ny);
            // float b = 0.2;
            vec3 color(float(i)/float(nx), float(j)/float(ny), 0.2);
            int ir = int(255.99*color[0]);
            int ig = int(255.99*color[1]);
            int ib = int(255.99*color[2]);

            outfile   << ir << " " << ig << " " << ib << "\n";
            //std::cout << ir << " " << ig << " " << ib << "\n";
        }
    }
    cout << "Image output succeeded! :)" << "\n";
}
