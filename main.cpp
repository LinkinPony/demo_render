
#include <iostream>
#include <memory.h>
#include <deque>
#include "include/include_all.h"
using namespace std;
const TGAColor white = TGAColor(255, 255, 255, 100);
const TGAColor red   = TGAColor(255, 0,   0,   100);
const TGAColor green = TGAColor(0  , 128, 0,   100);
int main(int argc, char** argv) {
    int width = 2000,height = 2000;
    float * zbuffer = new float [width*height];
    cout << INT_MIN << endl;
    std::fill(zbuffer,zbuffer+width*height,-1e18);
    Drawer drawer = Drawer(width,height, TGAImage::RGB);
    for(int i = 0;i < width;i++){
        for(int j = 0;j < height;j++)drawer.set(i,j,red);
    }
    Model * model = new Model("african_head.obj");
    Vec3f light_dir = Vec3f (1,-1,1).normalize(); // define light_dir
    Matrix<float> M_model = Matrix<float>::I(4);
    M_model[0][0] = M_model[1][1] = M_model[2][2] = 1000;//multiply .obj's coordinate by 500
    M_model[0][3] = 1000,M_model[1][3] = 1000;
    M_model[2][3] = -1000;
    M_model[3][3] = 1;
    int near = -300,far = -10000;
    //camera
    Vec3f e(0,0,-1000);//position
    Vec3f c = Vec3f (0,0,0);//Look-at direction
    Vec3f t(0,1,0);//Up direction
    Matrix<float> M_view = ViewTrans(e,c,t);
    Matrix<float> M_perse = PerspTrans(0,width,0,height,far,near);
    Matrix<float> M_viewport = ViewportTrans(width,height);
    Matrix<float> M = M_viewport * M_view;
//    Matrix<float> M = M_viewport * M_perse * M_view * M_model;
//    cout << M_view << endl;
//    cout << M_perse << endl;
//    cout << M_viewport << endl;
//    cout << M;
    for (int i=0; i<model->nfaces(); i++) {
        std::vector<int> face = model->face(i);
        Vec3f screen_coords[3];
        Vec3f world_coords[3];
        float intensity[3];
        for (int j=0; j<3; j++) {
            Vec3f v = model->vert(face[j]);
//            cout << v << endl;
            screen_coords[j] = m2v(M * v2m(v));
//            cout << screen_coords[j] << endl << endl;
            intensity[j] = model->norm(i,j) * light_dir;
        }
        Vec3f ver[3] = {screen_coords[0], screen_coords[1], screen_coords[2]};
        drawer.Triangle(ver, TGAColor(intensity[0]*255, intensity[1]*255, intensity[2]*255, 255),zbuffer);
    }
    drawer.flip_vertically(); // i want to have the origin at the left bottom corner of the image
    drawer.write_tga_file("output.tga");
    return 0;
}
